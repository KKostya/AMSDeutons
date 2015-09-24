import bigQueryPlotting as b
import matplotlib.pyplot as plt
import sys
import json
import re
import pandas as pd

def main(params,plot=False):

    # get selStatus word from params["trackSelectionMC"])
    matchObj=re.match(r'.*selStatus\^(.*)\)&.*', params["trackSelectionMC"])
    selStatus=int(matchObj.group(1))

    tableMC = params["tableMC"]
    
    finalMask=b.getSelectionsFromMask(tableMC, selStatus)

    mask=list()

    dfs=list()
    
    for m in finalMask:
        mask.append(m)
        #b.getSelectionsFromMask(selStatus)
        print mask
        theQuery="SELECT "+b.binLowEdgeFromArray("GenMomentum",params['binningRgdtTheoretic']) + "as binX, " \
            ' COUNT(1) as after_' + m + \
            ' FROM {0} WHERE '.format(tableMC) + b.makeSelectionMask(tableMC, mask) + \
            ' GROUP BY binX, HAVING binX >= 0 ORDER BY binX '

        plt.figure()
        dfs.append( b.histCustomCommand(theQuery) )

    df=reduce(lambda left, right: left.merge(right,on='binX',how='inner'), dfs)
    df['trackEff'] = 1
    for i in range(1,len(finalMask)):
        df['eff_'+finalMask[i]]=df['after_'+finalMask[i]]/df['after_'+finalMask[i-1]]
        df['trackEff'] *= df['eff_'+finalMask[i]]
        
    print df

    # if plot:
    #     print df
    #     h=b.Hist(df,50,0,50)
    #     nPreselected=jsonData[0]['f0_']
    #     h.plot(y='f0_')
    #     plt.show()

    # return df
    return df

if __name__ == "__main__":
    # Define a binning
    main(json.load(open('../param.json')),plot=True)
