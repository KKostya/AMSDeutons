import numpy  as np
import pandas as pd
import matplotlib.pyplot as plt
import sys
import os
from scipy.optimize import leastsq

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
except ImportError:
    print 'ROOT or root_numpy import failed'
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


def binIndex(df,var,bins,firstBin=None,lastBin=None):
    if isinstance(bins,int):
        if firstBin is None or lastBin is None:
            print 'firstBin and lastBin must be set !'; return
        binWidth=(lastBin-firstBin)/float(bins)
        return (df[var]-firstBin).floordiv(binWidth)
    else:
        return pd.cut(df[var], bins, labels=False, include_lowest=True, right=False).fillna(-1)

def binning(df,var,nBins,firstBin,lastBin):
    binWidth=(lastBin-firstBin)/float(nBins)
    return firstBin + binWidth * binIndex(df,var,nBins,firstBin,lastBin)

def plotDataFrame2D(df,nBinsX,firstBinX,lastBinX,nBinsY,firstBinY,lastBinY,varX,varY):
    # Plot a 2D histogram of varX vs varY
    binX='bin_'+varX
    binY='bin_'+varY
    dfTmp=pd.DataFrame(df[[varX,varY]])
    dfTmp=dfTmp[(dfTmp[varX] >= firstBinX) & (dfTmp[varX] < lastBinX) & (dfTmp[varY] >= firstBinY) & (dfTmp[varY] < lastBinY) ]
    dfTmp[binX]=binning(dfTmp,varX,nBinsX,firstBinX,lastBinX)
    dfTmp[binY]=binning(dfTmp,varY,nBinsY,firstBinY,lastBinY)
#    print dfTmp
    return plot_matrix( dfTmp.groupby([binY,binX]).count()[varX].unstack().fillna(0) )


gaussian = lambda par, x: par[0]*np.exp(-0.5*((x-par[1])/par[2])**2)

def fit(fitfunc,xdata,ydata,init):
    errfunc  = lambda par, x, y: (y - fitfunc(par, x))
    return leastsq( errfunc, init, args=(xdata, ydata))

