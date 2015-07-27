import os
import sys
import glob
import gzip
import pandas as pd
import ROOT
import root_numpy

lockdir = "/afs/cern.ch/user/k/kostams/temp/"
workdir = "/afs/cern.ch/user/k/kostams/eos/ams/user/k/kostams/DeuteronNtuples/month/"
filenames = sorted(glob.glob(workdir + "*.ntuple.root"))

def steps(N,n):
    current = 0
    while current < N:
        yield current, current+n
        current += n
        
def makeframe(dnumpy):
    frame = pd.DataFrame()
    for i in dnumpy.dtype.names:
        frame[i] = dnumpy[i]
        
    # This is an ugly hack for the buggy ntuplizer 
    fixdic = {
        'R_': (6,12),
        'chiq': (6,12),
        'ResiduiX': (6,13),
        'ResiduiY': (6,13),
        'EdepTOF': (0,4)
    } 
    
    for v,(a,b) in fixdic.iteritems():    
        for x in range(a,b):
            frame[v+'_'+str(x-a)] = frame[v].map(
                lambda ar: 0 if len(ar) < abs(x-b) else ar[x-b]
            )
        del frame[v]  
        
    return frame
    
    
    
for n,(i,j) in enumerate(steps(len(filenames),5)):
    
    outfname = "may2013." + str(n) + ".csv.gz" 
    print "Current target is " + outfname
    if os.path.exists(lockdir + outfname):
        print " already exists skipping."
        continue
    os.system("touch " + lockdir + outfname)

    with gzip.open(outfname, 'w') as csvOut:
        firstWrite = True
        for filename in filenames[i:j]:
            print "Reading " + filename.split('/')[-1]
            sys.stdout.flush()
            f = ROOT.TFile(filename)
            if f.IsZombie(): continue
            tree = f.Get("data")
            frame = makeframe(root_numpy.tree2rec(tree))
            print "Writing " + str(len(frame)) + " rows into " + outfname + " ... ",
            sys.stdout.flush()
            frame.to_csv(csvOut, header=firstWrite)  
            firstWrite = False
            print " done."
            sys.stdout.flush()
    
    print "Copying " + outfname + " ...",
    sys.stdout.flush()
    os.system("\cp " + outfname + " " + workdir)
    print " done."
    
    if os.path.exists(workdir + outfname) and os.path.getsize(workdir + outfname) > 0:
        print "Cleanup ...",
        sys.stdout.flush()
        os.system("rm -rf " + outfname)
        print " done."
