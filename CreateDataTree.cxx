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
#include "Data.h"
#include "SAA.h"

double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};

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

        // Geometry/Geography/SAA e.t.c
        data.ThetaS   = ev->fHeader.ThetaS;
        data.PhiS     = ev->fHeader.PhiS;
        if(!saa(data.PhiS, data.ThetaS)) continue;

        if(ev->fHeader.RunType <= 61442) continue;
        if(ev->fHeader.Zenith() > 25) continue; // Angle between zenith and Z

        int zona = 0;

        for(int i=0;i<12;i++)
        {
            // Are we sure this is the best way to get geomagnetic zone?
            double geo  = geomag[i];
            double geo2 =/*(i+1)/(double)10*/geomag[i+1];
            if(fabs(data.ThetaM) > geo && fabs(data.ThetaM)<geo2) 
                zona = i;
            else
                tempozona[i] = ev->UTime();
        }

        if(zona == 0) continue; 
        contaeventi++;

        data.U_time   = ev->UTime();
        data.Livetime = ev->LiveTime();
        data.Latitude = fabs(ev->fHeader.ThetaM);
        data.zonageo  = zona;
        if(ev->pParticle(0)) data.Rcutoff = ev->pParticle(0)->Cutoff;
        //14.9*pow((cos(((zona/(float)10+0.5)/(double)10))),4);	
        

    }
}

