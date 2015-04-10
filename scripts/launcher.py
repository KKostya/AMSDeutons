import os
import glob
import random

srcPath = "/storage/gpfs_ams/ams/Rec/2014/ISS.B950/pass6/"
dstPath = "/storage/gpfs_ams/ams/users/kostya/ntuples/"


lst = glob.glob(srcPath + "*")

for i in xrange(40):
    inf = random.choice(lst)
    outf = inf.split('/')[-1]
    outf = dstPath + '.'.join(outf.split('.')[:-1]) + ".ntuple.root"

    os.system("./ntupleData {0} -o {1}".format(inf,outf))

