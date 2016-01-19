
#include <vector>
#include <string>
#include <iostream>

#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif

#include "selezioni.h"
#include "amschain.h"
#include <Tofrec02_ihep.h>
#include "./scripsdati/inputs.h"



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
float BetaR=0;
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
int clustertrack=0;
int clustertottrack=0;
double Rup=0;
double Rdown=0;
double R=0;
/////////// ANALISI PRESELEZIONI ///////
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
std::vector<float> EndepR(4);
bool MinTOF[2];
bool GolTOF[2];
/////////////////////////////////////
float Beta=0;
float Betacorr=0;
std::vector<double> ResiduiX(7);
std::vector<double> ResiduiY(7);
float BetaRICH=-1;
float BetaRICH_new=-1;
float Massa=0;
int Ev_Num=0;
float EdepTRD=0;
int NTRDclusters=0;
std::vector<float> TRDclusters(1000);
float endepostatrack=0;
int NTrackHits=0;
std::vector<float> trtot_edep(9);
std::vector<float> trtrack_edep(9);
float Livetime=0;
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
float ThetaS=0;
float PhiS=0;
int DR1,DR2,DR3=0;
float Unbias=0;
float Pres_Unbias=0;
float Preselected=0;
int CUTMASK=0;
int IsPrescaled=0;
int controlloRICH=0;
int G=0;
float EdepECAL=0;
bool saa(float phi,float theta);
int RICHmask=-1;
int RICHmask_new=-1;
int Reig_num=0;
int Run=0;
int Trig_Num=0;
int main(int argc, char * argv[])
{
	for(int indice=4;indice<5;indice++)
	{
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
			/*        bin[i]=exp(E);
				  E=E+a;*/
			cout<<bin[i]<<endl;	

		}

		TFile * File;
		for(int giro=1;giro<2;giro++){

			AMSChain* ch;
			AMSEventList lista;

			cout<<"inizio...."<<endl;


			ch= new AMSChain;
			string ARGV(argv[1]);
			int INDX=atoi(argv[1]);
			for(int i=(int)2*INDX;i<(int)2*(INDX+1);i++){	
				string indirizzo="root://eosams.cern.ch///eos/ams/Data/AMS02/2014/"+tipo+"/"+energia+"/"+rootpla[i];
				std::cout<<"Processing : "<<indirizzo<<endl;
				ch->Add(indirizzo.c_str());
			}


			string istog= "/afs/cern.ch/user/f/fdimicco/Work/Dimiccoli/Compiled/istogrammidati/"+rootpla[(int)(2*INDX)];
			string *file=&istog;

			File = new TFile(istog.c_str(), "RECREATE");

			int entries =ch->GetEntries();
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
			measure_stuff->Branch("R_pre",&R_pre);
			measure_stuff->Branch("Beta_pre",&Beta_pre);
			measure_stuff->Branch("BetaR",&BetaR);
			measure_stuff->Branch("Pres_Unbias",&Pres_Unbias);
			measure_stuff->Branch("Preselected",&Preselected);		
			measure_stuff->Branch("CUTMASK",&CUTMASK);
			measure_stuff->Branch("IsPrescaled",&IsPrescaled);
			measure_stuff->Branch("Trig_Num",&Trig_Num);
			measure_stuff->Branch("Run",&Run);
			measure_stuff->Branch("trtrack_edep",&trtrack_edep);
			measure_stuff->Branch("trtot_edep",&trtot_edep);
			measure_stuff->Branch("Endep",&Endep);
			measure_stuff->Branch("EndepR",&EndepR);
			measure_stuff->Branch("BetaRICH",&BetaRICH);
			measure_stuff->Branch("BetaRICH_new",&BetaRICH_new);
			measure_stuff->Branch("RICHmask",&RICHmask);
			measure_stuff->Branch("RICHmask_new",&RICHmask_new);			
			measure_stuff->Branch("EdepECAL",&EdepECAL);

			cut_stuff->Branch("Trig_Num",&Trig_Num);
			cut_stuff->Branch("Run",&Run);
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
			cut_stuff->Branch("EndepR",&EndepR);
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
			cut_stuff->Branch("Beta",&Beta);
			cut_stuff->Branch("BetaR",&BetaR);
			cut_stuff->Branch("Betacorr",&Betacorr);
			cut_stuff->Branch("BetaRICH",&BetaRICH);
			cut_stuff->Branch("BetaRICH_new",&BetaRICH_new);
			cut_stuff->Branch("RICHmask",&RICHmask);
			cut_stuff->Branch("RICHmask_new",&RICHmask_new);
			cut_stuff->Branch("Massa",&Massa);
			cut_stuff->Branch("EdepTRD",&EdepTRD);
			cut_stuff->Branch("TRDclusters",&TRDclusters);
			cut_stuff->Branch("NTRDclusters",&NTRDclusters);
			cut_stuff->Branch("endepostatrack",&endepostatrack);
			cut_stuff->Branch("NTrackHits",&NTrackHits);
			cut_stuff->Branch("clustertrack",&clustertrack);
			cut_stuff->Branch("clustertottrack",&clustertottrack);
			cut_stuff->Branch("trtrack_edep",&trtrack_edep);
			cut_stuff->Branch("trtot_edep",&trtot_edep);
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
			cut_stuff->Branch("CUTMASK",&CUTMASK);
			cut_stuff->Branch("IsPrescaled",&IsPrescaled);	
			cut_stuff->Branch("EdepECAL",&EdepECAL);


			AMSSetupR::RTI::UseLatest();
			TkDBc::UseFinal();


			for(int ii=0;ii<entries;ii++)
			{ 
				if (contaeventi>entries) break;
				AMSEventR* ev=ch->GetEvent();
				ev->SetDefaultMCTuningParameters();
				if(ii%10000==0){
					printf("Processed %7d out of %7d\n",ii,entries);
					printf("Evento numero: %7d\n",contaeventi);
					if(contaeventi==0) {std::cout<<"RunType(>61442): "<<ev->fHeader.RunType<<" Zenith: "<<ev->fHeader.Zenith()<<std::endl;
						if(ev->IsInSAA()) std::cout<<"SAA!!"<<std::endl; }	
				}		
				Trig_Num=ev->Event();
				Run=ev->Run();
				Level1R* trig=ev->pLevel1(0);
				if(ev->pRichRing(0)&&controlloRICH!=1) {ev->pRichRing(0)->switchDynCalibration(); controlloRICH=1;}
				if(ev&&trig){
					if(trig->PhysBPatt == 0) Unbias =1;
					else Unbias=0;
				}
				//selezione delle run
				if(ii%10000==0) {cout<<"Latitudine geomagnetica: "<<ev->fHeader.ThetaM<<" rad"<<endl;
					cout<<ev->UTime()<<endl;}
				if(ev->IsInSAA()) continue;
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
				if(ev->pParticle(0)){
					double dirTheta_ams= ev->pParticle(0)->Theta;
					double dirPhi_ams= ev->pParticle(0)->Phi;
					AMSDir amsdir(dirTheta_ams, dirPhi_ams);
					double cutoff =0;
					int momOrR = 1; //==0 GeV/c  ; ==1 GV
					int positive = 1; //==0 particle.mon == 1 (+) , == 2 (-)
					int ss = ev->pParticle(0)->GetStoermerCutoff(cutoff,momOrR,positive ,amsdir);
					Rcutoff=cutoff;
				}
				U_time=ev->UTime();
				Livetime=ev->LiveTime();
				Latitude=fabs(ev->fHeader.ThetaM);
				ThetaS=ev->fHeader.ThetaS;
				PhiS=ev->fHeader.PhiS;
				zonageo=zona;
				TrTrackR* Tr = ev->pTrTrack(0);
				nPart=ev->nParticle();
				nTrTracks=ev->nTrTrack();
				CUTMASK=0;

				minimumbiasTOF(ev,MinTOF);
				goldenTOF(ev,severity,3,GolTOF);
				if(minimumbiasTRIGG(ev)) CUTMASK=CUTMASK|(1<<0);
				if(MinTOF[0]) CUTMASK=CUTMASK|(1<<1);
				if(minimumbiasTRD(ev)) CUTMASK=CUTMASK|(1<<2);
				if(minimumbiasTRACKER(ev,3)) CUTMASK=CUTMASK|(1<<3);
				if(goldenTRACKER(ev,severity,3)) CUTMASK=CUTMASK|(1<<4);
				if(GolTOF[0]) CUTMASK=CUTMASK|(1<<5);
				if(goldenTRD(ev,severity,3)) CUTMASK=CUTMASK|(1<<6);
				if(nTrTracks==1) CUTMASK=CUTMASK|(1<<7);
				if(MinTOF[1]) CUTMASK=CUTMASK|(1<<8);
				if(GolTOF[1]) CUTMASK=CUTMASK|(1<<9);


				for(int i=0;i<9;i++){trtot_edep[i]=0;trtrack_edep[i]=0;}
				if(minimumbiasTRACKER(ev,3)){
					// Edep Track
					clustertrack=0;
					clustertottrack=0;
					NTrackHits=Tr->NTrRecHit();
					int fitID3=Tr->iTrTrackPar(1,3,1);
					if(Tr->ParExists(fitID3)) R_pre=Tr->GetRigidity(fitID3); else R_pre=0;
					for(int i=0;i<9;i++){trtot_edep[i]=0;trtrack_edep[i]=0;}
					for(int i=0; i<Tr->NTrRecHit();i++){
						TrRecHitR *hit=ev->pTrTrack(0)->pTrRecHit (i);
						int ilay = hit->GetLayerJ()-1;
						TrClusterR* cluster = hit->GetYCluster();
						trtrack_edep[ilay] = cluster->GetEdep();
						clustertrack++;
					}
				}	
				for (int i=0; i<ev->NTrCluster(); i++) {
					TrClusterR* cluster = ev->pTrCluster(i);
					int ilay = cluster->GetLayerJ()-1;
					if(cluster->GetSide()==1) {trtot_edep[ilay] += cluster->GetEdep(); clustertottrack++;}
				}
				for(int j=0; j<4; j++)
					EndepR[j]=0;
				for(int j=0; j<ev->NTofCluster(); j++)
					EndepR[(ev->pTofCluster(j)->Layer)-1]+=ev->pTofCluster(j)->Edep;

				for(int j=0; j<4; j++)
					Endep[j]=0;
				for(int j=0; j<ev->NTofClusterH(); j++)
					Endep[(ev->pTofClusterH(j)->Layer)]+=ev->pTofClusterH(j)->GetEdep();

				Beta_pre=0; BetaR=0;
				if(ev->pBetaH(0)) Beta_pre=ev->pBetaH(0)->GetBeta();
				if(ev->pBeta(0)) BetaR=ev->pBeta(0)->Beta;


				int NhitECAL = ev->NEcalHit();
				EdepECAL=-100;
				if(ev->NEcalShower()==1) {EcalShowerR* show = ev->pEcalShower(0); EdepECAL=show->EnergyE;}

				BetaRICH=-1;
				BetaRICH_new=-1;
				RICHmask=1;RICHmask_new=1;
				if(ev->NRichRing()>0){
					RICHmask=RichQual(ev);
					RICHmask_new=RichQual_new(ev->pRichRing(0));
					if(RICHmask==0) BetaRICH=ev->pRichRing(0)->getBeta();
					if(RICHmask_new==0||RICHmask_new==512) BetaRICH_new=ev->pRichRing(0)->getBeta();
				}

				//////////////////////////////////////////////////////////////////////////////
				measure_stuff->Fill();
				if(ii%10000==0) measure_stuff->AutoSave();
				bool isPreselected=false;
				if(((int)CUTMASK&187)==187) isPreselected=true; 
				if(isPreselected){
					TofRecH::BuildOpt=0;
					TofRecH::ReBuild(); 
					ThetaS=ev->fHeader.ThetaS;
					PhiS=ev->fHeader.PhiS;
					int fitID=ev->pTrTrack(0)->iTrTrackPar(1,3,1);
					ParticleR* particella = ev->pParticle(0) ;
					int fitID1=Tr->iTrTrackPar(1,1,1);
					int fitID2=Tr->iTrTrackPar(1,2,1);
					int fitID3=Tr->iTrTrackPar(1,3,1);
					U_time=ev->UTime();
					Latitude=fabs(ev->fHeader.ThetaM);
					zonageo=zona;
					Livetime=ev->LiveTime();
					TrTrackPar parametri;
					if(Tr->ParExists(fitID3)) parametri=Tr->gTrTrackPar(fitID3);

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
					layernonusati=0;
					for(int layer=2;layer<9;layer++)
						if(!parametri.TestHitLayerJ(layer)) layernonusati++;
					NAnticluster=ev->NAntiCluster();
					NTRDSegments=ev->NTrdSegment();
					NTofClusters=ev->NTofClusterH();
					NTofClustersusati=ev->pBetaH(0)->NTofClusterH();
					if(Tr->ParExists(fitID1)) Rup=Tr->GetRigidity(fitID1); else Rup=0;
					if(Tr->ParExists(fitID2)) Rdown=Tr->GetRigidity(fitID2); else Rdown=0;
					if(Tr->ParExists(fitID3)) R=Tr->GetRigidity(fitID3); else R=0;
					if(Tr->ParExists(fitID3)) Chisquare=Tr->GetChisq(fitID3); 
					else Chisquare=1e7;
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
					Beta=ev->pBetaH(0)->GetBeta();
					//cout<<Beta<<" "<<Beta_pre<<" "<<ev->pParticle(0)->pBeta()->Beta<<endl;

					int clusterusati=0;
					Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Betacorr,2)),0.5)/Betacorr,2)),0.5);

					//Edep TRD
					EdepTRD=0;
					NTRDclusters=0;
					TRDclusters[1000];
					for(int u=0;u<ev->NTrdTrack();u++){
						if(u==0)
							for(int j=0;j<ev->pTrdTrack(u)->NTrdSegment();j++) {
								for(int i=0;i<ev->pTrdTrack(u)->pTrdSegment(j)->NTrdCluster();i++) {

									EdepTRD=EdepTRD+ev->pTrdTrack(u)->pTrdSegment(j)->pTrdCluster(i)->EDep;
									TRDclusters[NTRDclusters]=ev->pTrdTrack(u)->pTrdSegment(j)->pTrdCluster(i)->EDep;
									NTRDclusters++;
								}
							}
						for(int j=0;j<ev->pTrdTrack(u)->NTrdSegment();j++) {
							if(u==0) for(int i=0;i<ev->pTrdTrack(0)->pTrdSegment(j)->NTrdCluster();i++) {
								clusterusati++;
							}

						}
					}

					cut_stuff->Fill();
					if(ii%10000==0) cut_stuff->AutoSave();
				}
			}

			File->Write();
			File->Close();
		}
	}

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

