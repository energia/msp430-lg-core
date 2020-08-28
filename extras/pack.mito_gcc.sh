#!/usr/bin/env bash


# Copyright (c) 2018 StefanSch
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

# build and install Mito GCC toolchain for MSP430-Energia
#
# prerequisites
# - bash
# - wget, GNU patch, GNU make
# - things needed to build binutils, GCC and GDB
#

set -e

source ./extras/versions.sh
source ./extras/macro_lib.sh 


echo '!!! fetch files'
[ -d "extras/download" ] || mkdir extras/download 
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/export/msp430-gcc-${GCC_VER}_linux32.tar.bz2"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/export/msp430-gcc-${GCC_VER}_linux64.tar.bz2"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/export/msp430-gcc-${GCC_VER}_macos.tar.bz2"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/export/msp430-gcc-${GCC_VER}_win32.zip"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/export/msp430-gcc-${GCC_VER}_win64.zip"
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/export/msp430-gcc-support-files-${MSPSUPPORT_VER}.zip"
[ -f extras/download/md5sum.txt ] && rm extras/download/md5sum.txt
m_download "http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/${MSPGCC_VER}/export/md5sum.txt"
cd extras/download
#sed -i '/md5sum/d' ./md5sum.txt
echo check checksum
# md5 checksum file currently not provided
#md5sum --check --ignore-missing md5sum.txt
#md5sum --check --status md5sum.txt
cd ../..

[ -d "extras/build" ] || mkdir extras/build
[ -d "extras/build/tools" ] || mkdir extras/build/tools

echo '!!! untar+patch packages'

m_setup

m_extract "msp430-gcc-${GCC_VER}_linux32.tar.bz2" "extras/build/tools"
m_extract "msp430-gcc-${GCC_VER}_linux64.tar.bz2" "extras/build/tools"
m_extract "msp430-gcc-${GCC_VER}_macos.tar.bz2" "extras/build/tools"
m_extract "msp430-gcc-${GCC_VER}_win32.zip" "extras/build/tools"
m_extract "msp430-gcc-support-files-${MSPSUPPORT_VER}.zip" "extras/build/tools"
pause "done extract"

echo '!!! rename to elf'
cd extras/build/tools
#rename -v  msp430-gcc-${GCC_VER} msp430-elf-gcc-${GCC_VER} *
for f in msp430-elf-gcc*; do rm -rf  "$f"; done
for f in msp430-gcc-${GCC_VER}*; do echo mv "$f" "${f/msp430-gcc-${GCC_VER}/msp430-elf-gcc-${GCC_VER}}"; done
for f in msp430-gcc-${GCC_VER}*; do mv "$f" "${f/msp430-gcc-${GCC_VER}/msp430-elf-gcc-${GCC_VER}}"; done
cd ../../..
pause "done rename"

echo '!!! add support files and pack again'
m_pack "msp430-elf-gcc-${GCC_VER}_linux32" ".tar.bz2" "extras/build/tools" "msp430-gcc-support-files"  "linux32"
m_pack "msp430-elf-gcc-${GCC_VER}_linux64" ".tar.bz2" "extras/build/tools" "msp430-gcc-support-files"  "linux64"
m_pack "msp430-elf-gcc-${GCC_VER}_macos"   ".tar.bz2" "extras/build/tools" "msp430-gcc-support-files"  "macosx"
m_pack "msp430-elf-gcc-${GCC_VER}_win32"   ".tar.bz2" "extras/build/tools" "msp430-gcc-support-files"  "windows"
m_pack "msp430-elf-gcc-${GCC_VER}_win64"   ".tar.bz2" "extras/build/tools" "msp430-gcc-support-files"  "windows64"
pause "done packing"

echo '!!! clean up'
rm -rf "extras/build/tools/msp430-elf-gcc-support-files/"
rm -rf "extras/build/tools/msp430-gcc-support-files/"
