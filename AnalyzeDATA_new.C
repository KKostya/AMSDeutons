#include "TROOT.h"
#include "TFile.h"
#include "TF1.h"
#include "TNtuple.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include <TVector3.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstring>
#include <vector>
#include "TMath.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <TSpline.h>
#include "./Matriciselezione/TOF.h"
#include "./Matriciselezione/Track.h"
#include "./Matriciselezione/TRD.h"
#include "Functions.h"
#include "Selections.h"

using namespace std;
void aggiungiantupla (TTree *albero,int i,TNtuple *ntupla,int P_ID);
void Grandezzesep (TTree *albero,int i,TNtuple *ntupla);
void Grandezzesepd (TTree *albero,int i,TNtuple *ntupla);
void Grandezzequal (TTree *albero,int i,TNtuple *ntupla);
void Selez (TTree *albero,int i,TNtuple *ntupla);
int Ev_Num;
int scelta=0;
int giov=0;
int nprotoni=0;
int entriestot=0;
int events=0;
int INDX;

int main(int argc, char * argv[]){

    gROOT->ProcessLine("#include <vector>");
//////////////////////// LETTURA MATRICI //////////////////////
/* int linea=0;
{        ifstream fp("./rigvsbetaP.dat");
        while(!fp.eof()){
                for(int i=0;i<100;i++){
                fp>>matricervsbeta[linea][i];
                //cout<<matricervsbeta[linea][i];
                }
        linea++;
        //cout<<endl;
        }
}
linea=0;
{
ifstream fp("./rigvsbetaD.dat");
      while(!fp.eof()){
                for(int i=0;i<100;i++){
                fp>>matricervsbetad[linea][i];
                //cout<<matricervsbetad[linea][i];
                }
        linea++;
        //cout<<endl;
        }
}*/
/////////////////////////////////////////////////////////////////
cout<<"Vuoi Ntuple? (1-Sì;2-No)"<<endl;
//cin>>scelta;
scelta=1;
for(int i=0;i<24;i++)
{
        float temp=i+7;
        bin[i]=0.1*pow(10,temp/9.5);
        //************** bin DAV
/*        bin[i]=exp(E);
        E=E+a;*/
        cout<<bin[i]<<endl;

}
string ARGV(argv[1]);
bool check=true;
//string Nome_file= "/afs/ams.cern.ch/user/fdimicco/Dimiccoli/istogrammidati/" + file_name;
//TFile *file =TFile::Open("/storage/gpfs_ams/ams/users/kostya/sommadati.root");
string indirizzo_in="/storage/gpfs_ams/ams/users/fdimicco/MAIN/sommadati/sommadati"+ARGV+".root";
TFile *file =TFile::Open(indirizzo_in.c_str());
//TFile *file =TFile::Open("/storage/gpfs_ams/ams/users/kostya/DeutonsTest/J/data_test.root");
TTree *cut_stuff = (TTree *)file->Get("grandezze_tagli");
TTree *geo_stuff = (TTree *)file->Get("parametri_geo");
std::cout<<cut_stuff<<endl;
if(!(cut_stuff>0)) check=false;
if(!(geo_stuff>0)) check=false;
if(check==false) std::cout<<"Skipping file!"<<endl;
//string Nome_Output="/afs/ams.cern.ch/user/fdimicco/Dimiccoli/Analisi/ntupledati/risultati/_"+file_name;
string indirizzo_out="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/RisultatiDATI_"+ARGV+".root";
TFile * File = new TFile(indirizzo_out.c_str(), "RECREATE");

TNtuple *grandezzequal = new TNtuple("grandezzequal","grandezzequal","R:Beta:zonageo:Massa:NAnticluster:Clusterinutili:DiffR:residuoY:residuoX:fuoriX:L_fakeD:L_trueD:layernonusati:Chisquare:NTRDSegments");
TNtuple *grandezzesep = new TNtuple("grandezzesep","grandezzesep","R:Beta_corr:BetaRICH:DistTOF:EdepTRD:DistTRD:EdepTrack:RminTrack:DistTrack:PhiProjTOF:PhiProjTrack:PhiProjTRD:zonageo:Rcutoff");/*:clusterTOFfuori:clusterTrackfuori:clusterTRDfuori");*/
TNtuple *grandezzesepd = new TNtuple("grandezzesepd","grandezzesepd","R:Beta_corr:BetaRICH:RminTOF:RminTrack:RminTRD:DistTOF:DistTrack:DistTRD:PhiProjTOF:PhiProjTrack:PhiProjTRD:fakeD:trueD:Rcutoff");
TNtuple * Good_Qual = new TNtuple("Good_Qual","distr for pre","R:Beta:BetaRICH:EdepTOF:EdepTRD:EdepTrack:Massa:Zona:P_ID:DisTOF:DistTrack:DistTRD:Rcutoff:U_time");
TNtuple * pre = new TNtuple("Pre","distr for pre","R:Beta:BetaRICH:EdepTOF:EdepTRD:EdepTrack:Massa:Zona:P_ID:DisTOF:DistTrack:DistTRD:Rcutoff:U_time");
TNtuple * qual = new TNtuple("Qual","distr for giov","R:Beta:BetaRICH:EdepTOF:EdepTRD:EdepTrack:Massa:Zona:P_ID:DisTOF:DistTrack:DistTRD:Rcutoff:U_time");

if(check){
geo_stuff->SetBranchAddress("U_time",&U_time);
geo_stuff->SetBranchAddress("Latitude",&Latitude);
geo_stuff->SetBranchAddress("zonageo",&zonageo);
geo_stuff->SetBranchAddress("Rcutoff",&Rcutoff);
geo_stuff->SetBranchAddress("Livetime",&Livetime);
geo_stuff->SetBranchAddress("Unbias",&Unbias);
geo_stuff->SetBranchAddress("Pres_Unbias",&Pres_Unbias);
geo_stuff->SetBranchAddress("Preselected",&Preselected);
geo_stuff->SetBranchAddress("R_pre",&R_pre);

cut_stuff->SetBranchAddress("U_time",&U_time);
cut_stuff->SetBranchAddress("Livetime",&Livetime);
cut_stuff->SetBranchAddress("Latitude",&Latitude);
cut_stuff->SetBranchAddress("Rcutoff",&Rcutoff);
cut_stuff->SetBranchAddress("CaricaTOF",&CaricaTOF);
cut_stuff->SetBranchAddress("CaricaTRD",&CaricaTRD);
cut_stuff->SetBranchAddress("CaricaTrack",&CaricaTrack);
cut_stuff->SetBranchAddress("ProbQ",&ProbQ);
cut_stuff->SetBranchAddress("Qbest",&Qbest);
cut_stuff->SetBranchAddress("Endep",&Endep);
cut_stuff->SetBranchAddress("layernonusati",&layernonusati);
cut_stuff->SetBranchAddress("NAnticluster",&NAnticluster);
cut_stuff->SetBranchAddress("NTRDSegments",&NTRDSegments);
cut_stuff->SetBranchAddress("NTofClusters",&NTofClusters);
cut_stuff->SetBranchAddress("NTofClustersusati",&NTofClustersusati);
cut_stuff->SetBranchAddress("Rup",&Rup);
cut_stuff->SetBranchAddress("Rdown",&Rdown);
cut_stuff->SetBranchAddress("R",&R);
cut_stuff->SetBranchAddress("chiq",&chiq);
cut_stuff->SetBranchAddress("R_",&R_);
cut_stuff->SetBranchAddress("Chisquare",&Chisquare);
cut_stuff->SetBranchAddress("ResiduiX",&ResiduiX);
cut_stuff->SetBranchAddress("ResiduiY",&ResiduiY);
cut_stuff->SetBranchAddress("Beta",&Beta);
cut_stuff->SetBranchAddress("Betacorr",&Betacorr);
cut_stuff->SetBranchAddress("BetaRICH",&BetaRICH);
cut_stuff->SetBranchAddress("TRDclusters",&TRDclusters);
cut_stuff->SetBranchAddress("NTRDclusters",&NTRDclusters);
cut_stuff->SetBranchAddress("endepostatrack",&endepostatrack);
cut_stuff->SetBranchAddress("NTrackHits",&NTrackHits);
cut_stuff->SetBranchAddress("clusterTrack",&clusterTrack);
cut_stuff->SetBranchAddress("EdepTRD",&EdepTRD);
cut_stuff->SetBranchAddress("zonageo",&zonageo);
cut_stuff->SetBranchAddress("Massa",&Massa);
cut_stuff->SetBranchAddress("Unbias",&Unbias);
}
giov=0;
nprotoni=0;
if(check) entriestot=cut_stuff->GetEntries();
if(check) events =geo_stuff->GetEntries();
INDX=atoi(argv[1]);
cout<<endl;
cout<<INDX<<endl;
cout<<endl;
cout<<"Eventi: "<<events<<endl;
cout<<"Preselezionate: "<<entriestot<<endl;
int entries=entriestot;
if(entries>entriestot) entries=entriestot; 
//entriestot=500;
entries=entriestot;
for(int i=0;i<entries;i++)
{	
	if(!check) break;
	if(i%1300==0) cout<<i/(float)entries*100<<"%"<<endl;
	int k = cut_stuff->GetEvent(i);	
	R_corr=R;
        Beta_corr=Betacorr;
	if(i==0){ tbeg=U_time; cout <<"Tempo Iniziale: "<<tbeg<<endl;}
	if(i==entries-1) {tend=U_time; cout <<"Tempo Finale: "<<tend<<endl;}
	if(scelta==1) aggiungiantupla(cut_stuff,i,pre,0); 
	for(int I=0;I<23;I++) if(R<bin[I+1]&&R>bin[I]/*&&R>fabs(Rcutoff)*1.2&&(Betacorr>fb->Eval(R)||Betacorr<fa->Eval(R))*/) preselezionate[I][zonageo]++;
	
	if (Quality(cut_stuff,i)){
 		giov++;
		if(scelta==1) aggiungiantupla(cut_stuff,i,qual,0);
		for(int J=0;J<23;J++) if(fabs(R_corr)<bin[J+1]&&fabs(R_corr)>bin[J]) quality[J][zonageo]++;
                                                  			
		if (Protoni(cut_stuff,i)) {
					   nprotoni++;
				   if(scelta==1) Grandezzesep(cut_stuff,i,grandezzesep);	
					   Particle_ID=protonsID(cut_stuff,i);	
					   if(Particle_ID==1) {
							    for(int K=0;K<23;K++) if(fabs(R_corr)<bin[K+1]&&fabs(R_corr)>bin[K]) protoni[K][zonageo]++; 
							    for(int K=0;K<23;K++) if(fabs(R_corr)<bin[K+1]&&fabs(R_corr)>bin[K]&&R_corr>fabs(Rcutoff)*1.2) {primari[K][zonageo]++; PROTONI[K]++; if(Unbias>0.5) {Unbiascounts[K]++;Unbias_geo[K][zonageo]++;} 
																				if(BetaRICH>0) primari_RICH[K]++; }	
							    for(int K=0;K<23;K++) if((R)<bin[K+1]&&fabs(R)>bin[K]&&Rgenmis->Eval(R)>fabs(Rcutoff)*1.2) primari_bkgnd[K][zonageo]++;		
								}									
					   		 }				 
		if (Deutoni(cut_stuff,i)) {
                                          if(scelta==1) Grandezzesepd(cut_stuff,i,grandezzesepd);
					  Particle_ID=deutonsID(cut_stuff,i);
					  if(Particle_ID==2)  {
							 for(int L=0;L<23;L++) if(fabs(R_corr)<bin[L+1]&&fabs(R_corr)>bin[L]) deutoni[L][zonageo]++;  
							 for(int K=0;K<23;K++) if(fabs(R_corr)<bin[K+1]&&fabs(R_corr)>bin[K]&&R_corr>Rcutoff*1.2) {primari_D[K][zonageo]++; DEUTONI[K]++;} 
							}		
		  	 }

		
		
		}
	if(scelta==1) Grandezzequal(cut_stuff,i,grandezzequal);
	if(scelta==1) aggiungiantupla(cut_stuff,i,Good_Qual,Particle_ID);
}

cout<<"------Calcolo Live Time-----"<<endl;
zona=0;
for(int j=0;j<23;j++) for(int i=0;i<11;i++) tempobingeo[j][i]=0;
int contriniz=0;
int zona1=0;
int zona2=0;
int contaeventi=0;
int z=0;
int Tempo=0;
for(z=0;z<events;z++)
{
	if(!check) break;
	int k = geo_stuff->GetEvent(z);
	//if(U_time>tend) break;
	contaeventi++;
	if(z%1000000==0) cout<<z/(float)events*100<<"%"<<endl; 
	//////// SCARTO EVENTI FINCHE' NON ENTRO IN UNA NUOVA ZONA GEOM
	zona2=zona1;
		for(int x=0;x<11;x++){
                        double geo= geomag[x]  ;
                        double geo2=geomag[x+1];
                        if(Latitude>geo && Latitude<=geo2)
                        zona1=x;
				}
 	
	if(zona1!=zona2&&z!=0) contriniz=1;
        if(contriniz!=1) {continue;}	
        /////////////////////
	for(int i=0;i<11;i++){
                        double geo= geomag[i]  ;
                        double geo2=geomag[i+1];
                        if(Latitude>geo && Latitude<=geo2) 
                        zona=i;

                        else tempozona[i]=U_time;
                        }
	  if(U_time!=tempozona[zona]){
			tempozona[zona]=U_time;
                        Time[zona]=Time[zona]+Livetime;
                        contasecondi[zona]++;
			}


	////////// CALCOLO TEMPO DI ESPOSIZIONE /////////////
	//cout<<U_time<<" "<<Tempo<<" "<<Rcutoff<<endl;
	for(int i=0;i<11;i++) 
	if(U_time!=Tempo){
	//cout<<U_time<<" "<<Rcutoff<<endl;
	for(int i=0;i<23;i++)
		if(fabs(1.2*Rcutoff)<bin[i+1]&&Rcutoff!=0) {tempobin[i]=tempobin[i]+Livetime;
			tempobingeo[i][zonageo]=tempobingeo[i][zonageo]+Livetime;}
		if(Rcutoff!=0) Tempo=U_time;
	}
	
	/////////////////////////////////////////////////////	

	////////// CALCOLO EFF: DI PRESELEZIONE /////////////
	if(Pres_Unbias>0){
		 for(int L=0;L<23;L++) if(fabs(R_pre)<bin[L+1]&&fabs(R_pre)>bin[L]) pres_unbias[L][zonageo]++;
		 if(Preselected>0) for(int L=0;L<23;L++) if(fabs(R_pre)<bin[L+1]&&fabs(R_pre)>bin[L]) preselected[L][zonageo]++;
	}		
	/////////////////////////////////////////////////////
}	
 for(int i=0;i<11;i++){
                for(int j=0;j<23;j++) std::cout<<tempobingeo[j][i]<<" ";
                std::cout<<endl;}

cout<<"Eventi Tot: "<<events<<endl;
cout<<"Preselezionate Tot: "<<entriestot<<endl;
cout<<endl;
cout<<"Eventi Analizzati: "<<contaeventi<<endl;
cout<<"Preselezionate Analizzate: "<<entries<<endl;
cout<<"selezioni di qualità: "<<giov<<endl;
cout<<"N. Protoni: "<<nprotoni<<endl;
cout<<endl;
cout<<"-----------------------"<<endl;
cout<<"-----EFF. SELEZIONI (risp a PRE)----"<<endl;
cout<<"Taglio anticluster: "<<f/(float)entries*100<<endl;
cout<<"Taglio segmenti TRD: "<<g/(float)entries*100<<endl;
cout<<"Taglio TOF Clusters inutilizzati: "<<h/(float)entries*100<<endl;
cout<<"Taglio Confronto Rup/Rdown: "<<l/(float)entries*100<<endl;
cout<<"Taglio Prob. Q: "<<m/(float)entries*100<<endl;
cout<<"Taglio Fit multipli: "<<n/(float)entries*100<<endl;
cout<<"Taglio HitX: "<<o/(float)entries*100<<endl;
cout<<"Taglio Chi-Quadro traccia: "<<r/(float)entries*100<<endl;
cout<<"Taglio carica TOF: "<<t/(float)entries*100<<endl;
cout<<"Taglio carica Track: "<<u/(float)entries*100<<endl;
cout<<"Taglio carica TRD: "<<v/(float)entries*100<<endl;
cout<<"Taglio layer non usati: "<<s/(float)entries*100<<endl;
cout<<endl;
cout<<"-----SELEZIONI DI REIEZIONE----"<<endl;
cout<<"Edep TOF (R): "<<a/(float)giov*100<<endl;
cout<<"Edep TOF (Beta): "<<alpha/(float)giov*100<<endl;
cout<<"Cluster TOF: "<<b/(float)giov*100<<endl;
cout<<endl;
cout<<"Edep Track (R): "<<c/(float)giov*100<<endl;
cout<<"Edep Track (Beta): "<<delta/(float)giov*100<<endl;
cout<<"Cluster Track: "<<d/(float)giov*100<<endl;
cout<<endl;
cout<<"Edep TRD (R): "<<e/(float)giov*100<<endl;
cout<<"Edep TRD (Beta): "<<Gamma/(float)giov*100<<endl;
cout<<endl;

cout<<"-----ANALISI TEMPI------------- "<<endl;
cout<<endl;
for(int i=0;i<11;i++) {
cout<<"Tempo trascorso in zona "<<i<<": "<<contasecondi[i];
if(contasecondi[i]!=0)
cout<<" sec: Percentuale di tempo vivo: "<<Time[i]/(double)contasecondi[i]*100<<"% "<<endl;
else cout<<" sec"<<endl;
	}

cout<<"Tempo di Volo: "<<tend-tbeg<<" sec."<<endl;
int Contasecondi = 0;
for (int y=0;y<11;y++)
	Contasecondi=Contasecondi+contasecondi[y];
cout<<"Tempo di Misura: "<<Contasecondi<<" sec."<<endl;

for(int i=0;i<23;i++)
cout<<"Tempo di esposizione bin "<<i<<": "<<tempobin[i]<<endl;


if(scelta==1) File->Write();
if(scelta==1) File->Close();

string numero[11]={"0","1","2","3","4","5","6","7","8","9","10"};
{FILE *fp[11];
for(int i=1;i<11;i++){       	
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/protoni"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d	",protoni[j][i]);
        fprintf(fp[i],"\n");
       	fclose(fp[i]);
	}
}
{FILE *fp[11];
for(int i=1;i<11;i++){       	
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/primari"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d	",primari[j][i]);
        fprintf(fp[i],"\n");
       	fclose(fp[i]);
	}
}

