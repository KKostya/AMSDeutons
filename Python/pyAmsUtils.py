import ROOT
import root_numpy
import pandas as pd

def tree_to_frame(tree, branches=None):
    frame = pd.DataFrame(root_numpy.tree2rec(tree))
    if branches:
        frame = frame[branches]
    return frame