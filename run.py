import sys

sys.path.insert(0,'1.exposureTime')
sys.path.insert(0,'2.counting')
sys.path.insert(0,'3.acceptance')
sys.path.insert(0,'4.efficiencies')

import exposureTime
import acceptance

# Define a binning
binning=range(20)

expTime=exposureTime.main(binning)
acc=acceptance.main(binning)

print expTime
print acc
