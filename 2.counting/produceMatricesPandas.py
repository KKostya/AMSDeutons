import pandas as pd
import json
# from pd_model import *
# import seaborn as s
from matplotlib.colors import LogNorm
import utils
import matplotlib.pyplot as plt
import numpy as np
import os
import readBinary as r

def addMissingColumns(df, ref_columns):
    col=set(df.columns.values)
    fullColumns=set(range(0,len(ref_columns)))
    missingColumns=fullColumns-col
    
    for index in missingColumns:
        df[index]=0

def main(params, outFilename="2.counting/datasets/observed_data.txt"):
    def runAll(runMC):

        ################################################################################
        ##
        ##  BETA VS RIG MATRICES
        ##
        ################################################################################

        def mapperBetaVsR(frame):
            frame=frame.query( ' and '.join(params['preselectionList']) )
            frame['betaTrue'] = frame.GenMomentum/np.sqrt(0.88022 + frame.GenMomentum**2)
            frame['B_bin'] =   utils.binIndex(frame,'BetaTOFH', params['binningBetaMeasured'])
            frame['R_bin'] =   utils.binIndex(frame,'R',        params['binningRgdtMeasured'])
            frame['Gen_bin'] = utils.binIndex(frame,'betaTrue', params['binningBetaTheoretic'])
            # frame.dropna(how='any',subset=['R_bin','B_bin'], inplace=True)
            dfs=[]
            for i in range( len(params['binningBetaTheoretic']) - 1 ):
                dfs+=[ frame[frame['Gen_bin']==i].groupby(['R_bin','B_bin']).count()['R'].unstack().fillna(0) ]
            return dfs

        def reducerBetaVsRig(dfss):
            total=[ reduce(lambda x,y: x+y,dfs)  for dfs in zip(*dfss) ]
            for i, df in enumerate(total):
                bin='GenBin: ['+str(params['binningBetaTheoretic'][i])+';'+str(params['binningBetaTheoretic'][i+1])+']; '
                df = df/df.sum().sum()
                # Dropping overflow row and column
                for axis in [0,1]: df.drop(-1,axis=axis,errors='ignore',inplace=True)
                #for axis in [0,1]: addMissingColumns(df, params['binningBetaMeasured'], axis=axis)

                addMissingColumns(df, params['binningBetaMeasured'])
                df=df.transpose()
                addMissingColumns(df, params['binningRgdtMeasured'])

                df.index = params['binningBetaMeasured']
                df.columns = params['binningRgdtMeasured']
                df.to_csv('2.counting/mcmc/beta_vs_rgdt_GenBin'+str(i)+'.pd',index_label=bin+'R_bin/B_bin')

                print params['selStatusPreselection']+params['selStatusTrackSelection'],
        r.map_reduce(os.getenv('HOME')+'/eos/ams/user/b/bcoste/binaryAmsData/protons.B1034_pr.pl1.1200.qgsp_bic_ams_noSmearing/*/',
                     mapperBetaVsR,
                     reducerBetaVsRig,
                     ['BetaTOFH','R','GenMomentum'],
                     mask=params['selStatusPreselection']+params['selStatusTrackSelection'],
                     maxFiles=1)

        ################################################################################
        ##
        ##  TARGET
        ##
        ################################################################################
        
        def mapperTargetMatrix(frame):
            #frame=frame[preselectionData(frame) & trackSelectionData(frame) & goodSecond(frame)]
            frame['B_bin'] =   pd.cut(frame['BetaTOFH'], params['binningBetaMeasured'], labels=params['binningBetaMeasured'][:-1], right=False, include_lowest=True)
            frame['R_bin'] =   pd.cut(frame['R'],        params['binningRgdtMeasured'], labels=params['binningRgdtMeasured'][:-1], right=False, include_lowest=True)
            return frame.groupby(['R_bin','B_bin']).count()['R'].unstack().fillna(0).T

        def reducerTargetMatrix(dfs):
            result=reduce(lambda x,y: x+y,dfs)
            np.savetxt(outFilename,result.values)
            
        print r.map_reduce(os.getenv('HOME')+'/eos/ams/user/b/bcoste/binaryAmsData/newISS.B950/*/',
                     mapperTargetMatrix,
                     reducerTargetMatrix,
                     ['BetaTOFH','R','GenMomentum'],
                     maxFiles=1)
        
        

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


        # frame = frame.set_index(list(frame.columns[:-1])).unstack()['Count'].fillna(0)
        # frame = frame.T

    return runAll("protonMC")

# for debugging only
if __name__ == "__main__":
    import json
    os.chdir("..")
    print main(json.load(open('param.json')))

