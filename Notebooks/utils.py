import numpy  as np
import pandas as pd
import ROOT
import root_numpy

def get_data(filename="~/AMSDeutons/test.root", treename="data"):
    """ Converts a ROOT tree to a pandas dataframe. Unwraps vectors."""
    tfile = ROOT.TFile(filename)
    
    tree = tfile.Get(treename)
    data = root_numpy.tree2rec(tree)
    data = pd.DataFrame(data)
    row = data.ix[0]
    
    for c, t in data.dtypes.iteritems():
        if c == "fStatus": continue
        if not t == np.object: continue
        for i in range(len(row[c])):
            newc = "{0}_{1}".format(c,i)
            data[newc] = data[c].str.get(i)
        del data[c]
        
    return data 

def config_plots(rcParams):
    rcParams['savefig.dpi'] = 100
    rcParams['figure.facecolor'] = (1,1,1,1)
    rcParams['savefig.facecolor'] = (1,1,1,1)