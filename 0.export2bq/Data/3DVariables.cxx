#include <vector>
#include <numeric>

#include "TF1.h"
#include "TMath.h"

class AMSEventR;

#include "TOF.h"
#include "TRD.h"
#include "Tracker.h"



// Utility functions
template<typename T>
T Sum(const std::vector<T> & v) 
{ return std::accumulate(v.begin(),v.end(),0); }

double weightedDiff(double xTrue, double xMeasured, double sigma)
{ return (xTrue - xMeasured) / (pow(xTrue,2) * sigma); }


// Structure for distance variables 
struct DistanceData {
    double      TOF,      TRD,      Track;
    double  rMinTOF,  rMinTRD,  rMinTrack;
};

enum ParticleSpecies{
    kProton,
    kDeuton
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

    TSpline3 * sigma_rgdt;
    TSpline3 * sigma_beta;
    TSpline3 * sigma_etof;
    TSpline3 * sigma_etrk;
    TSpline3 * sigma_etrd;

    TSpline3 * EdepTOFbeta;
    TSpline3 * EdepTrackbeta;
    TSpline3 * EdepTRDbeta;

    TSpline3 * Corr_TOF;
    TSpline3 * Corr_Track;
    TSpline3 * Corr_TRD;

    TSpline3 * Rgenmis;
    TSpline3 * CorrRICH;

    TF1 * protonCurve;
    TF1 * deutonCurve;

    // the singleton
    static DistanceMinimizer* gDistanceMinimizer;

