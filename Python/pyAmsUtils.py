import ROOT
import pandas as pd
import numpy as np

def tree_to_frame(tree):
    
    N = tree.GetEntries()
    varNames = [b.GetName() for b in tree.GetListOfBranches() if  b.ClassName() == "TBranch"]
    arrNames = [b.GetName() for b in tree.GetListOfBranches() if  b.ClassName() == "TBranchElement"]
    
    vs = { v:np.zeros(N) for v in varNames }
    for j in xrange(N):
        tree.GetEntry(j)
        for v in varNames: vs[v][j] = getattr(tree,v)
        for v in arrNames: 
            for i in xrange(getattr(tree,v).size()):
                name = "{0}[{1}]".format(v,i)
                if name not in vs: vs[name] = np.zeros(N)
                vs[name][j] = getattr(tree,v)[i]
                
    return pd.DataFrame(vs)
