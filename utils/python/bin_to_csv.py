import argparse
import os.path
import glob
import numpy as np 
import pandas as pd
import glob

#homePath  = "/afs/cern.ch/user/k/kostams/eos"
#eosBenoit = "ams/user/b/bcoste"
#binaryDirs = glob.glob(
#    os.path.join(homePath, eosBenoit, "binaryAmsData/newISS.B950", "*")
#)

def dump_binaries_as_csv(dirtoload, step=100000, ext="_chunk0.bin"):
        
    def opseek(name, start):
        f = open(os.path.join(dirtoload, name) + ext, "rb")
        f.seek(start)
        return f

    variables, nVar = [], 0
    for line in open(os.path.join(dirtoload, "metadata.txt")):
        words = line.split()
        
        if words[0] == 'nVar':
            nVar = int(words[1])
            continue
            
        if words[0][-1] == ':': 
            continue
            
        varName, tsize, tname  = words[0], int(words[1]), words[2][0]
        if tname == 'd': tname = 'f'
        variables.append((varName, tsize, tname))
        
    # Checking stuff
    
    # ? that shit fails
    #if len(variables) != nVar: 
    #    raise RuntimeError("Number".format(vname+ext))
        
    nentries = None
    for vname, vsize, _ in variables:
        size = os.path.getsize(os.path.join(dirtoload, vname) + ext)
        if nentries is None: 
            nentries = size / vsize
            continue
        if nentries != size / vsize:
            raise RuntimeError("Inconsistency in \"{0}\"".format(vname+ext))
        
    for start in xrange(0, nentries, step):
        stop = start + step if start + step < nentries else nentries

        dataDict, varOrder = {}, []
        for vname, vsize, vtype in variables:
            varOrder.append(vname)
            with opseek(vname, int(vsize) * start) as inFile:
                dataDict[vname] = np.fromfile(
                    inFile, count=stop - start,
                    dtype=np.dtype(vtype + str(vsize))
                )

        frame = pd.DataFrame(dataDict)[varOrder]
        print frame.to_csv(header=False),
        
    return varOrder

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Read a directory and dump it to stdout. Piping stdout to gzip is highly advised. "
    )
    parser.add_argument('--in_directory', dest='indir', help='Input directory.')
    args = parser.parse_args()            

    # Learning how many chunks are there
    nchunks = len(glob.glob(os.path.join(args.indir,"Run*.bin")))
    for i in range(nchunks):
        varNames = dump_binaries_as_csv(args.indir, ext="_chunk{0}.bin".format(i))
    with open("bins.txt","w") as binFile:
        binFile.write(','.join(varNames))
