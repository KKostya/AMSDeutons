import bigQueryPlotting as b
import matplotlib.pyplot as plt
import pandas as pd

# This script returns the physical trigger efficiency as a function of the rigidity from flight data
# Note: since the variable 'Rfull' is used and not 'R', the efficiency is computed for FULL SPAN
#
# It is assumed that unbiased triggers have a 100% efficiency.
# It means that they see everything but they only ask for the acquisition once every their prescaling factor
#    Where:   _ Unbiased TOF is prescaled by 100
#             _ Unbiased ECAL is prescaled by 1000
#
# One can distinguish two kinds of acquisition condition.
#     1) The event has been seen by at least one physical trigger
#     2) Otherwise, the acquisition must have been asked by an unbiased trigger
#
# If there are 'nPhysicsTrigger' events in group 1) and 'nUnbiased' events in group 2),
# then the physiccal trigger effiency is defined as 'nPhysicsTrigger / (nPhysicsTrigger + nUnbiased*prescalingFactor)'
# 
# Here we have to unbiased trigger with different prescaling factor.
# The only trick is not to count twice unbiased event trigged by both UnbiasedEcal and UnbiasedTOF
# eff = nPhysicsTrigger / (nPhysicsTrigger + nTofAll*100   + nEcalNoTof*1000)'
#     = nPhysicsTrigger / (nPhysicsTrigger + nEcalAll*1000 + nTofNoEcal*100 )'
# TODO: understand why the second version currently gives wrong result
#
# @result: a pandas dataframe with a column 'binX' containing the bin low edge and a column
#          'trigEff' containing the physical trigger efficiency for this bin

def main(binArray):

    masks=[]
    masks.append("notFirstTwo")
    masks.append("notInSaaCut")
    masks.append("zenithCut")
    masks.append("runtypeCut")
    #masks.append("oneTRDTrack")
    masks.append("goldenTRACKER")
    masks.append("oneTrack")
    masks.append("chargeOne")
    masks.append("downGoing")
    masks.append("betaNotCrazy")


    theTable="AMS.Data"
    b.setTable(theTable)

    theMask=b.makeSelectionMask(masks)

    #whereClause="(Rfull > 0 && (selStatus&" + str(theMask)+ ")==" + str(theMask)+ " && " + mass + " > 0.8 && " + mass + " < 1.3 )"
    whereClause="(Rfull > 0 AND " + str(theMask)+ " AND AMS.cutoffs.goodSecond == 1)"
    havingClause="( binX IS NOT NULL )"

    isPhysicsTrigger=" (PhysBPatt >> 1)&"+str(int('11111',2))+ " != 0 as isPhysicsTrigger "
    isTof="(JMembPatt>>4)&1 as isTof"
    isEcal="(JMembPatt>>11)&1 as isEcal"

    variables='{} as binX, {},{},{},COUNT(1)'.format(b.binLowEdgeFromArray('Rfull', binArray),isPhysicsTrigger,isTof,isEcal)

    theCommand="""SELECT binX, IF(nTofNoEcal + nEcalAll > 0,nPhysics/(nPhysics + nEcalNoTof*1000 + nTofAll*100),1) AS trigEff, nTofAll, nEcalNoTof, IF(nTofNoEcal + nEcalAll > 0,nPhysics*100/(nPhysics + nEcalAll*1000 + nTofNoEcal*100),100) AS trigEff2, nPhysics, nEcalAll, nTofNoEcal FROM (
        SELECT binX,
                    SUM(IF(isPhysicsTrigger==True  && isEcal IS NULL       && isTof IS NULL,CAST(f0_ AS INTEGER),0)) AS nPhysics,
                    SUM(IF(isPhysicsTrigger==false && isEcal==True         && isTof IS NULL,CAST(f0_ AS INTEGER),0)) AS nEcalAll,
                    SUM(IF(isPhysicsTrigger==false && isEcal==False        && isTof==True,  CAST(f0_ AS INTEGER),0)) AS nTofNoEcal,
                    SUM(IF(isPhysicsTrigger==false && isEcal IS NOT NULL   && isTof==True,  CAST(f0_ AS INTEGER),0)) AS nTofAll,
                    SUM(IF(isPhysicsTrigger==false && isEcal==True         && isTof==False, CAST(f0_ AS INTEGER),0)) AS nEcalNoTof 
                FROM (SELECT """ + variables  + """ FROM [""" + theTable + """] JOIN EACH AMS.cutoffs ON AMS.Data.UTime=AMS.cutoffs.JMDCTime WHERE """ + whereClause + """ GROUP BY ROLLUP (binX,isPhysicsTrigger, isEcal, isTof) HAVING """ + havingClause + """ ORDER BY binX) GROUP BY binX )"""

    df=pd.read_gbq( theCommand, project_id='ams-test-kostya')
    return df



#for debugging only    
if __name__ == "__main__":
    main(range(1,20))
