import sys
import bigQueryPlotting as b
import numpy as np

sys.path.insert(0,'1.exposureTime')
sys.path.insert(0,'2.counting')
sys.path.insert(0,'2.counting/mcmc_py')
sys.path.insert(0,'3.acceptance')
sys.path.insert(0,'4.trigEfficiency')

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
# 1) Asking for at least 3 TOF layers with some deposited energy
cut3TOFLayers = " ( (EdepTOF_0>0.3)+(EdepTOF_1>0.3)+(EdepTOF_2>0.3)+(EdepTOF_3>0.3) >= 3) "

# 2) Asking for downgoing particle
mask=[]
mask.append("downGoing")

b.setTable(tableMC)
preselectionMC=b.makeSelectionMask(mask) + " AND " + cut3TOFLayers

b.setTable(tableData)
preselectionData=b.makeSelectionMask(mask) + " AND " + cut3TOFLayers

########################################################################################
#
# Define Track Selection
#
########################################################################################

# 1) Mask defined cuts
mask=[]
mask.append("physicsTrigger")
mask.append("betaNotCrazy")
mask.append("chargeOne")
mask.append("oneTrack")
mask.append("goldenTOF")
mask.append("goldenTRACKER")
mask.append("goldenTRD")
mask.append("oneParticle")



# 2) Remove events only trigged by ECAL physics trigger
noEcalTriggerOnly ="(physBPatt>>1)&31!=16"

b.setTable(tableMC)
trackSelectionMC=b.makeSelectionMask(mask) + " AND " + noEcalTriggerOnly

b.setTable(tableData)
trackSelectionData=b.makeSelectionMask(mask) + " AND " + noEcalTriggerOnly

########################################################################################
#
# Run the shit
#
########################################################################################
import exposureTime
import counting
import acceptance
import trigEfficiency

expTime=exposureTime.main(binningRgdtTheoretic)
countP, countD = counting.main(preselectionMC, trackSelectionMC, preselectionData, trackSelectionData, 
              binningBetaTheoretic, binningRgdtTheoretic, binningBetaMeasured, binningRgdtMeasured)
acc=acceptance.main(binningRgdtTheoretic,preselectionMC,tableMC)
trigEfficiency=trigEfficiency.main(binningRgdtTheoretic)


# print preselectionMC
# print trackSelectionMC
# print preselectionData
# print trackSelectionData, 

print expTime
print countP, countD
print acc
print trigEfficiency
