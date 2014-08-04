// This sets to use different TrTrack class --
// must be done before including AMSs' root.h
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif


#include "selezioni.h"
#include <TrTrackSelection.h>


using namespace std;
bool minimum_bias;
void IstoDeclaration(int mass,int enmin,int enmax);
int Enmin=5;
int Enmax=10;
int Mass=1;
int a=0;
int particelletot=0;
int eventiminimumbias=0;
int preselezionate=0;
int eventigolden=0;
int severity=0;
int minTRIGG=0;
int minTOF=0;
int minTRD=0;
int minTRACKER=0;
int golTRACKER=0;
int golTOF=0;
int golTRD=0;
int falsideut;
int anticluster=0;
int edeposta=0;
int hittracker=0;
int segmentitrd=0;
int clusterinutili=0;
int rigidityok=0;
int falsideutpre=0;
int deut=0;
int deut1=0;
int deut2=0;
int deut3=0;
int deut4=0;
int QTOF=0;
int QTrack=0;
int deut5=0;
int deut6=0;
int nprotoni=0;
float Massa=0;
int giovacch=0;
int buonfit1=0;
int buonfit2=0;
int residuiY=0;
int residuiX=0;
double errore=0.045;
int taglimiei=0;
float betacorr=0;
ParticleR* particella;
int edepostaTRD=0;
int edepostaTOF=0;
int edepostatracker=0;
int clusterTOF=0;
int clustertrack=0;

bool minimumbiasTRIGG(AMSEventR *ev);
bool minimumbiasTOF(AMSEventR *ev);
bool minimumbiasTRD(AMSEventR *ev);
bool minimumbiasTRIGG(AMSEventR *ev);
bool controllofit(AMSEventR* ev, int Fit) ;

int controlloprot=0;

AMSEventR* minimumbias(AMSEventR * ev,int fit);
AMSEventR* preselect(AMSEventR* ev);
AMSEventR* giovacchini(AMSEventR* ev);
AMSEventR* selezionadeutoni(AMSEventR* ev);

/*for(int i=0; i<23;i++)
{
 efficienzagen[i]=0;
 efficienzamis[i]=0;
 efficienzaver[i]=0;
}*/
TMatrixD  unfolding (23,23);



AMSEventR* minimumbias(AMSEventR * ev,int fit) {
    int c=0;
    bool bias[4];
    for(int i=0;i<4;i++) bias[i]=true;
    bias[0]=minimumbiasTRIGG(ev);
    if (bias[0]) minTRIGG++;
    bias[1]=minimumbiasTOF(ev);
     if (bias[1]) minTOF++;
    bias[2]=minimumbiasTRD(ev);
     if (bias[2]) minTRD++;
    bias[3]=minimumbiasTRACKER(ev,fit);
     if (bias[3]) minTRACKER++;
    for(int i=0; i<4; i++) if (!bias[i]) c++;
    if (c==0) 
     {
        eventiminimumbias++;
        return ev;
    }
    else return NULL;
}

AMSEventR* golden(AMSEventR * ev, int s, int fit) {
    int c=0;
    bool bias[3];
    for(int i=0;i<3;i++) bias[i]=true;
    bias[0]=goldenTRACKER(ev,s,fit);
     if (bias[0]) golTRACKER++;
    bias[1]=goldenTOF(ev,s,fit);
     if (bias[1]) golTOF++;
    bias[2]=goldenTRD(ev,s,fit);
     if (bias[2]) golTRD++;
    bias[3]=InTrdAcceptance(ev,s,fit);
    for(int i=0; i<3; i++) if (!bias[i]) c++;
    if (c==0) 
    {
        eventigolden++;
        return ev;
    }
    else return NULL;
}


