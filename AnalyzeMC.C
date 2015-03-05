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
#include "Functions.h"
#include "./Matriciselezione/TOF.h"
#include "./Matriciselezione/Track.h"
#include "./Matriciselezione/TRD.h"
#include "Selections.h"

using namespace std;
void aggiungiantupla (TTree *albero,int i,TNtuple *ntupla,int P_ID);
void Grandezzesep (TTree *albero,int i,TNtuple *ntupla);
void Grandezzesepd (TTree *albero,int i,TNtuple *ntupla);
void Grandezzequal (TTree *albero,int i,TNtuple *ntupla);
void Selez (TTree *albero,int i,TNtuple *ntupla);
int Ev_Num;
int Trig_Num;
double Trig;
double TotalTrig=0;
double Totalevents=0;
double totaltrig=0;
double totaltrig2=0;
double response[24][24];
double norm[24];
int Number=0;
int scelta=0;

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

//string Nome_file= "/afs/ams.cern.ch/user/fdimicco/Dimiccoli/istogrammiMC/" + file_name; 
//TFile *file =TFile::Open("/storage/gpfs_ams/ams/users/kostya/sommaMC.root");
TFile *file =TFile::Open("/storage/gpfs_ams/ams/users/fdimicco/MAIN/sommaMC/sommaMC.root");
TTree *cut_stuff = (TTree *)file->Get("grandezze_tagli");
TTree *geo_stuff = (TTree *)file->Get("parametri_geo");
//string Nome_Output="/afs/ams.cern.ch/user/fdimicco/Dimiccoli/Analisi/ntupleMC/risultati/_"+file_name;
string ARGV(argv[1]);
string indirizzo_out="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/RisultatiMC_"+ARGV+".root";
TFile * File = new TFile(indirizzo_out.c_str(), "RECREATE");

TNtuple *grandezzequal = new TNtuple("grandezzequal","grandezzequal","R:Beta:Massa_gen:Massa:NAnticluster:Clusterinutili:DiffR:residuoY:residuoX:fuoriX:L_trueD:L_fakeD:layernonusati:Chisquare:NTRDSegments");
TNtuple *grandezzesep = new TNtuple("grandezzesep","grandezzesep","R:Beta_corr:BetaRICH:EdepTOF:RminTOF:DistTOF:DistanzaTOT:DistTRD:EdepTrack:RminTrack:DistTrack:PhiProjTOF:PhiProjTrack:PhiProjTRD:Massagen");/*:clusterTOFfuori:clusterTrackfuori:clusterTRDfuori");*/
TNtuple *grandezzesepd = new TNtuple("grandezzesepd","grandezzesepd","R:Beta_corr:BetaRICH:Massagen:RminTOF:RminTrack:RminTRD:DistTOF:DistTrack:DistTRD:PhiProjTOF:PhiProjTrack:PhiProjTRD:fakeD:trueD");
TNtuple * Good_Qual = new TNtuple("Good_Qual","distr for pre","R:Beta:BetaRICH:EdepTOF:EdepTRD:EdepTrack:Massa:Massagen:Momentogen:Betagen:P_ID:DistTOF:DistTrack:DistTRD");
TNtuple * pre = new TNtuple("Pre","distr for pre","R:Beta:BetaRICH:EdepTOF:EdepTRD:EdepTrack:Massa:Massagen:Momentogen:Betagen:P_ID:DistTOF:DistTrack:DistTRD");
TNtuple * qual = new TNtuple("Qual","distr for giov","R:Beta:BetaRICH:EdepTOF:EdepTRD:EdepTrack:Massa:Massagen:Momentogen:Betagen:P_ID:DistTOF:DistTrack:DistTRD");
TNtuple * Background= new TNtuple("Background","distr for pre","R:Beta:BetaRICH:EdepTOF:EdepTRD:EdepTrack:Massa:Massagen:Momentogen:Betagen:P_ID:DistTOF:DistTrack:DistTRD");


