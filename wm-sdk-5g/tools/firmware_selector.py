#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# firmware_selector.py - A tool to select the right Wirepas firmware depending on app/board config
#


import sys
import os
import struct
import argparse
import textwrap
from os import listdir
from os.path import isfile, join, exists
from shutil import copyfile

import hextool

# Python 2 and Python 3 support
try:
    # Python 3
    import configparser

    config_parser_tweaks = {
        "comment_prefixes": ("#", ";"),
        "inline_comment_prefixes": (";",),
    }
except ImportError:
    # Python 2
    import ConfigParser as configparser

    config_parser_tweaks = {}


class FirmwareConfig(object):
    """Firmware configuration

    An object to store a firmware configuration

    general         Dictionary containing the general config
    meme_layout     Dictionary containing the memory layout
    libraries       Dictionary containing the list of libraries

    """

    def __init__(self, general, mem_layout=None, libraries=None):
        self.general = general
        self.mem_layout = mem_layout
        self.libraries = libraries

    @classmethod
    def from_file(cls, file):
        cp = configparser.RawConfigParser(
            **config_parser_tweaks
        )  # Most basic parser only
        cp.read(file)

        try:
            general_conf = dict(cp.items("general"))
        except Exception:
            return None

        try:
            mem_layout = dict(cp.items("memory"))
        except Exception:
            mem_layout = None

        try:
            libs = dict(cp.items("libraries"))
        except Exception:
            libs = None

        return cls(general=general_conf, mem_layout=mem_layout, libraries=libs)

    def __str__(self):
        return "Firmware config is: {}".format(self.__dict__)

    def is_version_greater_or_equal(self, min_version):
        # Both versions should have same format
        # List of digit separated by points
        min_ver_digits = min_version.split(".")
        cur_ver_digits = self.general["version"].split(".")

        if min_ver_digits.__len__() != cur_ver_digits.__len__():
            return False

        i = 0
        while i < min_ver_digits.__len__():
            if int(min_ver_digits[i]) > int(cur_ver_digits[i]):
                print(
                    "Version for this binary is too old: {} < {}".format(
                        self.general["version"], min_version
                    )
                )
                return False
            i += 1

        return True

    def is_compatible(self, target_config):
        # Function to check if config is compatible with provided config
        for key in target_config:
            # In case keys are string, just compare them in case insensitive
            try:
                if key == "version":
                    # Version is the minimal version to test
                    if not self.is_version_greater_or_equal(target_config[key]):
                        return False
                elif key == "mcu_sub":
                    possible_values = [target_config["mcu_sub"].lower()]
                    if "mcu_mem_var" in target_config:
                        possible_values.append(
                            target_config["mcu_sub"].lower()
                            + target_config["mcu_mem_var"].lower()
                        )

                    if self.general["mcu_sub"].lower() not in possible_values:
                        return False
                elif key == "mcu_mem_var":
                    # Handle in previous case
                    continue
                elif key == "modem_fw":
                    continue
                else:
                    # print("{} vs {}".format(self.general[key], target_config[key]))
                    # Other keys must match
                    if self.general[key].lower() != target_config[key].lower():
                        return False
            except KeyError:
                if key == "mcu_sub":
                    # if sub_mcu is not defined it is that the mcu is same for all
                    continue
                # Key doesn't exist
                return False

        # This Firmware has all the requirements
        return True

    def get_unspecified_keys(self, target_config):
        # Function to get all the keys that are not in specified target_config
        unspecified_keys = {}
        for key in self.general:
            if not key in target_config:
                unspecified_keys[key] = self.general[key]

        return unspecified_keys

    def has_lib(self, lib_name, lib_version=None):
        try:
            if self.libraries is None:
                return False
            version = self.libraries[lib_name]
            if lib_version is not None and int(version) >= int(lib_version):
                return False
        except KeyError:
            # Lib is not present
            return False

        return True


