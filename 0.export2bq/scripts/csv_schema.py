import gzip
import argparse
import numpy  as np
import pandas as pd



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='')
    parser.add_argument('--input', dest='inFile', default="", help='Input gzipped CSV file.')
    args = parser.parse_args()

    dic = {
        np.dtype('int64'):  "INTEGER",
        np.dtype('float64'):"FLOAT",
        np.dtype('O'):      "STRING",
    }

    frame = pd.DataFrame.from_csv(gzip.open(args.inFile))
    schema = [ name+':'+dic[dt] for name, dt in frame.dtypes.iteritems() ]
    
    print 'Index:INTEGER,' + ','.join(schema)
