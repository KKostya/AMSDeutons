import bigQueryPlotting as b
import matplotlib.pyplot as plt
import sys

def main(argv,plot=False):
    binArray=argv
    if binArray is None:
        print "No binning array given !"
        return


    theQuery="bq --format json query ' \
    
    '"

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
