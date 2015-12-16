import pandas as pd
import json

params=json.load(open('../../param.json'))
table=params['tableData']


df=pd.read_gbq('SELECT INTEGER(JMDCTime) AS JMDCTimeInSec FROM ' + table + ' GROUP BY JMDCTimeInSec ORDER BY JMDCTimeInSec', project_id='ams-test-kostya')
pd.io.gbq.to_gbq(df[['JMDCTimeInSec']], params['tableJMDCTimeInData'], project_id='ams-test-kostya',)
