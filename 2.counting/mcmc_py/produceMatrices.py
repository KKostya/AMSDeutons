import pandas as pd
from pd_model import *
import seaborn as s
from matplotlib.colors import LogNorm
import bq
from histQueryFactory import *
import matplotlib.pyplot as plt
import numpy as np

def main(preselectionMC, trackSelectionMC, preselectionData, trackSelectionData,
         binningBetaTheoretic, binningRgdtTheoretic, binningBetaMeasured, binningRgdtMeasured):
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
    ##  BETA MATRIX
    ##
    ################################################################################
    vs =  ",\n".join([ build_case_string("BetaTOF", "B_bin", binningBetaMeasured),
                       build_case_string("GenMomentum/SQRT(0.88022 + POW(GenMomentum,2))", "Gen_bin", binningBetaTheoretic),
                       "COUNT(1) as count" ])

    h = "SELECT\n" + vs + """
    FROM
       AMS.protonsB1034
    WHERE
       (""" + preselectionMC + """ AND """ + trackSelectionMC + """)
    GROUP BY B_bin,Gen_bin
    ORDER BY B_bin,Gen_bin"""

    tableid = client.Query(str(h))['configuration']['query']['destinationTable']
    bq_table = client.ReadTableRows(tableid)

    frame = pd.DataFrame(bq_table, columns=['Bbin', 'GenBin', 'Count']).astype(int)
    frame['Bbin'] = frame['Bbin'].map(lambda x: binningBetaMeasured[x] )
    frame['GenBin'] = frame['GenBin'].map(lambda x: binningBetaTheoretic[x] )
    frame = frame.set_index(list(frame.columns[:-1])).unstack()['Count'].fillna(0)

    frame.T.to_csv("2.counting/datasets/B_resolution.csv")

    #plt.figsize(5,4)
    # cc = plot_matrix(frame.ix[frame.index[:-1]][frame.columns[:-1]],
    #                             norm=LogNorm(vmin=1,vmax=10**6))
    # colorbar(cc)
    # xlabel("$\\beta$ True")
    # ylabel("$\\beta$ Measured")
    # ylim(0.6,1.4)

    ################################################################################
    ##
    ##  RIGIDITY MATRIX
    ##
    ################################################################################
    vs =  ",\n".join([ build_case_string("R", "R_bin", binningRgdtMeasured),
                                          build_case_string("GenMomentum", "Gen_bin", binningRgdtTheoretic),
                                          "COUNT(1) as count" ])

    h = "SELECT\n" + vs + """
    FROM
       AMS.protonsB1034
    WHERE
       (""" + preselectionMC + """ AND """ + trackSelectionMC + """)
    GROUP BY R_bin,Gen_bin
    ORDER BY R_bin,Gen_bin"""

    tableid = client.Query(str(h))['configuration']['query']['destinationTable']
    bq_table = client.ReadTableRows(tableid)
    frame = pd.DataFrame(bq_table, columns=['Rbin', 'GenBin', 'Count']).astype(int)
    frame['Rbin'] = frame['Rbin'].map(lambda x: binningRgdtMeasured[x] )
    frame['GenBin'] = frame['GenBin'].map(lambda x: binningRgdtTheoretic[x] )
    frame = frame.set_index(list(frame.columns[:-1])).unstack()['Count'].fillna(0)
    frame.T.to_csv("2.counting/datasets/R_resolution.csv")
    #plt.figsize(5,4)
    # cc = plot_matrix(frame.ix[frame.index[:-1]][frame.columns[:-1]],
    #                             norm=LogNorm(vmin=1,vmax=10**6))
    # colorbar(cc)
    # xlabel("$R$ True")
    # ylabel("$R$ Measured")
    # xlim(0.5,10)

    ################################################################################
    ##
    ##  TARGET
    ##
    ################################################################################

    vs =  ",\n".join([ build_case_string("R", "R_bin", binningRgdtMeasured),
                                          build_case_string("BetaTOF", "B_bin", binningBetaMeasured),
                                          "COUNT(1) as count" ])

    h = "SELECT\n" + vs + """
    FROM
       AMS.Data
    JOIN EACH
       AMS.cutoffs
    ON
       AMS.cutoffs.JMDCTime=AMS.Data.UTime
    WHERE
       (""" + preselectionData + """ AND """ + trackSelectionData + """ AND goodSecond==1)
    GROUP BY R_bin,B_bin
    ORDER BY R_bin,B_bin"""
    tableid = client.Query(str(h))['configuration']['query']['destinationTable']
    bq_table = client.ReadTableRows(tableid)

    frame = pd.DataFrame(bq_table, columns=['Rbin', 'Beta', 'Count']).astype(int)
    frame['Rbin'] = frame['Rbin'].map(lambda x: binningRgdtMeasured[x] )
    frame['Beta'] = frame['Beta'].map(lambda x: binningBetaMeasured[x] )
    frame = frame.set_index(list(frame.columns[:-1])).unstack()['Count'].fillna(0)
    frame = frame.T

    #plt.figsize(13,6)
    # cc = plot_matrix(frame.ix[frame.index[:-1]][frame.columns[:-1]],
    #                             norm=LogNorm(vmin=1,vmax=10**6))
    # colorbar(cc)
    # xlabel("$R$ Measured")
    # ylabel("$\\beta$ Measured")
    # xlim(0.5,5)
    # ylim(0.5,1.3)

    np.savetxt("2.counting/datasets/observed_data.txt",frame.values)
