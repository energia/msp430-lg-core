# ==========================================================
# this file contains the data sturcture for the compiler
# Note: this is tools specific and needs to be adjusted
# ==========================================================

import json
from collections import OrderedDict

def getCompilerToolName(args):
	if args.arch == "msp430": # legacy GCC
		return "msp430-gcc"
	else:
		return "msp430-elf-gcc"

def get_platform(args, my_url):
	tool = OrderedDict([
		('name', "Energia MSP430 boards (elf-GCC)"),
		('architecture', "msp430elf"),
		('version', args.version),
		('category', "Energia"),
		('url', my_url + args.arch + "-" + args.version + ".tar.bz2"),
		('archiveFileName', args.arch + "-" + args.version + ".tar.bz2"),
		('checksum', "0"),
		('size', ""),
		("boards", [
			{"name": "MSP-EXP430F5529"},
			{"name": "MSP-EXP430FR2433"},
			{"name": "MSP-EXP430FR4133"},
			{"name": "MSP-EXP430FR5969"},
			{"name": "MSP-EXP430FR6989"},
			{"name": "MSP-EXP430FR5739"},
			{"name": "MSP-EXP430FR2355"},
			{"name": "MSP-EXP430FR2231"},
			{"name": "MSP-EXP430G2"},
			{"name": "MSP-EXP430G2ET"},
			{"name": "MSP-EXP430FR5994"} 
		]),
		("toolsDependencies", []),
	])

	if args.version[:1] == "1": # patch for legacy GCC
		tool["name"] =  "Energia " + args.arch.upper() + " boards"
		tool["architecture"] = args.arch
		
	return tool

		

def init_tools_data(args, my_url):
	if args.arch == "msp430": # legacy GCC
		tool = OrderedDict([
		    ('name', args.cname),
		    ('version', args.cversion),
		    ('systems', [
			    {# Windows
					'host': 'i686-mingw32',
					'url': my_url + "windows/" + args.cname + "-" + args.cversion + "-i686-mingw32.tar.bz2",
					'archiveFileName': args.cname + "-" + args.cversion + "-i686-mingw32.tar.bz2",
			    },
			    {# MacOs
					'host': 'x86_64-apple-darwin',
					'url': my_url + 'macosx/' + args.cname + '-' + args.cversion + '-i386-apple-darwin11.tar.bz2',
					'archiveFileName': args.cname + "-" + args.cversion + '-i386-apple-darwin11.tar.bz2',
			    },
			    {# Linux64
					'host': 'x86_64-pc-linux-gnu',
					'url': my_url + 'linux64/' + args.cname + '-' + args.cversion + '-i386-x86_64-pc-linux-gnu.tar.bz2',
					'archiveFileName': args.cname + '-' + args.cversion + '-i386-x86_64-pc-linux-gnu.tar.bz2',
			    }
			])
		])
	else:
		tool = OrderedDict([
			('name', args.cname),
			('version', args.cversion),
			('systems', [
				{
					'host': 'i686-mingw32',
					'url': my_url + "windows/" + args.cname + "-" + args.cversion + "_win32.zip",
					'archiveFileName': args.cname + "-" + args.cversion + "_win32.zip",
				},
				{
					'host': 'x86_64-apple-darwin',
					'url': my_url + 'macosx/' + args.cname + '-' + args.cversion + '_macos.tar.bz2',
					'archiveFileName': args.cname + "-" + args.cversion + '_macos.tar.bz2',
				},
				{
					'host': 'x86_64-pc-linux-gnu',
					'url': my_url + 'linux64/' + args.cname + '-' + args.cversion + '_linux64.tar.bz2',
					'archiveFileName': args.cname + '-' + args.cversion + '_linux64.tar.bz2',
				}
			])
		])
	return tool


