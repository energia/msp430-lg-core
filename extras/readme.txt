Build instructions:

Note: Run all commands from the directory above
      Scripts are tested with cygwin

Build Compiler package with new GCC (elf) compiler
==================================================

Somnium:
--------
Update below version info in pack_somnium_gcc.sh with data from 
http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/latest/index_FDS.html

	gcc_ver="6.4.0.32"
	mspgcc_ver="latest"
	mspsupport_ver="1.201"
 
execute: ./extras/pack_somnium_gcc.sh
-> files are stored in extras/build


Mito:
--------
Update below version info in pack_mito_gcc.sh with data from 
http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSPGCC/latest/index_FDS.html

	gcc_ver="7.3.0.9"
	mspgcc_ver="6_00_00_900"
	mspsupport_ver="1.204"
 
execute: ./extras/pack_mito_gcc.sh
-> files are stored in extras/build


Build package for old GCC compiler
==================================
update version in platform.txt.oldgcc
execute: ./extras/pack.release_gcc.bash
-> files are stored in extras/build

Build package for GCC (elf) compiler
====================================
update version in platform.txt
execute: ./extras/pack.release_elf_gcc.bash
-> files are stored in extras/build


Build release Package
====================================
update supported board in package_msp430_elf_GCC_index.json
update supported comiler package version and checksum in package_msp430_elf_GCC_index.json
  (info and files are in the build folder)
  
uploaded files:
 - Compiler package (from Build folder)
 msp430* package
