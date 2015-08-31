import os
import argparse
import numpy  as np
import pandas as pd
import ROOT
import root_numpy

def get_vars_filename():
    mypath = os.path.dirname(os.path.realpath(__file__))
    return os.path.join(mypath, "varlist.txt")

def update_schema(rootBranches, branches):
    # First pass -- check that all vars are present
    missing = set(branches) - rootBranches
    # Second pass -- check if missing vars are actually vecotor names 
    missing = {'_'.join(n.split('_')[:-1]) if '_' in n else n for n in missing } 
    missing = missing - rootBranches

    if missing: 
        print "The following branches are missing in the tree:",
        print sorted(missing)
        raise ValueError("Missing branches found.")  
    
    removed = rootBranches - set(branches)
    removed = removed - {'_'.join(n.split('_')[:-1]) for n in branches }
    if removed:
        print "The following branches will not be exported to the csv:",
        print sorted(removed)

    return rootBranches - removed

def get_data(filename, treename="data"):
    """ Converts a ROOT tree to a pandas dataframe. Unwraps vectors."""
    tfile = ROOT.TFile(filename)

    tree = tfile.Get(treename)
    rootBranches = {b.GetName() for b in tree.GetListOfBranches()}

    varFile = open(get_vars_filename(), "r")
    branches = [v.strip() for v in varFile.readlines()]
    varFile.close()

    rootBranches = update_schema(rootBranches, branches)

    data = root_numpy.tree2rec(tree, branches=rootBranches)
    data = pd.DataFrame(data)
    row = data.ix[0]

    for c, t in data.dtypes.iteritems():
        if c == "fStatus": continue
        if not t == np.object: continue
        size = len(row[c]) if c != "rich_getTrackEmissionPoint"  else 5
        for i in range(size):
            newc = "{0}_{1}".format(c,i)
            data[newc] = data[c].str.get(i)
        del data[c]

    return data[branches]

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

