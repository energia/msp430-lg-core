import json
from collections import OrderedDict
import argparse
import os
import errno, sys


def update_file_info (index, dir):
    newText = ""
    file = index['archiveFileName']
    BSD = False
    if BSD:
        with open("build/"+dir+"/"+file+".sha256") as f:
            newText = f.read().split("=")

        index['checksum'] = "SHA-256:" + newText[1].replace("\n","").replace(" ","")
        index['size'] = str(os.path.getsize("build/"+dir+"/"+file))
    else:
        with open("build/" + dir + "/" + file + ".sha256") as f:
            newText = f.read().split("*")

        index['checksum'] = "SHA-256:" + newText[0].replace("\n", "").replace(" ", "")
        index['size'] = str(os.path.getsize("build/" + dir + "/" + file))
    return {'checksum': index['checksum'],
            'size': index['size'] }


def add_version(tooldata, json_data):
    found = False
    for tindex, t in enumerate(json_data["packages"][0]['platforms']):
        if t['architecture'] == tooldata['architecture'] and t['version'] == tooldata['version']:
            found = True
            json_data["packages"][0]['platforms'][tindex]=tooldata
    if found == False:
        json_data["packages"][0]['platforms'].append(tooldata)
    return json_data

def add_toolsDependencies(arch, version, tooldata, json_data):
    found = False
    for pindex, p in enumerate(json_data['packages'][0]['platforms']):
        if p['architecture'] == arch and p['version'] == version :
            for tindex, t in enumerate(p['toolsDependencies']):
                if t['name'] == tooldata['name']: # and t['version'] == tooldata['version']:
                    found = True
                    json_data['packages'][0]['platforms'][pindex]['toolsDependencies'][tindex] = tooldata
            if found == False:
                json_data['packages'][0]['platforms'][pindex]['toolsDependencies'].append(tooldata)
    return json_data

def add_tool(tooldata, json_data):
    found = False
    for tindex, t in enumerate(json_data['packages'][0]['tools']):
        if t['name'] == tooldata['name'] and t['version'] == tooldata['version']:
            found = True
            json_data['packages'][0]['tools'][tindex] = tooldata
    if found == False:
        json_data['packages'][0]['tools'].append(tooldata)
    return json_data


workPath = os.getcwd()


# Read command line parameters
# Initialisieren des parsers und setzen des Hilfetextes
parser = argparse.ArgumentParser(description='')
parser.add_argument('-a', '--arch', default='msp430',
                    help='Required: msp430 version')
parser.add_argument('-v', '--version', default='1.0.0',
                    help='Required: msp430 version')
parser.add_argument('-n', '--cname', default='msp430-elf-gcc',
                    help='Required: msp430 version')
parser.add_argument('-c', '--cversion', default='1.0.1',
                    help='Required: compiler version')
parser.add_argument('-d', '--dslite', default='1.0.2',
                    help='Required: dslite version')
parser.add_argument('-i', '--ino2cpp', default='1.0.4',
                    help='Required: dslite version')
parser.add_argument('-e', '--mspdebug', default='0.22',
                    help='Required: mspdebug version')
parser.add_argument('-u', '--url', default='http',
                    help='Required: dslite version')
parser.add_argument('-f', '--package_file', default='package_msp430_elf_GCC_index.json.template',
                    help='Required: package file version')
args = parser.parse_args()


my_url = str(args.url.replace("'",""))

# Generate json file
#-------------------
with open(args.package_file) as json_file:
    json_data = json.load(json_file, object_pairs_hook=OrderedDict)
with open(args.package_file+".xxx", 'w') as json_file:
    json.dump(json_data, json_file, indent=2) # write back with new format

    #if (workPath+"\compiler_data.py").is_file():
    from compiler_data import *
    #else:
    #    print ("File compiler_data.py missing\n")
    #    sys.exit(errno.EACCES)

    tool = get_platform(args, my_url)
    update_file_info(tool, 'cores')
    add_version(tool, json_data)

    # if args.compiler[:1] == "4": # legacy GCC
        # compiler_name = args.arch + "-gcc"
    # else:
        # compiler_name = args.arch + "-elf-gcc"

    ctn = getCompilerToolName(args)
    tool = OrderedDict([
        ('packager', "energia"),
        ('name', ctn),
        ('version', args.cversion),
    ])
    add_toolsDependencies(args.arch, args.version, tool, json_data)

    tool = OrderedDict([
        ('packager', "energia"),
        ('name', 'dslite'),
        ('version', args.dslite),
    ])
    add_toolsDependencies(args.arch, args.version, tool, json_data)

    tool = OrderedDict([
        ('packager', "energia"),
        ('name', 'ino2cpp'),
        ('version', args.ino2cpp),
    ])
    add_toolsDependencies(args.arch, args.version, tool, json_data)

    tool = OrderedDict([
        ('packager', "energia"),
        ('name', 'mspdebug'),
        ('version', args.mspdebug),
    ])
    if args.arch == "msp430":
        add_toolsDependencies(args.arch, args.version, tool, json_data)


    tool = init_tools_data(args, my_url)
    update_file_info(tool['systems'][0], 'tools/windows')
    update_file_info(tool['systems'][1], 'tools/macos')
    update_file_info(tool['systems'][2], 'tools/linux64')
    add_tool(tool, json_data)

    tool = OrderedDict([
        ('name','dslite'),
        ('version' , args.dslite),
        ('systems' , [
                {
                    'host' : 'i686-mingw32',
                    'url' : my_url + "windows/dslite-" + args.dslite + "-i686-mingw32.tar.bz2",
                    'archiveFileName' : "dslite-" + args.dslite + "-i686-mingw32.tar.bz2",
                },
                {
                    'host' :  'x86_64-apple-darwin',
                    'url' : my_url + 'macosx/dslite-' + args.dslite + '-x86_64_apple-darwin.tar.bz2',
                    'archiveFileName' : 'dslite-' + args.dslite + '-x86_64-apple-darwin.tar.bz2',
                },
                {
                    'host' : 'x86_64-pc-linux-gnu',
                    'url' : my_url + 'linux64/dslite-' + args.dslite + '-i386-x86_64-pc-linux-gnu.tar.bz2',
                    'archiveFileName' :  'dslite-' + args.dslite + '-i386-x86_64-pc-linux-gnu.tar.bz2',
                }
            ])
    ])
    update_file_info(tool['systems'][0], 'tools/windows')
    update_file_info(tool['systems'][1], 'tools/macos')
    update_file_info(tool['systems'][2], 'tools/linux64')
    add_tool(tool, json_data)


    with open('./build/'+args.package_file.replace(".template",""), 'w') as outfile:
        json.dump(json_data, outfile, indent=2)
    with open('./'+args.package_file.replace(".template",""), 'w') as outfile:
        json.dump(json_data, outfile, indent=2)

