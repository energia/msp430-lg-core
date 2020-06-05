#!/usr/bin/env bash


# Copyright (c) 2016 StefanSch
# 
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# build and install Somnium GCC toolchain for MSP430-Energia
#
# prerequisites
# - bash
# - wget, GNU patch, GNU make
# - things needed to build binutils, GCC and GDB
#

set -e
source ./extras/macro_lib.sh 


GCC_VER="6.4.0.32"
MSPGCC_VER="latest"
MSPSUPPORT_VER="1.201"






echo '!!! fetch files'
[ -d "extras/download" ] || mkdir extras/download 
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/exports/msp430-gcc-${GCC_VER}_linux32.tar.bz2"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/exports/msp430-gcc-${GCC_VER}_linux64.tar.bz2"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/exports/msp430-gcc-${GCC_VER}_osx.tar.bz2"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/exports/msp430-gcc-${GCC_VER}_win32.zip"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/exports/msp430-gcc-support-files-${MSPSUPPORT_VER}.zip"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/exports/md5sum.txt"
cd extras/download
md5sum --check --ignore-missing md5sum.txt
cd ../..


echo '!!! untar+patch packages'

[ -d "extras/build" ] && rm -rf extras/build 
mkdir extras/build
m_extract "msp430-gcc-${GCC_VER}_linux32.tar.bz2" "extras/build"
m_extract "msp430-gcc-${GCC_VER}_linux64.tar.bz2" "extras/build"
m_extract "msp430-gcc-${GCC_VER}_osx.tar.bz2" "extras/build"
m_extract "msp430-gcc-${GCC_VER}_win32.zip" "extras/build"
m_extract "msp430-gcc-support-files-${MSPSUPPORT_VER}.zip" "extras/build"

echo '!!! rename to elf'
cd extras/build
#rename -v  msp430-gcc-${GCC_VER} msp430-elf-gcc-${GCC_VER} *
for f in msp430-gcc-${GCC_VER}*; do mv "$f" "${f/msp430-gcc-${GCC_VER}/msp430-elf-gcc-${GCC_VER}}"; done
cd ../..

echo '!!! add support files'
m_pack "msp430-elf-gcc-${GCC_VER}_linux32" ".tar.bz2" "extras/build" "msp430-gcc-support-files"
m_pack "msp430-elf-gcc-${GCC_VER}_linux64" ".tar.bz2" "extras/build" "msp430-gcc-support-files"
m_pack "msp430-elf-gcc-${GCC_VER}_osx"     ".tar.bz2" "extras/build" "msp430-gcc-support-files"
m_pack "msp430-elf-gcc-${GCC_VER}_win32"   ".zip"     "extras/build" "msp430-gcc-support-files"

rm -rf "extras/build/msp430-elf-gcc-support-files/"
rm -rf "extras/build/msp430-gcc-support-files/"

