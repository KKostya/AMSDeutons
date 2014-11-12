/*#include <cstdio>
// #include <iomanip>
//
#include "root.h"
#include "HistoMan.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <TVector3.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstring>
#include "TMath.h"
#include <TrTrackSelection.h>
#include <stdio.h>*/

#include <vector>
#include <string>
#include <iostream>

#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif

#include <amschain.h>
#include "selezioni.h"


//#include <TSpline.h>
//#include </afs/cern.ch/work/f/fdimicco/private/Dimiccoli/Functions.h>

using namespace std;
long double bin[24];
double efficienzagen[23];
double efficienzamis[23][11];
double efficienzadeut[23][11];
double primari[23][11];
double efficienzaver[23];
double preselez[23];
std::vector<float> Time(11);
//long long double Utime=0; <-- unused
double tbeg,tend;
double tempozona[11]={0,0,0,0,0,0,0,0,0,0,0};
int contasecondi[11]={0,0,0,0,0,0,0,0,0,0,0};
int zona;
int controllogiov=0;
int contaeventi=0;
double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};
bool  deutoni(AMSEventR* ev);
int severity=0;
int U_time;
float Latitude;
float Chisquare=0;
int zonageo;
float Rcutoff;
float CaricaTOF=0;
float CaricaTRD=0;
float CaricaTrack=0;
float ProbQ=0;
float Qbest=0;
std::vector<float> Endep(4);
int layernonusati=0;
int NAnticluster=0;
int NTRDSegments=0;
int NTofClusters=0;
int NTofClustersusati=0;
double Rup=0;
double Rdown=0;
double R=0;
std::vector<float> chiq(6);
std::vector<float> R_(6);
float Beta=0;
float Betacorr=0;
std::vector<double> ResiduiX(7);
std::vector<double> ResiduiY(7);
float BetaRICH=-1;
float Massa=0;
int Ev_Num=0;
float EdepTRD=0;
int NTRDclusters=0;
std::vector<float> TRDclusters(1000);
 float endepostatrack=0;
int NTrackHits=0;
std::vector<float> clusterTrack(1000);
float Livetime=0;
int fit=3;
//////////////// ANALISI PRESELEZIONE /////////////////////////////
int nclusterTOFbuoni=0;
int nTOFflag=0;
int nTRDHSegment=0;
int minbiastrack=0;
float chisqX=0;
float chisqY=0;
int nTOFclustermatching=0;
float dxTRD=0;
float dyTRD=0;
int InTRDAcceptance=0;
int nTrTracks=0;
int nTRDtracks=0;
float Beta_pre=0;
float R_pre=0;
int nPart=0;
///////////////////////////////////////
float cosThetaTOF=0;
float cosPhiTOF=0;
float cosThetaTrack=0;
float cosPhiTrack=0;
float cosThetaTRD=0;
float cosPhiTRD=0;
float CooTOF[3]={0,0,0};
float CooTrack[3]={0,0,0};
float CooTRD[3]={0,0,0};
float RGDT=0;
float distR=0;
float distB=0;
float distETOF=0;
float distETrack=0;
float distETRD=0;
float DistTOF=0;
float DistTrack=0;
float DistTRD=0;
float ThetaS=0;
float PhiS=0;
int DR1,DR2,DR3=0;
float Unbias=0;
int controlloRICH=0;

bool saa(float phi,float theta);

