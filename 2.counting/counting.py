import sys
sys.path.insert(0,'2.counting/mcmc_py')
sys.path.insert(0,'mcmc_py')
import produceMatrices
import readMCMC
import os
import pandas as pd
import subprocess

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


def main(params,directory=None):
    if params['redoMCMC']:
        if params['redoMatrices']: produceMatrices.main(params)

        shellCmds=[
            'rm -rf 2.counting/mcmc/latestMCMC',
            'make -C 2.counting/mcmc',
            'cd 2.counting/mcmc && ./mcmc -f latestMCMC -n 1000000 -N '+ str(len(params['binningRgdtTheoretic'])-1)
        ]


        # subprocess.call(shellCmds[0])
        # subprocess.call(shellCmds[1])
        # sys.exit()

        
        def evalcommand(cmd):
            print cmd
            r=os.system(cmd)
            print r
            return r

        
        if any(evalcommand(cmd) for cmd in shellCmds):
            print 'error'
            sys.exit()
            
    fluxP,fluxD=readMCMC.main(params,directory)

    df=pd.DataFrame({'countP':fluxP.mean(), 'countD':fluxD.mean()})
    df.reset_index(level=0, inplace=True)
    df=df.rename(columns = {'index':'binX'})
    return df

# for debugging only
if __name__ == "__main__":
    import json
    os.chdir("..")
    print main(json.load(open('param.json')))