geo_stuff->SetBranchAddress("Momento_gen",&Momento_gen);
geo_stuff->SetBranchAddress("Beta_gen",&Beta_gen);
geo_stuff->SetBranchAddress("Massa_gen",&Massa_gen);
geo_stuff->SetBranchAddress("Ev_Num",&Ev_Num);
geo_stuff->SetBranchAddress("Trig_Num",&Trig_Num);
geo_stuff->SetBranchAddress("Pres_Unbias",&Pres_Unbias);
geo_stuff->SetBranchAddress("Preselected",&Preselected);
geo_stuff->SetBranchAddress("R_pre",&R_pre);
cut_stuff->SetBranchAddress("Trig_Num",&Trig_Num);
cut_stuff->SetBranchAddress("Ev_Num",&Ev_Num);
cut_stuff->SetBranchAddress("Momento_gen",&Momento_gen);
cut_stuff->SetBranchAddress("Beta_gen",&Beta_gen);
cut_stuff->SetBranchAddress("Massa_gen",&Massa_gen);
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
cut_stuff->SetBranchAddress("Chisquare",&Chisquare);
cut_stuff->SetBranchAddress("ResiduiX",&ResiduiX);
cut_stuff->SetBranchAddress("ResiduiY",&ResiduiY);
cut_stuff->SetBranchAddress("chiq",&chiq);
cut_stuff->SetBranchAddress("R_",&R_);
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
int giov=0;
int nprotoni=0;
int entries=cut_stuff->GetEntries();
int events =geo_stuff->GetEntries();
int INDX=atoi(argv[1]);
cout<<endl;
cout<<INDX<<endl;
cout<<endl;

cout<<"Eventi: "<<events<<endl;
cout<<"Preselezionate: "<<entries<<endl;
entries=entries;
//if(entries>entriestot) entries=entriestot; 

for(int i=(entries/100)*INDX;i<(entries/100)*(INDX+1);i++)
{
	if(i%1300==0) cout<<i/(float)entries*100<<"%"<<endl;
	int k = cut_stuff->GetEvent(i);	
        if(Trig_Num<Trig) TotalTrig=TotalTrig+(double)Trig; 	
	totaltrig=TotalTrig+Trig;
	Trig=Trig_Num;
	//cout<<Trig_Num<<" "<<TotalTrig<<" "<<totaltrig<<endl;
	R_corr=R;
	Beta_corr=Betacorr;
	if(scelta==1) aggiungiantupla(cut_stuff,i,pre,0);
	if(Massa_gen<1&&Massa_gen>0.5) for(int I=0;I<23;I++) if(fabs(R)<bin[I+1]&&fabs(R)>bin[I]) preselezionate[I][0]++;
	
	if (Quality(cut_stuff,i)){
 		giov++;
		if(scelta==1) aggiungiantupla(cut_stuff,i,qual,0);
		if(Massa_gen<1&&Massa_gen>0.5) for(int J=0;J<23;J++) if(fabs(R_corr)<bin[J+1]&&fabs(R_corr)>bin[J]) quality[J][0]++;
                if(Massa_gen>1&&Massa_gen<3) for(int J=0;J<23;J++) if(fabs(R_corr)<bin[J+1]&&fabs(R_corr)>bin[J]) quality_D[J]++;
		//////////////////// CORR EDEP /////////////////////
	        EdepTOF=1/((1/EdepTOF)*Corr_TOF->Eval(Beta_corr));
		E_depTRD=1/((1/E_depTRD)*Corr_TRD->Eval(Beta_corr));
		EdepTrack=1/((1/EdepTrack)*Corr_Track->Eval(Beta_corr));
		///////////////////////////////////////////////////// 
		/////////////////// CORR BETA RICH /////////////////
		//if(BetaRICH>0)
		//BetaRICH=BetaRICH*CorrRICH->Eval(R);
		////////////////////////////////////////////////////		
		//////////////// MATRICE DI RISPOSTA ///////////////
		if(Massa_gen<1&&Massa_gen>0.5){
		for(int I=0;I<24;I++)
                                        if(fabs(Momento_gen)<bin[I+1]&&fabs(Momento_gen)>bin[I])
						for(int J=0;J<24;J++)
							if(fabs(R_corr)<bin[J+1]&&fabs(R_corr)>bin[J])  response[J][I]++;
		for(int I=0;I<24;I++)
                                        if(fabs(Momento_gen)<bin[I+1]&&fabs(Momento_gen)>bin[I]) norm[I]++;
		}			
		////////////////////////////////////////////////////
		if (Protoni(cut_stuff,i)) {
					   nprotoni++;	
					   if(scelta==1) Grandezzesep(cut_stuff,i,grandezzesep);	
					   Particle_ID=protonsID(cut_stuff,i); 
					   if(Massa_gen<1&&Massa_gen>0.5&&Particle_ID==1) {for(int K=0;K<23;K++) if(fabs(R_corr)<bin[K+1]&&fabs(R_corr)>bin[K]) protoni[K][0]++;
												for(int K=0;K<23;K++) if(fabs(R_corr)<bin[K+1]&&fabs(R_corr)>bin[K]&&BetaRICH>0) primari_RICH_MC[K]++;}
							     	 
						}				 
		if (Deutoni(cut_stuff,i)) {
										
                                           	if(Massa_gen>1.5&&Massa_gen<3){
							if(scelta==1) Grandezzesepd(cut_stuff,i,grandezzesepd);
						       Particle_ID=deutonsID(cut_stuff,i);	
							if(Particle_ID==2) for(int L=0;L<23;L++) if(fabs(R_corr)<bin[L+1]&&fabs(R_corr)>bin[L]) deutoni[L][0]++;  
 									   
								}
						if(Massa_gen<1&&Massa_gen>0.5){
							if(scelta==1) Grandezzesepd(cut_stuff,i,grandezzesepd);
							Particle_ID=deutonsID(cut_stuff,i);	
						        if(Particle_ID==2) for(int L=0;L<23;L++) if(fabs(R_corr)<bin[L+1]&&fabs(R_corr)>bin[L]) background[L]++; 
 						   			

								}
							
						if(Massa_gen>3){
                                                        if(scelta==1) Grandezzesepd(cut_stuff,i,grandezzesepd);
							Particle_ID=deutonsID(cut_stuff,i);
                                                        if(Particle_ID==2) for(int L=0;L<23;L++) if(fabs(R_corr)<bin[L+1]&&fabs(R_corr)>bin[L]) background_He[L]++;


                                                                }
					        if(Massa_gen>-0.5&&Massa_gen<0){
                                                        if(scelta==1) Grandezzesepd(cut_stuff,i,grandezzesepd);
							Particle_ID=deutonsID(cut_stuff,i);
                                                        if(Particle_ID==2) for(int L=0;L<23;L++) if(fabs(R_corr)<bin[L+1]&&fabs(R_corr)>bin[L]) background_el[L]++;
	

                                                                }
						if(Massa_gen<0.5&&Massa_gen>0){
                                                        if(scelta==1) Grandezzesepd(cut_stuff,i,grandezzesepd);
							Particle_ID=deutonsID(cut_stuff,i);
                                                        if(Particle_ID==2) for(int L=0;L<23;L++) if(fabs(R_corr)<bin[L+1]&&fabs(R_corr)>bin[L]) background_pos[L]++;


                                                                }


					  }	 


		
		}
		if(scelta==1) Grandezzequal(cut_stuff,i,grandezzequal);
		if(scelta==1) aggiungiantupla(cut_stuff,i,Good_Qual,Particle_ID);

}

