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

echo '--- do compiler package'
./extras/pack.compiler.sh

echo '--- do dslite package'
./extras/pack.dslite.sh

echo '--- do energia package'
./extras/pack.release_gcc.sh


echo '--- update energia install files'
#wget --content-disposition -qO extras/package_index.json.template http://www.energia.nu/packages/package_index.json
curl -L ${http_proxy} -o extras/package_index.json.template http://www.energia.nu/packages/package_index.json

cd extras
echo "python update_json_data.py -a "msp430" -v ${ENERGIA1_VER}  -n "msp430-gcc" -c ${LEGACY_GCC_VER} -d ${DSLITE_VER} -i ${INO2CPP_VER} -u ${ENERGIA_URL} -f package_index.json.template"
python update_json_data.py -a "msp430" -v ${ENERGIA1_VER}  -n "msp430-gcc" -c ${LEGACY_GCC_VER} -d ${DSLITE_VER} -i ${INO2CPP_VER} -u ${ENERGIA_URL} -f package_index.json.template
cd ..
