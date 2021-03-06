#include <vector>
#include <numeric>

#include "TF1.h"
#include "TMath.h"

class AMSEventR;

////////////// Bin centers //////////////////
double Beta_cent[30] = {
    0.41,0.43,0.45,0.47,0.49,0.51,0.53,0.55,0.57,0.59,
    0.61,0.63,0.65,0.67,0.69,0.71,0.73,0.75,0.77,0.79,
    0.81,0.83,0.85,0.87,0.89,0.91,0.93,0.95,0.97,0.99,
};

double betacent[30] = {
    0,0.01,0.02,0.03,0.04,0.05,0.415919,0.453355,0.488411,0.520469,
    0.550179,0.578353,0.605235,0.631148,0.656092,0.680222,0.703866,
    0.726883,0.749455,0.771762,0.793729, 0.81529,0.836695,0.857886,
    0.878908,0.899705,0.920224,0.940778,0.961202,0.981896,
};

double valorecent[24] = {
    0.620376,0.79053,1.28364,1.63572,2.08435,2.65604,3.38452,4.31281,
    5.49571,7.00304,8.9238,11.3714,14.4903,18.4646,23.5289,29.9823,
    38.2058,48.6846,62.0376,79.053,100.735,128.364,162.378,0,
};
///////////////////////////////////////////////////////

////////////////// Correction R measurend vs R generated //////////
double R_gen[34] = {
    0.5633,0.6490,0.8449,1.0408,1.1755,1.3347,1.5306,1.7510,1.9469,
    2.1551,2.3510,2.5347,2.7551,2.9878,3.2204,3.5143,3.7347,3.9429,
    4.1755,4.4204,4.6653,4.9469,5.1918,5.5224,5.7918,6.0122,7.0000,
    8.0000,9.0000,10.000,11.000,20.000,50.000,100.00
};
double R_mis[34] = {
    0.7306,1.0000,1.3367,1.6902,1.9764,2.1279,2.2626,2.3805,2.4310,
    2.5320,2.7172,2.8182,3.0034,3.1886,3.3232,3.5926,3.8114,4.0303,
    4.2660,4.4680,4.6532,4.9226,5.1414,5.4613,5.7643,6.0337,7.0000,
    8.0000,9.0000,10.000,11.000,20.000,50.000,100.00
};

//////////////////	RICH Correcitons //////////////////////
double R_rich[25] ={
    3.18055,3.57491,4.01817,4.51638,5.07637,5.70579,6.41325,
    7.20844,8.10221,9.10681,10.2360,11.5051,12.9317,14.5351,
    16.3373,18.3629,20.6398,23.1989,26.0753,29.3084,32.9424,
    37.0269,41.6179,46.7781,52.5781
};
double Corr_rich[25]={
    1.00213,1.00045,1.00006,0.99960,0.99930,0.99921,0.99903,
    0.99895,0.99894,0.99888,0.99890,0.99887,0.99885,0.99882,
    0.99887,0.99883,0.99881,0.99883,0.99886,0.99885,0.99880,
    0.99888,0.99884,0.99883,0.99888
};
//////////////////////////////////////////////////////////////


