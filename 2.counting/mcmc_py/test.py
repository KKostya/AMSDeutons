import pandas as pd

df=pd.read_csv('fullfile.pd')

gen_bin=df['Gen_bin'].unique()

for i in gen_bin:
    df[df['Gen_bin']==i][['R_bin','B_bin','count']].set_index(['R_bin','B_bin']).unstack().fillna(0)['count'].drop(-1,axis=0).drop(-1,axis=1).to_csv('beta_vs_rgdt_GenBin'+str(i)+'.pd',index_label='R_bin/B_bin')