{FILE *fp[11];
for(int i=1;i<11;i++){
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/primari_Unb"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d      ",Unbias_geo[j][i]);
        fprintf(fp[i],"\n");
        fclose(fp[i]);
        }
}

{FILE *fp[11];
for(int i=1;i<11;i++){       	
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/primari_bkgnd"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d	",primari_bkgnd[j][i]);
        fprintf(fp[i],"\n");
       	fclose(fp[i]);
	}
}
{
FILE *fp[11];
for(int i=1;i<11;i++){
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/deutoni"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d	",deutoni[j][i]);
        fprintf(fp[i],"\n");
        fclose(fp[i]);
        }
}
{FILE *fp[11];
for(int i=1;i<11;i++){       	
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/primari_D"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d	",primari_D[j][i]);
        fprintf(fp[i],"\n");
       	fclose(fp[i]);
	}
}
{	
FILE *fp[11];
for(int i=1;i<11;i++){
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/preselezionate"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d	",preselezionate[j][i]);
        fprintf(fp[i],"\n");
        fclose(fp[i]);
        }
}
{
FILE *fp[11];
for(int i=1;i<11;i++){
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/quality"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d	",quality[j][i]);
        fprintf(fp[i],"\n");
        fclose(fp[i]);
        }
}
{
FILE *fp[11];
for(int i=1;i<11;i++){
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/tempi"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        fprintf(fp[i],"%7f	",Time[i]);
        fprintf(fp[i],"\n");
        fclose(fp[i]);
        }
}
{
FILE *fp[11];
for(int i=1;i<11;i++){
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/esposizionegeo"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
	for(int j=0;j<23;j++)
        fprintf(fp[i],"%7f      ",tempobingeo[j][i]);
        fprintf(fp[i],"\n");
        fclose(fp[i]);
        }
}