/////////////////// Resolutions /////////////
double sigmaEtofinv[30] = {
    0.00899569,0.00996743,0.0108831,0.0118423,0.0129914,0.0140838,0.0154319,0.0168052,0.0183226,0.0199137,
    0.0212392,0.0229006,0.0246924,0.0264303,0.0284476,0.0305052,0.0328218,0.03524,0.0378454,0.0408671,
    0.0439875,0.0475773,0.0516154,0.056525,0.0624549,0.0673932,0.0684668,0.0693609,0.0709575,0.0722128,
};
double sigmaEtrackinv[30] = {
    0.376403,0.384468,0.404461,0.430379,0.457556,0.488072,0.51523,0.54436,0.583514,0.632923,
    0.680909,0.732482,0.781644,0.825365,0.877882,0.92438,0.98154,1.03785,1.09345,1.14982,
    1.2129,1.26695,1.32773,1.3895,1.45023,1.49101,1.5112,1.51046,1.50503,1.50032,
};
double sigmaETRDinv[30] = {
    0.0310838,0.032454,0.0346566,0.03652,0.0390786,0.0410365,0.0436906,0.0462605,0.0488414,0.0515805,
    0.0550246,0.0586362,0.0623192,0.066604,0.0705662,0.0748593,0.0790194,0.0829998,0.0879374,0.0929052,
    0.0977786,0.102692,0.107555,0.111683,0.115074,0.11642,0.113636,0.106789,0.100175,0.0968766,
};
double sigmabetainv[30] = {
    0,0,0,0,0,0,0.0573443,0.0520392,0.0432293,0.0379055,
    0.0338566,0.031517,0.0300254,0.0286459,0.0280898,0.0282138,0.028392,0.0288077,0.0291304,0.0298285,
    0.0304994,0.031135,0.0317889,0.0327064,0.0336424,0.0344406,0.0353335,0.0362057,0.036882,0.0370433,
};
double sigmaRinv[24] = {
    0.280547,0.208388,0.138526,0.107565,0.0813971,0.0620257,0.0478087,0.0371768,0.0291764,0.0230166,
    0.018266,0.0146563,0.0119114,0.00984922,0.00829814,0.00712708,0.00630916,0.00570447,0.00529572,
    0.00500545,0.00478513,0.00461041,0.00408276,0,
};
//////////////////////////////////////////////////////////////

/////////////////////// "Bethe-Blochs" ///////////////////////////////////////
double ETOF[30] = {
    7.33459,6.73154,6.21838,5.77933,5.41455,5.05503,4.76332,4.50384,4.24691,4.0454,
    3.82136,3.63074,3.45281,3.30736,3.15405,3.01766,2.88775,2.76864,2.6594,2.56601,
    2.46595,2.37101,2.29062,2.20088,2.10814,2.0407,1.97511,1.95733,1.94137,1.93476,
};
/*double ETrack[30] = {
		0.433866,0.403712,0.378137,0.354177,0.330174,0.309673,0.290184,0.275008,0.261107,0.246993,
		0.233908,0.221272,0.21022,0.199872,0.190632,0.182479,0.173477,0.167334,0.159739,0.15309,
		0.147908,0.142102,0.136652,0.131178,0.125278,0.122466,0.119541,0.118683,0.11835,0.118275,
};*/

double ETrack[30]={
    0.455469,	0.423853,	0.395121,	0.369948,	0.347769,	0.327987,	0.3103,  	0.294531,	0.280963,	0.269078,
    0.257223,	0.245605,	0.23467, 	0.2258, 	0.216827,	0.209071,	0.202184,	0.195579,	0.189428,	0.183676,
    0.179251,	0.173987,	0.168831,	0.163942,	0.160387,	0.156104,	0.154149,	0.153156,	0.152782,	0.152665
};


double ETRD[30] = {
    7.62645,7.38946,7.24668,6.92716,6.5943,6.16163,5.8724,5.65727,5.42682,5.15488,
    4.91008,4.66791,4.43929,4.24111,4.02018,3.82748,3.67884,3.48597,3.33569,3.20963,
    3.07584,2.95305,2.88637,2.74594,2.64957,2.6319,2.62964,2.64484,2.6624,2.68055,
};

