// std includes
#include <math>
#include <vector>
#include <string>
#include <iostream>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif

#include <amschain.h>

// local includes
#include "Selections/Geo.h"
#include "Selections/Golden.h"
#include "Selections/MinBias.h"
#include "Data.h"

double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};

inline float getSubCharge(ChargeR * charge,const char * name)
{
    ChargeSubDR * subcharge = charge->getSubD(name);
    if(subcharge) return -1;
    return subcharge->Q;
}


int main(int argc, char * argv[])
{
    if(argc < 2) return 1;

    // Opening input file
    AMSChain  * ch = new AMSChain;
    ch->Add(argv[1]);

    // Creating an output
    TFile * File = new TFile("ntuple.root", "RECREATE");
    TTree * outTree = new TTree("data","data");
    DataPresel data(outTree);


    // Preparing work data
    double tempozona[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int contasecondi[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int contaeventi = 0;
    
    /////////////////////////////////////////////////////////////////
    // Event loop
    /////////////////////////////////////////////////////////////////
    int entries = ch->GetEntries();
    for(int ii=0;ii<entries;ii++)
    { 
        AMSEventR * ev = ch->GetEvent();

        // Trigger part
        Level1R * trig = ev->pLevel1(0);
        if((trig->PhysBPatt&1) == 1) data.Unbias=1; else data.Unbias=0;

        /////////////////////////////////
        // Geometry/Geography/SAA e.t.c//
        /////////////////////////////////
        if (!GeoSelection(ev)) continue;

        data.ThetaS   = ev->fHeader.ThetaS;
        data.PhiS     = ev->fHeader.PhiS;
        data.U_time   = ev->UTime();
        data.Livetime = ev->LiveTime();
        data.Latitude = fabs(ev->fHeader.ThetaM);

        for(int i=0;i<12;i++){
            double geo= geomag[i]  ;
            double geo2=/*(i+1)/(double)10*/geomag[i+1];
            if(fabs(ev->fHeader.ThetaM)>geo && fabs(ev->fHeader.ThetaM)<geo2) 
                data.zonageo = i;
            else 
                tempozona[i]=ev->UTime();
        }

        /////////////////////////////////
        //       Minbias + Golden      //
        /////////////////////////////////
        bool   minBias =      MinBias(ev);
        bool    golden =       Golden(ev);
        bool preselect = Preselection(ev);

        data.Rcutoff = ev->pParticle(0)->Cutoff;

        // Charge
        ChargeR * carica= ev->pCharge(0);
        data.CaricaTOF   = getSubCharge (carica,"AMSChargeTOF");         
        data.CaricaTRD   = getSubCharge (carica,"AMSChargeTRD");
        data.CaricaTrack = getSubCharge (carica,"AMSChargeTrackerInner");

        data.ProbQ = carica->getProb(0);
        data.Qbest = carica->Charge();

        // Energy dependence
        for(int j=0; j<4; j++) data.Endep[j] = 0;
        for(int j=0; j<ev->NTofCluster(); j++)
            Endep[(ev->pTofCluster(j)->Layer)-1]=ev->pTofCluster(j)->Edep;

        // Counts
        data.NAnticluster      = ev->NAntiCluster();
        data.NTRDSegments      = ev->NTrdSegment();
        data.NTofClusters      = ev->NTofCluster();
        data.NTofClustersusati = ev->pBeta(0)->NTofCluster();

        TrTrackR * Tr = ev->pTrTrack(0);
        int fitID1 = Tr->iTrTrackPar(1,1,1);
        int fitID2 = Tr->iTrTrackPar(1,2,1);
        int fitID3 = Tr->iTrTrackPar(1,3,1);


    }
}

