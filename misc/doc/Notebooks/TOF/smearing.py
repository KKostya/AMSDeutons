import matplotlib

display=True

if not display:
    matplotlib.use('Agg')

import numpy as np
from pandas import DataFrame
import pandas as pd
import glob
import sys
import bigQueryPlotting as bq
import math
import random

sys.path.insert(0,'../../../../utils/python')

import readBinary
from utils import *
import matplotlib.pyplot as plt

import os

maxFiles={ 'MC':40, 'Data':160}

def loadBinaryOld(dirname,varToLoad=None):
    print 'loading : '
    print dirname
    data=dict()
    for file in os.listdir(dirname):
        if file.startswith(varToLoad):
            data[file.split('_chunk')[0]] = np.fromfile(dirname+'/'+file, np.dtype('float32'))

    df = DataFrame(data)
    col=[]
    for c in df.columns:
        for v in newCol:
            if c.startswith(v[0]):
                col.append( c.replace(v[0],v[1]) )

    if len(col) != len(df.columns):
        print 'wrong df.columns size !\nExit !'
        sys.exit()
    df.columns=col
    return df

def makeDataframe(files, name, varToLoad, oldLoading=False):
    if oldLoading:
        loadFunction = loadBinaryOld
    else :
        loadFunction = readBinary

    def loadAndFilter(dirname,varToLoad=None):
        df=loadFunction(dirname,varToLoad)
        df = df[(df.Time_L0 > -999) & (df.Time_L1 > -999) & (df.Time_L2 > -999) & (df.Time_L3 > -999) & (df.R < 30) & (df.R > 1) & (df.BetaTOFH > 0.5) & (df.BetaTOFH < 1.2) & (df.NTofClustersHUsed == 4) & (df.ChiQ > 0) & (df.ChiQ < 10)]
        return df

    df = pd.concat(map(lambda f: loadAndFilter(f,varToLoad), files[:maxFiles[name]]))

    df['binRgdt'] = df['R'].astype('int')
    df.index.name = name
    return df

varToLoadNew=('Time_L','R','BetaTOF','NTofClustersHUsed','ChiQ')
varToLoadOld=('time_L','R','beta','NTofClusterH')

newCol=zip(varToLoadOld,varToLoadNew)

mc  ='/afs/cern.ch/user/b/bcoste/myeos/binaryAmsData/protons.B1034_pr.pl1.1200.qgsp_bic_ams_noSmearing/*.00000001.output'
data='/afs/cern.ch/user/b/bcoste/myeos/binaryAmsData/ISS.B950_pass6_allVariables/*.00000001.output'

if len(sys.argv) > 1:
    mc = '/afs/cern.ch/user/b/bcoste/myeos/binaryAmsData/smearingMinus'+sys.argv[1]+'/*.00000001.output'
    print mc

filesMC   = glob.glob(mc)
filesData = glob.glob(data)

random.shuffle(filesMC)
random.shuffle(filesData)

dfMC   = makeDataframe( filesMC, "MC", varToLoadNew)
dfData = makeDataframe( filesData, "Data", varToLoadNew)

#Old school
# dfMC   = makeDataframe( glob.glob('/afs/cern.ch/user/b/bcoste/myeos/dstTofTiming/protons.B1034_pr.pl1.1200.qgsp_bic_ams/*.00000001.output'),  "MC",varToLoadOld,oldLoading=True)
# dfData = makeDataframe( glob.glob('/afs/cern.ch/user/b/bcoste/myeos/dstTofTiming/ISS.B950_pass6/*.00000001.output'), "Data" , varToLoadOld , oldLoading=True)

print 'data : '+data
print 'mc : '+mc

def binning(df,var,nBins,firstBin,lastBin):
    binWidth=(lastBin-firstBin)/nBins
    return firstBin + binWidth * (df[var]-firstBin).floordiv(binWidth)

def plotDataFrame2D(df,nBinsX,firstBinX,lastBinX,nBinsY,firstBinY,lastBinY,varX,varY):
    binX='bin_'+varX
    binY='bin_'+varY
    dfTmp=pd.DataFrame(df[[varX,varY]])
    dfTmp[binX]=binning(dfTmp,varX,nBinsX,firstBinX,lastBinX)
    dfTmp[binY]=binning(dfTmp,varY,nBinsY,firstBinY,lastBinY)
    dfTmp=dfTmp[(dfTmp[binX] >= firstBinX) & (dfTmp[binX] < lastBinX) & (dfTmp[binY] >= firstBinY) & (dfTmp[binY] < lastBinY) ]
    plot_matrix( dfTmp.groupby([binY,binX]).count()[varX].unstack().fillna(0) )

for df in [dfData,dfMC]:
    print df.index.name
    df['invBetaH']=1/df.BetaTOFH
    # df['Time_L3-Time_L0']=df['Time_L3']-df['Time_L0']
    # df['Time_L1-Time_L0']=df['Time_L1']-df['Time_L0']
    # df['Time_L3-Time_L1']=df['Time_L3']-df['Time_L1']
    # df['Time_L3-Time_L2']=df['Time_L3']-df['Time_L2']


