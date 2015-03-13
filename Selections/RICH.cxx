#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "RICH.h"

bool    aRing(AMSEventR * ev) { return ev->NRichRing() >= 1; }
bool  oneRing(AMSEventR * ev) { return ev->NRichRing() == 1; }


float cut_prob=0.01;                        //  Kolmogorov test probability 
float cut_pmt=3;                            //  number of pmts
float cut_collovertotal=0.4;                //  ring photoelctrons / total photoelectrons in the event 
float cut_chargeconsistency=10;             //  hit/PMT charge consistency test
float cut_betaconsistency[2]={0.01,0.005};  //  beta_lip vs beta_ciemat consistency ([0]=NaF, [1]=aerogel) 
float cut_expphe[2]={1,2};                  //  expected number of photoelectrons   ([0]=NaF, [1]=aerogel)
float cut_aerogelexternalborder=3500.;      //  aerogel external border (r**2)
float cut_aerogel_nafborder[2]={17.,19.};   //  aerogel/NaF border                  ([0]=NaF, [1]=aerogel)

inline RichRingR * R(AMSEventR * ev){ return ev->pRichRing(0); }

bool     noNaF(AMSEventR * ev) { return R(ev) && R(ev)->IsNaF(); } 
bool ringGood (AMSEventR * ev) { return R(ev) && R(ev)->IsGood(); }
bool ringClean(AMSEventR * ev) { return R(ev) && R(ev)->IsClean(); }
bool ringProb (AMSEventR * ev) { return R(ev) && R(ev)->getProb() >= cut_prob; }
bool ringPMTs (AMSEventR * ev) { return R(ev) && R(ev)->getPMTs() >= cut_pmt; }

bool ringChargeConsistency (AMSEventR * ev) 
{ return R(ev) && R(ev)->getPMTChargeConsistency() <= cut_chargeconsistency; }

bool ringPhotoElectrons (AMSEventR * ev) 
{ 
    RichRingR * ring = R(ev); if(!ring ) return false;
    float totPhEl = RichHitR::getCollectedPhotoElectrons();
    return R(ev)->getPhotoElectrons()/totPhEl >= cut_collovertotal;
}

bool ringExpPhe (AMSEventR * ev) 
{ return R(ev) && R(ev)->getExpectedPhotoelectrons() >= cut_expphe[0]; }

bool ringBetaCons (AMSEventR * ev) 
{ return R(ev) && R(ev)->getBetaConsistency() <= cut_betaconsistency[0]; }

bool ringNaFBorder (AMSEventR * ev) 
{
    RichRingR * ring = R(ev); if(!ring ) return false;
    float x=ring->getTrackEmissionPoint()[0];
    float y=ring->getTrackEmissionPoint()[1];
    return max(abs(x),abs(y)) <= cut_aerogel_nafborder[0];
}

///////////////////////////////////
// Old selections
///////////////////////////////////

bool ringHits (AMSEventR * ev) { return R(ev) && R(ev)->getHits() >= 5; }

bool photFracG04(AMSEventR * ev) { 
    RichRingR * ring= ev->pRichRing(0);
    if(!ring) return false;
    return ring->getExpectedPhotoelectrons()/ring->getPhotoElectrons()>0.4; 
}

bool photFracL2(AMSEventR * ev) { 
    RichRingR * anello= ev->pRichRing(0);
    if(!anello) return false;
    return anello->getExpectedPhotoelectrons()/anello->getPhotoElectrons()<2; 
}


bool betaDisp(AMSEventR * ev) { 
    RichRingR * anello= ev->pRichRing(0);
    if(!anello) return false;
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pBeta()) return false;
    double beta = ev->pParticle(0)->pBeta()->Beta;
    return (beta - anello->getBeta()) / beta < 0.1;
}

bool counts5(AMSEventR * ev) { 
    RichRingR * anello= ev->pRichRing(0);
    if(!anello) return false;
    if(anello->getHits() < 5) return false;

    int totali = ev->NRichHit();
    int  usate = ev->pRichRing(0)->Used;
    int hotspots = 0;
    int usatebis = 0;
    for(int i=0; i<ev->NRichHit(); i++)
    {
        RichHitR * Hit = ev->pRichHit(i);
        if(Hit->UsedInRingNumber(0)) usatebis++;
        if(Hit->IsCrossed()) hotspots++;
    }
    return totali-usate-hotspots < 5;
}

