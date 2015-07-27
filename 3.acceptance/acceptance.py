import bigQueryPlotting as b
import matplotlib.pyplot as plt

b.setTable("AMS.protonsB1034")

# The MC Rig distrbution in uniform in log(R)
# We know that on the range [Rmin,Rmax], nTotal events have been generated
# log(Rmax)-log(Rmin) = nTotal
# Let's take a bin [A,B] and compute what fraction of the space it occupies in the [log(Rmin),log(Rmax)] 
# Let's define f such fraction: f = (log(B)-log(A)) / (log(Rmax) - log(Rmin))
# Since distribution is uniform in log(R) space, the number of event in bin [A,B] is
# f * nTotal = (log(B)-log(A)) / (log(Rmax) - log(Rmin)) * nTotal

#Preselection cut
mask=[]
mask.append("downGoing")

b.setTable("AMS.protonsB1034")

# The min and max rigidities used for the event generation
Rmin=1
Rmax=200

nBins=40
firstBin=1
lastBin=200

# Asking for at least 3 TOF layers with some deposited energy
cut3TOFLayers = " ( (EdepTOF_0>0)+(EdepTOF_1>0)+(EdepTOF_2>0)+(EdepTOF_3>0) >= 3) "

# Number of MC events passing the preselection cut

nGenPerBin="(log({}) - log({})) / (log({}) - log({})) * {}".format(b.binHighEdge(nBins,firstBin,lastBin,"GenMomentum"), 
                                                                   b.binLowEdge(nBins,firstBin,lastBin,"GenMomentum"),
                                                                   Rmax,Rmin,
                                                                   nTotal)
theQueryNumberPreselected="bq --format json query ' \
SELECT binX, nPreselPerBin, nGenPerBin, nPreselPerBin/nGenPerBin*3.9*3.9*PI() FROM (\
SELECT "+b.binCenter(nBins,firstBin, lastBin,"GenMomentum") +"as binX, \
COUNT(*) as nPreselPerBin, "+ nGenPerBin + " as nGenPerBin \
FROM AMS.protonsB1034 WHERE " + theMask + " && " + cut3TOFLayers + \
"GROUP BY binX, nGenPerBin  HAVING binX > 0 ORDER BY binX, nGenPerBin)'"

df=b.histCustomCommand(theQueryNumberPreselected)
h=b.Hist(df,nBins,firstBin,lastBin)
# nPreselected=jsonData[0]['f0_']
h.plot(y='f0_')
plt.show()
