import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy import interpolate

pFlux = pd.read_csv('../../misc/doc/protons_1800-SM.pd')
protonFluxInterpolated = interpolate.interp1d(pFlux.Rigidity_GV_inf, pFlux.Phi)

def reweightFormula(rig):
    # return fluxData/fluxMC, with fluxMC ~ 1/rig
    return protonFluxInterpolated(rig)/(1/rig)

x=np.arange(pFlux.Rigidity_GV_inf.min(), 20, 0.02)
y=reweightFormula(x)
plt.plot(x,y)
plt.show()

