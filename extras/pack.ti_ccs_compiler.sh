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

# build and install Somnium cgt toolchain for MSP430-Energia
#
# prerequisites
# - bash
# - wget, GNU patch, GNU make
# - things needed to build binutils, cgt and GDB
#

set -e
source ./extras/pack.mito_gcc.sh


cgt_ver="16.9.4.LTS"
cgt_ver_="16_9_4_LTS"


echo '!!! fetch files'
[ -d "extras/download" ] || mkdir extras/download 
m_download "http://syntaxerror.dal.design.ti.com/release/releases/msp/rel${cgt_ver_}/build/install/ti_cgt_msp430_${cgt_ver}_linux_installer_x86.bin"
m_download "http://syntaxerror.dal.design.ti.com/release/releases/msp/rel${cgt_ver_}/build/install/ti_cgt_msp430_${cgt_ver}_osx_installer.app.zip"
m_download "http://syntaxerror.dal.design.ti.com/release/releases/msp/rel${cgt_ver_}/build/install/ti_cgt_msp430_${cgt_ver}_windows_installer.exe"
cd extras/download
md5sum --check --ignore-missing md5sum.txt
cd ../..


echo '!!! untar+patch packages'

[ -d "extras/build" ] && rm -rf extras/build 
mkdir extras/build
m_extract "ti_cgt_msp430_${cgt_ver}_linux_installer_x86.bin" "extras/build"
m_extract "ti_cgt_msp430_${cgt_ver}_osx_installer.app.zip" "extras/build"
m_extract "ti_cgt_msp430_${cgt_ver}_windows_installer.exe" "extras/build"


#echo '!!! rename to elf'
#cd extras/build
#mv -v  msp430-cgt-${cgt_ver} msp430-elf-cgt-${cgt_ver} *
#for f in msp430-cgt-${cgt_ver}*; do mv "$f" "${f/msp430-gcc-${cgt_ver}/msp430-elf-cgt-${cgt_ver}}"; done
#cd ../..

#echo '!!! add support files'
#m_pack "msp430-elf-cgt-${cgt_ver}_linux32" ".tar.bz2" "extras/build" "msp430-cgt-support-files"
#m_pack "msp430-elf-cgt-${cgt_ver}_osx"     ".tar.bz2" "extras/build" "msp430-cgt-support-files"
#m_pack "msp430-elf-cgt-${cgt_ver}_win32"   ".zip"     "extras/build" "msp430-cgt-support-files"

#rm -rf "build/msp430-elf-cgt-support-files/"
#rm -rf "build/msp430-cgt-support-files/"

