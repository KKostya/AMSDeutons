####################################################
#
# PARAMETERS DEFINITION
#
###################################################

# BIG QUERY
protonMC="AMS.protonsB800"
deutonMC="AMS.dB1030_GG_Blic"
tableData="AMS.Data"

# MCMC
redoMCMC=True
redoMatrices=True

#  BINNINGS
betaMeasuredNBins=100
betaMeasuredMin=0.5
betaMeasuredMax=1.5
rgdtMeasuredNBins=100
rgdtMeasuredMin=1
rgdtMeasuredMax=40
betaTheoreticMax=0.5

# PRESELECTION
cut3TOFLayers=' NTofClustersUsed >= 3 '
selStatusPreselection=["downGoing"]

# TRACK SELECTION
selStatusTrackSelection=[
    "physicsTrigger",
    "chargeOne",
    "oneTrack",
    "goldenTOF",
    "goldenTRACKER",
    "oneParticle",
    "goldenTRD",
    "betaNotCrazy"]


####################################################
#
# END OF PARAMETER DEFINITION
#
####################################################

import sys
import numpy as np
import pandas as pd
import bigQueryPlotting as b
import math

sys.path.insert(0,'2.counting/mcmc_py')

import pd_model

# Binning magic
#
# "Theoretical" binning (the one we will look the spectrum for)
#  is bootstrapped from R-vs-beta curves for D and P
#
def make_beta_bins(beta):
    bbins = []
    for i in range(5):
        bbins.append(beta)
        beta = pd_model.beta_from_R(pd_model.R_from_beta(beta,pd_model.md),pd_model.mp)
    return bbins

bbins = make_beta_bins(0.5)
bbins += make_beta_bins((bbins[1]+bbins[0])/2)
bbins = sorted(bbins)

mid1,mid2 = (bbins[1]+bbins[0])/2,(bbins[2]+bbins[1])/2
bbins += make_beta_bins(mid1)
bbins += make_beta_bins(mid2)
bbins = np.array([bbin for bbin in sorted(bbins) ])

binningBetaTheoretic, binningRgdtTheoretic = np.array([bbins, pd_model.R_from_beta(bbins, pd_model.mp)])

#
# Measured values binnings are not very fancy
#
binningBetaMeasured = 1/np.linspace(1./betaMeasuredMax,1./betaMeasuredMin,betaMeasuredNBins+1)
binningBetaMeasured.sort()

binningRgdtMeasured = np.logspace((math.log(rgdtMeasuredMin)/math.log(10)), (math.log(rgdtMeasuredMax)/math.log(10)), rgdtMeasuredNBins+1)





# Preselection magic

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


preselectionMC  =b.makeSelectionMask( protonMC,   selStatusPreselection) + " AND " + cut3TOFLayers
preselectionData=b.makeSelectionMask( tableData, selStatusPreselection) + " AND " + cut3TOFLayers

# Track Selection magic

trackSelectionMC  =b.makeSelectionMask(protonMC, selStatusTrackSelection)
trackSelectionData=b.makeSelectionMask(tableData, selStatusTrackSelection)

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
   'protonMC':protonMC,
   'tableData':tableData,
   'redoMCMC':redoMCMC,
   'redoMatrices':redoMatrices,
}

#map(lambda obj: json.dump(obj,f), l)
json.dump(l,f,indent=4)
