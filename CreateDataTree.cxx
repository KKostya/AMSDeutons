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

        // Geometry/Geography/SAA e.t.c//
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

        //       Minbias + Golden      //
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

        // Tracker stuff
        TrTrackR * Tr = ev->pTrTrack(0);
        int fitID1 = Tr->iTrTrackPar(1,1,1);
        int fitID2 = Tr->iTrTrackPar(1,2,1);
        int fitID3 = Tr->iTrTrackPar(1,3,1);
        TrTrackPar parametri = Tr->gTrTrackPar(fitID3);

        data.Rup      = Tr->GetRigidity(fitID1);
        data.Rdown    = Tr->GetRigidity(fitID2);
        data.R        = Tr->GetRigidity(fitID3);
        data.Chisquare= Tr->GetChisq(fitID3);

        float  chiq[6];
        int fit[6];
        double R_[6];

        fit[0]=0x200+0x10+0x1+0x8000+0x10000+0x20000+0x40000;
        fit[1]=0x200+0x10+0x1+0x1000+0x2000+0x20000+0x40000;
        fit[2]=0x200+0x10+0x1+0x4000+0x8000+0x1000+0x2000;
        fit[3]=0x200+0x10+0x1+0x4000+0x8000+0x10000;
        fit[4]=0x200+0x10+0x1+0x4000+0x8000+0x10000+0x20000+0x2000+0x1000;
        fit[5]=0x200+0x10+0x1+0x4000+0x8000+0x10000+0x20000+0x40000+0x2000;

        fitt[0] = 0x78211;  //  1111000001000010001
        fitt[1] = 0x63211;  //  1100011001000010001
        fitt[2] = 0x0f211;  //  0001111001000010001
        fitt[3] = 0x1c211;  //  0011100001000010001
        fitt[4] = 0x3f211;  //  0111111001000010001
        fitt[5] = 0x7e211;  //  1111110001000010001

        for(int nFit=0; nFit<6; nFit++)
        {
            chiq[nFit] = Tr->FitT(fit[nFit],-1);
            R_[nFit]   = Tr->GetRigidity(fit[nFit]);
        }

        for (int layer=2;layer<9;layer++) {
            ResiduiX[layer-2]=-999999;
            ResiduiY[layer-2]=-999999;
        }
        for(int layer=2;layer<9;layer++)  {
            if( ! Tr->TestHitLayerJ(layer)) continue;
            AMSPoint Residual_point=Tr->GetResidualJ(layer,fitID3);
            if(Tr->TestHitLayerJHasXY(layer) )
                ResiduiX[layer-2]=Residual_point.x();
            ResiduiY[layer-2]=Residual_point.y();
        }










        // Unused layers
        data.layernonusati = 0;
        for(int layer=2; layer<9; layer++)
            if(!parametri.TestHitLayerJ(layer)) layernonusati++;

        //Edep Tracker
        data.endepostatrack = 0;   
        for(int i=0; i<Tr->NTrRecHit();i++){
            TrRecHitR *hit=ev->pTrTrack(0)->pTrRecHit(i);
            data.endepostatrack += hit->Sum();
        }

        //Edep TRD
        data.EdepTRD      = 0;
        data.NTRDclusters = 0;
        for(int j = 0; j < ev->pTrdTrack(0)->NTrdSegment(); j++) 
        {
            TrdSegmentR * trdSegment = ev->pTrdTrack(0)->pTrdSegment(j);
            for(int i = 0;i < trdSegment->NTrdCluster(); i++) 
            {
                data.EdepTRD += trdSegment->pTrdCluster(i)->EDep;
                data.NTRDclusters++;
            }
        }

        int clusterusati=0;
        for(int j=0;j<ev->pTrdTrack(0)->NTrdSegment();j++) {
            for(int i=0;i<ev->pTrdTrack(0)->pTrdSegment(j)->NTrdCluster();i++) {
                clusterusati++;	
            }


        // TOF energy deposit
        for(int j=0; j<4; j++) data.Endep[j] = 0;
        for(int j=0; j<ev->NTofCluster(); j++)
            data.Endep[(ev->pTofCluster(j)->Layer)-1] = ev->pTofCluster(j)->Edep;

        // Counts
        data.NAnticluster      = ev->NAntiCluster();
        data.NTRDSegments      = ev->NTrdSegment();
        data.NTRDclusters      = ev->NTrdSegment();
        data.NTofClusters      = ev->NTofCluster();
        data.NTrackHits        = Tr->NTrRecHit(); 
        data.NTofClustersusati = ev->pBeta(0)->NTofCluster();

        // Mass
        data.Massa = pow(fabs(pow(fabs(R)*pow((1-pow(Betacorr,2)),0.5)/Betacorr,2)),0.5);


    }
}

