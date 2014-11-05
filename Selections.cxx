#include <math.h>
#include <TSpline.h>
#include "Selections.h"


//////////////////// SELEZIONE CHI^2 //////////////////////////////////////
double ChiR[23] = { 
    0.2417,	0.2941,	0.3469,	0.4587,	0.5313,	0.5841,	0.6434,	0.7351,	0.8459,
    1.0091,	2.0607,	3.6153,	5.4246,	7.1555,	8.8994,	1.2704,	1.5774,	1.8974,
    2.6878,	4.4905,	6.2802, 60, 100 };
																				
double Chi[23] = {
    0.0122,	0.1458,	0.5711,	1.0996,	1.6768,	2.1628,	2.4970, 2.7217,	2.5699,
    2.4909,	2.4909,	2.5030,	2.5030,	2.5091,	2.4727,	2.4666,	2.4666, 2.4848,
    2.50,	2.50,	2.50,   2.5,    2.5}; 

TSpline3 *Chi2 = new TSpline3("Cubic Spline",ChiR,Chi,23);
////////////////////////////////////////////////////////////////////////////

bool SubSelection::Test(Data & data) 
{ 
    bool result = eval(data);
    if(!result) nSelected += 1;
    return result;
}

////////////////////////////////////////////// Quality selection functions //////////////////////////////////////////

bool betaPositiveCut(Data & data) { return data.Beta<0; } 
bool rPositiveCut   (Data & data) { return data.R<0; } 
bool nAnticlusterCut(Data & data) { return data.NAnticluster >=1;} 
bool nTRDSegmentsCut(Data & data) { return data.NTRDSegments < 1;} 
bool nTofUnusedCut  (Data & data) { return (data.NTofClusters-data.NTofClustersusati) > 1;}
bool rupdownCut     (Data & data) { return fabs(data.Rup-data.Rdown)/data.R > 0.2; } 
bool probQCut       (Data & data) { return data.ProbQ < 0.43; } 
bool rChi2Cut       (Data & data) { return data.Chisquare > Chi2->Eval(data.R); } 
bool unusedLayersCut(Data & data) { return data.layernonusati > 2; } 

bool controlFit(Data & data) 
{ 
    int badfits=0;
    for(int j=0;j<6;j++)
        if((*data.chiq)[j]<0||(*data.chiq)[j]>15||fabs((*data.R_)[j]-data.R)/data.R>0.2) badfits++;
    return badfits > 0;
} 

bool xMisses(Data & data) 
{ 
    int fuoriX = 0;
    for(int layer=0;layer<7;layer++) 
        if((*data.ResiduiY)[layer]<-200 && (*data.ResiduiX)[layer]>-200 ) fuoriX++;
    return fuoriX > 2;
} 
/////////////////////////////////////// 1-st level quality cuts colletion ///////////////////////////////////

std::vector<SubSelection *> qualityCuts;
std::vector<SubSelection *> GetListOfSelections()
{
    if(qualityCuts.size() > 0) return qualityCuts;
    qualityCuts.push_back(new SubSelection(betaPositiveCut, "beta positiva"             ));
    qualityCuts.push_back(new SubSelection(nAnticlusterCut, "anticluster"               ));
    qualityCuts.push_back(new SubSelection(nTRDSegmentsCut, "segmenti TRD"              ));
    qualityCuts.push_back(new SubSelection(nTofUnusedCut,   "TOF clusters inutilizzati" ));
    qualityCuts.push_back(new SubSelection(rupdownCut,      "confronto Rup/Rdown"       ));
    qualityCuts.push_back(new SubSelection(probQCut,        "Prob. Q"                   ));
    qualityCuts.push_back(new SubSelection(controlFit,      "fit multipli"              ));
    qualityCuts.push_back(new SubSelection(rChi2Cut,        "Chi-Quadro"                ));
    qualityCuts.push_back(new SubSelection(unusedLayersCut, "layer non usati"           ));
    qualityCuts.push_back(new SubSelection(xMisses,         "missx"                     ));
    return qualityCuts;
}

bool Quality(Data &data)
{
    bool selection = true;
    std::vector<SubSelection *> cuts =  GetListOfSelections();

    for (int i=0; i<cuts.size(); i++) 
        selection &= (!cuts[i]->Test(data));
    return selection;
}   


/////////////////////////////////////// 2-nd level resolution band selection ///////////////////////////////////

template <typename T>
int countOutliers(T array, int N, float mean, float sigma, int Nsigma)
{
    // This function returns the number of entries in the array that are lying outside Nsigma bound.
    // Please note that the ''sigma'' parameter is the variance of the 1/variable
    int count = 0;
    for (int i=0; i<N; i++) 
        if (fabs(1/array[i]-1/theo) > Nsigma*sigma) count++;
   return count; 
}

bool TOFErrorBand(Data & data)
{
    int n_sigmaTOF = 3;
    float Beta_corr = data.corrData->Beta_corr;
    float theo      = EdepTOFbeta->Eval(Beta_corr);
    float sigma     = etof->Eval(Beta_corr);
    int clusterTOFfuori = countOutliers(*(data.Endep), 4, theo, sigma, n_sigmaTOF);
    return clusterTOFfuori > 1;
}

bool TrackErrorBand(Data & data)
{
    int n_sigmaTrack = 3;
    float Beta_corr = data.corrData->Beta_corr;
    float theo      = EdepTrackbeta->Eval(Beta_corr);
    float sigma     = etrack->Eval(Beta_corr);
    int clusterTrackFuori = countOutliers(*(data.clusterTrack), data.NTrackHits, theo, sigma, n_sigmaTrack);
    return clusterTrackFuori > 2;
}

bool TRDErrorBand(Data & data)
{
    int n_sigmaTRD = 3;
    float Beta_corr = data.corrData->Beta_corr;
    float theo      = EdepTRDbeta->Eval(Beta_corr);
    float sigma     = etrd->Eval(Beta_corr);
    int clusterTRDfuori = countOutliers(*(data.TRDclusters), data.NTRDclusters, theo, sigma, n_sigmaTRD);
    return clusterTRDfuori > 8;
}


std::vector<SubSelection *> errBandCuts;
std::vector<SubSelection *> GetListOfBandCuts()
{
    if(errBandCuts.size() > 0) return errBandCuts;
    errBandCuts.push_back(new SubSelection(TOFErrorBand   , "TOF sigma out"   ));
    errBandCuts.push_back(new SubSelection(TrackErrorBand , "Track sigma out" ));
    errBandCuts.push_back(new SubSelection(TRDErrorBand   , "TRD sigma out"   ));
    return errBandCuts;
}

bool Belt(Data &data)
{
    bool selection = true;
    std::vector<SubSelection *> cuts =  GetListOfBandCuts();

    for (int i=0; i<cuts.size(); i++) 
        selection &= (!cuts[i]->Test(data));
    return selection;
}   


