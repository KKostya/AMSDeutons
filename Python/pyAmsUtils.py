import sys
import ROOT
import root_numpy
import numpy as np
import pandas as pd

def tree_to_frame(tree, branches=None):
    frame = pd.DataFrame(root_numpy.tree2rec(tree))
    if branches:
        frame = frame[branches]
    return frame

class Progress:
    def __init__(self, N, L):
        if N>L: N=L
        self.N, self.L = N, L
        self.current = 0
        sys.stdout.write("-" * N)
        sys.stdout.write("\n")
        sys.stdout.flush()
        
    def step(self,i):
        if int((self.N*i)/self.L) > self.current:
            self.current = int((self.N*i)/self.L)
            sys.stdout.write("-")
            sys.stdout.flush()
            
def get_mass(r,b):
    return r*np.sqrt(1-b**2)/b
    