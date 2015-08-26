import pandas as pd

df=pd.read_csv('fullfile.pd')

gen_bin=df['Gen_bin'].unique()

gen_bin=gen_bin[1:] # Strip the -1 bin

for i in gen_bin:
    df[df['Gen_bin']==i][['R_bin','B_bin','count']].set_index(['R_bin','B_bin']).unstack().fillna(0).to_csv('beta_vs_rgdt_GenBin'+str(i)+'.pd')
