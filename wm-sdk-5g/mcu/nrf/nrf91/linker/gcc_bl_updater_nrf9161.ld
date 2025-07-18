/* Copyright 2024 Wirepas Ltd. All Rights Reserved.
 *
 * See file LICENSE.txt for full license details.
 *
 */

/* Linker script for Wirepas Generic Bootloader Updater Tool on nRF9161
 *
 * This file is for the 1024 kB Flash, 256 kB RAM variant
 *
 * Flash is split into:
 *  - Bootloader area (BOOTLOADER)
 *  - Wirepas Mesh stack executable code area (FLASH)
 *  - Bootloader updater entry point and configuration (ENTRYPOINT)
 *    - Overlapping with first erase block of FLASH area
 *  - Bootloader updater executable code (BL_UPDATER)
 *    - At the end of FLASH area
 *    - Also contains the compressed new bootloader
 *    - Also contains backup copy of the first erase block of FLASH area
 *
 * The Generic Bootloader Updater Tool may use all RAM above 31k. The first 1k
 * is reserved for the bootloader, so that calling the bootloader API works
 * until the old bootloader is erased. The next 30k is RAM for Wirepas Mesh
 * stack that is retained over boots (RETAINED_RAM). This area is not to be
 * altered by the bootloader updater.

 */

__erase_sector_size__ = 4K;  /* Must match the eraseblock value in nnn_wp.ini */

MEMORY
{
    BOOTLOADER (rx)     : ORIGIN = 0x00000000,
                          LENGTH = 32K
    FLASH (rx)          : ORIGIN = 0x00000000 + 32K,
                          LENGTH = 240K
    ENTRYPOINT (rx)     : ORIGIN = 0x00000000 + 32K,
                          LENGTH = __erase_sector_size__
    BL_UPDATER (rx)     : ORIGIN = 0x00000000 + 32K + 240K - 24K,
                          LENGTH = 24K

    /* Leave the first 1K of RAM alone, so that the bootloader API is available */
    BL_STATIC (rwx)     : ORIGIN = 0x20000000,              LENGTH = 1K
    RETAINED_RAM (r)    : ORIGIN = 0x20000000 + 1K,         LENGTH = 30K
    RAM (rwx)           : ORIGIN = 0x20000000 + 1K + 30K,   LENGTH = 33K
    INVALID (rwx)       : ORIGIN = 0xFFFFFFFF,              LENGTH = 0
}

INCLUDE gcc_bl_updater_common.ld
