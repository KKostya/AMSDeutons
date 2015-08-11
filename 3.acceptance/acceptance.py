import bigQueryPlotting as b
import matplotlib.pyplot as plt
import sys

def main(binArray,preselectionMC,tableMC,plot=False):
    b.setTable(tableMC)

    # The MC Rig distrbution in uniform in log(R)
    # We know that on the range [Rmin,Rmax], nTotal events have been generated
    # log(Rmax)-log(Rmin) = nTotal
    # Let's take a bin [A,B] and compute what fraction of the space it occupies in the [log(Rmin),log(Rmax)] 
    # Let's define f such fraction: f = (log(B)-log(A)) / (log(Rmax) - log(Rmin))
    # Since distribution is uniform in log(R) space, the number of event in bin [A,B] is
    # f * nTotal = (log(B)-log(A)) / (log(Rmax) - log(Rmin)) * nTotal

    b.setTable(tableMC)

    # The min and max rigidities used for the event generation
    Rmin=1
    Rmax=200
    
    # Total number of generated events
    # is estimated as the sum of the differences between max and min event number in every run
    theQueryTotalNumberOfEvents="SELECT SUM(biggestEventsPerRun-smallestEventsPerRun) FROM (SELECT MAX(Event) as biggestEventsPerRun, MIN(Event) as smallestEventsPerRun, AMS.protonsB1034.Run as runNumber FROM AMS.protonsB1034 GROUP BY runNumber ORDER BY runNumber )"
    df=b.histCustomCommand(theQueryTotalNumberOfEvents)
    nTotal=df['f0_'][0]
    print 'nTotal : {}'.format(nTotal)

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

    # theQueryNumberPreselected="bq --format json query ' \
    #  SELECT SUM(nGenPerBin) FROM(SELECT binX, nPreselPerBin, nGenPerBin, nPreselPerBin/nGenPerBin*3.9*3.9*PI() FROM (\
    #       SELECT "+b.binLowEdgeFromArray("GenMomentum",binArray) +"as binX, \
    #       COUNT(*) as nPreselPerBin, "+ nGenPerBin + " as nGenPerBin \
    #       FROM AMS.protonsB1034 WHERE " + cut3TOFLayers + \
    #       "GROUP BY binX, nGenPerBin  HAVING binX >= 0 ORDER BY binX, nGenPerBin))'"

    theQueryNumberPreselected="SELECT binX, nPreselPerBin, nGenPerBin, nPreselPerBin/nGenPerBin*3.9*3.9*PI() FROM (\
          SELECT "+b.binLowEdgeFromArray("GenMomentum",binArray) +"as binX, \
          COUNT(*) as nPreselPerBin, "+ nGenPerBin + " as nGenPerBin \
          FROM AMS.protonsB1034 WHERE " + preselectionMC + \
          "GROUP BY binX, nGenPerBin  HAVING binX >= 0 ORDER BY binX, nGenPerBin)"

    df=b.histCustomCommand(theQueryNumberPreselected)

    if plot:
        print df
        h=b.Hist(df,50,0,50)
        nPreselected=jsonData[0]['f0_']
        h.plot(y='f0_')
        plt.show()

    return df


if __name__ == "__main__":
    # Define a binning
    binning=range(1,200,2)
    print main(binning,plot=True)

