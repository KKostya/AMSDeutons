import numpy as np
from pandas import DataFrame
import matplotlib.pyplot as plt

import os
dirname='/afs/cern.ch/user/b/bcoste/myeos/dstTofTiming/test7/1208399660.00000001.output'
#dirname = 'protonB800'
df = dict()
data=dict()
for file in os.listdir(dirname):
    if not file.endswith("metadata.txt"):
        data[file.split('_chunk')[0]] = np.fromfile(dirname+'/'+file, np.dtype('float32'))

df = DataFrame(data)

print df.columns

