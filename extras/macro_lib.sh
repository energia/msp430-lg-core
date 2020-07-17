#!/bin/bash 


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

m_download()
{
	local fn
	# SF directlinks
	fn="$( basename "${1%}" )"
	# check if already there
	[ -f extras/download/"${fn}" ] && return
	echo Fetching: "${fn}" - "${1}"
	[ ! -d "extras/download" ] && mkdir extras/download
	#wget --content-disposition -qO extras/download/"${fn}" "${1}"
	#echo curl -L ${https_proxy} -o extras/download/"${fn}" "${1}"
	curl -L ${https_proxy} -o extras/download/"${fn}" "${1}"
}

m_extract()
{
	local fn="${1}"
	local dn="${2}"
	local command="echo no valid extension"
	echo Extracting: "${fn}"
	expr "${fn}" : '.*\.gz$' >/dev/null && command="${G}tar -xzf " && [ -d $( basename "${fn%%.*}" .tar.gz ) ] && rm -rf $( basename "${fn%%.*}" .tar.gz )/
	expr "${fn}" : '.*\.bz2$' >/dev/null && command="${G}tar -xjf " && [ -d $( basename "${fn%%.*}" .tar.bz2 ) ] && rm -rf $( basename "${fn%%.*}" .tar.bz2 )/ && echo rm -rf $( basename "${fn%%.*}" .tar.bz2 )/
	expr "${fn}" : '.*\.zip$' >/dev/null && command="${G}unzip -q -o " && [ -d $( basename "${fn%%.*}" .zip ) ] && rm -rf $( basename "${fn%%.*}" .zip )/
	expr "${fn}" : '.*\.7z$' >/dev/null && command="${G}p7zip -d " && [ -d $( basename "${fn%%.*}" .7z ) ] && rm -rf $( basename "${fn%%.*}" .7z )/
	pushd "${dn}" >/dev/null
	echo ${command} ../../download/"${fn}"
	${command} ../../download/"${fn}"
	popd >/dev/null
} 

m_pack()
{
	local fn="${1}"
	local en="${2}"
	local dn="${3}"
	local an="${4}"
	local td="${5}"
	local command="echo no valid extension"
	echo Packing: "${fn}"
	expr "${en}" : '.*\.gz$' >/dev/null && command="${G}tar -czf "
	expr "${en}" : '.*\.bz2$' >/dev/null && command="${G}tar -cjf "
	expr "${en}" : '.*\.zip$' >/dev/null && command="${G}zip -q -r "

	pushd "${dn}" >/dev/null
	# attention space needed after [ and before ]
	if [[ "$an" != "" ]]; then
		cp -r ${an} ${fn}/
	fi
	[ -f ${fn}/version.properties ] && rm ${fn}/version.properties
	[ -d "msp430" ] && rm -rf msp430/
	mkdir msp430
	cd "${fn}"
	cp -r * ../msp430
	cd ..
	#pause "start packing..."
	${command} "${fn}${en}" msp430
	if [ "$(expr substr $(uname -s) 1 6)" == "CYGWIN" ]; then
		sha256sum "${fn}${en}" >"${fn}${en}".sha256
	else
		shasum -a 256 "${fn}${en}" >"${fn}${en}".sha256
	fi
	if [[ "$td" != "" ]]; then
		mv -f "${fn}${en}" ${td}
		mv -f "${fn}${en}".sha256 ${td}
	fi
	rm -rf msp430/
	rm -rf "${fn}"/
	popd >/dev/null
} 

pause()
{
	
	#echo current path:
	#pwd
	echo ${1}
	#echo Hit Enter
	#read -p "$*"
}

m_setup()
{
	#[ ! -d "extras/build" ] && rm -rf extras/build 
	[ ! -d "extras/build" ] && mkdir extras/build
	[ ! -d "extras/build/cores" ] && mkdir extras/build/cores
	[ ! -d "extras/build/tools" ] && mkdir extras/build/tools
	[ ! -d "extras/build/tools/windows" ] && mkdir extras/build/tools/windows
	[ ! -d "extras/build/tools/windows64" ] && mkdir extras/build/tools/windows64
	[ ! -d "extras/build/tools/macos" ] && mkdir extras/build/tools/macos
	[ ! -d "extras/build/tools/linux32" ] && mkdir extras/build/tools/linux32
	[ ! -d "extras/build/tools/linux64" ] && mkdir extras/build/tools/linux64
	[ -d "extras/build/tools/linux64" ]  # check to return true
}

echo script_lib loaded