    DistanceMinimizer() : rgdtMeasured(0), 
                          betaMeasured(0),
                          etofMeasured(0),
                          etrdMeasured(0),
                          etrkMeasured(0)
    {
        ////////////// Bin centers //////////////////
        double betaTrueArray[30] = {
            0.41,0.43,0.45,0.47,0.49,0.51,0.53,0.55,0.57,0.59,
            0.61,0.63,0.65,0.67,0.69,0.71,0.73,0.75,0.77,0.79,
            0.81,0.83,0.85,0.87,0.89,0.91,0.93,0.95,0.97,0.99,
        };

        double betaTrueArrayForSigmaBetaInv[30] = {
            0,0.01,0.02,0.03,0.04,0.05,0.415919,0.453355,0.488411,0.520469,
            0.550179,0.578353,0.605235,0.631148,0.656092,0.680222,0.703866,
            0.726883,0.749455,0.771762,0.793729, 0.81529,0.836695,0.857886,
            0.878908,0.899705,0.920224,0.940778,0.961202,0.981896,
        };

        double rgdtTrueArray[24] = {
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

        //////////////////  RICH Correcitons //////////////////////
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
        double ETrack[30] = {
            0.433866,0.403712,0.378137,0.354177,0.330174,0.309673,0.290184,0.275008,0.261107,0.246993,
            0.233908,0.221272,0.21022,0.199872,0.190632,0.182479,0.173477,0.167334,0.159739,0.15309,
            0.147908,0.142102,0.136652,0.131178,0.125278,0.122466,0.119541,0.118683,0.11835,0.118275,
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

        ////////////// Defining splines  //////////////////
        sigma_rgdt  = new TSpline3("Cubic Spline", rgdtTrueArray, sigmaRinv,      23);
        sigma_beta  = new TSpline3("Cubic Spline", betaTrueArrayForSigmaBetaInv,   sigmabetainv,   30);
        sigma_etof  = new TSpline3("Cubic Spline", betaTrueArray,  sigmaEtofinv,   30);
        sigma_etrk  = new TSpline3("Cubic Spline", betaTrueArray,  sigmaEtrackinv, 30);
        sigma_etrd  = new TSpline3("Cubic Spline", betaTrueArray,  sigmaETRDinv,   30);

        EdepTOFbeta   = new TSpline3("Cubic Spline",betaTrueArray,ETOF,30);
        EdepTrackbeta = new TSpline3("Cubic Spline",betaTrueArray,ETrack,30);
        EdepTRDbeta   = new TSpline3("Cubic Spline",betaTrueArray,ETRD,30);

        Corr_TOF      = new TSpline3("Cubic Spline",betaTrueArray,CorrTOF,30);
        Corr_Track    = new TSpline3("Cubic Spline",betaTrueArray,CorrTrack,30);
        Corr_TRD      = new TSpline3("Cubic Spline",betaTrueArray,CorrTRD,30);

        Rgenmis       = new TSpline3("",R_mis,R_gen,34);
        CorrRICH      = new TSpline3("",R_rich,Corr_rich,25);

        //////////////////////// Theoretic curves /////////////////////////////
        protonCurve = new TF1("f1","((x)^2/0.938^2/(1 + (x)^2/0.938^2))^0.5",0.1,100);
        deutonCurve = new TF1("f1","((x)^2/1.875^2/(1 + (x)^2/1.875^2))^0.5",0,100);
    }

public:
    static DistanceMinimizer* getDistanceMinimizer(AMSEventR * ev){
        if( gDistanceMinimizer == NULL ) gDistanceMinimizer = new DistanceMinimizer();
        return gDistanceMinimizer;
    }

    void update(AMSEventR * ev){
        rgdtMeasured = R(ev); // call to Tracker R(AMSEvent * ev)
        betaMeasured = BetaTOF(ev); 
        etofMeasured = Sum(EdepTOF(ev))/4; // The average over 4 TOF planes
        etrdMeasured = EdepTRD(ev) / NTRDclusters(ev);

        std::vector<float> eTrackX = EDepLayerX(ev); eTrackX[0] = 0; eTrackX[8] = 0;
        std::vector<float> eTrackY = EDepLayerY(ev); eTrackY[0] = 0; eTrackY[8] = 0;

        etrkMeasured = (Sum(eTrackX) + Sum(eTrackY))/14;
    }

    DistanceData FindMinimum(ParticleSpecies part) 
    {
        TF1 * RvsB;
        if( part == kProton ) RvsB = protonCurve;
        else if( part == kDeuton ) RvsB = deutonCurve;
        else{
            std::cout << "Unknown particle type : " << part << " in DistanceMinimizer::FindMinimum" << endl;
            exit(-1);
        }

        DistanceData distance;
        // Initialising 
        distance.TRD   = 1000000; distance.rMinTRD   = 0;
        distance.TOF   = 1000000; distance.rMinTOF   = 0;
        distance.Track = 1000000; distance.rMinTrack = 0; 

        //Checking that we're good
        if(rgdtMeasured <= 0) return distance;
        if(betaMeasured <= 0) return distance;
        if(betaMeasured >= 2) return distance;
        if(etofMeasured <= 0) return distance;
        if(etrdMeasured <= 0) return distance;
        if(etrkMeasured <= 0) return distance;

        // Scanning Rtrue and recording the minimal values for distance
        int DR1 = 0, DR2 = 0, DR3 = 0;
        double step = 0.05;
        for(double rgdtTrue = 0; rgdtTrue < step * 1E6; rgdtTrue += step)
        {
            double betaTrue = RvsB->Eval(rgdtTrue);

            // Thist uses splines for the "theoretical values"
            double etofTrue = EdepTOFbeta  -> Eval(betaTrue);  
            double etrdTrue = EdepTRDbeta  -> Eval(betaTrue);  
            double etrkTrue = EdepTrackbeta-> Eval(betaTrue);  

            double rgdtDist = weightedDiff(rgdtTrue, rgdtMeasured, sigma_rgdt->Eval(rgdtTrue));
            double betaDist = weightedDiff(betaTrue, betaMeasured, sigma_beta->Eval(betaTrue));
            double etofDist = weightedDiff(etofTrue, etofMeasured, sigma_etof->Eval(betaTrue));
            double etrdDist = weightedDiff(etrdTrue, etrdMeasured, sigma_etrd->Eval(betaTrue));
            double etrkDist = weightedDiff(etrkTrue, etrkMeasured, sigma_etrk->Eval(betaTrue));

            double CurrentTOF   = pow(pow(rgdtDist,2) + pow(betaDist,2) + pow(etofDist,2), 0.5);
            double CurrentTRD   = pow(pow(rgdtDist,2) + pow(betaDist,2) + pow(etrdDist,2), 0.5);
            double CurrentTrack = pow(pow(rgdtDist,2) + pow(betaDist,2) + pow(etrkDist,2), 0.5);

            if(CurrentTOF   < distance.TOF)   { DR1 = 0; distance.TOF   = CurrentTOF;   distance.rMinTOF   = rgdtTrue;} else DR1++;
            if(CurrentTRD   < distance.TRD)   { DR2 = 0; distance.TRD   = CurrentTRD;   distance.rMinTRD   = rgdtTrue;} else DR2++;
            if(CurrentTrack < distance.Track) { DR3 = 0; distance.Track = CurrentTrack; distance.rMinTrack = rgdtTrue;} else DR3++;

            if(DR1 > 25 && DR2 > 25 && DR3 > 25) break;
        }
    }
};

// Initialization of the singleton
DistanceMinimizer* DistanceMinimizer::gDistanceMinimizer = NULL;


// Two globals. I hate globals.
DistanceData protonDists, deutonDists;

//
//   Exported functions start from here
//

//That claculates distances and populates the globals
void CalculateDistances(AMSEventR * ev)
{
    DistanceMinimizer* minimizer = DistanceMinimizer::getDistanceMinimizer(ev);
    minimizer -> update(ev);

    protonDists = minimizer -> FindMinimum(kProton);
    deutonDists = minimizer -> FindMinimum(kDeuton);
}

double DistanceTOF_P      (AMSEventR * ev) { return protonDists.TOF;       }
double DistanceTRD_P      (AMSEventR * ev) { return protonDists.TRD;       }
double DistanceTracker_P  (AMSEventR * ev) { return protonDists.Track;     }
double MLRigidityTOF_P    (AMSEventR * ev) { return protonDists.rMinTOF;   }
double MLRigidityTRD_P    (AMSEventR * ev) { return protonDists.rMinTRD;   }
double MLRigidityTracker_P(AMSEventR * ev) { return protonDists.rMinTrack; }

double DistanceTOF_D      (AMSEventR * ev) { return deutonDists.TOF;       }
double DistanceTRD_D      (AMSEventR * ev) { return deutonDists.TRD;       }
double DistanceTracker_D  (AMSEventR * ev) { return deutonDists.Track;     }
double MLRigidityTOF_D    (AMSEventR * ev) { return deutonDists.rMinTOF;   }
double MLRigidityTRD_D    (AMSEventR * ev) { return deutonDists.rMinTRD;   }
double MLRigidityTracker_D(AMSEventR * ev) { return deutonDists.rMinTrack; }

