#include <configs/platform-auto.h>
#define CONFIG_SYS_BOOTM_LEN 0xF000000

#define DFU_ALT_INFO_RAM \
                "dfu_ram_info=" \
        "setenv dfu_alt_info " \
        "image.ub ram $netstart 0x1e00000\0" \
        "dfu_ram=run dfu_ram_info && dfu 0 ram 0\0" \
        "thor_ram=run dfu_ram_info && thordown 0 ram 0\0"

#define DFU_ALT_INFO_MMC \
        "dfu_mmc_info=" \
        "set dfu_alt_info " \
        "${kernel_image} fat 0 1\\\\;" \
        "dfu_mmc=run dfu_mmc_info && dfu 0 mmc 0\0" \
        "thor_mmc=run dfu_mmc_info && thordown 0 mmc 0\0"

/*Required for uartless designs */
#ifndef CONFIG_BAUDRATE
#define CONFIG_BAUDRATE 115200
#ifdef CONFIG_DEBUG_UART
#undef CONFIG_DEBUG_UART
#endif
#endif

/*Define CONFIG_ZYNQMP_EEPROM here and its necessaries in u-boot menuconfig if you had EEPROM memory. */
#ifdef CONFIG_ZYNQMP_EEPROM
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN  1
#define CONFIG_CMD_EEPROM
#define CONFIG_ZYNQ_EEPROM_BUS          5
#define CONFIG_ZYNQ_GEM_EEPROM_ADDR     0x54
#define CONFIG_ZYNQ_GEM_I2C_MAC_OFFSET  0x20

/* Extra U-Boot Env settings */
#define CONFIG_EXTRA_ENV_SETTINGS \
        SERIAL_MULTI \
        CONSOLE_ARG \
        DFU_ALT_INFO_RAM \
        DFU_ALT_INFO_MMC \
        PSSERIAL0 \
        "bootenv=uEnv.txt\0" \
        "importbootenv=echo \"Importing environment from SD ...\"; " \
                "env import -t ${loadbootenv_addr} $filesize\0" \
        "loadbootenv=load mmc $sdbootdev:$partid ${loadbootenv_addr} ${bootenv}\0" \
        "sd_uEnvtxt_existence_test=test -e mmc $sdbootdev:$partid /uEnv.txt\0" \
        "uenvboot=" \
                "if run sd_uEnvtxt_existence_test; then " \
                        "run loadbootenv; " \
                        "echo Loaded environment from ${bootenv}; " \
                        "run importbootenv; " \
                        "fi; " \
                "if test -n $uenvcmd; then " \
                        "echo Running uenvcmd ...; " \
                        "run uenvcmd; " \
                "fi\0" \
        "autoload=no\0" \
        "sdbootdev=0\0" \
        "clobstart=0x10000000\0" \
        "netstart=0x10000000\0" \
        "dtbnetstart=0x23fff000\0" \
        "loadaddr=0x10000000\0" \
        "boot_img=BOOT.BIN\0" \
        "install_boot=mmcinfo && fatwrite mmc ${sdbootdev} ${clobstart} ${boot_img} ${filesize}\0" \
        "bootenvsize=0x40000\0" \
        "bootenvstart=0x100000\0" \
        "eraseenv=sf probe 0 && sf erase ${bootenvstart} ${bootenvsize}\0" \
        "jffs2_img=rootfs.jffs2\0" \
        "sd_update_jffs2=echo Updating jffs2 from SD; mmcinfo && fatload mmc ${sdbootdev}:1 ${clobstart} ${jffs2_img} && run install_jffs2\0" \
        "install_jffs2=sf probe 0 && sf erase ${jffs2start} ${jffs2size} && " \
                "sf write ${clobstart} ${jffs2start} ${filesize}\0" \
        "kernel_img=image.ub\0" \
        "install_kernel=mmcinfo && fatwrite mmc ${sdbootdev} ${clobstart} ${kernel_img} ${filesize}\0" \
        "cp_kernel2ram=mmcinfo && fatload mmc ${sdbootdev} ${netstart} ${kernel_img}\0" \
        "dtb_img=system.dtb\0" \
        "sd_update_dtb=echo Updating dtb from SD; mmcinfo && fatload mmc ${sdbootdev}:1 ${clobstart} ${dtb_img} && run install_dtb\0" \
        "loadbootenv_addr=0x00100000\0" \
        "fault=echo ${img} image size is greater than allocated place - partition ${img} is NOT UPDATED\0" \
        "test_crc=if imi ${clobstart}; then run test_img; else echo ${img} Bad CRC - ${img} is NOT UPDATED; fi\0" \
        "test_img=setenv var \"if test ${filesize} -gt ${psize}\\; then run fault\\; else run ${installcmd}\\; fi\"; run var; setenv var\0" \
        "default_bootcmd=run uenvboot; run cp_kernel2ram && bootm ${netstart}\0" \
""

/* BOOTCOMMAND */


#endif
