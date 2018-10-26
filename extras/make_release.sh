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

m_download()
{
	local fn
	# SF directlinks
	fn="$( basename "${1%}" )"
	# check if already there
	[ -f extras/download/"${fn}" ] && return
	echo Fetching: "${fn}" - "${1}"
	wget --content-disposition -qO extras/download/"${fn}" "${1}"
}


#[ ! -d "extras/build" ] && rm -rf extras/build 
[ ! -d "extras/build" ] && mkdir extras/build
[ ! -d "extras/build/windows" ] && mkdir extras/build/windows
[ ! -d "extras/build/macos" ] && mkdir extras/build/macos
[ ! -d "extras/build/linux32" ] && mkdir extras/build/linux32
[ ! -d "extras/build/linux64" ] && mkdir extras/build/linux64


 
echo '--- do compiler packages'
echo 'prepare gcc'
echo "this needs to be already available online at: ${dslite_url}"
m_download "${dslite_url}/windows/msp430-gcc-${legacy_gcc_ver}-i686-mingw32.tar.bz2"
cp  extras/download/msp430-gcc-${legacy_gcc_ver}-i686-mingw32.tar.bz2 extras/build/windows/
m_download "${dslite_url}/macosx/msp430-gcc-${legacy_gcc_ver}-i386-apple-darwin11.tar.bz2"
cp  extras/download/msp430-gcc-${legacy_gcc_ver}-i386-apple-darwin11.tar.bz2 extras/build/macos/
m_download "${dslite_url}/linux64/msp430-gcc-${legacy_gcc_ver}-i386-x86_64-pc-linux-gnu.tar.bz2"
cp  extras/download/msp430-gcc-${legacy_gcc_ver}-i386-x86_64-pc-linux-gnu.tar.bz2 extras/build/linux64/
for filename in $(find extras/build/ -name 'msp430-gcc-*' ); do
    sha256sum --tag "$filename" >"$filename".sha256
done



echo 'prepare dslite'
echo "this needs to be already available online at: ${dslite_url}"
m_download "${dslite_url}/windows/dslite-${dslite_ver}-i686-mingw32.tar.bz2"
cp  extras/download/dslite-${dslite_ver}-i686-mingw32.tar.bz2 extras/build/windows/
m_download "${dslite_url}/macosx/dslite-${dslite_ver}-x86_64-apple-darwin.tar.bz2"
cp  extras/download/dslite-${dslite_ver}-x86_64-apple-darwin.tar.bz2 extras/build/macos/
m_download "${dslite_url}/linux64/dslite-${dslite_ver}-i386-x86_64-pc-linux-gnu.tar.bz2"
cp  extras/download/dslite-${dslite_ver}-i386-x86_64-pc-linux-gnu.tar.bz2 extras/build/linux64/

for filename in $(find extras/build/ -name 'dslite-*' ); do
    sha256sum --tag "$filename" >"$filename".sha256
done


echo '--- do energia package'
./extras/pack.release_gcc.bash


echo '--- update energia install files'
cd extras
echo "python update_json_data.py -m ${energia1_ver} -c ${legacy_gcc_ver} -d ${dslite_ver} -u ${energia_url} -f 'package_index.json.template'"
python update_json_data.py -m ${energia1_ver} -c ${legacy_gcc_ver} -d ${dslite_ver} -u ${energia_url} -f 'package_index.json.template'
cd ..