import os
import glob
import random

srcPath = "/storage/gpfs_ams/ams/Rec/2014/ISS.B950/pass6/"
dstPath = "/storage/gpfs_ams/ams/users/kostya/ntuples/"

def getn(f):
    return f.split('/')[-1].replace('.root','').replace('.ntuple','') 

patt = "1367[3-9]*"
lst = set(getn(f) for f in glob.glob(srcPath + patt))

for i in xrange(40):
    produced = set(getn(f) for f in  glob.glob(dstPath + "*"))
    lst = lst - produced

    inf = random.choice(list(lst))
    os.system("../ntupleData {1}/{0}.root -o {2}/{0}.ntuple.root".format(inf,srcPath,dstPath))

