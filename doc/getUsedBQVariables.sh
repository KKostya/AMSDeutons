#!/bin/bash
find .. -name "*.py" -exec grep -o '".*"' {} \; | sed  's/[="\+:<>(){}\.&]/ /g' | tr ' ' '\n' | sort | uniq > var

useless="
_\n-\n,\n!\n/\n'\n','\n[\n]\n*\n&\n&&\n#\n0\n1\n-1\n&1\n1000000\n11\n'11111',2\n1200\n2\n3\n4\n8\n88022\n9\na\n/afs/cern\nAMS\n~/AMSDeutons/test\nAND\nare\nas\nAS\nb\n-B;\nB1034/pr\nB950/pass6/\nB_bin\nbe\nbeta_from_R\nbetaNotCrazy\nbiggestEventsPerRun,\nbiggestEventsPerRun-smallestEventsPerRun\nbin\n_BIN\nbinHighEdgeFromArray\nbinLowEdgeFromArray\nbins\nbinX\nbinX,\nbinX,isPhysicsTrigger,\nbname\nbranches\nB_resolution\nbuild_case_string\nBY\nCASE\ncd\nchargeOne\nch/user/k/kostams/eos/ams/MC/AMS02/2014/protons\ncommon\nConverts\ncount\nCOUNT\ncounting/datasets/observed_data\ncounting/mcmc;\ncounting/mcmc/latestMCMC/\ncsv\ncutoffs\nd\ndata\nData\ndataframe\n/data/protonsB1034\ndatasets/B_resolution\ndatasets/observed_mock_equal\ndatasets/R_resolution\ndirectory\ndone\ndownGoing\nEACH\nELSE\nEND\nEvent\nExecuting\nexported\nf\n-f\nfile\nfiles\nFLOAT\n*FLOOR\nfollowing\nformat\n--format\nfound\nfrom\nFROM\nfStatus\nfull_test\nGen_bin\nGenMomentum,2\nGenMomentum/SQRT\ngoldenTOF\ngoldenTRACKER\ngoldenTRD\nGROUP\ngzip\nhas\nHAVING\nhavingClause\nin\nInput\nint\nINTEGER\nis\nIS\nisEcal\nisEcal,\nisPhysicsTrigger\nisTof\nJob\njoin\nJOIN\njson\nlatestMCMC\nlatestMCMC;\nLatitude\nlog\nm\n__main__\nmake\nmass\nMAX\n/mcmc\nmd\nmi\nMIN\nmismatch!\nmissing\nMissing\nmp\nn\n-n\nN\nnGenPerBin\nnot\nNOT\nntuple\n/ntupleData\nNULL\n-o\nof\nON\noneParticle\noneTrack\noneTRDTrack\nORDER\noutput\nOutput\npandas\npar*\n,params['binningRgdtTheoretic']\nparams['preselectionData']\nparams['preselectionMC']\nparams['trackSelectionData']\nparams['trackSelectionMC']\nPDModel\nphysicsTrigger\npl1\nPOW\nProcessing\nprotonsB1034\nqgsp_bic_ams/\nr\nrb\nR_bin\n-rf\nR_from_beta\nrich_getTrackEmissionPoint\nrm\nrng\nROLLUP\nroot\nROOT\nR_resolution\nrunNumber\ns\nSchema\nschemas\nschemas[s]\nselect\nSELECT\nSent\nsmallestEventsPerRun,\nsome\n/storage/gpfs_ams/ams/Rec/2014/ISS\n/storage/gpfs_ams/ams/users/kostya/ntuples/\nstr\nSTRING\nSUM\nt\nthe\nThe\ntheMask\nTHEN\nTheoretical\nThere\ntheTable\nto\ntree\ntreename\ntxt\ntypes\nUnwraps\nvar\nvariables\nvarlist\nvectors\nvs\nWHEN\nwhere\nWHERE\nwhereClause\nwill\n[x]"

echo -e  ${useless} > useless
comm -23 var useless
rm -f var useless