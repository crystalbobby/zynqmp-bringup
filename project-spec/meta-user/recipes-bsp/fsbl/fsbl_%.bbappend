#Enable appropriate FSBL debug flags
#YAML_COMPILER_FLAGS_append = " -DFSBL_DEBUG"
YAML_COMPILER_FLAGS_remove = " -Os -flto --ffat-lto-objects"

SRC_URI_append += " \
                file://0001-sw_apps-zynqmp_fsbl-add-SI5338-configuration.patch \
                file://0002-sw_apps-zynqmp_fsbl-add-ethernet-reset.patch \
                file://0003-sw_apps-zynqmp_fsbl-add-4G-powerkey.patch \
                "

FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

# Note: This is not required if you are using Yocto
# CAUTION!: EXTERNALXSCTSRC and EXTERNALXSCTSRC_BUILD is required only for 2018.2 and below petalinux releases
EXTERNALXSCTSRC = ""
EXTERNALXSCTSRC_BUILD = ""
  
