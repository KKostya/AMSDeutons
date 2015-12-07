import os
import threading
import time
import signal
import subprocess
import shutil
from periodic_thread import PeriodicThread
import pandas as pd
import numpy  as np
import glob
import inspect
import pickle

def map_reduce(globPath, mapper, reducer, varToLoad=None, maxFiles=100000, useCachedMapper=False, mask=None):
    files = glob.glob(globPath)[:maxFiles]
    if not files: print 'No file found in: '+globPath; return
    def mapperCached(f):
        if useCachedMapper is False: return mapper( read(f, varToLoad, mask))
        cachedName=inspect.getsource(mapper)+f+str(varToLoad)+str(mask)
        def funcNotInCache(fUseless):
            file=open('/tmp/customCache/'+str(cachedName.__hash__()),'w')
            pickle.dump( mapper( read(f, varToLoad, mask)),  file)
            file.close()

        file=open(fromCache( cachedName, funcNotInCache))
        ret = pickle.load( file )
        file.close()
        return ret
                   
    return reducer( map( mapperCached, files ) )


def concat(globPath, varToLoad=None, filter=None, maxFiles=100000, mask=None):
    files = glob.glob(globPath)[:maxFiles]
    
    def loadAndFilter(f):
        try:
            df=read(f,varToLoad,mask)
        except MemoryError:
            print 'MemoryError, skipping'
            raise StopIteration

        if filter is not None: return df[filter(df)]
        else : return df
    
    dfs=[]
    for f in files:
        try:
            df=loadAndFilter(f)
        except StopIteration:
            dfs.pop()
            break

        dfs.append(df)

    df = pd.concat(dfs)
    del dfs

    return df


def read(dirname,varToLoad=None, mask=None):
    print 'loading : ' + dirname
    df = dict()
    data=dict()

    varType=dict()
    if isinstance(varToLoad, basestring): varToLoad=[varToLoad]

    if varToLoad is not None: 
        varToLoad=tuple(map(lambda x: x+'_', varToLoad))
        if mask is not None and 'selStatus_' not in varToLoad:
            varToLoad = varToLoad + ('selStatus_',)

    for line in open(dirname+'/metadata.txt'):
        words=line.split()
        if words[0] in ['chunkSize', 'nVar'] or words[0][-1] is ':' : continue
        vartype=words[2][0] + words[1]
        if vartype == 'd8': vartype = 'f8'
        varType[words[0]] = vartype

    print varType
    try:
        if varToLoad is None:
            for file in os.listdir(dirname):
                if file.endswith("metadata.txt"): continue
                var=file.split('_chunk')[0]
                data[var] = np.fromfile(fromCache(dirname+'/'+file), np.dtype(varType[var]))
        else:
            for var in varToLoad:
                var=var.strip('_')
                data[var] = np.fromfile(fromCache(dirname+'/'+var+'_chunk0.bin'), np.dtype(varType[var]))
                    
    except MemoryError:
        print 'Memory error in np.fromfile, skipping next files: '+dirname
        raise

    print 'end of loading'
    
    try:
        df = pd.DataFrame(data)
    except MemoryError:
        print 'Memory error in pd.DataFrame, skipping the file: '+dirname
        raise


    if mask is not None:
        cut=makeSelectionMask(df,dirname, mask)
        df=df[cut]

    return df


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
    
def fromCache(pathname, funcNotInCache=None, useCache=True):
    if useCache is False:
        return pathname

    if not os.path.exists('/tmp/customCache'):
        os.mkdir('/tmp/customCache')

    if not os.path.exists('/tmp/customCache/'+str(pathname.__hash__())):
        #print 'not in cache'
        if funcNotInCache is None: toCache(pathname)
        else: funcNotInCache(pathname)
    
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

    cuts=None
    for l in f:
        if l[:11] != 'selStatus: ': continue
        cuts=l[11:-1].split(',')

    return cuts
    
def makeSelectionMask(df,dirname, cutList):
    cuts=getSelStatus(dirname)

    if cuts is None:
        print 'selStatus not found in '+dirname
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