////////////////////// Edep COrrecitons //////////////////////////
double CorrTOF[30] = {
    0.87745,0.8774,0.876843,0.880285,0.88604,0.886568,0.88934,0.892939,0.896916,0.902652,
    0.906289,0.908549,0.91285,0.916994,0.920442,0.923319,0.927292,0.930783,0.933816,0.936375,
    0.938598,0.940583,0.941729,0.9435,0.949729,0.962855,0.972775,0.97159,0.963259,0.954864,
};
double CorrTrack[30] = {
    1.18247,1.16855,1.14415,1.12406,1.10919,1.09773,1.08364,1.07224,1.06295,1.05666,
    1.05225,1.0484,1.04369,1.04191,1.04042,1.03791,1.03613,1.03537,1.03469,1.03276,
    1.02944,1.0283,1.02502,1.02152,1.02027,1.02103,1.02086,1.01645,1.01111,1.00803,
};
double CorrTRD[30] = {
    1.32576,1.3222,1.32926,1.33375,1.33092,1.33805,1.33699,1.34036,1.33705,1.33552,
    1.33315,1.33999,1.34244,1.34935,1.34776,1.34417,1.34091,1.33739,1.33758,1.33909,
    1.34156,1.34009,1.33849,1.33596,1.33436,1.32501,1.29415,1.2545,1.22218,1.20732,
};




////////////// SIGMA INVERSE //////////////////
//double sigmaEL1Uinv[30]={0.970957,1.04192,1.10556,1.14401,1.24219,1.26227,1.30781,1.35168,1.45222,1.47188,1.57204,1.73897,1.66397,1.81122,1.87095,2.03394,2.19796,2.21012,2.31127,2.5424,2.57978,2.74788,2.86475,3.11243,3.11764,3.2911,3.31339,3.33095,3.36837,3.43848,};
double sigmaEtofUinv[30]={
    0.0101297,0.0110989,0.0120282,0.0131133,0.0144645,0.0158628,0.0169694,0.0186552,0.02047,0.0220818,
    0.0236242,0.0256012,0.0279676,0.0301341,0.0326991,0.0355509,0.038673,0.0417572,0.0447985,0.0482951,
    0.05181,0.0555078,0.0596518,0.0640575,0.0704583,0.075315,0.0723733,0.0690903,0.0686398,0.0685094
};

double sigmaEtofDinv[30]={
    0.00853534,0.00903033,0.0101331,0.0115938,0.012811,0.0138879,0.0158775,0.0173705,0.0191504,0.0216741,
    0.0237663,0.0258621,0.0285843,0.031213,0.0335755,0.0369004,0.0395596,0.0435354,0.0464305,0.0504471,
    0.0527212,0.0580913,0.0618128,0.0653969,0.0748281,0.0804738,0.081752,0.0764883,0.0761559,0.0762702
};

//double sigmaEtrackinv[30]={0.41056,0.436897,0.462218,0.488687,0.51566,0.543865,0.573436,0.595749,0.629892,0.667451,0.697552,0.730861,0.764488,0.795942,0.826946,0.859546,0.896498,0.935313,0.9639,1.01319,1.04522,1.07816,1.13431,1.16763,1.19834,1.2238,1.24327,1.2485,1.26364,1.25528,};
//double sigmabetainv[30]={0,0,0,0,0,0.0929367,0.0565443,0.0437849,0.0379531,0.0341387,0.031662,0.029738,0.0288943,0.0279256,0.0275206,0.0276242,0.0277547,0.0282102,0.0286772,0.0292948,0.0299222,0.0308157,0.0313665,0.0322035,0.0331144,0.0338065,0.0344434,0.0353787,0.0359952,0.0362678,};
//double sigmaRinv[24]={0.348232,0.199008,0.127109,0.0903188,0.065722,0.0492337,0.0375834,0.029166,0.0230523,0.0181399,0.0145463,0.0119335,0.00979743,0.00829124,0.00724542,0.00635019,0.00567553,0.00530079,0.00503532,0.00483557,0.00472022,0.00448518,0.00443712,0,};
///////////////////////////////////////////////////////