bool minimumbiasTOF(AMSEventR *ev){
        //chiedo che almeno 4 layers del TOF abbiano un buon cluster
    int c=0;
    bool minimumbias=false;
        if (ev->nParticle()==0) return false;
    TofClusterR* cluster;
    bool goodlayer[4]={false,false,false,false};
    if(ev->nTofCluster()>0)
    {
        for(int ic=0;ic<ev->nTofCluster();ic++)
        {
            cluster=ev->pTofCluster(ic);
            bool good_c=false;
            if(cluster>0)
            {
                good_c=true;
                for(int i=7;i<13;i++)
                if((cluster->Status>>i)&1==1) good_c=false;
                if((cluster->Status>>2)&1==1) good_c=false;
                if((cluster->Status>>4)&1==1) good_c=false;
            }
            if(good_c) goodlayer[cluster->Layer-1]=true;
        }
    }
    for(int i=0;i<4;i++) if (goodlayer[i]) c++;
    if(c>3) minimumbias=true;
    BetaHR *betah=ev->pParticle(0)->pBetaH();
    if(!betah) return false;
            if(betah->IsGoodBeta()==false) minimumbias=false;
    return minimumbias;
}

bool minimumbiasTRIGG(AMSEventR *ev){
        //chiedo un numero di TOF trigger <=4	
    bool minimumbias=false;
    Level1R* level1=ev->pLevel1(0);
    if(level1>0){
        minimumbias=(level1->TofFlag1>=0&&level1->TofFlag1<5);
    }
    return minimumbias;
}

bool minimumbiasTRD(AMSEventR* ev){
        //chiedo un numero di TRDHSegment=2
    bool minimumbias=false;
    for(int i=0; /*i<ev->nTrdHTrack()*/i<1;i++){
        TrdHTrackR *traccia = ev-> pTrdHTrack(i);
        if(!traccia) continue;
        if(traccia->nTrdHSegment()==2) minimumbias=true;
    }
    return minimumbias;
}




bool minimumbiasTRACKER(AMSEventR *pev,int fit) 
{   		//chiedo che esista almeno un fit sui layer interni
    bool minimum_bias = false;
    if (pev->nTrTrack()<=0) return false;
    for(int i=0;i<pev->nTrTrack();i++) {
    TrTrackR* track = pev->pTrTrack(i);
    if (!track) continue;
    if(track->IsFake()) continue;
    Int_t fitID = track->iTrTrackPar(1, fit, 1);
    if (fitID < 0 || !track->ParExists(fitID)) continue;
    Double_t rgt = fabs(track->GetRigidity (fitID));
    Double_t csq = track->GetNormChisqY(fitID);
    if (rgt == 0 || csq < 0) continue;
    Int_t span = TrTrackSelection::GetSpanFlags(track) & 0xff;
    if (! (span & TrTrackSelection::kMaxInt)) continue;
    minimum_bias=true;
    }
return minimum_bias;
}


bool goldenTRACKER(AMSEventR *ev,int s,int fit)
{	//chiedo che il fit sui layer interni sia buono
    
    float quality=5-(s*10*20/100);
    TrTrackR* traccia=ev->pTrTrack(0);
    int fitID=traccia->iTrTrackPar(1,fit,1);
    if (fitID < 0 || !traccia->ParExists(fitID)) return false;
    Double_t rgt = fabs(traccia->GetRigidity (fitID));
    Double_t csq = traccia->GetNormChisqY(fitID);
    Double_t qtracciaY,qtracciaX;
    qtracciaY=traccia->GetNormChisqY(fitID);
    qtracciaX=traccia->GetNormChisqX(fitID);
    if(qtracciaY>5||qtracciaX>10) return false;
    else return true;
}  

