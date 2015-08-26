import bigQueryPlotting as b
import matplotlib.pyplot as plt
import sys
import json

def main(params,plot=False):

    mask = ["physicsTrigger",
            "betaNotCrazy",
            "chargeOne",
            "oneTrack",
            "goldenTOF",
            "goldenTRACKER",
            "goldenTRD",
            "oneParticle"]
    
    l=b.getSelectionsFromMask(1754880)

    # theQuery="bq --format json query ' \
    
    # '"

    # df=b.histCustomCommand(theQueryNumberPreselected)

    # if plot:
    #     print df
    #     h=b.Hist(df,50,0,50)
    #     nPreselected=jsonData[0]['f0_']
    #     h.plot(y='f0_')
    #     plt.show()

    # return df
    return None

if __name__ == "__main__":
    # Define a binning
    print main(json.load(open('../param.json')),plot=True)
