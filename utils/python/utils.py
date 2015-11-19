import numpy  as np
import pandas as pd
import matplotlib.pyplot as plt
import sys
import os
from scipy.optimize import leastsq
import shutil
import threading
import time
import signal
import subprocess
from periodic_thread import PeriodicThread

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


def binning(df,var,nBins,firstBin,lastBin):
    binWidth=(lastBin-firstBin)/float(nBins)
    return firstBin + binWidth * (df[var]-firstBin).floordiv(binWidth)

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


def readBinary(dirname,varToLoad=None):
    print 'loading : ' + dirname
    df = dict()
    data=dict()

    varType=dict()

    try:
        for line in open(dirname+'/metadata.txt'):
            words=line.split()
            if words[0] == 'chunkSize' or words[0] == 'nVar' : continue
            varType[words[0]] = words[2][0] + words[1]

        for file in os.listdir(dirname):
            if ( varToLoad is not None and file.startswith(tuple(map(lambda x: x+'_', varToLoad)))) or ( varToLoad is None and not file.endswith("metadata.txt") ):
                var=file.split('_chunk')[0]
                data[var] = np.fromfile(fromCache(dirname+'/'+file), np.dtype(varType[var]))
                print 'data['+var+'] : '+str(len(data[var]))
                #print fromCache(dirname+'/'+file)

        print 'end of loading'
        df = pd.DataFrame(data)
    except IOError as e:
        print e
        df = pd.DataFrame()

    return df

useCache=True

def evictCache():
    print 'evicting cache...'
    oldestFiles=sorted(os.listdir('/tmp/customCache/'), key=lambda x: os.stat('/tmp/customCache/'+x).st_mtime)[:1000]
    for f in oldestFiles:
        os.remove('/tmp/customCache/'+f)
    print 'cache evicted'

def cacheThread(func):
    def checkCacheSize():
        print 'checking cache size'
        s = os.statvfs('/tmp')
        freeSpace = (s.f_bavail * s.f_frsize) / 1024
        if freeSpace < 5000000:
            evictCache()

    # signal.signal(signal.SIGINT, t.cancel())
    t = PeriodicThread(callback=checkCacheSize,period=30)
    t.start()

    return func

# @cacheThread
def toCache(pathname):
    shutil.copy(pathname, '/tmp/customCache/'+str(pathname.__hash__()))
    
def fromCache(pathname):
    if not useCache:
        return pathname

    if not os.path.exists('/tmp/customCache'):
        os.mkdir('/tmp/customCache')

    if not os.path.exists('/tmp/customCache/'+str(pathname.__hash__())):
        #print 'not in cache'
        toCache(pathname)
    
    res='/tmp/customCache/'+str(pathname.__hash__())
    if os.path.isdir(pathname): res += '/'
    # print 'name : ' + pathname
    # print 'cached name : ' + res
    return res


