import sys
import numpy as np
import pandas as pd
import bigQueryPlotting as b

sys.path.insert(0,'2.counting/mcmc_py')

import pd_model
################################################################################
#
#  MAKE BINNINGS
#
################################################################################
#
# "Theoretical" binning (the one we will look the spectrum for)
#  is bootstrapped from R-vs-beta curves for D and P
#
def make_beta_bins(beta):
    bbins = []
    for i in range(10):
        bbins.append(beta)
        beta = pd_model.beta_from_R(pd_model.R_from_beta(beta,pd_model.md),pd_model.mp)
    return bbins

bbins = make_beta_bins(0.5)
bbins += make_beta_bins((bbins[1]+bbins[0])/2)
bbins = sorted(bbins)

mid1,mid2 = (bbins[1]+bbins[0])/2,(bbins[2]+bbins[1])/2
bbins += make_beta_bins(mid1)
bbins += make_beta_bins(mid2)
bbins = np.array([bbin for bbin in sorted(bbins) if 1 < pd_model.R_from_beta(bbin,pd_model.mp) < 30 ])

binningBetaTheoretic, binningRgdtTheoretic = np.array([bbins, pd_model.R_from_beta(bbins, pd_model.mp)])

#
# Measured values binnings are not very fancy
#
binningBetaMeasured = 1/np.linspace(0.5,2,28)
binningBetaMeasured.sort()

binningRgdtMeasured = np.logspace(-5.0 / 19, 1, 25)


# Define the tables to use
tableMC="AMS.protonsB1034"
tableData="AMS.Data"


#########################################################################################
#
# Define preselection
#
########################################################################################


# Track extrapolation to L1, L9
# Might be usefull one day for full span
# https://twiki.cern.ch/twiki/bin/view/AMS/PHeFluxStandardSelection
#
# upperX=' (TOFCoordsX_0+TOFCoordsX_1)/((TOFCoordsX_0!=0) + (TOFCoordsX_1!=0)) '
# lowerX=' (TOFCoordsX_2+TOFCoordsX_3)/((TOFCoordsX_2!=0) + (TOFCoordsX_3!=0)) '
# upperY=' (TOFCoordsY_0+TOFCoordsY_1)/((TOFCoordsY_0!=0) + (TOFCoordsY_1!=0)) '
# lowerY=' (TOFCoordsY_2+TOFCoordsY_3)/((TOFCoordsY_2!=0) + (TOFCoordsY_3!=0)) '
# upperZ=' (TOFCoordsZ_0+TOFCoordsZ_1)/((TOFCoordsZ_0!=0) + (TOFCoordsZ_1!=0)) '
# lowerZ=' (TOFCoordsZ_2+TOFCoordsZ_3)/((TOFCoordsZ_2!=0) + (TOFCoordsZ_3!=0)) '

# slopeX='({}-{})/({}-{})'.format(upperX,lowerX,upperZ,lowerZ)
# offsetZX='({} - {}*{})'.format(upperX,slopeX,upperZ)


# print 'SELECT ' \
#     + slopeX + ' as slopeX, ' \
#     + offsetZX + ' as offsetZX, ' \
#     + upperX + ' as upperX, ' \
#     + lowerX + ' as lowerX ' \
#     + 'FROM ' + tableMC

# 1)
cut3TOFLayers=' NTofClustersUsed >= 3 '
# 2) Asking for downgoing particle
mask=[]
mask.append("downGoing")

preselectionMC  =b.makeSelectionMask(tableMC,   mask) + " AND " + cut3TOFLayers
preselectionData=b.makeSelectionMask(tableData, mask) + " AND " + cut3TOFLayers

########################################################################################
#
# Define Track Selection
#
########################################################################################

# 1) Mask defined cuts
mask=[]
mask.append("physicsTrigger")
mask.append("chargeOne")
mask.append("oneTrack")
mask.append("goldenTOF")
mask.append("goldenTRACKER")
mask.append("oneParticle")

trackSelectionMC  =b.makeSelectionMask(tableMC, mask)
print 'trackSelectionMC : '+trackSelectionMC
trackSelectionData=b.makeSelectionMask(tableData, mask)

########################################################################################
#
# Write the JSON file: param.json
#
########################################################################################

import json
f=open('param.json','w')
l={'binningBetaTheoretic':binningBetaTheoretic.tolist(),
   'binningRgdtTheoretic':binningRgdtTheoretic.tolist(),
   'binningBetaMeasured':binningBetaMeasured.tolist(),
   'binningRgdtMeasured':binningRgdtMeasured.tolist(),
   'preselectionMC':preselectionMC,
   'preselectionData':preselectionData,
   'trackSelectionMC':trackSelectionMC,
   'trackSelectionData':trackSelectionData,
   'tableMC':tableMC,
   'tableData':tableData,
   'redoMCMC':False,
   'redoMatrices':False
}

#map(lambda obj: json.dump(obj,f), l)
json.dump(l,f,indent=4)
