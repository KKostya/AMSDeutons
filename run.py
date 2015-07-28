import sys
import bigQueryPlotting as b

sys.path.insert(0,'1.exposureTime')
sys.path.insert(0,'2.counting')
sys.path.insert(0,'3.acceptance')
sys.path.insert(0,'4.trigEfficiency')

import exposureTime
import acceptance
import trigEfficiency

# Define a binning
binning=range(1,20)

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
# expTime=exposureTime.main(binning)
# acc=acceptance.main(binning,preselectionMC,tableMC)
trigEfficiency=trigEfficiency.main(binning)

# print expTime
# print acc
print trigEfficiency
