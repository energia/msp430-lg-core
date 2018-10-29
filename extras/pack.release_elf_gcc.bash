#!/bin/bash -ex

#  pack.*.bash - Bash script to help packaging samd core releases.
#  Copyright (c) 2015 Arduino LLC.  All right reserved.
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

source ./extras/versions.sh

VERSION=$energia_ver
echo $VERSION

PWD=`pwd`
FOLDERNAME=`basename $PWD`
echo $FOLDERNAME
THIS_SCRIPT_NAME=`basename $0`

rm -f extras/build/msp430-$VERSION.tar.bz2
rm -f extras/build/msp430-$VERSION.tar.bz2.sha256

sed -r s/version=xxx/version=$VERSION/ platform.txt.template | sed -r s/dslite-xxx/dslite-$dslite_ver/ > platform.txt

cd ..
tar --transform "s|$FOLDERNAME|msp430-$VERSION|g"  --exclude=*.sha256 --exclude=*.bz2 --exclude=platform.txt.oldgcc --exclude=platform.txt.template --exclude=extras --exclude=.git* --exclude=.idea -cjf msp430-$VERSION.tar.bz2 $FOLDERNAME
cd -

[ -d "extras/build" ] || mkdir extras/build 
mv ../msp430-$VERSION.tar.bz2 ./extras/build/

cd extras/build
shasum -a 256 msp430-$VERSION.tar.bz2 > msp430-$VERSION.tar.bz2.sha256
stat -f -c %z msp430-$VERSION.tar.bz2
cd ../..