def create_stack_binary(filename, stack_area_addr):
    """Create a stack binary file and add padding if necessary"""

    memory = hextool.Memory(gap_fill_byte=0xFF)
    hextool.load_intel_hex(memory, filename=filename)

    # Get stack start address
    stack_min_addr = memory.min_address

    # Determine the need for padding
    padding_needed = stack_min_addr - stack_area_addr

    if padding_needed == 0:
        # Stack already at the correct address, do nothing
        pass
    elif padding_needed < 0:
        # Stack binary starts at an address that
        # is below the stack area start address
        raise ValueError("{}: start address is too low".format(filename))
    elif padding_needed > 0:
        # Stack binary starts at an address that is larger than
        # the stack area start address, padding required

        # Jump trampoline
        trampoline = bytearray(
            [
                # fmt: off
                0x03, 0xB4,     # push  {r0, r1}
                0x01, 0x48,     # ldr   r0, [pc, #4]    ; (8 <entrypoint+0x8>)
                0x01, 0x90,     # str   r0, [sp, #4]
                0x01, 0xBD,     # pop   {r0, pc}

                0x00, 0x00, 0x00, 0x00, # Jump address

                0x00, 0x00, 0x00, 0x00, # Align to 16 bytes

                0xFF, 0xFF, 0xFF, 0xFF, # Bootloader info header, 20 bytes
                0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF,

                0xFF, 0xFF, 0xFF, 0xFF, # 12 bytes for future use, align to 16 bytes
                0xFF, 0xFF, 0xFF, 0xFF,
                0xFF, 0xFF, 0xFF, 0xFF,
                # fmt: on
            ]
        )

        if padding_needed < len(trampoline):
            # Not enough space for the jump trampoline and bootloader info header
            raise ValueError("{}: not enough space to add padding".format(filename))

        # Store an address for the jump trampoline to jump to
        # LSB must be 1 as we are jumping to Thumb code
        trampoline[8:12] = struct.pack("<L", stack_min_addr | 0x1)

        # Add jump trampoline to stack binary, with implicit 0xff padding
        memory.cursor = stack_area_addr
        memory += trampoline

    return memory


def dir_path(string):
    if os.path.isdir(string):
        return string
    else:
        raise NotADirectoryError("{} is not a valid directory".format(string))


def firmware_type(string):
    if string == "wp_bootloader" or string == "wp_stack":
        return string
    else:
        raise ValueError("{} is not a valid firmware type".format(string))


def str2bool(string):
    if string.lower() in ("yes", "true", "t", "y", "1"):
        return True
    elif string.lower() in ("no", "false", "f", "n", "0", ""):
        # '' means False
        return False
    else:
        raise argparse.ArgumentTypeError("Boolean value expected.")


stars_line = """*******************************************************************************"""

warning_unprotected_bootloader_msg = """* WARNING:
*     The generated image is UNPROTECTED and must not be used
*     in the field"""

error_no_firmware_found = """* ERROR:
*     No firmware found fulfilling your requirements.
*     Please contact the Wirepas support team with the following message
*     to fix the issue:"""

error_multiple_firmwares_found = """* ERROR:
*     Multiple firmware found fulfilling your requirements.
*     In order to avoid ambiguity, please add requirements to your app config.mk
*     Here is the list of potential differentiators:"""


def print_red(skk):
    print("\033[91m {}\033[00m".format(skk))


def print_unprotected_bootloader():
    print_red(stars_line)
    print_red(warning_unprotected_bootloader_msg)
    print_red(stars_line)


def print_no_firmware_found(target_config):
    print_red(stars_line)
    print_red(error_no_firmware_found)
    print_red("*        {}".format(target_config))
    print_red(stars_line)


def print_multiple_firmware_found(target_config, firmwares):
    print_red(stars_line)
    print_red(error_multiple_firmwares_found)
    for fw in firmwares:
        # Print all keys that are not in target_config
        print_red(
            "*        {}: {}".format(fw[0], fw[1].get_unspecified_keys(target_config))
        )
    print_red(stars_line)


