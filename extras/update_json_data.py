import json
from collections import OrderedDict
import argparse
import os

def update_file_info (index, dir):
    newText = ""
    file = index['archiveFileName']
    with open("build/"+dir+"/"+file+".sha256") as f:
        newText = f.read().split("=")

    index['checksum'] = "SHA-256:" + newText[1].replace("\n","").replace(" ","")
    index['size'] = str(os.path.getsize("build/"+dir+"/"+file))
    return {'checksum': "SHA-256:" + newText[1].replace("\n","").replace(" ",""),
            'size': str(os.path.getsize("build/" + dir + "/" + file))}


def add_version(tooldata, json_data):
    found = False
    for t in json_data["packages"][0]['platforms']:
        if t['name'] == tooldata['name'] and t['version'] == tooldata['version']:
            found = True
            t = tooldata
    if found == False:
        json_data["packages"][0]['platforms'].append(tooldata)
    return json_data

def add_toolsDependencies(tooldata, json_data):
    found = False
    for t in json_data['packages'][0]['platforms'][0]['toolsDependencies']:
        if t['name'] == tooldata['name'] and t['version'] == tooldata['version']:
            found = True
            t = tooldata
    if found == False:
        json_data['packages'][0]['platforms'][0]['toolsDependencies'].append(tooldata)
    return json_data

def add_tool(tooldata, json_data):
    found = False
    for t in json_data['packages'][0]['tools']:
        if t['name'] == tooldata['name'] and t['version'] == tooldata['version']:
            found = True
            t = tooldata
    if found == False:
        json_data['packages'][0]['tools'].append(tooldata)
    return json_data


workPath = os.getcwd()


# Read command line parameters
# Initialisieren des parsers und setzen des Hilfetextes
parser = argparse.ArgumentParser(description='')
parser.add_argument('-m', '--msp430', default='1.0.0',
                    help='Required: msp430 version')
parser.add_argument('-c', '--compiler', default='1.0.1',
                    help='Required: compiler version')
parser.add_argument('-d', '--dslite', default='1.0.2',
                    help='Required: dslite version')
parser.add_argument('-e', '--mspdebug', default='0.22',
                    help='Required: mspdebug version')
parser.add_argument('-u', '--url', default='http',
                    help='Required: dslite version')
parser.add_argument('-f', '--package_file', default='package_msp430_elf_GCC_index.json.template',
                    help='Required: package file version')
parser.add_argument('-p', '--platform_file', default='../platform.txt.template',
                    help='Required: platform file version')
args = parser.parse_args()


my_url = str(args.url.replace("'","")+"/")

# update platform.txt file
#---------------------------
with open(args.platform_file) as f:
    newText=f.read().replace("version=xxx", "version="+args.msp430).replace("dslite-xxx", "dslite-"+args.dslite)

with open("../platform.txt", "w") as f:
    f.write(newText)


# Generate json file
#-------------------
with open(args.package_file) as json_file:
    json_data = json.load(json_file, object_pairs_hook=OrderedDict)

    tool = OrderedDict({
        'name': "Energia MSP430 boards (elf-GCC)",
        'architecture': "msp430elf",
        'version': args.msp430,
        'category': "Energia",
        'url': my_url + "msp430-" + args.msp430 + ".tar.bz2",
        'archiveFileName': "msp430-" + args.msp430 + ".tar.bz2",
    })
    update_file_info(tool, '.')
    add_version(tool, json_data)


    tool = OrderedDict({
        'name': 'msp430-elf-gcc',
        'version': args.compiler,
    })
    add_toolsDependencies(tool, json_data)

    tool = OrderedDict({
        'name': 'dslite',
        'version': args.dslite,
    })
    add_toolsDependencies(tool, json_data)

    tool = OrderedDict({
        'name': 'mspdebug',
        'version': args.mspdebug,
    })
    #add_toolsDependencies(tool, json_data)


    tool = OrderedDict({
        'name': 'msp430-elf-gcc',
        'version': args.compiler,
        'systems': [
            {
                'host': 'i686-mingw32',
                'url': my_url + "windows/msp430-elf-gcc-" + args.compiler + "_win32.zip",
                'archiveFileName': "msp430-elf-gcc-" + args.compiler + "_win32.zip",
            },
            {
                'host': 'x86_64-apple-darwin',
                'url': my_url + 'macosx/msp430-elf-gcc-' + args.compiler + '_macos.tar.bz2',
                'archiveFileName': 'msp430-elf-gcc-' + args.compiler + '_macos.tar.bz2',
            },
            {
                'host': 'x86_64-pc-linux-gnu',
                'url': my_url + 'linux64/msp430-elf-gcc-' + args.compiler + '_linux64.tar.bz2',
                'archiveFileName': 'msp430-elf-gcc-' + args.compiler + '_linux64.tar.bz2',
            }
        ]
    })
    update_file_info(tool['systems'][0], 'windows')
    update_file_info(tool['systems'][1], 'macos')
    update_file_info(tool['systems'][2], 'linux64')
    add_tool(tool, json_data)

    tool = OrderedDict({
        'name':'dslite',
        'version' : args.dslite,
        'systems' : [
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
            ]
    })
    update_file_info(tool['systems'][0], 'windows')
    update_file_info(tool['systems'][1], 'macos')
    update_file_info(tool['systems'][2], 'linux64')
    add_tool(tool, json_data)


    with open('./build/package_msp430_elf_GCC_index.json', 'w') as outfile:
        json.dump(json_data, outfile, indent=2)
    with open('./package_msp430_elf_GCC_index.json', 'w') as outfile:
        json.dump(json_data, outfile, indent=2)