//ANALISI EFFICIENZA DI GENERAZIONE
cout<<"Trigger tot: "<<totaltrig<<endl;
TotalTrig=0;
Trig=0;
int z;
for(z=(events/100)*INDX;z<(events/100)*(INDX+1);z++)
{
	int k = geo_stuff->GetEvent(z);
	//std::cout<<Massa_gen<<" "<<Momento_gen<<std::endl;
	if(Trig_Num<Trig)TotalTrig=TotalTrig+(double)Trig;
        totaltrig2=TotalTrig+Trig;
        Trig=Trig_Num;
	//cout<<Trig_Num<<" "<<TotalTrig<<" "<<totaltrig2<<endl;
	if(z%100000==0) cout<<z/(float)events*100<<" "<<totaltrig2<<endl;
	 if(Massa_gen<0.5&&Massa_gen>0) for(int M=0;M<23;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) efficienzagen_pos[M]++;
	 if(Massa_gen<0&&Massa_gen>-0.5) for(int M=0;M<23;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) efficienzagen_el[M]++;
	if(Massa_gen<1&&Massa_gen>0.5) for(int M=0;M<23;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) efficienzagen[M]++; 
	if(Massa_gen>1&&Massa_gen<3) for(int M=0;M<23;M++) if(fabs(Momento_gen)<bin[M+1]&&fabs(Momento_gen)>bin[M]) efficienzagen_D[M]++;
	if(Massa_gen>3) for(int M=0;M<23;M++) if(fabs(Momento_gen/2)<bin[M+1]&&fabs(Momento_gen/2)>bin[M]) efficienzagen_He[M]++;
//	if(totaltrig<=totaltrig2) break;
	////////////////////////////// EFFICIENZA DI PRESELEZIONE////////////////////////////////
	if(Pres_Unbias>0&&Massa_gen<1&&Massa_gen>0.5){
                 for(int L=0;L<23;L++) if(fabs(R_pre)<bin[L+1]&&fabs(R_pre)>bin[L]) pres_unbias[L][0]++;
                 if(Preselected>0) for(int L=0;L<23;L++) if(fabs(R_pre)<bin[L+1]&&fabs(R_pre)>bin[L]) preselected[L][0]++;
        }

}

