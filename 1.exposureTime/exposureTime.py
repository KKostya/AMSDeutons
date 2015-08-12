import bigQueryPlotting as b
import matplotlib.pyplot as plt
import sys

# Exposure time is computed as a function of the rigidity cutoff value
# The sample used is made of all seconds having 'goodSecond == 1' which is a flag that indicates
# the detector was in proper configuration during this second (ex: not in SAA, not doing calibration,...)
# Exposure time is computed as the integrated number of such seconds spent above a given cutoff
#
# TODO: fix the exposure time value for the first bin when it is not 0
#
# @return: a pandas dataframe with a column 'binX' containing the bin low edge
#          and a column 'expTime' giving the exposure time spent having Rcutoff >= binX
def main(binning):
    theTable="AMS.cutoffs"
    queryOption=str()
    globalOptions=str()

    queryOption=" --format json "


    theCommand="""
        SELECT
          cut as binX,
          SUM(Lifetime) OVER (ORDER BY binX) as expTime
        FROM (
          SELECT
            NTH_VALUE(Lifetime,1) OVER(ORDER BY cut) AS total,
            SUM(Lifetime) AS Lifetime, """ + \
                b.binHighEdgeFromArray('IGRF40pos',binning) + """ as cut 
            FROM """ + theTable + """
          JOIN AMS.timeInSecInData
          ON (AMS.timeInSecInData.JMDCTimeInSec = """ + theTable + """.JMDCTime)
          WHERE (
             goodSecond == 1
          )
          GROUP BY
            ROLLUP (cut)
          ORDER BY
            cut )
        WHERE
          cut > 0
    """

    df=b.histCustomCommand(theCommand)
    # h=b.Hist( df, 1, -50, 50 )
    # h.plot()
    # plt.show()

    return df



# for debugging only
if __name__ == "__main__":
    binning=range(0,20)
    print main(binning)