def create_argument_parser(pgmname):
    """Create a parser for parsing the command line"""

    # Determine help text width
    try:
        help_width = int(os.environ["COLUMNS"])
    except (KeyError, ValueError):
        help_width = 80
    help_width -= 2

    parser = argparse.ArgumentParser(
        prog=pgmname,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description=textwrap.fill(
            "A tool to select correct Wirepas firmware binary", help_width
        ),
    )

    parser.add_argument(
        "--firmware_path",
        "-i",
        help="Colon separated list of folders where the different Wirepas firmware are stored",
        default="./image",
    )
    parser.add_argument(
        "--output_name", help="Name for the firmware binaries", type=str
    )
    parser.add_argument(
        "--output_path", help="Path to copy the firmware binaries", type=dir_path
    )

    parser.add_argument(
        "--firmware_type",
        "-ft",
        type=firmware_type,
        help="Type of firmware to get (wp_bootloader or wp_stack)",
        required=True,
    )
    parser.add_argument("--version", "-v", help="Target minimum version", default=None)
    parser.add_argument("--mcu", "-m", help="Target mcu", required=True)
    parser.add_argument("--mcu_sub", "-ms", help="Target sub_mcu")
    parser.add_argument("--mcu_mem_var", "-mmv", help="Target mcu memory variant")
    parser.add_argument(
        "--radio", "-r", help="Target radio (if relevant)", default=None
    )
    parser.add_argument(
        "--radio_config", "-rc", help="Target radio_config (if relevant)", default=None
    )
    parser.add_argument(
        "--channel_map", "-b", help="Target band (if relevant)", default=None
    )
    parser.add_argument(
        "--mac_profile", "-p", help="Target profile (if relevant)", default=None
    )
    parser.add_argument(
        "--mac_profileid", "-pid", help="Target profile id (if relevant)", default=None
    )
    parser.add_argument(
        "--unlocked",
        "-u",
        help="Unlocked version (only valid if type is wp_bootloader)",
        type=str2bool,
        default=False,
    )
    parser.add_argument(
        "--mode", "-mo", help="Special mode for the binary", default=None
    )
    parser.add_argument(
        "--modem_fw", "-mfw", help="Modem firmware image file name", default=None
    )
    parser.add_argument(
        "--key_type",
        "-kt",
        help="Supported key types in bootloader "
        "(only valid if type is wp_bootloader)",
        default=None,
    )
    parser.add_argument(
        "--stack_area_addr",
        "-sa",
        help="Start address of the stack area, for stack binary padding "
        "(only valid if type is wp_stack)",
        type=lambda x: int(x, 0),
        default=0,
    )

    return parser


