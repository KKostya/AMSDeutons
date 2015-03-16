// std includes
#include <cmath>
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
#include "Selections/SelectionLists.hpp"
#include "Data.h"

double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};

inline float getSubCharge(ChargeR * charge,const char * name)
{
    if(!charge) return -1;
    ChargeSubDR * subcharge = charge->getSubD(name);
    if(!subcharge) return -1;
    return subcharge->Q;
}

int main(int argc, char * argv[])
{

    //Processing input options
    int c;
    int entries = 0;
    std::string outFname;
    std::string  inFname;
    while((c = getopt(argc, argv, "o:n:")) != -1) {
        if(c == 'o') outFname = std::string(optarg);
        if(c == 'n') entries = atoi(optarg);
    }
    if(outFname.empty()) outFname = std::string("ntuple.root");
    if (optind < argc) inFname = std::string(argv[optind++]); else return 1;

    std::cout << "Input file: " << inFname << std::endl;
    std::cout << "Output file: " << outFname << std::endl;

    // Opening input file
    AMSChain  * ch = new AMSChain;
    ch->Add(inFname.c_str());

    // Creating an output
    TFile * File = new TFile(outFname.c_str(), "RECREATE");

    TTree * outTree = new TTree("data","data");
    DataPresel  * pdata = new DataPresel(outTree); // I was forced to do it -- free() exception on destruction otherwise
    DataPresel &data = *pdata;


    TTree * geoTree = new TTree("dataigeo","datageo");
    DataGeo datageo(geoTree);

    // Preparing work data
    double tempozona[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int contasecondi[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int contaeventi = 0;

    /////////////////////////////////////////////////////////////////
    // Creating selections arrays
    /////////////////////////////////////////////////////////////////
    SelectionList geoSelections;
    AddGeoSelections    (geoSelections);

    SelectionList selections;
    AddGoldenSelections (selections);
    AddMinBiasSelections(selections);
    AddPreSelections    (selections);

    SelectionList richSelections;
    AddRICHSelections   (richSelections);

    std::map<std::string, std::pair<long,long> > counts;
    for(int nsel=0; nsel<geoSelections.size(); nsel++)
        counts[geoSelections[nsel].first] = std::make_pair(0,0);
    for(int nsel=0; nsel<selections.size(); nsel++)
        counts[selections[nsel].first] = std::make_pair(0,0);
    for(int nsel=0; nsel<richSelections.size(); nsel++)
        counts[richSelections[nsel].first] = std::make_pair(0,0);
    
    /////////////////////////////////////////////////////////////////
    // Event loop
    /////////////////////////////////////////////////////////////////
    if(entries == 0) entries = ch->GetEntries();
    std::cout << "\n Strating processing " << entries << " events.\n" << std::endl;
    for(int ii=0;ii<entries;ii++)
    { 
        bool eventPasses = true;
        AMSEventR * ev = ch->GetEvent();

        // Trigger part
        Level1R * trig = ev->pLevel1(0);
        if(trig && ((trig->PhysBPatt&1) == 1)) data.Unbias=1; else data.Unbias=0;
       
        // Looping over geometric/geomagnetinc selections 
        for(int nsel=0; nsel<geoSelections.size(); nsel++)
        {
            std::string name = geoSelections[nsel].first;
            bool thisPasses = geoSelections[nsel].second(ev);
            eventPasses = eventPasses && thisPasses;
            if(thisPasses) counts[name].first++;
            if(eventPasses) counts[name].second++;
        }
        // If doesn't pass Geometry/Geography/SAA e.t.c then skip event
        if (!eventPasses) continue;

        datageo.ThetaS   = ev->fHeader.ThetaS;
        datageo.PhiS     = ev->fHeader.PhiS;
        datageo.U_time   = ev->UTime();
        datageo.Livetime = ev->LiveTime();
        datageo.Latitude = fabs(ev->fHeader.ThetaM);


        if(ev->pParticle(0))
            datageo.Rcutoff = ev->pParticle(0)->Cutoff;
        else
            datageo.Rcutoff = -1;

        for(int i=0;i<12;i++){
            double geo= geomag[i]  ;
            double geo2=/*(i+1)/(double)10*/geomag[i+1];
            if(fabs(ev->fHeader.ThetaM)>geo && fabs(ev->fHeader.ThetaM)<geo2) 
                datageo.zonageo = i;
            else 
                tempozona[i]=ev->UTime();
        }
        geoTree->Fill();

        // Looping over selections 
        for(int nsel=0; nsel<selections.size(); nsel++)
        {
            std::string name = selections[nsel].first;
            bool thisPasses = selections[nsel].second(ev);
            eventPasses = eventPasses && thisPasses;
            if(thisPasses) counts[name].first++;
            if(eventPasses) counts[name].second++;
        }
        if(!eventPasses) continue;

        ChargeR *   charge   = ev->pCharge(0);
        TrTrackR *  track    = ev->pTrTrack(0);
        ParticleR *  particle    = ev->pParticle(0);
        
        data.Rcutoff = particle->Cutoff;
        data.EventNumber = ev->fHeader.Event;
        data.RunNumber = ev->fHeader.Run;

        // Charge
        data.CaricaTOF   = getSubCharge (charge,"AMSChargeTOF");         
        data.CaricaTRD   = getSubCharge (charge,"AMSChargeTRD");
        data.CaricaTrack = getSubCharge (charge,"AMSChargeTrackerInner");

        data.ProbQ = charge->getProb(0);
        data.Qbest = charge->Charge();

        // Tracker stuff
        int fitID1 = track->iTrTrackPar(1,1,1);
        int fitID2 = track->iTrTrackPar(1,2,1);
        int fitID3 = track->iTrTrackPar(1,3,1);
        TrTrackPar parametri = track->gTrTrackPar(fitID3);

        data.Rup      = track->GetRigidity(fitID1);
        data.Rdown    = track->GetRigidity(fitID2);
        data.R        = track->GetRigidity(fitID3);
        data.Chisquare= track->GetChisq(fitID3);

        int fit[6];
        fit[0] = 0x78211;  //  1111000 0010 0001 0001
        fit[1] = 0x63211;  //  1100011 0010 0001 0001
        fit[2] = 0x0f211;  //  0001111 0010 0001 0001
        fit[3] = 0x1c211;  //  0011100 0010 0001 0001
        fit[4] = 0x3f211;  //  0111111 0010 0001 0001
        fit[5] = 0x7e211;  //  1111110 0010 0001 0001

        for(int nFit=0; nFit<6; nFit++)
        {
            data.chiq[nFit] = track->FitT(fit[nFit],-1);
            data.R_[nFit]   = track->GetRigidity(fit[nFit]);
        }

        data.layernonusati = 0;
        for (int layer=2;layer<9;layer++) 
        {
            if(!parametri.TestHitLayerJ(layer)) data.layernonusati++;
            data.ResiduiX[layer-2]=-999999;
            data.ResiduiY[layer-2]=-999999;
            if(!track->TestHitLayerJ(layer)) continue;
            AMSPoint Residual_point = track->GetResidualJ(layer,fitID3);
            if(track->TestHitLayerJHasXY(layer))
                data.ResiduiX[layer-2] = Residual_point.x();
            data.ResiduiY[layer-2] = Residual_point.y(); // Theres always an Y hit
        }

        //Edep Tracker
        data.endepostatrack = 0;   
        for(int i=0; i<track->NTrRecHit();i++){
            TrRecHitR *hit=track->pTrRecHit(i);
            data.endepostatrack += hit->Sum();
        }

        //TRD
        data.EdepTRD      = 0;
        data.NTRDclusters = 0;
        for(int j = 0; j < ev->pTrdTrack(0)->NTrdSegment(); j++) 
        {
            TrdSegmentR * trdSegment = ev->pTrdTrack(0)->pTrdSegment(j);
            for(int i = 0;i < trdSegment->NTrdCluster(); i++) 
            {
                data.NTRDclusters++;
                data.EdepTRD += trdSegment->pTrdCluster(i)->EDep;
            }
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
        data.NTrackHits        = track->NTrRecHit(); 
        data.NTofClustersusati = ev->pBeta(0)->NTofCluster();

        // Beta and RICH
        data.Betacorr=0;
        if(particle->pBetaH()) data.Beta = particle->pBetaH()->GetBeta();
        if(data.Beta>=1) data.Betacorr = data.Beta/(2*data.Beta-1);
        else data.Betacorr = data.Beta;

        data.BetaRICH = -1;

        // Looping over roch selections 
        for(int nsel=0; nsel<richSelections.size(); nsel++)
        {
            std::string name = richSelections[nsel].first;
            bool thisPasses = richSelections[nsel].second(ev);
            eventPasses = eventPasses && thisPasses;
            if(thisPasses) counts[name].first++;
            if(eventPasses) counts[name].second++;
        }

        if (eventPasses) 
        {
            data.BetaRICH = ev->pRichRing(0)->getBeta();
            data.Betacorr = data.BetaRICH;
        }

        // Mass
        data.Massa = pow(fabs(pow(fabs(data.R)*pow((1-pow(data.Betacorr,2)),0.5)/data.Betacorr,2)),0.5);

        outTree->Fill();
        if(ii%10000==0) outTree->AutoSave();
    }
    File->Write();

    //Printing all the selection counts
    for(int nsel=0; nsel<geoSelections.size(); nsel++)
    {
        std::string name = geoSelections[nsel].first;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
    for(int nsel=0; nsel<selections.size(); nsel++)
    {
        std::string name = selections[nsel].first;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
    for(int nsel=0; nsel<richSelections.size(); nsel++)
    {
        std::string name = richSelections[nsel].first;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
}