bool goldenTOF(AMSEventR *ev,int s,int fit)
{	//chiedo che i cluster del TOF abbiano un buon match con la traccia
    int c=0;
    if (ev->nParticle()==0) return false;
    TrTrackR* track=ev->pTrTrack(0);
    int fitID=track->iTrTrackPar(1,fit,1);
    float LONGCUT[4][10]={9.,8.,8.,8.,8.,8.,8.,9.,0.,0.,
                  12.,8.,8.,8.,8.,8.,8.,12.,0.,0.,
                  12.,8.,8.,8.,8.,8.,8.,8.,8.,12.,
                  10.,8.,8.,8.,8.,8.,8.,10.,0.,0.,};
    float TRANCUT[4][10]={13.,6.,6.,6.,6.,6.,6.,13.,0.,0.,
                  14.,6.,6.,6.,6.,6.,6.,14.,0.,0.,
                  10.,6.,6.,6.,6.,6.,6.,6.,6.,10.,
                  14.,6.,6.,6.,6.,6.,6.,14.,0.,0.};	
    TofClusterR* cluster;
    bool good_match=false;
    double tlen;
    AMSPoint pnt;
    AMSDir dir;
    int longit[4]={0,1,1,0};
    int tranit[4]={1,0,0,1};
    double dlong,dtran;
    bool goodlayer[4]={false,false,false,false};
    for(int i=0; i<ev->nTofCluster();i++) 
    {
        cluster=ev->pTofCluster(i);
        if(cluster>0)
        {
            int layer=cluster->Layer-1;
            int bar=cluster->Bar-1;
            tlen=track->Interpolate(cluster->Coo[2],pnt,dir,fitID);
            dlong=cluster->Coo[longit[layer]]-pnt[longit[layer]];
            dtran=cluster->Coo[tranit[layer]]-pnt[tranit[layer]];
            if(fabs(dlong)<(LONGCUT[layer][bar])-(s*10*LONGCUT[layer][bar]/100) && fabs(dtran)<TRANCUT[layer][bar]-s*10*TRANCUT[layer][bar]/100)
                goodlayer[layer]=true;
        }
    }
    
    for(int i=0; i<4; i++)
        if(goodlayer[i]) c++;
    if(c>=3) good_match=true;
    BetaHR *betah=ev->pParticle(0)->pBetaH();
    if(!betah) return false;
        if(betah->IsTkTofMatch()==false) good_match=false;
    return good_match;
}

bool goldenTRD(AMSEventR* ev, int s,int fit) {
    //chiedo che la traccia del TRD sia compatibile con quella del TRACKER

    int TRDclustersontrack=0;
    if (!ev->pTrdTrack(0)) return false;
    for(int i=0;i<ev->pTrdTrack(0)->NTrdSegment();i++) {
    for(int j=0; j<ev->pTrdTrack(0)->pTrdSegment(i)->NTrdCluster();j++)
    TRDclustersontrack++;}

    TrTrackR* track=ev->pTrTrack(0);
    int fitID=track->iTrTrackPar(1,fit,1);
    bool golden=false;
    TrdHTrackR* trd_track;
    for(int i=0;/* i<ev->nTrdHTrack()*/i<1;i++)
    {
            trd_track=ev->pTrdHTrack(i);
            if(trd_track>0)
            {
                    int nHits=ev->nTrdRawHit();
                    int nHitsonTrack=trd_track->Nhits;
                    if(/*(nHitsonTrack/(float)(nHits))>0*/TRDclustersontrack/(double)ev->NTrdCluster()!=10000000000)
                    {
                            if(trd_track->status>0)
                            {
                                    AMSPoint pnt;
                                    AMSDir dir;
                                    TrTrackR* track=ev->pTrTrack(0);
                                    track->Interpolate(trd_track->Coo[2],pnt,dir,fitID);

                                    Double_t dtx=pnt.x()-trd_track->Coo[0];
                                    Double_t dty=pnt.y()-trd_track->Coo[1];
                                    if(dtx*dtx+dty*dty<(1.5-(s*10*1.5/100))*(1.5-(s*10*1.5/100))) golden=true;
                            }
                    }
            }
    }
    return golden;
}

