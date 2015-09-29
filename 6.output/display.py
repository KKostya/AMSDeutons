import pandas as pd
import matplotlib.pyplot as plt

df=pd.read_csv('6.output/flux.pd')
dfRef=pd.read_csv('doc/protons_1800-SM.pd')
ax=df.plot(y='fluxP',xlim=(0,20),label='Protons: this work')
df.plot(y='fluxD',xlim=(0,20),label='Deutons: this work',ax=ax)
dfRef.plot(x='Rigidity_GV_inf',y='Phi',xlim=(0,20),ax=ax,label='Protons: AMS02 paper')

plt.yscale('log')

# plt.figure()
# (df['fluxD']/df['fluxP']).plot()
plt.show()