{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/esposizione.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7f         ", tempobin[j]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/PROTONI.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ", PROTONI[j]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/DEUTONI.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ", DEUTONI[j]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Rich_Dati.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ", primari_RICH[j]);
        fprintf(fp,"\n");
        fclose(fp);

}

{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/UNBIAS.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ", Unbiascounts[j]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp[11];
for(int i=1;i<11;i++){
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Preselected"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d      ",preselected[j][i]);
        fprintf(fp[i],"\n");
        fclose(fp[i]);
        }
}

{
FILE *fp[11];
for(int i=1;i<11;i++){
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Pres_Unbias"+numero[i]+".dat";
        fp[i]=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp[i],"%7d      ",pres_unbias[j][i]);
        fprintf(fp[i],"\n");
        fclose(fp[i]);
        }
}

return 1;
}
void aggiungiantupla (TTree *albero,int i,TNtuple *ntupla,int P_ID)
{
	 int k = albero->GetEvent(i);
	 ntupla->Fill(R,Beta_corr,BetaRICH,EdepTOF,E_depTRD,EdepTrack,Massa,zonageo,P_ID,DistTOF,DistTrack,DistTRD,Rcutoff,U_time);
}


void Grandezzequal (TTree *albero,int i,TNtuple *ntupla)
{
         int k = albero->GetEvent(i);

ntupla->Fill(R,Beta,zonageo,Massa,NAnticluster,NTofClusters-NTofClustersusati,fabs(Rup-Rdown)/R,(*ResiduiY)[4],(*ResiduiX)[4],fuoriX,L_fakeD,L_trueD,layernonusati,Chisquare,NTRDSegments);
}


void Grandezzesep (TTree *albero,int i,TNtuple *ntupla)
{
       
        int k = albero->GetEvent(i);
     
ntupla->Fill(R_corr,Beta_corr,BetaRICH,DistTOF,EdepTRD,DistanzaTOT,DistTRD,EdepTrack,RminTrack,DistTrack,PhiProjTOF,PhiProjTrack,PhiProjTRD,zonageo,Rcutoff);
//,clusterTOFfuori,clusterTrackfuori,clusterTRDfuori);
}

void Grandezzesepd (TTree *albero,int i,TNtuple *ntupla)
{

        int k = albero->GetEvent(i);
 ntupla->Fill(R_corr,Beta_corr,BetaRICH,RminTOF,RminTrack,RminTRD,DistTOF,DistTrack,DistTRD,PhiProjTOF,PhiProjTrack,PhiProjTRD,fakeD,trueD,Rcutoff);
}