def main():
    """Main program"""

    # Determine program name, for error messages.
    pgmname = os.path.split(sys.argv[0])[-1]

    try:
        # Parse command line arguments
        args = create_argument_parser(pgmname).parse_args()

        # Do some sanity check on parameters and impossible combinations
        if args.unlocked and args.firmware_type == "wp_stack":
            raise ValueError("wp_stack cannot be unlocked only apply to wp_bootloader")

        # Select right deliverable format
        if args.firmware_type == "wp_stack":
            firmware_suffix = ".hex"
        else:
            firmware_suffix = ".a"

        # Create a dictionary based on parameters
        target_config = {}

        # Mandatory fields
        target_config["type"] = args.firmware_type
        target_config["mcu"] = args.mcu

        # Mandatory fields for "wp_bootloader"
        if args.firmware_type == "wp_bootloader":
            if args.key_type == "OMAC1_AES128CTR":
                auth_type = "cmac"
            elif args.key_type == "ES256_AES128CTR":
                auth_type = "es256"
            else:
                raise RuntimeError(
                    "Invalid or missing key_type: {}".format(args.key_type)
                )
            target_config["auth_type"] = auth_type
        else:
            if args.key_type not in (None, ""):
                raise RuntimeError(
                    "Argument key_type is for " "--firmware_type=wp_bootloader only"
                )

        # Optional fields
        if args.mcu_sub not in (None, ""):
            target_config["mcu_sub"] = args.mcu_sub
        if args.mcu_mem_var not in (None, ""):
            target_config["mcu_mem_var"] = args.mcu_mem_var
        if args.version not in (None, ""):
            target_config["version"] = args.version
        if args.radio not in (None, ""):
            target_config["radio"] = args.radio
        if args.radio_config not in (None, ""):
            target_config["radio_config"] = args.radio_config
        if args.channel_map not in (None, ""):
            target_config["radio_channel_map"] = args.channel_map
        if args.mac_profile not in (None, ""):
            target_config["mac_profile"] = args.mac_profile
        if args.mac_profileid not in (None, ""):
            target_config["mac_profileid"] = args.mac_profileid
        if args.mode not in (None, ""):
            target_config["mode"] = args.mode
        if args.modem_fw not in (None, ""):
            target_config["modem_fw"] = args.modem_fw

        if args.firmware_type == "wp_bootloader":
            # Set it as a string instead of bool to ease the following check
            target_config["unlocked"] = str(args.unlocked)

        # Get all the binaries available
        conf_files = []
        for p in args.firmware_path.split(":"):
            conf_files += [
                join(p, f)
                for f in listdir(p)
                if isfile(join(p, f)) and f.endswith(".conf")
            ]

        # Check all available binaries with the target config
        possible_firmwares = []
        for conf in conf_files:
            config = FirmwareConfig.from_file(conf)

            if config is None:
                # File without right format
                print("{} has wrong format".format(conf))
                continue

            if not config.is_compatible(target_config):
                # Un-compatible with target config
                continue

            possible_firmwares.append((conf, config))

        # Check result of the check
        if len(possible_firmwares) == 1:
            conf_file = possible_firmwares[0][0]
            print(
                "Firmware for {} found with name: {}".format(
                    args.firmware_type, conf_file
                )
            )

            binary_file = os.path.splitext(conf_file)[0] + firmware_suffix
            if not os.path.isfile(binary_file):
                print(
                    "Cannot find the associated binary to conf file {}".format(
                        conf_file
                    )
                )
                raise ValueError

            if args.output_path is not None:
                # Copy conf file to output folder
                copyfile(
                    conf_file,
                    os.path.join(args.output_path, args.output_name + ".conf"),
                )

                if args.firmware_type == "wp_stack":
                    # Create a stack firmware binary with padding, as needed
                    memory = create_stack_binary(
                        binary_file,
                        args.stack_area_addr,
                    )

                    # Write stack firmware binary to output folder
                    hextool.save_intel_hex(
                        memory,
                        filename=os.path.join(
                            args.output_path, args.output_name + firmware_suffix
                        ),
                    )
                    del memory
                else:
                    # Copy firmware binary to output folder as is
                    copyfile(
                        binary_file,
                        os.path.join(
                            args.output_path, args.output_name + firmware_suffix
                        ),
                    )

                if (
                    args.modem_fw is not None
                    and len(args.modem_fw) != 0
                    and args.radio != "none"
                ):
                    binary_path = os.path.split(conf_file)[0]
                    modem_fw_file = os.path.join(binary_path, args.modem_fw)
                    if exists(modem_fw_file):
                        copyfile(
                            modem_fw_file, os.path.join(args.output_path, args.modem_fw)
                        )

            if args.unlocked:
                print_unprotected_bootloader()

        elif len(possible_firmwares) == 0:
            print_no_firmware_found(target_config)
            raise RuntimeError("No firmware found")
        else:
            print_multiple_firmware_found(target_config, possible_firmwares)
            raise RuntimeError("Too many firmware found")

        # Check Libraries configurations
        # Once firmware is selected, Lib version could be checked to
        # be sure app doesn't need higher versions

    except (ValueError, IOError, OSError, RuntimeError) as exc:
        sys.stdout.write("%s: %s\n" % (pgmname, exc))
        return 1

    return 0


# Run main.
if __name__ == "__main__":
    sys.exit(main())
