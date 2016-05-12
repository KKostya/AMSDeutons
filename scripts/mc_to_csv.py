import argparse                                                                                                       
import glob
import os.path
import numpy as np
import pandas as pd
                  
def dump_binaries_as_csv(dirtoload, step=100000, ext="_chunk0.bin"):
                                                                   
    def opseek(name, start):
        f = open(os.path.join(dirtoload, name) + ext, "rb")
        f.seek(start)
        return f

    variables, nVar = [], 0
    for line in open(os.path.join(dirtoload, "metadata.txt")):
        words = line.split()
        
        if words[0] == 'nVar:':
            nVar = int(words[1])
            continue
            
        if words[0].startswith("Distance"  ): continue 
        if words[0].startswith("MLRigidity"): continue 
        if words[0].startswith("Livetime"  ): continue 
        if words[0].startswith("ThetaS"    ): continue 
        if words[0].startswith("PhiS"      ): continue 
        if words[0].startswith("Latitude"  ): continue 
        if words[0].startswith("Rcutoff"   ): continue 
        if words[0].startswith("GenCoo2"   ): continue 

        if words[0] in ['chunkSize:', 'selStatus:', "gitversion:", "gitversion:"]: 
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
        print frame.to_csv(),
        
    return varOrder

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Read a MC directory and dump it to stdout")
    parser.add_argument('--in_directory', dest='indir', help='Input directory.')
    args = parser.parse_args()            

    # Learning how many chunks are there
    nchunks = len(glob.glob(os.path.join(args.indir,"Run*.bin")))
    for i in range(nchunks):
        varNames = dump_binaries_as_csv(args.indir, ext="_chunk{0}.bin".format(i))

