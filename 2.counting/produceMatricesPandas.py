import pandas as pd
import json
from pd_model import *
import seaborn as s
from matplotlib.colors import LogNorm
from histQueryFactory import *
import matplotlib.pyplot as plt
import numpy as np
import os
import readBinary as r

def main(params, outFilename="2.counting/datasets/observed_data.txt"):
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


    def betaVsR(frame):
        for i in range( len(params['binningBetaTheoretic']) - 1 ):
            bin='GenBin: ['+str(params['binningBetaTheoretic'][i])+';'+str(params['binningBetaTheoretic'][i+1])+']; '
            df=frame[frame['Gen_bin']==i][['R_bin','B_bin','count']].set_index(['R_bin','B_bin']).unstack().fillna(0)['count']
            df = df/df.sum().sum()
            
            # Dropping overflow row and column
            if -1 in df.columns:
                df=df.drop(-1,axis=1)
            if -1 in df.index:
                df=df.drop(-1,axis=0)

            def addMissingColumns(ref_columns):
                col=set(df.columns.values)
                fullColumns=set(range(0,len(ref_columns)))
                missingColumns=fullColumns-col

                for index in missingColumns:
                    df[index]=0

            addMissingColumns(params['binningBetaMeasured'])
            df=df.transpose()
            addMissingColumns(params['binningRgdtMeasured'])

            df.index = params['binningBetaMeasured']
            df.columns = params['binningRgdtMeasured']

            #df.to_csv('2.counting/mcmc/beta_vs_rgdt_GenBin'+str(i)+'.pd',index_label=bin+'R_bin/B_bin')
            return df


    # Produce Beta Vs Rigidity matrices
    def runAll(runMC):
        def mapper(frame):
            frame=frame[preselection(frame)]
            frame['B_bin'] = utils.binIndex(frame,'BetaTOFH', 100,0.5,1.2)
            frame['R_bin'] = utils.binIndex(frame,'R', 100,1,20)
            frame['betaTrue'] = frame.GenMomentum/np.sqrt(0.88022 + frame.GenMomentum**2)
            frame['Gen_bin'] = utils.binIndex(frame,'betaTrue',100,0.5,1)
            frame.drop('betaTrue',inplace=True)
            return betaVsR(frame)

        r.map_reduce('~/eos/ams/user/b/bcoste/binaryAmsData/old_protons.B1034_pr.pl1.1200.qgsp_bic_ams_noSmearing_chunked', mapper, reducer, ['BetaTOFH','R','GenMomentum'])



        def mapperTargetMatrix(frame):
            frame=frame[preselectionData(frame)]
            frame['B_bin'] = utils.binIndex(frame,'BetaTOFH', 100,0.5,1.2)
            frame['R_bin'] = utils.binIndex(frame,'R', 100,1,20)
            frame['betaTrue'] = frame.GenMomentum/np.sqrt(0.88022 + frame.GenMomentum**2)
            frame['Gen_bin'] = utils.binIndex(frame,'betaTrue',100,0.5,1)
            frame.drop('betaTrue',inplace=True)
            return betaVsR(frame)

        r.map_reduce('~/eos/ams/user/b/bcoste/binaryAmsData/newISS.B950/', mapperTargetMatrix, reducer, ['BetaTOFH','R','GenMomentum'])        

        # h = "SELECT\n" + vs + """
        # FROM
        #    AMS.Data
        # JOIN EACH
        #    AMS.cutoffs
        # ON
        #    AMS.cutoffs.JMDCTime=AMS.Data.UTime
        # WHERE
        #    (""" + params['preselectionData'] + """ AND """ + params['trackSelectionData'] + """ AND goodSecond==1)
        # GROUP BY R_bin,B_bin
        # ORDER BY R_bin,B_bin"""

        frame = pd.read_gbq(str(h),project_id='ams-test-kostya')
        frame.columns = ['Rbin', 'Beta', 'Count']
        frame['Rbin'] = frame['Rbin'].map(lambda x: params['binningRgdtMeasured'][x] )
        frame['Beta'] = frame['Beta'].map(lambda x: params['binningBetaMeasured'][x] )
        frame = frame.set_index(list(frame.columns[:-1])).unstack()['Count'].fillna(0)
        frame = frame.T

        np.savetxt(outFilename,frame.values)

        return frame

    return runAll("protonMC")

# for debugging only
if __name__ == "__main__":
    import json
    os.chdir("../..")
    print main(json.load(open('param.json')))

