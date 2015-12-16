import argparse
import json
import gzip

import numpy as np
import pandas as pd
from scipy.optimize import curve_fit


def gauss(x,N,mu,sigma):
    return N*np.exp(-(x-mu)**2/(2*sigma**2))/(sigma*np.sqrt(2*np.pi))

 
def gauss_fit(frame):
    x,y = np.array(frame.index), frame.values
    x,y = np.nan_to_num(x), np.nan_to_num(y)
    if not len(x): return np.zeros(6)
    
    p0 = [ y.sum()*(x[1]-x[0]),
           (x*y).sum()/y.sum(),
           np.sqrt(((x**2)*y).sum()/y.sum() - ((x*y).sum()/y.sum())**2)
         ]
    try:
        p, pcov = curve_fit(gauss, x, y, p0=p0, sigma=1/np.sqrt(y))
    except:
        return np.array(p0 + [0,0,0])
    perr = np.sqrt(np.diag(pcov))
    return np.concatenate([p, perr])


def gauss_refit(frame): 
    ret = gauss_fit(frame)    
    N, mu, sigma, _,_,_ = ret
    if not N: return [0]*6
    return gauss_fit(frame[mu-2*sigma:mu+2*sigma])
    

def resolution_frame(frame):
    frame = frame.unstack().sum(axis=1) # This unstacks TrueB column
    frame = frame.unstack().iloc[1:,1:] # This removes overflow bin
    res = pd.DataFrame({c:gauss_refit(frame[c]) for c in frame.columns}).T
    res.columns = ["N","mu","sigma","err_N","err_mu","err_sigma"]
    res.index.name = frame.columns.name
    return res.reset_index() 


def get_series(dct):
    f = pd.DataFrame(dct)
    cidx = ["invBetaMeasured", "invRgdtMeasured", "invBetaTheoretic"]
    return f.set_index(cidx)['count'].sort_index()


class JSONEncoder(json.JSONEncoder):
    def default(self, obj):
        if hasattr(obj, 'to_json'):
            return obj.to_json()
        return json.JSONEncoder.default(self, obj)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Extract resolutions from dataframes stored in json")
    parser.add_argument('--frames_json', dest='frames_json', default="frames.json",   help='Input json file with frames in it.')
    parser.add_argument('--out_json',  dest= 'out_json', default="resolutions.json", help='Output json with fitted resolutions.')
    parser.add_argument('--gzip',      dest='gzip', action='store_true', help='Use GZIP for input and output files.')
    parser.set_defaults(gzip=False)
    args = parser.parse_args()
    
    opf = open
    if args.gzip: 
        opf = gzip.open
        args.out_json += '.gz'

    print "Reading the frames from \"{0}\"".format(args.frames_json)
    with opf(args.frames_json, 'r') as infile:
        data = json.load(infile)
    
    frames = data["frames"]
    B1034 = get_series(frames["B1034"])
    B800  = get_series(frames["B800" ])
    Data  = get_series(frames["Data" ])
    Deut  = get_series(frames["Deut" ]) 
    
    print "Running the fits..."
    resolutionData = {
        "B1034": resolution_frame(B1034).to_dict(),
         "B800": resolution_frame( B800).to_dict(),         
         "Deut": resolution_frame( Deut).to_dict(),
         "Data": resolution_frame( Data).to_dict()
    }    
        
    print "Saving the fit data into \"{0}\"...".format(args.out_json)
        
    with opf(args.out_json,"w") as f:
        json.dump(resolutionData, f, cls=JSONEncoder)
        