bool InTrdAcceptance(AMSEventR* ev, int s,int fit){
  //check if particle passing inside acceptance of the 20 layers TRD                                                                                             
  TrTrackR* this_trk=ev->pTrTrack(0);
  int fitID=this_trk->iTrTrackPar(1,fit,1);
  if(!this_trk) return false;//return true to have the cutnotpassed evaluated more reasonably

  //only top layer and bottom layer checked
  //this is a gross check. A more fine tuned check is going to be provided by Aachen group

  int nTrdBottom = 9;
  float AccepBottomX[] = {+40, +78, +78, +40, -40, -78, -78, -40, +40};
  float AccepBottomY[] = {+76, +35, -35, -76, -76, -35, +35, +76, +76};
  float TrdBottomZ = 86.725;

  int nTrdCenter = 9;
  float AccepCenterX[] = {-80.0, -47.0, 47.0, 80.0,  80.0,  47.0, -47.0, -80.0, -80.0};
  float AccepCenterY[] = { 43.5,  75.5, 75.5, 43.5, -43.5, -75.5, -75.5, -43.5,  43.5};
  float TrdCenterZ = 0.5 * (141.825 +  86.725);//                                                                                                                                                                 
  int nTrdTop = 37;
  float AccepTopX[] = {-99.0,-89.0,-89.0,-78.7,-78.7,-67.8,-67.8,-57.7,-57.7, 57.7, 57.7, 67.8, 67.8, 78.7, 78.7, 89.0, 89.0, 99.0,
                       99.0, 89.0, 89.0, 78.7, 78.7, 67.8, 67.8, 57.7, 57.7,-57.7,-57.7,-67.8,-67.8,-78.7,-78.7,-89.0,-89.0,-99.0,-99.0};
  float AccepTopY[] = { 54.5, 54.5, 62.5, 62.5, 74.0, 74.0, 84.0, 84.0, 95.3, 95.3, 84.0, 84.0, 74.0, 74.0, 62.5, 62.5, 54.5, 54.5,
                        -51.7,-51.7,-62.2,-62.2,-72.0,-72.0,-82.5,-82.5,-92.5,-92.5,-82.5,-82.5,-72.0,-72.0,-62.2,-62.2,-51.7,-51.7, 54.5};
  float TrdTopZ = 141.825; //                                                                                                                                                                                     
  AMSPoint pTop, pCenter, pBottom;
  AMSDir   dTop, dCenter, dBottom;

  this_trk->Interpolate(TrdBottomZ, pBottom, dBottom, fitID);
  this_trk->Interpolate(TrdCenterZ, pCenter, dCenter, fitID);
  this_trk->Interpolate(TrdTopZ,    pTop,    dTop,    fitID);

  bool passTrdBottom = TMath::IsInside((float)pBottom.x(), (float)pBottom.y(), nTrdBottom, AccepBottomX, AccepBottomY);
  bool passTrdCenter = TMath::IsInside((float)pCenter.x(), (float)pCenter.y(), nTrdCenter, AccepCenterX, AccepCenterY);
  bool passTrdTop    = TMath::IsInside((float)pTop.x(),    (float)pTop.y(),    nTrdTop,    AccepTopX,    AccepTopY);

  return (passTrdTop && passTrdBottom);
}


AMSEventR* preselect ( AMSEventR* ev) {
    //chiedo eventi con una particella,una traccia, un beta e carica =1
    if(ev->nParticle()==1)
    particelletot++;
    if(ev->nParticle()==1)
    {
        ParticleR* particella = ev->pParticle(0);
        Beta=particella->pBetaH()->GetBeta();
        if(ev->nTrTrack()==1 &&  ev->NTrdTrack()>=1 && Beta>0 && particella->pCharge()->Charge()==1&&Beta<8)
        {	
            preselezionate++;
            return ev;
        }
         else return NULL;
    }
    else  return NULL;	
}


AMSEventR* giovacchiniRICH (AMSEventR* ev) {
    if(ev->NRichRing()<1|| !ev->pRichRing(0)/*||!ev->pRichRingB(0)*/||ev->NRichRing()>1) return NULL;
    RichRingR* anello= ev->pRichRing(0);
    if(anello->getHits()>=5 &&anello->getExpectedPhotoelectrons()/anello->getPhotoElectrons()>0.4 && anello->getExpectedPhotoelectrons()/anello->getPhotoElectrons()<2&&anello->getProb()>0.2) {
        int totali= ev->NRichHit();
        int hotspots=0;
        int usate=ev->pRichRing(0)->Used;
        int usatebis=0;

        for(int i=0;i<ev->NRichHit();i++)
        {
            RichHitR* Hit= ev->pRichHit(i);
            if(Hit->UsedInRingNumber (0)) usatebis++;
            if(Hit->IsCrossed()) hotspots++;
        }
    //la prima è diversa sui dati	
        if(totali-usate-hotspots<5&&((ev->pParticle(0)->pBeta()->Beta)-anello->getBeta())/(ev->pParticle(0)->pBeta()->Beta)<0.1/*&&(ev->pRichRingB(0)->getBetaConsistency()/anello->getBeta())<0.001*/&&!ev->pRichRing(0)->IsNaF()) 
        return ev;
        else return NULL;
    } 
    else return NULL;
} 
		




