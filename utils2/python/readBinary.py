import numpy as np
from pandas import DataFrame
import matplotlib.pyplot as plt
import os

def readBinary(dirname,varToLoad=None):
    df = dict()
    data=dict()

    varType=dict()

    for line in open(dirname+'/metadata.txt'):
        words=line.split()
        if words[0] == 'chunkSize' or words[0] == 'nVar' : continue
        varType[words[0]] = words[2][0] + words[1]

    for file in os.listdir(dirname):
        if ( varToLoad is not None and file.startswith(varToLoad)) or ( varToLoad is None and not file.endswith("metadata.txt") ):
            var=file.split('_chunk')[0]
            data[var] = np.fromfile(dirname+'/'+file, np.dtype(varType[var]))
            print var

    df = DataFrame(data)

    return df


