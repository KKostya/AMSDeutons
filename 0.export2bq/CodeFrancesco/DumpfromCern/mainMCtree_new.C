#include <vector>
#include <string>
#include <iostream>
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif

#include "selezioni.h"
#include "amschain.h"
#include "Functions.h"
#include "./scripsMC/inputs.h"

using namespace std

long double bin[24];
double efficienzagen[23];
double efficienzamis[23][11];
double efficienzadeut[23][11];
double primari[23][11];
double efficienzaver[23];
double preselez[23];
std::vector<float> Time(11);
//long long double Utime=0;
double tbeg,tend;
double tempozona[11]={0,0,0,0,0,0,0,0,0,0,0};
int contasecondi[11]={0,0,0,0,0,0,0,0,0,0,0};
int zona;
int severity=0;
int controllogiov=0;
int contaeventi=0;
double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};
bool  deutoni(AMSEventR* ev);
float U_time;
float Latitude;
int zonageo;
float Rcutoff;
float CaricaTOF=0;
float CaricaTRD=0;
float CaricaTrack=0;
float ProbQ=0;
float Qbest=0;
float Chisquare=0;
int Ev_Num=0;
int Trig_Num=0;
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
float BetaRICH=-1;

float Massa=0;
float EdepTRD=0;
int NTRDclusters=0;
std::vector<float> TRDclusters(1000);
 float endepostatrack=0;
int NTrackHits=0;
std::vector<float> trtot_edep(9);
std::vector<float> trtrack_edep(9);
std::vector<double> ResiduiX(7);
std::vector<double> ResiduiY(7);
float Momento_gen=0;
float Massa_gen=0;
float Beta_gen=0;
int fit=3;
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
int DR1,DR2,DR3=0;
float Unbias=0;
float Pres_Unbias=0;
float Preselected=0;
int clustertrack=0;
int clustertottrack=0;
////////////// ANALISI PRESELEZIONE ///////////////////
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
int nTrTOTHits=0;
int nTRDtracks=0;
float Beta_pre=0;
float R_pre=0;
int nPart=0;
std::vector<float> Endep_Pre(4);
////////////////////////////////////////////////////////
int CUTMASK=0;
int IsPrescaled=0;
int G=0;
int RICHmask=-1;
int RICHmask_new=-1;
float BetaRICH_new=-1;
int Run=0;

int main(int argc, char * argv[]){
	cout<<"Inserisci parametri simulazione: massa part (GeV),energia min,energia max"<<endl;
	cout<<"Errore?"<<endl;
        float E=-1.203972804;
        float EM=6.66722056;
        float a=(EM-E)/23;
	for(int i=0;i<11;i++) Time[i]=0;
	for(int i=0;i<24;i++)
	{
        	float temp=i+7;
        	bin[i]=0.1*pow(10,temp/9.5);
        	//************** bin DAV
	/*      bin[i]=exp(E);
        	E=E+a;*/
        	cout<<bin[i]<<endl;

	}	
	TFile * File;
	AMSChain *ch;
        AMSEventList lista;
	ch= new AMSChain;
                string ARGV(argv[1]);
                int INDX=atoi(argv[1]);
                string istog="/afs/cern.ch/user/f/fdimicco/Work/Dimiccoli/Compiled/istogrammiMC/"+ARGV+".root";
                string *file=&istog;


                File = new TFile(istog.c_str(), "RECREATE");
                cout<<"inizio.."<<endl;
                for(int i=(int)(7528)/2000*INDX;i<(int)(7528)/2000*(INDX+1);i++){
                 string indirizzo="root://eosams.cern.ch///eos/ams/MC/AMS02/2014/"+tipo+"/"+energia+"/"+rootpla[i];
                //string indirizzo="root://castorpublic.cern.ch///castor/cern.ch/ams/MC/AMS02/2014/"+tipo+"/"+energia+"/"+rootpla[i];   

                AMSChain *ch2=new AMSChain;
                ch->Add(indirizzo.c_str());

                //if(ch2) 
                // cout<<"****************************"<<indirizzo<<"+++++++++++++++"<<endl;
		int entries = 10000;//ch->GetEntries();
        	cout<<entries<<endl;
		TTree *measure_stuff= new TTree("parametri_geo","parametri_geo");
		TTree *cut_stuff = new TTree("grandezze_tagli","grandezze_tagli");
		measure_stuff->Branch("Momento_gen",&Momento_gen);
		measure_stuff->Branch("Beta_gen",&Beta_gen);
		measure_stuff->Branch("Massa_gen",&Massa_gen);
		measure_stuff->Branch("Ev_Num",&Ev_Num);
		measure_stuff->Branch("Trig_Num",&Trig_Num);
		measure_stuff->Branch("Run",&Run);
		measure_stuff->Branch("Unbias",&Unbias);
		measure_stuff->Branch("Beta_pre",&Beta_pre);
		measure_stuff->Branch("R_pre",&R_pre);
		measure_stuff->Branch("Pres_Unbias",&Pres_Unbias);
		measure_stuff->Branch("Preselected",&Preselected);
		measure_stuff->Branch("CUTMASK",&CUTMASK);
		measure_stuff->Branch("IsPrescaled",&IsPrescaled);

