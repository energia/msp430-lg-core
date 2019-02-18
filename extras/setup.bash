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
	wget --content-disposition -qO extras/download/"${fn}" "${1}"
}


#[ ! -d "extras/build" ] && rm -rf extras/build 
[ ! -d "extras/build" ] && mkdir extras/build
[ ! -d "extras/build/windows" ] && mkdir extras/build/windows
[ ! -d "extras/build/macos" ] && mkdir extras/build/macos
[ ! -d "extras/build/linux32" ] && mkdir extras/build/linux32
[ ! -d "extras/build/linux64" ] && mkdir extras/build/linux64
[ -d "extras/build/linux64" ]  # check to return true
