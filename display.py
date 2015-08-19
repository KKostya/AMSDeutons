import pandas as pd
import matplotlib.pyplot as plt

df=pd.read_csv('6.output/flux.pd')
df.plot(y='fluxP')
plt.show()
