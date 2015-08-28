import os
import argparse
import numpy  as np
import pandas as pd
import ROOT
import root_numpy

def unique(seq):
    seen = set()
    seen_add = seen.add
    return [ x for x in seq if not (x in seen or seen_add(x))]

def get_data(filename, treename="data"):
    """ Converts a ROOT tree to a pandas dataframe. Unwraps vectors."""
    tfile = ROOT.TFile(filename)

    tree = tfile.Get(treename)
    data = root_numpy.tree2rec(tree, branches=unique([b.GetName() for b in tree.GetListOfBranches()]) )
    data = pd.DataFrame(data)
    row = data.ix[0]

    to_delete = [
        "DistanceTOF_P",
        "DistanceTRD_P",
        "DistanceTracker_P",
        "MLRigidityTOF_P",
        "MLRigidityTRD_P",
        "MLRigidityTracker_P",
        "DistanceTOF_D",
        "DistanceTRD_D",
        "DistanceTracker_D",
        "MLRigidityTOF_D",
        "MLRigidityTRD_D",
        "MLRigidityTracker_D",
    ]

    for c, t in data.dtypes.iteritems():
        if c == "fStatus": continue
        if c in to_delete: 
            del data[c]
            continue
        if not t == np.object: continue
        size = len(row[c]) if c != "rich_getTrackEmissionPoint"  else 5
        for i in range(size):
            newc = "{0}_{1}".format(c,i)
            data[newc] = data[c].str.get(i)
        del data[c]

    return data

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Convert a root file to a csv file.')
    parser.add_argument('--srcroot', dest='srcFile', default="",          help='Input ROOT file.')
    parser.add_argument('--dstcsv',  dest='dstFile', default="",          help='Output CSV file.')
    parser.add_argument('--gzip',    dest='gzip',    action='store_true', help='GZIP the resulting file.')
    parser.set_defaults(gzip=False)
    args = parser.parse_args()

    frame = get_data(args.srcFile)
    frame.to_csv(args.dstFile)

    if args.gzip:
        os.system("gzip " + args.dstFile)