//for(int J=0;J<23;J++)
//                      for(int I=0;I<23;I++) {if(norm[I]!=0) response[J][I]=response[J][I]/norm[I]; else response[J][I]=0;}
         
cout<<"Eventi Tot: "<<z<<endl;
cout<<"Preselezionate Tot: "<<entries<<endl;
cout<<endl;
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
cout<<"Taglio Chi-Quadro: "<<r/(float)entries*100<<endl;
cout<<"Taglio carica TOF: "<<t/(float)entries*100<<endl;
cout<<"Taglio carica Track: "<<u/(float)entries*100<<endl;
cout<<"Taglio carica TRD: "<<v/(float)entries*100<<endl;
cout<<"Taglio layer non usati: "<<s/(float)entries*100<<endl;
cout<<endl;
cout<<"-----SELEZIONI DI REIEZIONE----"<<endl;
cout<<"Cluster TOF: "<<b/(float)giov*100<<endl;
cout<<endl;
cout<<"Cluster Track: "<<d/(float)giov*100<<endl;
cout<<endl;
cout<<"Cluster TRD: "<<e/(float)giov*100<<endl;
cout<<endl;

cout<<"-----ANALISI EFFICIENZA (PROTONI)------------- "<<endl;
cout<<endl;
 for(int i=0; i<23;i++)
        if(efficienzagen[i]!=0)
		cout<<"efficienza da"<<bin[i]<<" a " << bin[i+1]<<": "<<protoni[i][0]<<" nel bin " <<i<<" "<<( protoni[i][0]/(double)efficienzagen[i]*100)<<"%"<< " rispetto a preselezione:  "<<protoni[i][0]/(double)preselezionate[i][0]*100<<"%"<<endl;

        else cout<<"efficienza da "<<bin[i]<<" a "<< bin[i+1]<<": nessun evento generato nel bin"<<endl;
cout<<endl;   
cout<<"-----ANALISI EFFICIENZA (DEUTONI)------------- "<<endl;
cout<<endl;
 for(int i=0; i<23;i++)
        if(efficienzagen_D[i]!=0)
		cout<<"efficienza da"<<bin[i]<<" a " << bin[i+1]<<": "<<deutoni[i][0]<<" nel bin " <<i<<" "<<( deutoni[i][0]/(double)efficienzagen_D[i]*100)<<"%"<<endl;

        else cout<<"efficienza da "<<bin[i]<<" a "<< bin[i+1]<<": nessun evento generato nel bin"<<endl;
cout<<endl;       
cout<<"----ANALISI FONDO----"<<endl;
cout<<endl;
for(int i=0; i<23;i++) {
	 if(efficienzagen[i]!=0&&background[i]>0)
         	   cout<<"Fondo da"<<bin[i]<<" a " << bin[i+1]<<": "<<background[i]<<" nel bin " <<i<<" su "<< efficienzagen[i]<<" : "<<(background[i]/(double)efficienzagen[i]*100)<<"% ---> R.P. : "<< protoni[i][0]/background[i]<<endl;

	  if(efficienzagen[i]!=0&&background[i]==0)
	cout<<"Fondo da"<<bin[i]<<" a " << bin[i+1]<<": "<<background[i]<<" nel bin " <<i<<" su "<<efficienzagen[i]<<" : "<<"Minore di: "<<(1/(double)efficienzagen[i]*100)<<"% ---> R.P. Maggiore di: "<<protoni[i][0]<<endl;

        if(efficienzagen[i]==0) cout<<"Fondo da "<<bin[i]<<" a "<< bin[i+1]<<": nessun evento generato nel bin"<<endl;
}

cout<<"------------------- MATRICE DI RISPOSTA -------------"<<endl;
for(int j=0; j<23;j++){
	for(int i=0; i<23;i++)
			cout<<response[j][i]<<" ";
			cout<<endl;}

cout<<"------------------- NORM -------------"<<endl;
	 for(int i=0; i<23;i++)
			cout<<norm[i]<<" ";
			cout<<endl;

