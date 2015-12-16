import argparse
import json
import gzip

import numpy as np
import pandas as pd

def get_series(dct):
    f = pd.DataFrame(dct)
    cidx = ["invBetaMeasured", "invRgdtMeasured", "invBetaTheoretic"]
    return f.set_index(cidx)['count'].sort_index()


def update_bins(series, bins):
    edges = [ np.append(-1, bins[k]) for k in series.index.names ]
    newIndex = pd.MultiIndex.from_product( edges, names=series.index.names)
    return series.reindex(newIndex).fillna(0).sort_index()


class JSONEncoder(json.JSONEncoder):
    def default(self, obj):
        if hasattr(obj, 'to_json'):
            return obj.to_json()
        return json.JSONEncoder.default(self, obj)


def get_kernel(fDT, fMC, N, R, tau):
   
    aMC   = fMC.unstack().sum(axis=1).unstack().iloc[1:,N].fillna(0).values
    aData = fDT.unstack().sum(axis=1).unstack().iloc[1:,N].fillna(0).values
    aMC   /= aMC.sum()
    aData /= aData.sum() 
    
    # Build upper half of the matrix
    i,j = np.indices(aMC.shape*2)
    M = np.array([ (i==j+dh).astype(int).dot(aMC) for dh in range(-R+1,R+1)]).T

    # Build lower half "cost" matrix
    C = np.zeros((2*R,2*R))
    C[(np.arange(0,2*R),  np.arange(0,2*R  ))]=-2
    C[(np.arange(1,2*R),  np.arange(0,2*R-1))]=1
    C[(np.arange(0,2*R-1),np.arange(1,2*R  ))]=1

    # Combine and SVD
    M = np.concatenate([M, tau * C])
    lft, lmbda, rght = np.linalg.svd(M)
    
    # Extract the solution
    rhs = np.concatenate([aData, np.zeros((2*R,))])
    kernel = rght.T.dot(lft.T.dot(rhs)[:2*R]/lmbda)
    return kernel 



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="")
    parser.add_argument('--frames_json', dest='frames_json', default="frames.json",   
                        help='Input json file with frames in it.')
    parser.add_argument('--data_frame', dest='data_frame', default="Data",   
                        help='Name of the data frame in the \"frames_json\" file')
    parser.add_argument('--mc_frame', dest='mc_frame', default="B1034",   
                        help='Name of the MC frame in the \"mc_json\" file')
    parser.add_argument('--smear', dest='to_smear', nargs='+', default=[],   
                        help='A list of frames to smear with the extracted kernel.')
    parser.add_argument('--out_json',  dest= 'out_json', default="smearing.json",  
                        help='Output json with convolution kernel and the smeared MC in it.')
    parser.add_argument('--gzip',      dest='gzip', action='store_true', help='Use GZIP for input and output files.')
    parser.set_defaults(gzip=False)
    args = parser.parse_args()

    # Processing arguments
    if not args.to_smear: 
        args.to_smear = [args.mc_frame]
    
    opf = open
    if args.gzip: 
        opf = gzip.open
        args.out_json += '.gz'
        
    # Parameters 
    N = 2
    R = 50
    tau = 0.01
    cutoff = 1e-6

    print "The algorithm parameters:"
    print " - N(invRigidity) bin = {0}".format(N)
    print " - number of kernel bins= {0}".format(2*R)
    print " - second derivative penalty = {0}".format(tau)
    print " - smearing cutoff = {0}".format(cutoff)
    
    print "Reading the frames from \"{0}\"".format(args.frames_json)
    with opf(args.frames_json, 'r') as infile:
        data = json.load(infile)
    frames, binnings = data['frames'], data['bins'] 
    
    seriesData = get_series(frames[args.data_frame])
    seriesMC   = get_series(frames[args.mc_frame  ])
        
    seriesData = update_bins(seriesData, binnings)
    seriesMC   = update_bins(seriesMC,   binnings)
    
    print "Running SVD extraction on frames Data={0} and MC={1}".format(args.data_frame, args.mc_frame)
    ker = get_kernel(seriesData, seriesMC, N, R, tau)
   
    def f(x): 
        return np.convolve(x.values, ker, mode='same')

    smeared = {}
    for to_smear in args.to_smear:
        print "Preparing the \"{0}\" frame for smearing".format(to_smear)
        frame = get_series(frames[to_smear]) 
        frame = update_bins(frame, binnings)
        print "Smearing the \"{0}\" frame with the extracted kernel".format(to_smear)
        frame = frame.unstack(['invBetaTheoretic','invRgdtMeasured'])
        frame = frame.iloc[1:].apply(f).stack([1,0])
        frame = frame[frame > cutoff*frame.max()]
        frame.name = 'count'
        smeared["smeared_" + to_smear] = frame.reset_index().to_dict()

    print "Saving the frames to " +  args.out_json
    data = { "bins":binnings, "kernel":list(ker) ,"frames": smeared }
    with opf(args.out_json, 'w') as outFile:
        json.dump(data, outFile, cls=JSONEncoder)
    