////////////// CURVE TEORICHE //////////////////
//double EL1[30]={0.245547,0.237816,0.227947,0.219182,0.21111,0.202293,0.193406,0.186228,0.178492,0.170928,0.162972,0.156751,0.149985,0.14368,0.136937,0.130776,0.126023,0.120878,0.115004,0.11083,0.106096,0.101696,0.0966076,0.0935387,0.0900668,0.0871954,0.0861131,0.0857362,0.0856461,0.0857493,};
double ETOFU[30]={6.79949,6.45587,6.11214,5.79775,5.49986,5.20407,4.94075,4.6989,4.46422,4.24133,4.04447,3.84596,3.67633,3.51737,3.37001,3.21704,3.08622,2.98246,2.86636,2.75453,2.64742,2.54568,2.46139,2.35995,2.25499,2.15223,2.10089,2.07612,2.03444,2.02878,};
//double ETrack[30]={0.455469,0.423853,0.395121,0.369948,0.347769,0.327987,0.3103,0.294531,0.280963,0.269078,0.257223,0.245605,0.23467,0.2258,0.216827,0.209071,0.202184,0.195579,0.189428,0.183676,0.179251,0.173987,0.168831,0.163942,0.160387,0.156104,0.154149,0.153156,0.152782,0.152665,};
double ETOFD[30]={9.42785,8.40718,7.59028,6.93065,6.38188,5.91976,5.50794,5.14134,4.81215,4.52703,4.27131,4.05617,3.84279,3.66294,3.4782,3.32355,3.1771,3.04323,2.91502,2.79547,2.68128,2.59665,2.49237,2.38775,2.28355,2.21541,2.13379,2.10078,2.07869,2.02932,};







// Utility functions
template<typename T>
T Sum(const std::vector<T> & v) 
{ return std::accumulate(v.begin(),v.end(),0); }

double weightedDiff(double xTrue, double xMeasured, double sigma)
{ return (xTrue - xMeasured) / (pow(xTrue,2) * sigma); }


// Structure for distance variables 
struct DistanceData {
		double			TOF,			TRD,			Track;
		double	rMinTOF,	rMinTRD,	rMinTrack;
};

// This singleton class does all the work -- it reads the measured data 
// in the constructor. And then finds minimal "distance" by scanning
// true rigidity variable.
class DistanceMinimizer
{
    double rgdtMeasured; 
    double betaMeasured; 
    double etofMeasured; 
    double etrdMeasured; 
    double etrkMeasured;

    unsigned int nevt;

    TSpline3 * sigma_rgdt;
    TSpline3 * sigma_beta;
    TSpline3 * sigma_etof;
    TSpline3 * sigma_etrk;
    TSpline3 * sigma_etrd;
    TSpline3 * sigma_etofu;
    TSpline3 * sigma_etofd;

    TSpline3 * EdepTOFbeta;
    TSpline3 * EdepTrackbeta;
    TSpline3 * EdepTRDbeta;
    TSpline3 * EdepTOFUbeta;
    TSpline3 * EdepTOFDbeta;

    TSpline3 * Rgenmis;
    TSpline3 * CorrRICH;

    //////////////////////// Theoretic curves /////////////////////////////
    TF1 * protons = new TF1("fp","((x)^2/0.938^2/(1 + (x)^2/0.938^2))^0.5",0.1,100);
    TF1 * deutons = new TF1("fd","((x)^2/1.875^2/(1 + (x)^2/1.875^2))^0.5",0.1,100);

    // Laurent's added 3-polynomial of ETracker points
    // The degree 3 ensured that it was monotonic
    TF1* fETrackBeta = new TF1("fETrackBeta","pol3",0.4, 1);
    TF1* fETRDBeta	 = new TF1("fETRDBeta",	"pol2",0.4, 1);
    TF1* fETOFBeta	 = new TF1("fETOFBeta",	"pol5",0.4, 1);

public:

    float etofUMeas, etofDMeas, etofHMeas;

