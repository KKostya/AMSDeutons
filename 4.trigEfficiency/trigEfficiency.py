import bigQueryPlotting as b
import matplotlib.pyplot as plt

def main(argv):
    binArray=argv
    if binArray is None:
        print "No binning array given !"
        return

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

    # print "{0:b}".format(theMask)

    #whereClause="(Rfull > 0 && (selStatus&" + str(theMask)+ ")==" + str(theMask)+ " && " + mass + " > 0.8 && " + mass + " < 1.3 )"
    whereClause="(Rfull > 0 && (selStatus&" + str(theMask)+ ")==" + str(theMask)+ " )"
    havingClause="( binX IS NOT NULL )"

    isPhysicsTrigger=" (PhysBPatt >> 1)&"+str(int('11111',2))+ " != 0 as isPhysicsTrigger "
    isTof="(JMembPatt>>4)&1 as isTof"
    isEcal="(JMembPatt>>11)&1 as isEcal"

    variables='{} as binX, {},{},{},COUNT(1)'.format(b.binLowEdgeFromArray('Rfull', binArray),isPhysicsTrigger,isTof,isEcal)

    theCommand="""SELECT binX, IF(nTofNoEcal + nEcalAll > 0,nPhysics*100/(nPhysics + nEcalNoTof*1000 + nTofAll*100),100), nTofAll, nEcalNoTof, IF(nTofNoEcal + nEcalAll > 0,nPhysics*100/(nPhysics + nEcalAll*1000 + nTofNoEcal*100),100), nPhysics, nEcalAll, nTofNoEcal FROM (

        SELECT binX,
                    SUM(IF(isPhysicsTrigger==True  && isEcal IS NULL       && isTof IS NULL,CAST(f0_ AS INTEGER),0)) AS nPhysics,
                    SUM(IF(isPhysicsTrigger==false && isEcal==True         && isTof IS NULL,CAST(f0_ AS INTEGER),0)) AS nEcalAll,
                    SUM(IF(isPhysicsTrigger==false && isEcal==False        && isTof==True,  CAST(f0_ AS INTEGER),0)) AS nTofNoEcal,
                    SUM(IF(isPhysicsTrigger==false && isEcal IS NOT NULL   && isTof==True,  CAST(f0_ AS INTEGER),0)) AS nTofAll,
                    SUM(IF(isPhysicsTrigger==false && isEcal==True         && isTof==False, CAST(f0_ AS INTEGER),0)) AS nEcalNoTof 

                FROM (SELECT """ + variables  + """ FROM [""" + theTable + """] WHERE """ + whereClause + """ GROUP BY ROLLUP (binX,isPhysicsTrigger, isEcal, isTof) HAVING """ + havingClause + """ ORDER BY binX)

                GROUP BY binX )"""

    print theCommand
    df=b.executeQuery( theCommand)
    return df
    
if __name__ == "__main__":
    main(sys.argv[1:])
