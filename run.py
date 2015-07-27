import sys

sys.path.insert(0,'1.exposureTime')
sys.path.insert(0,'2.counting')
sys.path.insert(0,'3.acceptance')
sys.path.insert(0,'4.trigEfficiency')

import exposureTime
import acceptance
import trigEfficiency

# Define a binning
binning=range(20)

expTime=exposureTime.main(binning)
acc=acceptance.main(binning)
trigEfficiency=trigEfficiency.main(binning)

print expTime
print acc
print trigEfficiency
