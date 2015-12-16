import itertools
import argparse
import json
import gzip

import numpy as np
import pandas as pd

def iterpairs(l):
    i1,i2 = itertools.tee(l); next(i2)
    return((x1,x2) for x1,x2 in itertools.izip(i1,i2))


def build_case_string(var, name, bins):
    casestr = ["CASE"]
    casestr += ["  WHEN {1} < {0} AND {0} < {2} THEN {3}".format(var,s,e,n)
                 for n,(s,e)  in enumerate(iterpairs(bins))]
    casestr += ["  ELSE -1",  "END as {0}".format(name)]
    return '\n'.join(casestr)


def get_hist_series(table, varList, overflow=True, selection=None):
    if selection is None:
        selection = "INTEGER(selStatus)&2097151=2097151"
    
    variables = ",\n".join([ build_case_string(*var) for var in varList] + ["COUNT(1) as count"])
    groupers =  ','.join([var[1] for var in varList])

    h = """SELECT {1} FROM {0} WHERE {3}
    GROUP BY {2} ORDER BY {2}""".format(table, variables, groupers, selection)

    # Making the request 
    frame = pd.read_gbq(h,'ams-test-kostya')
    
    if not overflow:
        for __, v, __ in varList:
            frame = frame[frame[v] != -1.0]
            
    for __, v, bins in varList:
        frame[v] = frame[v].map(lambda x: -1 if x == -1 else bins[x]  )

    # Populating 
    edges = [ np.append(v[2],-1) if overflow else v[2] for v in varList ]
    newIndex = pd.MultiIndex.from_product( edges,
                                           names=[ v[1] for v in varList ] )
    series = frame.set_index(list(frame.columns[:-1]))['count']
    series = series.reindex(newIndex).dropna() 
    
    return series


def read_json(fname):
    def parse_entry(e):
        if type(e) is list: return e
        elif type(e) is dict: 
            return list(np.linspace(e['start'], e['stop'], e['num']))
        else:
            raise ValueError("Malformed JSON.")

    with open(fname,"r") as bin_json:
        dct = json.load(bin_json)
        dct = {k:parse_entry(dct[k]) for k in dct}
    return dct


def read_bq(table, binnings, mass=0.938272, mc=False):
    genInvBeta = "SQRT({0} + POW(GenMomentum,2))/GenMomentum".format(mass*mass)
    varNames         = [('1/BetaTOF',  'invBetaMeasured',   np.array(binnings["invBetaMeasured"] )),
                        ('1/R',        'invRgdtMeasured',   np.array(binnings["invRgdtMeasured"] ))]
    if mc: varNames += [(genInvBeta,   'invBetaTheoretic',  np.array(binnings["invBetaTheoretic"]))]

    frame = get_hist_series(table, varNames).reset_index()
    if not mc: frame['invBetaTheoretic'] = -1
        
    return frame

class JSONEncoder(json.JSONEncoder):
    def default(self, obj):
        if hasattr(obj, 'to_json'):
            return obj.to_json()
        return json.JSONEncoder.default(self, obj)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Read data from bq and save to a (possibly gzipped) json.")
    parser.add_argument('--bins_json', dest='bins_json', default="bins.json",   help='Input json file with binnings in it.')
    parser.add_argument('--out_json',  dest= 'out_json', default="frames.json", help='Output json file.')
    parser.add_argument('--gzip',      dest='gzip', action='store_true', help='GZIP the resulting file.')
    parser.set_defaults(gzip=False)
    args = parser.parse_args()
    
    print "Reading binning from \"{}\"".format(args.bins_json)
    binnings = read_json(args.bins_json)
    
    for k in ["invBetaMeasured", "invRgdtMeasured", "invBetaTheoretic"]:
        if k in binnings: 
            continue
        msg = "Error: {0} not in the {1} file.".format(k, args.bins_json )
        raise ValueError(msg)

    print "Making BQ requests:"
    frames = {
        "B1034": read_bq('AMS.protonsB1034',   binnings, mass=0.938272, mc=True ).to_dict(),
        "B800":  read_bq('AMS.protonsB800',    binnings, mass=0.938272, mc=True ).to_dict(),
        "Data":  read_bq('AMS.Data',           binnings, mass=0.938272, mc=False).to_dict(),
        "Deut":  read_bq('AMS.dB1030_GG_Blic', binnings, mass=2.014102, mc=True ).to_dict()
    }
    
    opf = open
    if args.gzip: 
        opf = gzip.open
        args.out_json += '.gz'
        
    print "Saving the frames to " +  args.out_json
    data = { "bins":binnings, "frames": frames }
    with opf(args.out_json, 'w') as outFile:
        json.dump(data, outFile, cls=JSONEncoder)