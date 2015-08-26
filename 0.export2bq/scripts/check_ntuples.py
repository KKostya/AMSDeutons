import os
import glob
import argparse
import ROOT

def code(name):
    return '.'.join(name.split('/')[-1].split('.')[:2])

def getFileDict(gpath):
    filelist  = glob.glob(os.path.join(gpath,  "*.root"))
    return {code(n):n for n in filelist}


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Compare input and directories.')
    parser.add_argument('--indir',   dest= 'indir', default="",          help='Input drectory.')
    parser.add_argument('--outdir',  dest='outdir', default="",          help='Output directory.')
    parser.add_argument('--tree',    dest='tree',   default="data",      help='Name of the tree.')
    parser.add_argument('--schema',  dest='schema', action='store_true', help='Check that branches.')
    parser.set_defaults(schema=False)
    args = parser.parse_args()

    inputFiles  = getFileDict(args.indir)
    outputFiles = getFileDict(args.outdir)

    print inputFiles.keys()
    print outputFiles.keys()

    commonFiles = sorted(set(inputFiles.keys()) & set(outputFiles.keys()))

    print commonFiles

    print "Input  directory has {} files.".format(len(inputFiles ))
    print "Output directory has {} files.".format(len(outputFiles))
    if len(commonFiles) != len(outputFiles):
        print "There is some file mismatch! There are {} common files.".format(len(commonFiles))
     
    if args.schema:
        print "Processing schemas ..."
        schemas = {}
        for f in commonFiles:
            tfile = ROOT.TFile(outputFiles[f])
            tree  = tfile.Get(args.tree)
            ns = tuple([n.GetName() for n in tree.GetListOfBranches()])
            if ns not in schemas: schemas[ns] = []
            schemas[ns].append(f)
            tfile.Close()

        print "There are {} types of schemas in the output files.".format(len(schemas.keys()))

        for n,s in enumerate(schemas):
            print "Schema #{}".format(n)
            print "[" + (','.join(        s )) + "]"
            print "[" + (','.join(schemas[s])) + "]"
	
        

