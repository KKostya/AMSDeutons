import sys
sys.path.insert(0,'2.counting/mcmc_py')
sys.path.insert(0,'mcmc_py')
import produceMatrices
import readMCMC
import os
import pandas as pd

# This script do the following things
# 1) If 'redoMatrices' is set to 'True' and given the preselection and selection cuts, it computes
#    the beta and rigidity resolution matrices. It also compute the target matrix from the data
#    defined as an histogram of number of events in every (beta-measured, rigidity-measured) 2D-bin
#
# 2) If 'redoMCMC' is set to 'True', it run the MCMC algorithm.
#    The parameters of the MCMC are the number of proton and deuteriums in every rigidity-theoretic bin
#    The MCMC find the parameters that reproduce the most the target matrix (computed in step 1) given the 
#    beta and rigidity resolution matrices (computed in step 1)
#
# 3) Since the output of the MCMC is a chain of set of parameters (ie. proton and deuton number of counts),
#    the last step is to extract the average along the chain value of each parameter 
#    
# @return: A pandas dataframe with columns 'countP' and 'countD' containing the number of counts
#          for the bin having low edge given by column 'binX'

redoMCMC=True
redoMatrices=True

def main(preselectionMC, trackSelectionMC, preselectionData, trackSelectionData, 
         binningBetaTheoretic, binningRgdtTheoretic, binningBetaMeasured, binningRgdtMeasured):

    if redoMCMC:
        if redoMatrices: produceMatrices.main(preselectionMC, trackSelectionMC, preselectionData, trackSelectionData,
                             binningBetaTheoretic, binningRgdtTheoretic, binningBetaMeasured, binningRgdtMeasured)
        os.system("cd 2.counting/mcmc; rm -rf latestMCMC; make -B; ./mcmc -f latestMCMC -n 1000000")
        
    fluxP,fluxD=readMCMC.main(binningRgdtTheoretic)

    df=pd.DataFrame({'countP':fluxP.mean(), 'countD':fluxD.mean()})
    df.reset_index(level=0, inplace=True)
    df=df.rename(columns = {'index':'binX'})
    return df


    
#for debugging only    
if __name__ == "__main__":
    os.chdir("..")
    print main( "((selStatus^262144)&262144)==0  AND  ( (EdepTOF_0>0.3)+(EdepTOF_1>0.3)+(EdepTOF_2>0.3)+(EdepTOF_3>0.3) >= 3)",
                 "((selStatus^1754880)&1754880)==0  AND (physBPatt>>1)&31!=16",
                 "((selStatus^262144)&262144)==0  AND  ( (EdepTOF_0>0.3)+(EdepTOF_1>0.3)+(EdepTOF_2>0.3)+(EdepTOF_3>0.3) >= 3)",
                 "((selStatus^1754880)&1754880)==0  AND (physBPatt>>1)&31!=16",
                 [ 0.75579077,  0.8067325 ,  0.84989074,  0.88647115,  0.91753928,
                   0.93895811,  0.95511736,  0.96755398,  0.9772995 ,  0.98361644,
                   0.98817874,  0.99157629,  0.99417195,  0.99582393,  0.99700241,
                   0.99787215,  0.99853213,  0.99895017,  0.99924743,  0.99946631],
                 [  1.08287816,   1.28085109,   1.51314916,   1.79713963,
                    2.16483296,   2.56061   ,   3.02500807,   3.59274685,
                    4.32781998,   5.11903658,   6.04743672,   7.18243018,
                    8.65194964,  10.23370818,  12.08971682,  14.35873592,
                    17.2965218 ,  20.45869011,  24.16912477,  28.7052282 ],
                 [ 0.5       ,  0.51428571,  0.52941176,  0.54545455,  0.5625    ,
                   0.58064516,  0.6       ,  0.62068966,  0.64285714,  0.66666667,
                   0.69230769,  0.72      ,  0.75      ,  0.7826087 ,  0.81818182,
                   0.85714286,  0.9       ,  0.94736842,  1.        ,  1.05882353,
                   1.125     ,  1.2       ,  1.28571429,  1.38461538,  1.5       ,
                   1.63636364,  1.8       ,  2.        ],
                 [  0.54555948,   0.61584821,   0.6951928 ,   0.78475997,
                    0.88586679,   1.        ,   1.12883789,   1.27427499,
                    1.43844989,   1.62377674,   1.83298071,   2.06913808,
                    2.33572147,   2.6366509 ,   2.97635144,   3.35981829,
                    3.79269019,   4.2813324 ,   4.83293024,   5.45559478,
                    6.15848211,   6.95192796,   7.8475997 ,   8.8586679 ,  10.        ])

