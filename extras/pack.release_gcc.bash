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

VERSION=`grep version= platform.txt.oldgcc | sed 's/version=//g'`
echo $VERSION

PWD=`pwd`
FOLDERNAME=`basename $PWD`
echo $FOLDERNAME
THIS_SCRIPT_NAME=`basename $0`

rm -f extras/build/msp430-$VERSION.tar.bz2
rm -f extras/build/msp430-$VERSION.tar.bz2.sha256

#filter board.txt
#sed -r s/(-msmall|-mcode-region=lower|-mhwmult=f5series)// boards.txt > boards.txt.oldgcc
sed -r s/build\.extra_flags=.*$/build.extra_flags=/ boards.txt > boards.txt.oldgcc

cd ..
tar --transform "s|$FOLDERNAME|msp430-$VERSION|g" --transform "s|boards.txt.oldgcc|boards.txt|g" --transform "s|platform.txt.oldgcc|platform.txt|g"  --exclude=*.sha256 --exclude=*.bz2 --exclude=boards.txt --exclude=platform.txt --exclude=extras --exclude=build --exclude=.git* --exclude=.idea -cjf msp430-$VERSION.tar.bz2 $FOLDERNAME
cd -
rm boards.txt.oldgcc

[ -d "build" ] || mkdir build 
mv ../msp430-$VERSION.tar.bz2 ./extras/build/

sha256sum --tag extras/build/msp430-$VERSION.tar.bz2 > extras/build/msp430-$VERSION.tar.bz2.sha256
stat -f -c%z extras/build/msp430-$VERSION.tar.bz2
