import numpy as np
from pandas import DataFrame
import matplotlib.pyplot as plt
import os

def read(dirname):
    df = dict()
    data=dict()

    varType=dict()
    for line in open(dirname+'/metadata.txt'):
        words=line.split()
        if words[0] == 'chunkSize' or words[0] == 'nVar' : continue
        varType[words[0]] = words[2][0] + words[1]

    # print varType
    # import sys
    # sys.exit()
    for file in os.listdir(dirname):
        if not file.endswith("metadata.txt"):
            var=file.split('_chunk')[0]
            data[var] = np.fromfile(dirname+'/'+file, np.dtype(varType[var]))

    df = DataFrame(data)

    return df


