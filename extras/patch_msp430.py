import os
import sys
import datetime
import zipfile
import shutil
import argparse

sys.path.append('common/')

def main():
    workPath = os.getcwd()
    
    
    # Read command line parameters
    # Initialisieren des parsers und setzen des Hilfetextes
    parser = argparse.ArgumentParser(description='')
    parser.add_argument('-d', '--patch', default='patch_fr5994.zip',
                    help='Required: patch file')
    parser.add_argument('-p', '--path', default='extras/build/windows/',
                    help='Required: path to destination')
    args = parser.parse_args()
    
    patch=args.patch
    device=patch.replace("patch_","").replace(".zip","")

    try:
        import zlib
        compression = zipfile.ZIP_DEFLATED
    except:
        compression = zipfile.ZIP_STORED


    os.chdir(args.path)
    

    patch_msp430spec(device);
    patch_msp430_h(device);
    
    zf = zipfile.ZipFile('../../patches/' + patch, mode='r')
    zf.extractall() 
    #zf.printdir()
    zf.close()
    
    os.chdir(workPath)

    return 0


def patch_msp430_h(Device):
    f = open("msp430/include/msp430.h",'r')
    filedata = f.read()
    f.close()

    if filedata.find(Device) == -1: # not found
        search1  = "#include \"msp430fr5969.h\"";
        replace1 = "\n\n#elif defined (__MSP430" + Device.upper() + "__)\n#include \"msp430" + Device + ".h\"";
        filedata = filedata.replace(search1,search1+replace1)

        f = open("msp430/include/msp430.h",'w')
        f.write(filedata)
        f.close()
        

def patch_msp430spec(Device):
    f = open("msp430/lib/msp430mcu.spec",'r')
    filedata = f.read()
    f.close()

    if filedata.find(Device) == -1: # not found
        search1  = " mmcu=msp430fr5969|mmcu=msp430fr5969_*:-mivcnt=64;";
        replace1 = " mmcu=msp430" + Device + "|mmcu=msp430" + Device + "_*:-mivcnt=64;";
        search2  = " mmcu=msp430fr5969|mmcu=msp430fr5969_*:-mcpu=430xv2;";
        replace2 = " mmcu=msp430" + Device + "|mmcu=msp430" + Device + "_*:-mcpu=430xv2;";
        search3  = " mmcu=msp430fr5969|mmcu=msp430fr5969_*:-mmpy=32dw;";
        replace3 = " mmcu=msp430" + Device + "|mmcu=msp430" + Device + "_*:-mmpy=32dw;";
        filedata = filedata.replace(search1,search1+replace1)
        filedata = filedata.replace(search2,search2+replace2)
        filedata = filedata.replace(search3,search3+replace3)

        f = open("msp430/lib/msp430mcu.spec",'w')
        f.write(filedata)
        f.close()



if __name__ == '__main__':
    main()
