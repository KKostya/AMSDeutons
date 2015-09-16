import bigQueryPlotting as b
import matplotlib.pyplot as plt
import sys

# This script computes the effective acceptance using the proton Monte-Carlo.
# The formula of the effective acceptance is: Neff = Acc_gen * N_presel/N_gen
# where Acc_gen is the acceptance of generation, N_presel the number of events
# passing the preselection and N_gen the number of generated events.
#
# Here are the following steps of the calculation:
#
# 1) The Monte-Carlo does not keep track of the number of generated events
#    This number by looking at the biggest and smallest event number for each run
#    The difference between these two numbers is a good approximation of the number 
#    of generated events
#
# 2) During step 1) was computed the total number of generated events but we
#    need the number of generated events in every energy bin. This can be 
#    estimated since we know that the distribution of rigidity for the generated 
#    events is flat in log(R)
#
# 3) In every rigidity bin, it then computes the number of events passing
#    the preselection cuts. The ratio of this number with the number of generated
#    number of events in this bin gives N_presel/N_gen
#
# 4) Computation of Acc_gen:
#    In the Monte-Carlo events are generated downward from a 3.9 * 3.9 m^2 surface
#    located above AMS. This gives Acc_gen = 3.9 * 3.9 * Pi m^2
#    
#
# @return: A pandas dataframe with a column 'AccEff' containing effective acceptance
#          for the bin having low edge given by column 'binX'

def main(params,plot=False):
    b.setTable(params['tableMC'])

    # The MC Rig distrbution in uniform in log(R)
    # We know that on the range [Rmin,Rmax], nTotal events have been generated
    # log(Rmax)-log(Rmin) = nTotal
    # Let's take a bin [A,B] and compute what fraction of the space it occupies in the [log(Rmin),log(Rmax)] 
    # Let's define f such fraction: f = (log(B)-log(A)) / (log(Rmax) - log(Rmin))
    # Since distribution is uniform in log(R) space, the number of event in bin [A,B] is
    # f * nTotal = (log(B)-log(A)) / (log(Rmax) - log(Rmin)) * nTotal

    b.setTable(params['tableMC'])

    # The min and max rigidities used for the event generation
    Rmin=1
    Rmax=200
    
    # Total number of generated events
    # is estimated as the sum of the differences between max and min event number in every run
    theQueryTotalNumberOfEvents="SELECT SUM(biggestEventsPerRun-smallestEventsPerRun) FROM (SELECT MAX(Event) as biggestEventsPerRun, MIN(Event) as smallestEventsPerRun, AMS.protonsB1034.Run as runNumber FROM AMS.protonsB1034 GROUP BY runNumber ORDER BY runNumber )"
    df=b.histCustomCommand(theQueryTotalNumberOfEvents)
    nTotal=df['f0_'][0]
    #print 'nTotal : {}'.format(nTotal)

    # Number of MC events passing the preselection cut

    nGenPerBin='CASE\n'
    for i in range(len(params['binningRgdtTheoretic'])-1):
        nGenPerBin+='    WHEN GenMomentum >= {} AND GenMomentum < {} THEN (log({}) - log({})) / (log({}) - log({})) * {}'.format(
            params['binningRgdtTheoretic'][i],
            params['binningRgdtTheoretic'][i+1],
            params['binningRgdtTheoretic'][i+1],
            params['binningRgdtTheoretic'][i],
            Rmax,Rmin,
            nTotal)
    nGenPerBin+=' ELSE NULL END '

    # nGenPerBin="(log({}) - log({})) / (log({}) - log({})) * {}".format(b.binHighEdgeFromArray("GenMomentum",params['binningRgdtTheoretic']), 
    #                                                                    b.binLowEdgeFromArray("GenMomentum",params['binningRgdtTheoretic']),
    #                                                                    Rmax,Rmin,
    #                                                                    nTotal)

    # theQueryNumberPreselected="bq --format json query ' \
    #  SELECT SUM(nGenPerBin) FROM(SELECT binX, nPreselPerBin, nGenPerBin, nPreselPerBin/nGenPerBin*3.9*3.9*PI() FROM (\
    #       SELECT "+b.binLowEdgeFromArray("GenMomentum",params['binningRgdtTheoretic']) +"as binX, \
    #       COUNT(*) as nPreselPerBin, "+ nGenPerBin + " as nGenPerBin \
    #       FROM AMS.protonsB1034 WHERE " + cut3TOFLayers + \
    #       "GROUP BY binX, nGenPerBin  HAVING binX >= 0 ORDER BY binX, nGenPerBin))'"

#    theQueryNumberPreselected="SELECT binX, nPreselPerBin, nGenPerBin, nPreselPerBin/nGenPerBin AS AccEff FROM (\
    theQueryNumberPreselected="SELECT binX, nPreselPerBin, nGenPerBin, nPreselPerBin/nGenPerBin*3.9*3.9*PI() AS AccEff FROM (\
          SELECT "+b.binLowEdgeFromArray("GenMomentum",params['binningRgdtTheoretic']) +"as binX, \
          COUNT(1) as nPreselPerBin, "+ nGenPerBin + " as nGenPerBin \
          FROM AMS.protonsB1034 WHERE " + params['preselectionMC'] + \
          "GROUP BY binX, nGenPerBin  HAVING binX >= 0 ORDER BY binX, nGenPerBin)"

    df=b.histCustomCommand(theQueryNumberPreselected)
    
    if plot:
        print df
        h=b.Hist(df,50,0,50)
        h.plot(y='AccEff')
        plt.show()

    return df

# for debugging only
if __name__ == "__main__":
    import json
    print main(json.load(open('../param.json')),plot=True)

