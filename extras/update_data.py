import json
from collections import OrderedDict
import argparse
import os

def update_file_info (file, index, dir):
    newText = ""
    with open("build/"+dir+"/"+file+".sha256") as f:
        newText = f.read().split("=")

    index['checksum'] = "SHA-256:" + newText[1].replace("\n","").replace(" ","")
    index['size'] = str(os.path.getsize("build/"+dir+"/"+file))

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
parser.add_argument('-u', '--url', default='http',
                    help='Required: dslite version')
args = parser.parse_args()
#print (args.msp430)
#print (args.compiler)
#print (args.dslite)

#my_url = 'https://s3.amazonaws.com/energiaUS/tools/'
my_url = args.url+"/"

#update platform.txt


with open("../platform.txt.template") as f:
    newText=f.read().replace("version=xxx", "version="+args.msp430).replace("dslite-xxx", "dslite-"+args.dslite)

with open("../platform.txt", "w") as f:
    f.write(newText)


with open("package_msp430_elf_GCC_index.json.template") as json_file:
    json_data = json.load(json_file, object_pairs_hook=OrderedDict)
    #print(json_data)

    json_data["packages"][0]['platforms'][0]['url'] = my_url + "msp430-" + args.msp430 + ".tar.bz2"
    json_data["packages"][0]['platforms'][0]['archiveFileName']="msp430-" + args.msp430 + ".tar.bz2"
    json_data['packages'][0]['platforms'][0]['version']=args.msp430
    v=json_data['packages'][0]['platforms'][0]
    update_file_info(v['archiveFileName'], json_data['packages'][0]['platforms'][0], ".")

    for i in json_data['packages'][0]['platforms'][0]['toolsDependencies']:
        if i['name'] == 'msp430-elf-gcc':
            i['version'] = args.compiler
        if i['name'] == 'dslite':
            i['version'] = args.dslite
        #if i['value'] == 'mspdebug':
        #    i['version'] = args.dslite


    for t in json_data['packages'][0]['tools']:
        if t['name'] == 'msp430-elf-gcc':
            t['version'] = args.compiler
            for v in t['systems']:
                if v['host'] == 'i686-mingw32':
                    v['url'] = my_url + "windows/msp430-elf-gcc-" + args.compiler + "_win32.zip"
                    v['archiveFileName'] = "msp430-elf-gcc-" + args.compiler + "_win32.zip"
                    update_file_info( v['archiveFileName'], v, 'windows')
                if v['host'] == 'x86_64-apple-darwin':
                    v['url'] = my_url + 'macosx/msp430-elf-gcc-' + args.compiler + '_macos.tar.bz2'
                    v['archiveFileName'] = 'msp430-elf-gcc-' + args.compiler + '_macos.tar.bz2'
                    update_file_info( v['archiveFileName'], v, 'macos')
                if v['host'] == 'x86_64-linux-gnu':
                    v['url'] = my_url + 'linux64/msp430-elf-gcc-' + args.compiler + '_linux64.tar.bz2'
                    v['archiveFileName'] = 'msp430-elf-gcc-' + args.compiler + '_linux64.tar.bz2'
                    update_file_info( v['archiveFileName'], v, 'linux64')

        if t['name'] == 'dslite':
            t['version'] = args.dslite
            for v in t['systems']:
                if v['host'] == 'i686-mingw32':
                    v['url'] = my_url + "windows/dslite-" + args.dslite + "-i686-mingw32.tar.bz2"
                    v['archiveFileName'] = "dslite-" + args.dslite + "-i686-mingw32.tar.bz2"
                    update_file_info( v['archiveFileName'], v, 'windows')
                if v['host'] == 'x86_64-apple-darwin':
                    v['url'] = my_url + 'macosx/dslite-' + args.dslite + '-x86_64_apple-darwin.tar.bz2'
                    v['archiveFileName'] = 'dslite-' + args.dslite + '-x86_64-apple-darwin.tar.bz2'
                    update_file_info( v['archiveFileName'], v, 'macos')
                if v['host'] == 'x86_64-pc-linux-gnu':
                    v['url'] = my_url + 'linux64/dslite-' + args.dslite + '-i386-x86_64-pc-linux-gnu.tar.bz2'
                    v['archiveFileName'] = 'dslite-' + args.dslite + '-i386-x86_64-pc-linux-gnu.tar.bz2'
                    update_file_info( v['archiveFileName'], v, 'linux64')


    with open('./build/package_msp430_elf_GCC_index.json', 'w') as outfile:
        json.dump(json_data, outfile, indent=2)
    with open('./package_msp430_elf_GCC_index.json', 'w') as outfile:
        json.dump(json_data, outfile, indent=2)

