import sys
import bigQueryPlotting as b
import numpy as np
import pandas as pd
import inspect
import json

sys.path.insert(0,'1.exposureTime')
sys.path.insert(0,'2.counting')
sys.path.insert(0,'3.acceptance')
sys.path.insert(0,'4.trigEfficiency')

param=json.load(open('param.json'))

########################################################################################
#
# Run the shit
#
########################################################################################
import exposureTime
import counting
import acceptance
import trigEfficiency

# Functions to call
funct=[exposureTime.main,
       counting.main,
       acceptance.main,
       trigEfficiency.main]

# Creating the list of output DataFrames
dfs=map(lambda f: f(param), funct)

# Saving intermediate DataFrames
map(lambda df,f: df.to_csv(inspect.getmodule(f).__name__+'.pd')  , dfs, funct)

# Reading them back lol
dfs=map(lambda f: pd.read_csv(inspect.getmodule(f).__name__+'.pd')  , funct)

# Merging them altogether
df=reduce(lambda left, right: left.merge(right,on='binX',how='inner'), dfs)

# Adding a column bin width
df['deltaR']=df.binX.diff().shift(-1)

# Computing the flux
df['fluxP'] = df['countP'] / (df['AccEff'] * df['expTime'] * df['trigEff'] * df['deltaR'] )
df['fluxD'] = df['countD'] / (df['AccEff'] * df['expTime'] * df['trigEff'] * df['deltaR'] )

# Adding a binCenter column (centered in a logarithmic way)
df['binCenter'] = (df['binX']*(df['binX']+df['deltaR'])).apply(np.sqrt)

df.to_csv('flux.pd')

print 'Done !'
