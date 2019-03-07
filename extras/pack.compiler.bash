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

# package GCC toolchain for Energia
#
# prerequisites
# - bash
# - wget, GNU patch, GNU make
# - things needed to build binutils, GCC and GDB
#

set -e

source ./extras/versions.sh
source ./extras/setup.bash


m_extract()
{
	local fn="${1}"
	local wd="${2}"
	local command="echo no valid extension"
	echo Extracting: "${fn}"
	expr "${fn}" : '.*\.gz$' >/dev/null && command="${G}tar -xzf "
	expr "${fn}" : '.*\.bz2$' >/dev/null && command="${G}tar -xjf "
	expr "${fn}" : '.*\.zip$' >/dev/null && command="${G}unzip -q "
	pushd "${wd}" >/dev/null
	${command} ../download/"${fn}"
    if [ ! -f "msp430-gcc-${LEGACY_GCC_VER}" ]; then
        echo rename to "msp430-gcc-${LEGACY_GCC_VER}"
        mv "msp430-gcc-${LOAD_GCC_VER}" "msp430-gcc-${LEGACY_GCC_VER}"
    fi
	popd >/dev/null
} 

m_pack()
{
	local fn="${1}"
	local en="${2}"
	local wd="${3}"
	local td="${4}"
	local command="echo no valid extension"
	echo Packing: "${fn}"
	expr "${en}" : '.*\.gz$' >/dev/null && command="${G}tar -czf "
	expr "${en}" : '.*\.bz2$' >/dev/null && command="${G}tar -cjf "
	expr "${en}" : '.*\.zip$' >/dev/null && command="${G}zip -q -r "
	pushd "${wd}" >/dev/null
    for d in */; { 
        ${command} "${fn}${en}" "$d"
        shasum -a 256 "${fn}${en}" >"${fn}${en}".sha256
        #rm -rf "${fn}"/
    }
	popd >/dev/null
    mv "${wd}/${fn}${en}" ${td}
    mv "${wd}/${fn}${en}".sha256 ${td}
}  


m_patch()
{
	local fn="${1}"
	local en="${2}"
	local wd="${3}"
	local td="${4}"
    [ -d "extras/temp" ] && rm -rf extras/temp
    mkdir extras/temp
    m_extract "msp430-gcc-${LOAD_GCC_VER}${fn}${en}" "${wd}"
    for filename in $(find extras/patches/ -name 'patch_*.zip' ); {
        echo Patching: $filename
        python extras/patch_msp430.py --patch=$(basename -- "$filename") --path="${wd}/msp430-gcc-${LEGACY_GCC_VER}"
    }

    m_pack "msp430-gcc-${LEGACY_GCC_VER}${fn}" "${en}" "${wd}" "${td}"
    [ -d "extras/temp" ] && rm -rf extras/temp
}
 
echo '--- do compiler packages'
echo 'prepare gcc'
echo "this needs to be already available online at: ${DSLITE_URL}"
m_download "${DSLITE_URL}/windows/msp430-gcc-${LOAD_GCC_VER}-i686-mingw32.tar.bz2"
m_patch "-i686-mingw32" ".tar.bz2" "extras/temp"  "extras/build/windows"

m_download "${DSLITE_URL}/macosx/msp430-gcc-${LOAD_GCC_VER}-i386-apple-darwin11.tar.bz2"
m_patch  "-i386-apple-darwin11" ".tar.bz2" "extras/temp"  "extras/build/macos"

m_download "${DSLITE_URL}/linux64/msp430-gcc-${LOAD_GCC_VER}-i386-x86_64-pc-linux-gnu.tar.bz2"
m_patch  "-i386-x86_64-pc-linux-gnu" ".tar.bz2" "extras/temp"  "extras/build/linux64"

#for filename in $(find extras/build/ -name 'msp430-gcc-*.sha256' ); do
#    rm "$filename" 
#done
#for filename in $(find extras/build/ -name 'msp430-gcc-*' ); do
#    shasum -a 256 "$filename" >"$filename".sha256
#done