if(scelta==1) File->Write();
File->Close();

string numero[11]={"0","1","2","3","4","5","6","7","8","9","10"};
{
FILE *fp;
      
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Matricerisposta.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<24;j++)  {
        for(int i=0; i<24;i++)	fprintf(fp,"%7f         ",response[j][i]);
        fprintf(fp,"\n");
	}
	fclose(fp); 
}    
{
FILE *fp; 

        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Norm.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ",norm[j]);
        fprintf(fp,"\n");
        fclose(fp); 
}  
{
FILE *fp;

        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/protoni0.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d		",protoni[j][0]);
        fprintf(fp,"\n");
        fclose(fp);
}
{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/deutoni0.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d		",deutoni[j][0]);
        fprintf(fp,"\n");
        fclose(fp);
}
{
FILE *fp;

        
	string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/preselezionate0.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d		",preselezionate[j][0]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp;
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Preselected0.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d      ",preselected[j][0]);
        fprintf(fp,"\n");
        fclose(fp);
        
}

{
FILE *fp;
        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Pres_Unbias0.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d      ",pres_unbias[j][0]);
        fprintf(fp,"\n");
        fclose(fp);
        
}

{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/quality0.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d		",quality[j][0]);
        fprintf(fp,"\n");
        fclose(fp);

}

{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/quality_D.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ",quality_D[j]);
        fprintf(fp,"\n");
        fclose(fp);

}

{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/tempi0.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d 	",efficienzagen[j]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/tempi0_D.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d 	",efficienzagen_D[j]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/tempi0_el.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ",efficienzagen_pos[j]);
        fprintf(fp,"\n");
        fclose(fp);

}


{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Template_D.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ",Template_D[j]);
        fprintf(fp,"\n");
        fclose(fp);

}

{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/tempi0_He.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ",efficienzagen_He[j]);
        fprintf(fp,"\n");
        fclose(fp);

}

{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/background.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ",background[j]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/background_He.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ",background_He[j]);
        fprintf(fp,"\n");
        fclose(fp);

}
{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/Rich_MC.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ", primari_RICH_MC[j]);
        fprintf(fp,"\n");
        fclose(fp);

}

{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/background_el.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7d         ",background_pos[j]);
        fprintf(fp,"\n");
        fclose(fp);

}

{
FILE *fp;


        string stringa="/storage/gpfs_ams/ams/users/fdimicco/Risultati/risultati/trigger.dat";
        fp=fopen(stringa.c_str(),"a");
        for(int j=0;j<23;j++)
        fprintf(fp,"%7g         ",totaltrig2/(double)12);
        fprintf(fp,"\n");
        fclose(fp);

}


return 1;
}


void aggiungiantupla (TTree *albero,int i,TNtuple *ntupla,int P_ID)
{
	 int k = albero->GetEvent(i);
	ntupla->Fill(R,Beta_corr,BetaRICH,EdepTOF,E_depTRD,EdepTrack,Massa,Massa_gen,Momento_gen,Beta_gen,P_ID,DistTOF,DistTrack,DistTRD);

}


void Grandezzequal (TTree *albero,int i,TNtuple *ntupla)
{
         int k = albero->GetEvent(i);

ntupla->Fill(R,Betacorr,Massa_gen,Massa,NAnticluster,NTofClusters-NTofClustersusati,fabs(Rup-Rdown)/R,(*ResiduiY)[4],(*ResiduiX)[4],fuoriX,L_trueD,L_fakeD,layernonusati,Chisquare,NTRDSegments);
}


void Grandezzesep (TTree *albero,int i,TNtuple *ntupla)
{
       
        int k = albero->GetEvent(i);
     
ntupla->Fill(R_corr,Beta_corr,BetaRICH,EdepTOF,RminTOF,DistTOF,DistanzaTOT,DistTRD,EdepTrack,RminTrack,DistTrack,PhiProjTOF,PhiProjTrack,PhiProjTRD,Massa_gen);
//,clusterTOFfuori,clusterTrackfuori,clusterTRDfuori);
}

void Grandezzesepd (TTree *albero,int i,TNtuple *ntupla)
{

        int k = albero->GetEvent(i);
 ntupla->Fill(R_corr,Beta_corr,BetaRICH,Massa_gen,RminTOF,RminTrack,RminTRD,DistTOF,DistTrack,DistTRD,PhiProjTOF,PhiProjTrack,PhiProjTRD,fakeD,trueD);
}

	
	


