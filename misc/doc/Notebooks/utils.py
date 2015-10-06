import numpy  as np
import pandas as pd
import matplotlib.pyplot as plt

try:
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
except:
    print 'import failed'
    pass

def config_plots(rcParams):
    rcParams['savefig.dpi'] = 100
    rcParams['figure.facecolor'] = (1,1,1,1)
    rcParams['savefig.facecolor'] = (1,1,1,1)
    
def plot_matrix(frame, xInf=None,yInf=None,xSup=None,ySup=None, **args):
    from matplotlib.colors import LogNorm
    x,y = np.meshgrid(np.array(frame.index,   dtype=float),
                      np.array(frame.columns, dtype=float))
    z = frame.T.values.astype(float)
    ret = plt.gca().pcolor(y,x,z, **args)
    if xInf is None:
        xInf=frame.columns[0]
    if xSup is None:
        xSup=frame.columns[-1]
    if yInf is None:
        yInf=frame.index[0]
    if ySup is None:
        ySup=frame.index[-1]
        
    
    plt.xlim(xInf,xSup)
    plt.ylim(yInf,ySup)
    
    return ret