int main(int argc, char * argv[])
{

    float E=-1.203972804;
    float EM=6.66722056;
    float a=(EM-E)/23;
    for(int i=0;i<11;i++) Time[i]=0;

    if(argc < 2) return 1;

    // Opening input file
    AMSChain  * ch = new AMSChain;
    ch->Add(argv[1]);

    // Creating an output
    TFile * File = new TFile("ntuple.root", "RECREATE");

    int entries = ch->GetEntries();

    cout<<entries<<endl;

    TTree *measure_stuff= new TTree("parametri_geo","parametri_geo");
    TTree *cut_stuff = new TTree("grandezze_tagli","grandezze_tagli");
    measure_stuff->Branch("U_time",&U_time);
    measure_stuff->Branch("Latitude",&Latitude);
    measure_stuff->Branch("zonageo",&zonageo);
    measure_stuff->Branch("Rcutoff",&Rcutoff);
    measure_stuff->Branch("Livetime",&Livetime);
    measure_stuff->Branch("ThetaS",&ThetaS);
    measure_stuff->Branch("PhiS",&PhiS);
    measure_stuff->Branch("Unbias",&Unbias);

    cut_stuff->Branch("Livetime",&Livetime);
    cut_stuff->Branch("U_time",&U_time);
    cut_stuff->Branch("Latitude",&Latitude);
    cut_stuff->Branch("ThetaS",&ThetaS);
    cut_stuff->Branch("PhiS",&PhiS);
    cut_stuff->Branch("Rcutoff",&Rcutoff);
    cut_stuff->Branch("CaricaTOF",&CaricaTOF);
    cut_stuff->Branch("CaricaTRD",&CaricaTRD);
    cut_stuff->Branch("CaricaTrack",&CaricaTrack);
    cut_stuff->Branch("ProbQ",&ProbQ);
    cut_stuff->Branch("Qbest",&Qbest);
    cut_stuff->Branch("Endep",&Endep);
    cut_stuff->Branch("layernonusati",&layernonusati);
    cut_stuff->Branch("NAnticluster",&NAnticluster);
    cut_stuff->Branch("NTRDSegments",&NTRDSegments);
    cut_stuff->Branch("NTofClusters",&NTofClusters);
    cut_stuff->Branch("NTofClustersusati",&NTofClustersusati);
    cut_stuff->Branch("Rup",&Rup);
    cut_stuff->Branch("Rdown",&Rdown);
    cut_stuff->Branch("R",&R);
    cut_stuff->Branch("Chisquare",&Chisquare);
    cut_stuff->Branch("ResiduiX",&ResiduiX);
    cut_stuff->Branch("ResiduiY",&ResiduiY);
    cut_stuff->Branch("chiq",&chiq);
    cut_stuff->Branch("R_",&R_);
    cut_stuff->Branch("Beta",&Beta);
    cut_stuff->Branch("Betacorr",&Betacorr);
    cut_stuff->Branch("BetaRICH",&BetaRICH);
    cut_stuff->Branch("Massa",&Massa);
    cut_stuff->Branch("EdepTRD",&EdepTRD);
    cut_stuff->Branch("TRDclusters",&TRDclusters);
    cut_stuff->Branch("NTRDclusters",&NTRDclusters);
    cut_stuff->Branch("endepostatrack",&endepostatrack);
    cut_stuff->Branch("NTrackHits",&NTrackHits);
    cut_stuff->Branch("clusterTrack",&clusterTrack);

    cut_stuff->Branch("DistTOF",&DistTOF);
    cut_stuff->Branch("cosThetaTOF",&cosThetaTOF);
    cut_stuff->Branch("cosPhiTOF",&cosPhiTOF);
    cut_stuff->Branch("DistTrack",&DistTrack);
    cut_stuff->Branch("cosThetaTrack",&cosThetaTrack);
    cut_stuff->Branch("cosPhiTrack",&cosPhiTrack);
    cut_stuff->Branch("DistTRD",&DistTRD);
    cut_stuff->Branch("cosThetaTRD",&cosThetaTRD);
    cut_stuff->Branch("cosPhiTRD",&cosPhiTRD);
    cut_stuff->Branch("Unbias",&Unbias);
    cut_stuff->Branch("zonageo",&zonageo);


/////////////////////////////////////////////////////////////////
// Event loop
/////////////////////////////////////////////////////////////////

    for(int ii=0;ii<entries;ii++)
    { 
        if (contaeventi>entries) break;
        if(ii%10000==0){
            printf("Processed %7d out of %7d\n",ii,entries);
            printf("Evento numero: %7d\n",contaeventi);
        }		
        AMSEventR* ev=ch->GetEvent();
        Level1R* trig=ev->pLevel1(0);
        if(ev->pRichRing(0)&&controlloRICH!=1) {ev->pRichRing(0)->switchDynCalibration(); controlloRICH=1;}
        if(ev&&trig){
            if((trig->PhysBPatt&1)==1) Unbias=1;
            else Unbias=0;
        }
        //selezione delle run
        if(ii%10000==0) {cout<<"Latitudine geomagnetica: "<<ev->fHeader.ThetaM<<" rad"<<endl;
            cout<<ev->UTime()<<endl;}
            if(!saa(ev->fHeader.PhiS,ev->fHeader.ThetaS)) continue;
            if(ev->UTime()==ev->fHeader.Run||ev->UTime()==ev->fHeader.Run+1) continue;
            if(ev->fHeader.RunType<=61442) continue;
            if(ev->fHeader.Zenith()>25) continue;		//scelta zona geomagnetica
            for(int i=0;i<12;i++){
                double geo= geomag[i]  ;
                double geo2=/*(i+1)/(double)10*/geomag[i+1];
                if(fabs(ev->fHeader.ThetaM)>geo && fabs(ev->fHeader.ThetaM)<geo2) //cout<<"yes "<< 14.9*pow((cos(ev->fHeader->ThetaM)),4)<<endl;
                zona=i;

                        else tempozona[i]=ev->UTime();
                    }
                    int controllo=0;
                    if(ii%10000==0) cout<<"Zona: "<<zona<<endl;	
                    if(zona>=0)	controllo=1;
                    if(controllo!=1) continue; 
                    contaeventi++;
                    if(ev->UTime()!=tempozona[zona]){
                        tempozona[zona]=ev->UTime();
                        Time[zona]=Time[zona]+ev->LiveTime()/*trig->LiveTime*/;
                        contasecondi[zona]++;
                    }
                    //cout<<"Theta Mag: "<<ev->fHeader->ThetaM<<endl;
                    //double Rcutoff=14.9*pow((cos(ev->fHeader->ThetaM)),4);
                    if(ev->pParticle(0))
                        Rcutoff=ev->pParticle(0)->Cutoff;//14.9*pow((cos(((zona/(float)10+0.5)/(double)10))),4);	
                    U_time=ev->UTime();
                    Livetime=ev->LiveTime();
                    Latitude=fabs(ev->fHeader.ThetaM);
                    ThetaS=ev->fHeader.ThetaS;
                    PhiS=ev->fHeader.PhiS;
                    zonageo=zona;
                    ////////////////////////////////////////////////ANALISI PRESELEZIONE /////////////////////////////////
                    /*                nclusterTOFbuoni=-1;
                                      nTOFflag=0;
                                      nTRDHSegment=-1;
                                      minbiastrack=0;
                                      chisqX=0;
                                      chisqY=0;
                                      nTOFclustermatching=-1;
                                      dxTRD=-1;
                                      dyTRD=-1;
                                      InTRDAcceptance=0;
                                      nTrTracks=0;
                                      nTRDtracks=0;
                                      Beta_pre=-1;
                                      R_pre=-1;
                                      nPart=-1;
                                      Qbest=-1;
                                      int c=0;
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
                                      nclusterTOFbuoni=c;
                                      Level1R* level1=ev->pLevel1(0);
                                      if (level1)nTOFflag=level1->TofFlag1;
                                      TrdHTrackR *tracc = ev-> pTrdHTrack(0);
                                      if(tracc)nTRDHSegment=tracc->nTrdHSegment();
                                      if(minimumbiasTRACKER) minbiastrack=1;
                                      TrTrackR* traccia=ev->pTrTrack(0);
                                      if (traccia) {
                                      int fitID=traccia->iTrTrackPar(1,3,1);
                                      if(fitID>0&&traccia->ParExists(fitID)){
                                      float rgt = fabs(traccia->GetRigidity (fitID));
                                      R_pre=rgt;
                                      chisqY=traccia->GetNormChisqY(fitID);
                                      chisqX=traccia->GetNormChisqX(fitID);

                                      int c=0;
                                      TrTrackR* track=ev->pTrTrack(0);
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
                            if(fabs(dlong)<(LONGCUT[layer][bar])&& fabs(dtran)<TRANCUT[layer][bar])
                                goodlayer[layer]=true;
                        }
                    }

                    for(int i=0; i<4; i++)
                        if(goodlayer[i]) c++;
                    nTOFclustermatching=c;
                    TrdHTrackR* trd_track;
                    trd_track=ev->pTrdHTrack(0);
                    if(trd_track) if(trd_track->status>0)
                    {
                        AMSPoint pnt;
                        AMSDir dir;
                        TrTrackR* track=ev->pTrTrack(0);
                        track->Interpolate(trd_track->Coo[2],pnt,dir,fitID);

                        dxTRD=pnt.x()-trd_track->Coo[0];
                        dyTRD=pnt.y()-trd_track->Coo[1];
                    }
                    if(InTrdAcceptance(ev,severity,3)) InTRDAcceptance=1;
            }}
            nTrTracks=ev->nTrTrack();
            nTRDtracks=ev->NTrdTrack();
            nPart=ev->nParticle();
            ParticleR* particella = ev->pParticle(0) ;
            if(particella) {
                Beta_pre=particella->Beta;
                if(particella->pCharge()) Qbest=particella->pCharge()->Charge();
            }*/
            /////////////////////////////////////////////////////////////////////////////////////
            measure_stuff->Fill();
            if(ii%10000==0) measure_stuff->AutoSave();
            if(ev==NULL) break;
            if(minimumbias(ev,3)==NULL || golden(ev,severity,3)==NULL) continue;
            //for(int i=0; i<100;i++) cout<<ii<<" "<<endl;
            ev=preselect(ev);
            //for(int i=0; i<100;i++) cout<<ii<<endl;
            if(ev!=NULL&&ev->pTrTrack(0)&&ev->pParticle(0)){ 
                ThetaS=ev->fHeader.ThetaS;
                PhiS=ev->fHeader.PhiS;
                int fitID=ev->pTrTrack(0)->iTrTrackPar(1,3,1);
                TrTrackR* Tr = ev->pTrTrack(0);
                ParticleR* particella = ev->pParticle(0) ;
                int fitID1=Tr->iTrTrackPar(1,1,1);
                int fitID2=Tr->iTrTrackPar(1,2,1);
                int fitID3=Tr->iTrTrackPar(1,3,1);
                U_time=ev->UTime();
                Latitude=fabs(ev->fHeader.ThetaM);
                zonageo=zona;
                Livetime=ev->LiveTime();
                Rcutoff=ev->pParticle(0)->Cutoff;//14.9*pow((cos(((zona/(float)10+0.5)/(double)10))),4);
                if(!Tr->ParExists(fitID1) || !Tr->ParExists(fitID3) ||!Tr->ParExists(fitID2) ) continue;
                TrTrackPar parametri = Tr->gTrTrackPar(fitID3);
                ChargeR* carica= ev->pCharge(0);
                if(!carica) continue;
                ChargeSubDR* subcaricaTOF=carica->getSubD("AMSChargeTOF");
                ChargeSubDR* subcaricaTrack=carica->getSubD("AMSChargeTrackerInner");
                ChargeSubDR* subcaricaTRD=carica->getSubD("AMSChargeTRD");
                if(subcaricaTOF)
                    CaricaTOF=subcaricaTOF->Q;
                else CaricaTOF=-1;
                if(subcaricaTRD)
                    CaricaTRD=subcaricaTRD->Q;
                else CaricaTRD=-1;
                if(subcaricaTrack)
                    CaricaTrack=subcaricaTrack->Q;
                else CaricaTrack =-1;
                ProbQ=carica->getProb(0);
                Qbest=carica->Charge();

                for(int j=0; j<4; j++)
                    Endep[j]=0;
                for(int j=0; j<ev->NTofCluster(); j++)
                    Endep[(ev->pTofCluster(j)->Layer)-1]=ev->pTofCluster(j)->Edep;
                layernonusati=0;
                for(int layer=2;layer<9;layer++)
                    if(!parametri.TestHitLayerJ(layer)) layernonusati++;
                NAnticluster=ev->NAntiCluster();
                NTRDSegments=ev->NTrdSegment();
                NTofClusters=ev->NTofCluster();
                NTofClustersusati=ev->pBeta(0)->NTofCluster();
                Rup=Tr->GetRigidity(fitID1);
                Rdown=Tr->GetRigidity(fitID2);
                R=Tr->GetRigidity(fitID3);
                Chisquare=Tr->GetChisq(fitID3);
                float  chiq[6];
                int fit[6];
                double R_[6];

                fit[0]=0x200+0x10+0x1+0x8000+0x10000+0x20000+0x40000;
                fit[1]=0x200+0x10+0x1+0x1000+0x2000+0x20000+0x40000;
                fit[2]=0x200+0x10+0x1+0x4000+0x8000+0x1000+0x2000;
                fit[3]=0x200+0x10+0x1+0x4000+0x8000+0x10000;
                fit[4]=0x200+0x10+0x1+0x4000+0x8000+0x10000+0x20000+0x2000+0x1000;
                fit[5]=0x200+0x10+0x1+0x4000+0x8000+0x10000+0x20000+0x40000+0x2000;
                for(int i=0; i<6;i++)  chiq[i] =Tr->FitT(fit[i],-1);
                for(int i=0; i<6;i++) R_[i]=Tr->GetRigidity(fit[i]);
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
                if(particella->pBetaH()) Beta=particella->pBetaH()->GetBeta();
                Betacorr=0;
                if (Beta>=1)  Betacorr=Beta/(2*Beta-1);
                else Betacorr=Beta;
                BetaRICH=-1;
                if (giovacchiniRICH(ev)) {
                    BetaRICH=ev->pRichRing(0)->getBeta();
                    Betacorr=BetaRICH;
                }
                int clusterusati=0;
                Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Betacorr,2)),0.5)/Betacorr,2)),0.5);
                for(int j=0;j<ev->pTrdTrack(0)->NTrdSegment();j++) {
                    for(int i=0;i<ev->pTrdTrack(0)->pTrdSegment(j)->NTrdCluster();i++) {
                        clusterusati++;	
                    }

                }
                //Edep TRD
                EdepTRD=0;
                NTRDclusters=0;
                TRDclusters[1000];
                for(int j=0;j<ev->pTrdTrack(0)->NTrdSegment();j++) {
                    for(int i=0;i<ev->pTrdTrack(0)->pTrdSegment(j)->NTrdCluster();i++) {

                        EdepTRD=EdepTRD+ev->pTrdTrack(0)->pTrdSegment(j)->pTrdCluster(i)->EDep;
                        TRDclusters[NTRDclusters]=ev->pTrdTrack(0)->pTrdSegment(j)->pTrdCluster(i)->EDep;
                        NTRDclusters++;
                    }
                }

                //Edep Tracker
                endepostatrack=0;	
                NTrackHits=Tr->NTrRecHit();	
                clusterTrack[1000];
                for(int i=0; i<Tr->NTrRecHit();i++){
                    TrRecHitR *hit=ev->pTrTrack(0)->pTrRecHit (i);
                    clusterTrack[i]=hit->Sum();
                    endepostatrack=endepostatrack+hit->Sum();
                }
                //////////////////////// NUOVA SELEZIONE  //////////////////////
                /*RGDT=0;
                  distR=0;
                  distB=0;
                  distETOF=0;
                  distETrack=0;
                  distETRD=0;
                  DistTOF=0;
                  DistTrack=0;
                  DistTRD=0;
                  DR1=0; DR2=0; DR3=0;
                  for(int P=0;P<3;P++) CooTOF[P]=0;
                  for(int P=0;P<3;P++) CooTrack[P]=0;
                  for(int P=0;P<3;P++) CooTRD[P]=0;
                  Dist1=1000000;
                  Dist2=1000000;
                  Dist3=1000000;
                  for(int z=0;z<1e6;z++){
                  distR=(RGDT-R)/(pow(R,2)*Rig->Eval(R));
                  distB=(deutons->Eval(RGDT)-Betacorr)/(pow(Betacorr,2)*beta->Eval(Betacorr));
                  distETOF=(fvera->Eval(RGDT)-EndepTOF)/(pow(fvera->Eval(RGDT),2)*etof->Eval(RGDT));
                  distETrack=(fveratr->Eval(RGDT)-endepostatrack/NTrackHits)/(pow(fveratr->Eval(RGDT),2)*etrack->Eval(RGDT));
                  distETRD=(fveraTRD->Eval(RGDT)-EdepTRD/NTRDclusters)/(pow(fveraTRD->Eval(RGDT),2)*etrd->Eval(RGDT));
                  DistTOF=pow(pow(distR,2)+pow(distB,2)+pow(distETOF,2),0.5);
                  DistTrack=pow(pow(distR,2)+pow(distB,2)+pow(distETrack,2),0.5);
                  DistTRD=pow(pow(distR,2)+pow(distB,2)+pow(distETRD,2),0.5);
                  if(DistTOF<Dist1) { Dist1=DistTOF; CooTOF[0]=distETOF; CooTOF[1]=distB; CooTOF[2]=distR;}
                  else DR1++;
                  if(DistTrack<Dist2) { Dist2=DistTrack; CooTrack[0]=distETrack; CooTrack[1]=distB; CooTrack[2]=distR;}
                  else DR2++;
                  if(DistTRD<Dist3) { Dist3=DistTRD; CooTRD[0]=distETRD; CooTRD[1]=distB; CooTRD[2]=distR;}
                  else DR3++;
                  if(DR1>2&&DR2>2&&DR3>2) break;
                  RGDT=RGDT+0.05;
                  }
                  cosPhiTOF=CooTOF[2]/pow(pow(CooTOF[0],2)+pow(CooTOF[2],2),0.5);
                  cosThetaTOF=CooTOF[1]/Dist1;
                  cosPhiTrack=CooTrack[2]/pow(pow(CooTrack[0],2)+pow(CooTrack[2],2),0.5);
                  cosThetaTrack=CooTrack[1]/Dist2;
                  cosPhiTRD=CooTRD[2]/pow(pow(CooTRD[0],2)+pow(CooTRD[2],2),0.5);
                  cosThetaTRD=CooTRD[1]/Dist3;
                  DistTOF=Dist1;
                  DistTrack=Dist2;
                  DistTRD=Dist3;*/

                cut_stuff->Fill();
                if(ii%10000==0) cut_stuff->AutoSave();
            }
            }

            File->Write();
            File->Close();
    return 1;
}



