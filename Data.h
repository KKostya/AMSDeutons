#ifndef DATA_H_
#define DATA_H_

#include <vector>
#include <TTree.h>
#include <TNtuple.h>

struct DataCorr;

// Structure for geometric/geographic/geomagnetic data
struct DataGeo
{
    int EventNumber;
    int U_time, zonageo;
    float Latitude, ThetaS, PhiS;
    float Rcutoff;
    float Unbias;
    float Livetime;

    DataGeo(TTree * tree); // Constructor
};

// Data from MC Truth
struct DataMC
{
    float Momento_gen, Beta_gen, Massa_gen;

    DataMC(TTree * tree); // Constructor
};

// Structure for the detector response
struct DataPresel: public DataMC
{
    int EventNumber;

    int Trig_Num;
    float CaricaTOF, CaricaTRD, CaricaTrack;
    float ProbQ, Qbest;
    std::vector<float> * Endep;
    int layernonusati;
    int NAnticluster;    
    int NTRDSegments;     
    int NTofClusters;     
    int NTofClustersusati;
    int NTRDclusters;
    int NTrackHits;
    double Rup, Rdown, R;
    float Chisquare;
    std::vector<double> * ResiduiX;
    std::vector<double> * ResiduiY;         
    std::vector<float> * chiq;
    std::vector<float> * R_;
    float Beta, Betacorr, BetaRICH;
    float EdepTRD, endepostatrack;
    std::vector<float> * TRDclusters;
    std::vector<float> * clusterTrack;
    float Massa;

    DataPresel(TTree * tree); // Constructor
};

#endif
