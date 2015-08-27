import pandas as pd
from pd_model import *
import seaborn as s
from matplotlib.colors import LogNorm
import bq
from histQueryFactory import *
import matplotlib.pyplot as plt
import numpy as np
import os

def main(params, outFilename="2.counting/datasets/observed_data.txt"):
    ################################################################################
    ##
    ##  MAKING BQ CLEAR
    ##
    ################################################################################

    client = bq.Client.Get()
    schema = client.GetTableSchema({
        'projectId': 'ams-test-kostya',
        'datasetId': 'AMS',
        'tableId': 'protonsB1034'
    })

    bitFields = None
    for field in schema['fields']:
        if field['name'] != 'selStatus':
            continue
        bitFields = field['description'].split(',')
        break

    get_cumulative_mask = lambda sel: (1 << (bitFields.index(sel))) - 1


    import itertools
    def iterpairs(l):
        i1,i2 = itertools.tee(l); next(i2)
        return((x1,x2) for x1,x2 in itertools.izip(i1,i2))

    def build_case_string(var, name, bins):
        casestr = ["CASE"]
        casestr += ["  WHEN {1} < {0} AND {0} < {2} THEN {3}".format(var,s,e,n)
                    for n,(s,e)  in enumerate(iterpairs(bins))]
        casestr += ["  ELSE -1",  "END as {0}".format(name)]
        return '\n'.join(casestr)

    ################################################################################
    ##
    ##  BETA VS RIG MATRICES
    ##
    ################################################################################
    vs =  ",\n".join([ build_case_string("BetaTOF", "B_bin", params['binningBetaMeasured']),
                       build_case_string("R", "R_bin", params['binningRgdtMeasured']),
                       build_case_string("GenMomentum/SQRT(0.88022 + POW(GenMomentum,2))", "Gen_bin", params['binningBetaTheoretic']),
                       "COUNT(1) as count" ])

    h = "SELECT\n" + vs + """
    FROM
       AMS.protonsB1034
    WHERE
       (""" + params['preselectionMC'] + """ AND """ + params['trackSelectionMC'] + """)
    GROUP BY B_bin,R_bin,Gen_bin
    ORDER BY B_bin,R_bin,Gen_bin"""

    # tableid = client.Query(str(h))['configuration']['query']['destinationTable']
    # bq_table = client.ReadTableRows(tableid)

    # frame = pd.DataFrame(bq_table, columns=['Bbin', 'GenBin', 'Count']).astype(int)
    frame=pd.read_gbq(str(h),project_id='ams-test-kostya')
    # frame['Bbin'] = frame['Bbin'].map(lambda x: params['binningBetaMeasured'][x] )
    # frame['GenBin'] = frame['GenBin'].map(lambda x: params['binningBetaTheoretic'][x] )
    # frame = frame.set_index(list(frame.columns[:-1])).unstack()['Count'].fillna(0)

    # frame.T.to_csv(os.path.dirname(outFilename)+"B_resolution.csv")

    gen_bin=frame['Gen_bin'].unique()

    for i in gen_bin:
        bin='GenBin: ['+str(params['binningBetaTheoretic'][i])+';'+str(params['binningBetaTheoretic'][i+1])+']; '
        df=frame[frame['Gen_bin']==i][['R_bin','B_bin','count']].set_index(['R_bin','B_bin']).unstack().fillna(0)['count']
        print df.sum().sum()
        df.to_csv('beta_vs_rgdt_GenBin'+str(i)+'.pd',index_label=bin+ 'R_bin/B_bin')

        df = df/df.sum().sum()
        
        df=df.drop(-1,axis=0).drop(-1,axis=1)
        
        def addMissingColumns(ref_columns):
            col=set(df.columns.values)
            fullColumns=set(range(0,len(ref_columns)))
            missingColumns=fullColumns-col

            for index in missingColumns:
                df[index]=0

        addMissingColumns(params['binningBetaMeasured'])
        df=df.transpose()
        addMissingColumns(params['binningRgdtMeasured'])

        df.to_csv('beta_vs_rgdt_GenBin'+str(i)+'.pd',index_label=bin+ 'R_bin/B_bin')
    return frame

# for debugging only
if __name__ == "__main__":
    import json
    print main(json.load(open('../../param.json')))