def makeHistAndFit(data,init,hist_range,ylimit,widthSecondFit,funcFit=None,**kwargs):
    if funcFit is None: funcFit=gaussian
    if len(data):
        n, bins, patches = plt.hist(data,normed=True,range=hist_range,bins=100,histtype='step',linewidth=2.0,**kwargs)
        plt.ylim(ylimit)
        xdata, ydata = ((bins[:-1] + bins[1:])*0.5,n)
        out = fit(funcFit,xdata,ydata,init)
        if len(out[0]) > 2:
            x,y = zip(*filter(lambda x: -math.fabs(out[0][2])*widthSecondFit < x[0]-out[0][1] < math.fabs(out[0][2])*widthSecondFit,zip(xdata,ydata)))
            out = fit(funcFit,x,y,out[0])
            plt.plot(x,funcFit(out[0],x),linewidth=2.0)
        else : plt.plot(xdata,funcFit(out[0],xdata),linewidth=2.0)
        return out[0]
    return (-1,-1)

def fitAllRigBin(data,var,rigBins,init,hist_range,ylimit,widthSecondFit,**kwargs):
    par = []
    for i in range(len(rigBins[:-1])):
        name=var + 'distribution - rigidity : ['+str(rigBins[i])+','+str(rigBins[i+1])+']'
        if display:
            plt.figure(name)
            plt.title(name)
        par.append( makeHistAndFit( df[(df['R']>=rigBins[i]) & (df['R']<rigBins[i+1])][var].values, init, hist_range,ylimit,widthSecondFit,**kwargs) )
    return par


mean = dict()
std = dict()

variables={}
rigBins=np.linspace(2,29,40)
print rigBins

variables['BetaTOFH']=([9.0, 0.95, 0.05], (0.8, 1.1), (0,12), 1)
# variables['BetaTOF'] =([9.0, 0.95, 0.05], (0.8, 1.1), (0,12), 1)
# variables['Time_L3-Time_L0']=([1.0, 6.0, 1.0], (4,7),(0,1), 1)
# variables['Time_L3-Time_L1']=([1.0, 6.0, 1.0], (4,7),(0,1), 1)
# variables['Time_L3-Time_L2']=([1.0, 0, 0.5], (-1,1),(0,2), 1.5)
# variables['Time_L1-Time_L0']=([1.0, 0, 0.5], (-1,1),(0,2), 1.5)


for var in variables:
    mean[var]=dict()
    std[var]=dict()

for df in [dfData,dfMC]:
    for var in variables:
        scale,mean[var][df.index.name],std[var][df.index.name]=zip(* fitAllRigBin(df,var,rigBins,*variables[var]) )    


canvasMean={ 'Time_L3-Time_L0':(0.99,1.03),
             'Time_L3-Time_L2':(0.80,1.10),
             'Time_L3-Time_L1':(0.98,1.03),
             'Time_L1-Time_L0':(0.70,1.10),
             'BetaTOFH':          (0.98,1.01),
             'BetaTOF':           (0.98,1.01)}

canvasStd={ 'Time_L3-Time_L0':(0.80,1.30),
            'Time_L3-Time_L2':(0.80,1.10),
            'Time_L3-Time_L1':(0.85,1.30),
            'Time_L1-Time_L0':(0.80,1.10),
            'BetaTOFH':       (0.80,1.40),
            'BetaTOF':        (0.80,1.40)}

for var in variables:
    print var
    plt.figure(figsize=(10,10))
    plt.subplot(221)
    ratioMean=[x/y for x,y in zip(mean[var]['Data'],mean[var]['MC'])]

    plt.title('Mean '+ var + ': ratio Data/MC')
    plt.plot(rigBins[:-1],ratioMean,'o')
    plt.plot((rigBins[0],rigBins[-1]),(1,1))
    plt.ylim(canvasMean[var])

    plt.subplot(222)
    ratioStd=[x/y for x,y in zip(std[var]['Data'],std[var]['MC'])]
    plt.title('Standard deviation '+ var + ': ratio Data/MC')
    plt.plot(rigBins[:-1],ratioStd,'o')
    plt.plot((rigBins[0],rigBins[-1]),(1,1))
    plt.ylim(canvasStd[var])
    if(len(sys.argv) > 1): plt.savefig(var+'_smearingMinus'+sys.argv[1]+'.png')
    else: plt.savefig(var+'_noSmearing.png')

# plt.figure()    
# plt.plot(rigBins[:-1],[x-y for x,y in zip(std['Time_L1-Time_L0']['Data'],std['Time_L1-Time_L0']['MC'])],'o')
# plt.plot(rigBins[:-1],[x-y for x,y in zip(std['Time_L3-Time_L2']['Data'],std['Time_L3-Time_L2']['MC'])],'o')

if display:
    plt.show()
