import ROOT
import pandas as pd
import numpy as np

def tree_to_frame(tree, verbose=False):
    
    N = tree.GetEntries()
    blist = [b for b in tree.GetListOfBranches() if tree.GetBranchStatus(b.GetName())]
    varNames = [b.GetName() for b in tree.GetListOfBranches() if  b.ClassName() == "TBranch"]
    arrNames = [b.GetName() for b in tree.GetListOfBranches() if  b.ClassName() == "TBranchElement"]
   
    if verbose:
        print 'Scalars: ' + ', '.join(varNames) 
        print 'Vectors: ' + ', '.join(arNames) 
    vs = { v:np.zeros(N) for v in varNames }
    for j in xrange(N):
        tree.GetEntry(j)
        for v in varNames: vs[v][j] = getattr(tree,v)
        for v in arrNames: 
            for i in xrange(getattr(tree,v).size()):
                name = "{0}[{1}]".format(v,i)
                if name not in vs: vs[name] = np.zeros(N)
                vs[name][j] = getattr(tree,v)[i]
        if verbose and j%10000 == 0:
            print j
                
    return pd.DataFrame(vs)
