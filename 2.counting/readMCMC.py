import pandas as pd
import glob
import matplotlib.pyplot as plt
import numpy as np
import struct

plot=False

def main(binningRgdtTheoretic):
    directory = "2.counting/mcmc/latestMCMC/"
    files = sorted( glob.glob(directory + "par*.bin"), 
                    key=lambda x:int(x.split("/")[-1][3:].split('_')[0]))

    bins = np.array(binningRgdtTheoretic)

    data = {}
    for fname in files:
        with open(fname, "rb") as f: 
            size = int(struct.unpack('<i', f.read(4))[0])
            data[fname] = np.fromfile(f,np.float32)
    data = pd.DataFrame(data)[files]

    dataP = data.iloc[:,:len(data.columns)/2]
    dataP.columns = bins[:-1]

    dataD = data.iloc[:,len(data.columns)/2:]
    dataD.columns = bins[:-1]

    data.iloc[::1000].plot(legend=False)
    
    if plot:
        plt.subplot(121)
        dataP.boxplot();
        plt.xticks(rotation='vertical')
        plt.ylim(0,40000)
        plt.subplot(122)
        dataD.boxplot();
        plt.xticks(rotation='vertical')
        plt.ylim(0,40000)
        plt.show()

    return dataP, dataD
    
