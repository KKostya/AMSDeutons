import sys
sys.path.insert(0,'mcmc_py')
import produceMatrices

def main(preselectionMC, trackSelectionMC, preselectionData, trackSelectionData):
    print preselectionMC
    print trackSelectionMC
    produceMatrices.main(preselectionMC, trackSelectionMC, preselectionData, trackSelectionData)
    return

#for debugging only    
if __name__ == "__main__":
    main("(((selStatus^262144)&262144)==0  AND  ( (EdepTOF_0>0.3)+(EdepTOF_1>0.3)+(EdepTOF_2>0.3)+(EdepTOF_3>0.3) >= 3))",
         "(((selStatus^1736704)&1736704)==0  AND (physBPatt>>1)&31!=16)",
         "(((selStatus^262144)&262144)==0  AND  ( (EdepTOF_0>0.3)+(EdepTOF_1>0.3)+(EdepTOF_2>0.3)+(EdepTOF_3>0.3) >= 3))",
         "(((selStatus^1736704)&1736704)==0  AND (physBPatt>>1)&31!=16)")
