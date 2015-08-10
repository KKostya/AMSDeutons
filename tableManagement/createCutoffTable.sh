selectionCut="AVG(Lifetime>0.5 && IsInSAA==0 && BadRunReason IS NULL)"

bq query --allow_large_results --destination_table AMS.cutoffs "SELECT ${selectionCut} as goodSecond, INTEGER(JMDCtime) as JMDCtime, AVG(ThetaM) as ThetaM, AVG(PhiM) as PhiM, AVG(ThetaS) as ThetaS, AVG(PhiS) as PhiS, AVG(Zenith) as Zenith, AVG(Lifetime) as Lifetime, AVG(IGRF40neg) as IGRF40neg, AVG(IGRF30neg) as IGRF30neg, AVG(IGRF35neg) as IGRF35neg, AVG(IGRF25neg) as IGRF25neg,  AVG(IGRF40pos) as IGRF40pos, AVG(IGRF30pos) as IGRF30pos, AVG(IGRF35pos) as IGRF35pos, AVG(IGRF25pos) as IGRF25pos from AMS.RTI GROUP EACH BY JMDCtime"