    DistanceMinimizer(): 
        rgdtMeasured(0), betaMeasured(40),
        etofMeasured(0), etrdMeasured(0), etrkMeasured(0)
    {
        ////////////// Defining splines	//////////////////
        sigma_rgdt	= new TSpline3("Cubic Spline", valorecent, sigmaRinv,			23);
        sigma_beta	= new TSpline3("Cubic Spline", betacent,	 sigmabetainv,	 30);
        sigma_etof	= new TSpline3("Cubic Spline", Beta_cent,	sigmaEtofinv,	 30);
        sigma_etrk	= new TSpline3("Cubic Spline", Beta_cent,	sigmaEtrackinv, 30);
        sigma_etrd	= new TSpline3("Cubic Spline", Beta_cent,	sigmaETRDinv,	 30);
        sigma_etofu	= new TSpline3("Cubic Spline", Beta_cent,	sigmaEtofUinv,	 30);
        sigma_etofd	= new TSpline3("Cubic Spline", Beta_cent,	sigmaEtofDinv,	 30);
        

        EdepTOFbeta	 = new TSpline3("Cubic Spline",Beta_cent,ETOF,30);
        EdepTrackbeta= new TSpline3("Cubic Spline",Beta_cent,ETrack,30);
        EdepTRDbeta	 = new TSpline3("Cubic Spline",Beta_cent,ETRD,30);
        EdepTOFUbeta = new TSpline3("Cubic Spline",Beta_cent,ETOFU,30);
        EdepTOFDbeta = new TSpline3("Cubic Spline",Beta_cent,ETOFD,30);

        Rgenmis			 = new TSpline3("",R_mis,R_gen,34);
        CorrRICH			= new TSpline3("",R_rich,Corr_rich,25);
    }

    void reset(Dst* dst)
    {
        rgdtMeasured = 0;
        betaMeasured = 0;

        etofMeasured = 0;
        etrdMeasured = 0;
        etrkMeasured = 0;

        etofUMeas=0;
        etofDMeas=0;
        etofHMeas=0;
        
        fETrackBeta->SetParameters(1.50051636, -4.04471459,	4.2095067 , -1.5178394);
        fETRDBeta	->SetParameters(17.69329971,	-30.2543069 ,	15.1275584 );
        fETOFBeta	->SetParameters(56.15254105, -276.13822103, 600.37793391, -668.0716316, 368.33924203, -78.73769398);

        // Ev initialisation
        AMSEventR* ev=dst -> ev;
        if( ev == NULL || dst -> tr == NULL || dst -> betaH == NULL ) return;
        nevt= ev -> Event();
        
        // Event rigidity, beta, various energies
        rgdtMeasured = dst -> tr -> GetRigidity();
        betaMeasured = dst -> betaH -> GetBeta();
        
        if (EdepTRD(ev) != -1 && NTRDclusters(ev) != -1)
        etrdMeasured = EdepTRD(ev) / NTRDclusters(ev);
    
        
        for (int i=0; i<ev->NTrCluster(); i++) {
            TrClusterR* pclus = ev->pTrCluster(i);
            int ilay = pclus->GetLayerJ();
            if (ilay<2 || ilay > 8 || pclus->GetSide()!=1 ) continue;
            etrkMeasured+=pclus->GetEdep();
        }
        etrkMeasured/=7; // because average per layer, layers 2-3-4-5-6-7-8


        for(int ic=0; ic<ev->NTofClusterH(); ic++) {
            TofClusterHR* pclus	= ev->pTofClusterH(ic);
            float edep          = pclus->GetEdep();
            if (pclus->Layer<=1)	etofUMeas+=edep;
            else                  etofDMeas+=edep;
            etofHMeas+=edep;
        }
        etofUMeas/=2;
        etofDMeas/=2;
        etofHMeas/=4;
        


        for(int ic=0; ic< ev -> NTofCluster() ; ic++)	 etofMeasured += ev->pTofCluster(ic)->Edep;
        etofMeasured/=4;
            
    }

