import sys
sys.path.insert(0,'2.counting/mcmc_py')
sys.path.insert(0,'mcmc_py')
import produceMatrices
import readMCMC
import os

redoMCMC=True
redoMatrices=False

def main(preselectionMC, trackSelectionMC, preselectionData, trackSelectionData, 
         binningBetaTheoretic, binningRgdtTheoretic, binningBetaMeasured, binningRgdtMeasured):
    print binningRgdtTheoretic
    if redoMCMC:
        if redoMatrices: produceMatrices.main(preselectionMC, trackSelectionMC, preselectionData, trackSelectionData,
                             binningBetaTheoretic, binningRgdtTheoretic, binningBetaMeasured, binningRgdtMeasured)
        os.system("cd 2.counting/mcmc; rm -rf latestMCMC; make -B; ./mcmc -f latestMCMC -n 10000000")
        os.chdir("../../")

    #readMCMC.main(binningRgdtTheoretic)

    
#for debugging only    
if __name__ == "__main__":
    os.chdir("..")
    main("(((selStatus^262144)&262144)==0  AND  ( (EdepTOF_0>0.3)+(EdepTOF_1>0.3)+(EdepTOF_2>0.3)+(EdepTOF_3>0.3) >= 3))",
         "(((selStatus^1736704)&1736704)==0  AND (physBPatt>>1)&31!=16)",
         "(((selStatus^262144)&262144)==0  AND  ( (EdepTOF_0>0.3)+(EdepTOF_1>0.3)+(EdepTOF_2>0.3)+(EdepTOF_3>0.3) >= 3))",
         "(((selStatus^1736704)&1736704)==0  AND (physBPatt>>1)&31!=16)",
         [ 0.95511736,  0.96755398,  0.9772995,   0.98361644,  0.98817874,  0.99157629,
           0.99417195,  0.99582393,  0.99700241,  0.99787215,  0.99853213,  0.99895017,
           0.99924743,  0.99946631],
         [  3.02500807,   3.59274685,   4.32781998,   5.11903658,   6.04743672,
            7.18243018,   8.65194964,  10.23370818,  12.08971682,  14.35873592,
            17.2965218,   20.45869011,  24.16912477,  28.7052282 ],
         [ 0.5,         0.51428571,  0.52941176,  0.54545455,  0.5625,      0.58064516,
           0.6,         0.62068966,  0.64285714,  0.66666667,  0.69230769,  0.72,        0.75,
           0.7826087,   0.81818182,  0.85714286,  0.9,         0.94736842,  1.,
           1.05882353,  1.125,       1.2,         1.28571429,  1.38461538,  1.5,
           1.63636364,  1.8,         2.        ],
         [  0.54555948,   0.61584821,   0.6951928,    0.78475997,   0.88586679,   1.,
            1.12883789,   1.27427499,   1.43844989,   1.62377674,   1.83298071,
            2.06913808,   2.33572147,   2.6366509,    2.97635144,   3.35981829,
            3.79269019,   4.2813324,    4.83293024,   5.45559478,   6.15848211,
            6.95192796,   7.8475997,    8.8586679,   10.        ])
