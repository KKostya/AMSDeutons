import bigQueryPlotting as b
import matplotlib.pyplot as plt
import sys

def main(argv):
    binArray=argv
    if binArray is None:
        print "No binning array given !"
        return

    b.setTable("AMS.protonsB1034")

    # The MC Rig distrbution in uniform in log(R)
    # We know that on the range [Rmin,Rmax], nTotal events have been generated
    # log(Rmax)-log(Rmin) = nTotal
    # Let's take a bin [A,B] and compute what fraction of the space it occupies in the [log(Rmin),log(Rmax)] 
    # Let's define f such fraction: f = (log(B)-log(A)) / (log(Rmax) - log(Rmin))
    # Since distribution is uniform in log(R) space, the number of event in bin [A,B] is
    # f * nTotal = (log(B)-log(A)) / (log(Rmax) - log(Rmin)) * nTotal

    #Preselection cut
    mask=[]
    mask.append("downGoing")

    b.setTable("AMS.protonsB1034")

    # The min and max rigidities used for the event generation
    Rmin=1
    Rmax=200
    
    # Total number of generated events
    # is estimated as the sum of the differences between max and min event number in every run
    theQueryTotalNumberOfEvents="bq --format json query 'SELECT SUM(biggestEventsPerRun-smallestEventsPerRun) FROM (SELECT MAX(Event) as biggestEventsPerRun, MIN(Event) as smallestEventsPerRun, AMS.protonsB1034.Run as runNumber FROM AMS.protonsB1034 GROUP BY runNumber ORDER BY runNumber )'"
    jsonData=b.executeQuery(theQueryTotalNumberOfEvents)
    nTotal=jsonData[0]['f0_']


    # Asking for at least 3 TOF layers with some deposited energy
    cut3TOFLayers = " ( (EdepTOF_0>0)+(EdepTOF_1>0)+(EdepTOF_2>0)+(EdepTOF_3>0) >= 3) "

    # Number of MC events passing the preselection cut

    nGenPerBin='CASE\n'
    for i in range(len(binArray)-1):
        nGenPerBin+='    WHEN GenMomentum >= {} AND GenMomentum < {} THEN (log({}) - log({})) / (log({}) - log({})) * {}'.format(
            binArray[i],
            binArray[i+1],
            binArray[i+1],
            binArray[i],
            Rmax,Rmin,
            nTotal)
    nGenPerBin+='ELSE NULL END '

    # nGenPerBin="(log({}) - log({})) / (log({}) - log({})) * {}".format(b.binHighEdgeFromArray("GenMomentum",binArray), 
    #                                                                    b.binLowEdgeFromArray("GenMomentum",binArray),
    #                                                                    Rmax,Rmin,
    #                                                                    nTotal)
    theQueryNumberPreselected="bq --format json query ' \
    SELECT binX, nPreselPerBin, nGenPerBin, nPreselPerBin/nGenPerBin*3.9*3.9*PI() FROM (\
          SELECT "+b.binLowEdgeFromArray("GenMomentum",binArray) +"as binX, \
          COUNT(*) as nPreselPerBin, "+ nGenPerBin + " as nGenPerBin \
          FROM AMS.protonsB1034 WHERE " + cut3TOFLayers + \
    "GROUP BY binX, nGenPerBin  HAVING binX > 0 ORDER BY binX, nGenPerBin)'"

    df=b.histCustomCommand(theQueryNumberPreselected)
    # h=b.Hist(df,nBins,firstBin,lastBin)
    # nPreselected=jsonData[0]['f0_']
    # h.plot(y='f0_')
    # plt.show()
    return df

if __name__ == "__main__":
    main(sys.argv[1:])
