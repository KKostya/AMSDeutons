import pandas as pd
import matplotlib.pyplot as plt

df=pd.read_csv('flux.pd')
df.plot(y='fluxP')
plt.show()
