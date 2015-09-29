import json
import itertools
import numpy  as np
import pandas as pd

def iterpairs(l):
    i1,i2 = itertools.tee(l); next(i2)
    return((x1,x2) for x1,x2 in itertools.izip(i1,i2))

def build_case_string(var, name, bins):
    casestr = ["CASE"]
    casestr += ["  WHEN {1} < {0} AND {0} < {2} THEN {3}".format(var,s,e,n)
                 for n,(s,e)  in enumerate(iterpairs(bins))]
    casestr += ["  ELSE -1",  "END as {0}".format(name)]
    return '\n'.join(casestr)

def get_hist_series(table, varList, overflow=True, selection=None):
    if selection is None:
        selection = "selStatus&2097151=2097151"
    
    variables = ",\n".join([ build_case_string(*var) for var in varList] + ["COUNT(1) as count"])
    groupers =  ','.join([var[1] for var in varList])

    h = """SELECT {1}
    FROM {0}
    WHERE
        {3}
    GROUP BY {2}
    ORDER BY {2}""".format(table, variables, groupers, selection)

    # Making the request 
    frame = pd.read_gbq(h,'ams-test-kostya')
    
    if not overflow:
        for __, v, __ in varList:
            frame = frame[frame[v] != -1.0]

    # Tweaking the resulting frame:
    # - convert bin numbers to values
    for __, v, bins in varList:
        frame[v] = frame[v].map(lambda x: -1 if x == -1 else bins[x]  )

    # Populating 
    edges = [ np.append(v[2],-1) if overflow else v[2] for v in varList ]
    newIndex = pd.MultiIndex.from_product( edges,
                                           names=[ v[1] for v in varList ] )
    series = frame.set_index(list(frame.columns[:-1]))['count']
    series = series.reindex(newIndex).fillna(0) 
    
    return series


def get_selection_schema(**args):
    """    
    Args:
        projectId: string, Project ID of the requested table (required)
        datasetId: string, Dataset ID of the requested table (required)
          tableId: string, Table ID of the requested table (required)    
    
    Example:
        get_selection_schema(projectId='ams-test-kostya', datasetId='AMS', tableId='Data')
    """
    connector = pd.io.gbq.GbqConnector(args['projectId'], reauth=False)
    tbls = connector.service.tables()
    tabelData = tbls.get(**args).execute()
    for column in tabelData['schema']['fields']:
        if column['name'] == 'selStatus':
            return column['description'].split(',')




