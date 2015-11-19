import os
import threading
import time
import signal
import subprocess
import shutil
from periodic_thread import PeriodicThread
import pandas as pd
import numpy  as np

def read(dirname,varToLoad=None, cutList=None):
    print 'loading : ' + dirname
    df = dict()
    data=dict()

    varType=dict()
    
    if isinstance(varToLoad, basestring): 
        tmp=varToLoad
        varToLoad=[tmp]

    if varToLoad is not None: 
        varToLoad=tuple(map(lambda x: x+'_', varToLoad))
        if cutList is not None and 'selStatus_' not in varToLoad:
            varToLoad = varToLoad + ('selStatus_',)

    try:
        for line in open(dirname+'/metadata.txt'):
            words=line.split()
            if words[0] in ['chunkSize', 'nVar', 'selStatus:'] : continue
            varType[words[0]] = words[2][0] + words[1]

        for file in os.listdir(dirname):
            if ( varToLoad is not None and file.startswith(varToLoad)) or ( varToLoad is None and not file.endswith("metadata.txt") ):
                var=file.split('_chunk')[0]
                data[var] = np.fromfile(fromCache(dirname+'/'+file), np.dtype(varType[var]))
                #print 'data['+var+'] : '+str(len(data[var]))
                #print fromCache(dirname+'/'+file)

        print 'end of loading'
        df = pd.DataFrame(data)
    except IOError as e:
        print e
        df = pd.DataFrame()

    if cutList is not None:
        cut=makeSelectionMask(df,dirname, cutList)
        df=df[cut]

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


def getSelStatus(dirname):
    metadataFile=dirname+'/metadata.txt'
    try:
        f=open(metadataFile)
    except IOError:
        print 'Could not open file: '+metadataFile
        return None

    for l in f:
        if l[:11] != 'selStatus: ': continue
        cuts=l[11:-1].split(',')

    return cuts
    
def makeSelectionMask(df,dirname, cutList):
    cuts=getSelStatus(dirname)

    if cuts is None:
        print 'selStatus not found in '+metadataFile
        return None

    bitIndex=dict()
    for index in range(len(cuts)):
        bitIndex[cuts[index]]=index

    selMask=0 # has a 1 for every bit that has to be checked
    statusMask=0 # take the bit value for every bit that has to be checked
    for cut in cutList:
        val=1
        if cut[0]=='!':
            val=0
            cut=cut[1:]

        if cut in bitIndex:
            selMask+=1<<bitIndex[cut]
            statusMask+=val<<bitIndex[cut]
        else:
            print 'Cut ' + cut + ' not found !'
            return None

        
    return  (df.selStatus^statusMask)&selMask==0



