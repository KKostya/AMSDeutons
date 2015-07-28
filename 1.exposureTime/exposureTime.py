import bigQueryPlotting as b
import matplotlib.pyplot as plt
import sys

def main(argv):
    theTable="AMS.cutoffs"
    queryOption=str()
    globalOptions=str()

    queryOption=" --format json "

    if argv: binning=argv
    binning=[i for i in range(51)]

    theCommand="""bq """ + globalOptions + """ query """ + queryOption + """'
        SELECT
          SUM(Lifetime) OVER (ORDER BY binX),
          cut as binX
        FROM (
          SELECT
            NTH_VALUE(Lifetime,1) OVER(ORDER BY cut) AS total,
            SUM(Lifetime) AS Lifetime,
            """ + b.binHighEdgeFromArray('IGRF40pos',binning) + """ as cut
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
    '"""

#     theCommand="""bq """ + globalOptions + """ query """ + queryOption + """'
# SELECT
#     NTH_VALUE(Lifetime,1) OVER(ORDER BY cut) AS total,
#     SUM(Lifetime) AS Lifetime,
#     """ + b.binHighEdgeFromArray('IGRF40pos',binning) + """ as cut
#     FROM """ + theTable + """
#     JOIN AMS.timeInSecInData
#     ON (AMS.timeInSecInData.JMDCTimeInSec = """ + theTable + """.JMDCTime)
#     WHERE (
#     goodSecond == 1
#     )
#     GROUP BY
#     ROLLUP (cut)
#     ORDER BY
#     cut'"""

    df=b.histCustomCommand(theCommand)
    # h=b.Hist( df, 1, -50, 50 )
    # h.plot()
    # plt.show()

    return df


if __name__ == "__main__":
    binning=range(0,20)
    print main(binning)
