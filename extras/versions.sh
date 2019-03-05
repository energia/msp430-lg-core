# file to maintain version information used for getting packages and genration
# eneriga distrubition files

# url where the package can be finally loaded from:
ENERGIA_URL="http://energia.nu/downloads/download_core.php?file="


# tool versions - used to download and create packages

# gcc compiler versions can be found here:
# web page: http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/latest/index_FDS.html
GCC_VER="7.3.2.154"
#MSPGCC_VER="6_01_00_000"
MSPGCC_VER="latest"
MSPSUPPORT_VER="1.206"

# url where dslite should be grabed for the package:
DSLITE_URL="https://s3.amazonaws.com/energiaUS/tools"
DSLITE_VER="8.2.0.1400"

INO2CPP_VER="1.0.4"

# New GCC Compiler (Mito)
# Energia tools version number - stored in platform.txt
ENERGIA_VER="2.0.5"


# Legacy GCC Compiler
# Energia tools version number - stored in platform.txt
ENERGIA1_VER="1.0.6"
# GCC version to load
LOAD_GCC_VER="4.6.6"
# GCC version after patching and packing
LEGACY_GCC_VER="4.6.7"