bool saa(float phi,float theta) {
  double const Pi=3.141592;
  phi=(phi-2*Pi)*100;
  theta=theta*100;
  // phi, theta geographic
  bool ssa_good=true;
  if(phi>=-74 && phi<-72 && theta>=-23 && theta<-18) ssa_good=false;
  if(phi>=-72 && phi<-70 && theta>=-27 && theta<-15) ssa_good=false;
  if(phi>=-70 && phi<-68 && theta>=-31 && theta<-13) ssa_good=false;
  if(phi>=-68 && phi<-66 && theta>=-34 && theta<-12) ssa_good=false;
  if(phi>=-66 && phi<-64 && theta>=-36 && theta<-11) ssa_good=false;
  if(phi>=-64 && phi<-62 && theta>=-38 && theta<-10) ssa_good=false;
  if(phi>=-62 && phi<-60 && theta>=-40 && theta<-10) ssa_good=false;
  if(phi>=-60 && phi<-58 && theta>=-40 && theta<-9) ssa_good=false;
  if(phi>=-58 && phi<-56 && theta>=-42 && theta<-8) ssa_good=false;
  if(phi>=-56 && phi<-54 && theta>=-43 && theta<-8) ssa_good=false;
  if(phi>=-54 && phi<-52 && theta>=-43 && theta<-8) ssa_good=false;
  if(phi>=-52 && phi<-50 && theta>=-43 && theta<-8) ssa_good=false;
  if(phi>=-50 && phi<-48 && theta>=-43 && theta<-8) ssa_good=false;
  if(phi>=-48 && phi<-46 && theta>=-44 && theta<-8) ssa_good=false;
  if(phi>=-46 && phi<-44 && theta>=-44 && theta<-8) ssa_good=false;
  if(phi>=-44 && phi<-42 && theta>=-44 && theta<-9) ssa_good=false;
  if(phi>=-42 && phi<-40 && theta>=-43 && theta<-9) ssa_good=false;
  if(phi>=-40 && phi<-38 && theta>=-43 && theta<-11) ssa_good=false;
  if(phi>=-38 && phi<-36 && theta>=-42 && theta<-13) ssa_good=false;
  if(phi>=-36 && phi<-34 && theta>=-42 && theta<-12) ssa_good=false;
  if(phi>=-34 && phi<-32 && theta>=-42 && theta<-14) ssa_good=false;
  if(phi>=-32 && phi<-30 && theta>=-41 && theta<-16) ssa_good=false;
  if(phi>=-30 && phi<-28 && theta>=-40 && theta<-17) ssa_good=false;
  if(phi>=-28 && phi<-26 && theta>=-40 && theta<-18) ssa_good=false;
  if(phi>=-26 && phi<-24 && theta>=-39 && theta<-19) ssa_good=false;
  if(phi>=-24 && phi<-22 && theta>=-38 && theta<-20) ssa_good=false;
  if(phi>=-22 && phi<-20 && theta>=-37 && theta<-21) ssa_good=false;
  if(phi>=-20 && phi<-18 && theta>=-36 && theta<-22) ssa_good=false;
  if(phi>=-18 && phi<-16 && theta>=-35 && theta<-24) ssa_good=false;
  if(phi>=-16 && phi<-14 && theta>=-34 && theta<-25) ssa_good=false;
  if(phi>=-14 && phi<-12 && theta>=-32 && theta<-26) ssa_good=false;
  if(phi>=-12 && phi<-10 && theta>=-31 && theta<-27) ssa_good=false;
  if(phi>=-10 && phi<-8 && theta>=-28 && theta<-27) ssa_good=false;
  return ssa_good;
}