    DistanceData FindMinimum(TF1 * RvsB, bool bprot) 
    {
        DistanceData distance;
        // Initialising 
        distance.TRD	 = 1000000; distance.rMinTRD	 = 0;
        distance.TOF	 = 1000000; distance.rMinTOF	 = 0;
        distance.Track = 1000000; distance.rMinTrack = 0; 

        //Checking that we're good
        if (rgdtMeasured <= 0) return distance;
        if (betaMeasured <= 0) return distance;
        if (betaMeasured >= 2) return distance;
        if (etofMeasured <= 0) return distance;
        if (etrdMeasured <= 0) return distance;
        if (etrkMeasured <= 0) return distance;


        // Scanning Rtrue and recording the minimal values for distance
        int DR1 = 0, DR2 = 0, DR3 = 0;
        double step = 0.05;
        float betaPrev=0;
        for(double rgdtTrue = 0; rgdtTrue < step * 1E6; rgdtTrue += step)
        {
            double betaTrue = RvsB->Eval(rgdtTrue);
            if (betaTrue<betaPrev+1e-5) continue;
            betaPrev=betaTrue;

            // Thist uses splines for the "theoretical values"
            double etofTrue = fETOFBeta	-> Eval(betaTrue);	 // tof is fine
            double etrdTrue = 1.5*fETRDBeta	 -> Eval(betaTrue);	 // dummy factor to have same mean with theoretical
            double etrkTrue = fETrackBeta -> Eval(betaTrue);	 // again, dummy factor
            double etofUMeas = EdepTOFUbeta -> Eval(betaTrue);
            double etofDMeas = EdepTOFUbeta -> Eval(betaTrue);

            double rgdtDist = weightedDiff(rgdtTrue, rgdtMeasured, sigma_rgdt->Eval(rgdtTrue));
            double betaDist = weightedDiff(betaTrue, betaMeasured, sigma_beta->Eval(betaTrue));
            double etofDist = weightedDiff(etofTrue, etofMeasured, sigma_etof->Eval(betaTrue));
            double etofuDist = weightedDiff(etofTrue,etofUMeas,   sigma_etofu->Eval(betaTrue));
            double etofdDist = weightedDiff(etofTrue,etofDMeas,   sigma_etofd->Eval(betaTrue));
            
            // tof fine for mean, untouched for sigmas ; two others take half-width sigma
            //double etrdDist = weightedDiff(etrdTrue, etrdMeasured, sigma_etrd->Eval(betaTrue));
            double etrkDist = weightedDiff(etrkTrue, etrkMeasured, sigma_etrk->Eval(betaTrue));
            double etrdDist = weightedDiff(etrdTrue, etrdMeasured, 1);
            //double etrkDist = weightedDiff(etrkTrue, etrkMeasured, 1.5);

            double CurrentTOF	 = pow(pow(rgdtDist,2) + pow(betaDist,2) + pow(etofDist,2), 0.5);
            double CurrentTRD	 = pow(pow(rgdtDist,2) + pow(betaDist,2) + pow(etrdDist,2), 0.5);
            double CurrentTrack = pow(pow(rgdtDist,2) + pow(betaDist,2) + pow(etrkDist,2), 0.5);

            if(CurrentTOF	 < distance.TOF)	 { DR1 = 0; distance.TOF	 = CurrentTOF;	 distance.rMinTOF	 = rgdtTrue;} else DR1++;
            if(CurrentTRD	 < distance.TRD)	 { DR2 = 0; distance.TRD	 = CurrentTRD;	 distance.rMinTRD	 = rgdtTrue;} else DR2++;
            if(CurrentTrack < distance.Track) { DR3 = 0; distance.Track = CurrentTrack; distance.rMinTrack = rgdtTrue;} else DR3++;

            if(DR1 > 25 && DR2 > 25 && DR3 > 25) break;
        }
    }

    void CalculateDistances()
    {
        protonDists = FindMinimum(protons, true);
        deutonDists = FindMinimum(deutons, false);
    }

public:
    // Two globals. I hate globals.
    DistanceData protonDists, deutonDists;
};

