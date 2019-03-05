Build instructions:

Note: Run all commands from the directory above
      Scripts are tested with cygwin

	  
	  
Prepare
=======
	update version.sh file with correct version information
	-> see also some instructions there
	copy/update the json.template file with the current released json files.
	
	  
Build Compiler package with new GCC (elf) compiler
==================================================
	run ./extras/make_mito_release.sh
	- files are collected from the source defined in version.sh then updated and patched
	- dslite is assumed to be available on the web ready to use package
	- the json file is generated / updated / added with the new or changed version and file details
	- finally the files are stored in the build folder


	
Build Compiler package with legacy GCC compiler
==================================================
	run ./extras/make_release.sh
	- files are collected from the source defined in version.sh then updated and patched
	- currently it assumes that the compiler is already available and just taken from the web
	- dslite is assumed to be available on the web ready to use package
	- the json file is generated / updated / added with the new or changed version and file details
	- finally the files are stored in the build folder
    
    Patch function:
    ---------------
    when providing a patch file within the patches folder this will be applied to the legacy GCC compiler package 
    during the release build. The script will add the header and linker file and also update the msp430.h and 
    msp430mcu.spec file.
	
	
	

=============================================================================================================

	
outdated info:
=================	
	
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
