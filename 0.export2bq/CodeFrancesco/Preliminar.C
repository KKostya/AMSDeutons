#include "TH2.h"
#include "TH3.h"
#include <TVector3.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstring>
#include <vector>
#include "TMath.h"
#include "TCanvas.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <stdarg.h>
#include <TSpline.h>
#include "TFractionFitter.h"
#include "THStack.h"
#include "TNtuple.h"
#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF2.h"
#include <math.h>
#include <cstring>
#include <TGraphErrors.h>

using namespace std;

float Massa=0;
float Massagen=0;
float Beta=0;
float Betacorr=0;
float CaricaTOF=0;
float CaricaTRD=0;
float CaricaTrack=0;
float EdepTOFU=0;
float EdepTOFD=0;
float EdepTrack=0;
float EdepTOFteo=0;
float R=0;
float BetaRICH=0;
float Momentogen=0;
float Betagen=0;
float Beta_corr=0;
float Rcutoff=0;
float bin[24];
float Qbest=0;
double betacent[30];
float B1,B2;
float EdepL1=0;
float Cutmask=0;
double mean_beta[30]={0};
double mean_betaNaF[30]={0};
double mean_betaAgl[30]={0};
int main(int argc, char * argv[]){

	TCanvas *a1=new TCanvas("Beta vs R - TOF");
	TCanvas *a2=new TCanvas("Beta vs R - RICH NaF");
	TCanvas *a3=new TCanvas("Beta vs R - RICH Agl");
	TCanvas *c=new TCanvas("Inv. E. Dep. L1 (no corr)");
	TCanvas *c_2=new TCanvas("E. Dep. vs Beta (L1)");
	TCanvas *c_3=new TCanvas("E. Dep. L1 (no corr)");
	TCanvas *c1=new TCanvas("Inv. E. Dep. TOF (no corr)");
	TCanvas *c1_bis=new TCanvas("Inv. E. Dep. Track (no corr)");
	TCanvas *c1_tris=new TCanvas("Inv. E. Dep. TRD (no corr)");
	TCanvas *c2=new TCanvas("E. Dep. vs Beta (TOF)");
	TCanvas *c2_bis=new TCanvas("E. Dep. vs Beta (Track)");
	TCanvas *c2_tris=new TCanvas("E. Dep. vs Beta (TRD)");
	TCanvas *c3=new TCanvas("E. Dep. TOF (no corr)");
	TCanvas *c3_bis=new TCanvas("E. Dep. Track (no corr)");
	TCanvas *c3_tris=new TCanvas("E. Dep. TRD (no corr)");
	TCanvas *c4=new TCanvas("DATA/MC E.Dep Difference vs Beta");
	TCanvas *c5=new TCanvas("E. Dep. TOF (corr)");
	TCanvas *c5_bis=new TCanvas("E. Dep. Track (corr)");
	TCanvas *c5_tris=new TCanvas("E. Dep. TRD (corr)");
	TCanvas *c_6=new TCanvas("sigma Edep L1 (inv)");
	TCanvas *c6=new TCanvas("sigma Edep TOF (inv)");
	TCanvas *c6_bis=new TCanvas("sigma Edep Track (inv)");
	TCanvas *c6_tris=new TCanvas("sigma Edep TRD (inv)");
	TCanvas *c7=new TCanvas("Inverse Beta (TOF)");
	TCanvas *c7_bis=new TCanvas("Inverse Beta (RICH NaF)");
	TCanvas *c7_tris=new TCanvas("Inverse Beta (RICH Agl)");
	TCanvas *c8=new TCanvas("Sigma Inverse Beta (TOF)");
	TCanvas *c8_bis=new TCanvas("Sigma Inverse Beta (RICH NaF)");
	TCanvas *c8_tris=new TCanvas("Sigma Inverse Beta (RICH Agl)");
	TCanvas *c9=new TCanvas("Inverse R");
	TCanvas *c10=new TCanvas("Sigma R");
	TCanvas *c11=new TCanvas("Inverse Beta (TOF - measured R Bins)");
	TCanvas *c12=new TCanvas("Beta Peak (MC/Data)");
	TCanvas *c13=new TCanvas("Sigma Inverse Beta");
	TCanvas *c14=new TCanvas("Inverse R (measured Beta Bins)");	
	TCanvas *c14_bis=new TCanvas("Inverse R (measured Beta NaF Bins)");
	TCanvas *c14_tris=new TCanvas("Inverse R (measured Beta Agl Bins)");
	TCanvas *c15=new TCanvas("R Peak (MC/Data)");
	TCanvas *c16=new TCanvas("Sigma Inverse R");
	TCanvas *c17=new TCanvas("Inverse Mass (measured Beta Bins)");
        TCanvas *c17_bis=new TCanvas("Inverse Mass (measured Beta NaF Bins)");
        TCanvas *c17_tris=new TCanvas("Inverse Mass (measured Beta Agl Bins)");
	TCanvas *c18=new TCanvas("Inverse Mass Resolution ");

	c->Divide(6,5);
	c_2->Divide(6,5);
	c_3->Divide(6,5);
	c1->Divide(6,5);
	c1_bis->Divide(6,5);
	c1_tris->Divide(6,5);
	c3->Divide(6,5);
	c3_bis->Divide(6,5);
	c3_tris->Divide(6,5);
	c5->Divide(6,5);
	c5_bis->Divide(6,5);
	c5_tris->Divide(6,5);
	c7->Divide(6,5);
	c7_bis->Divide(6,5);
	c7_tris->Divide(6,5);
	c9->Divide(6,4);
	c11->Divide(6,4);
	c14->Divide(6,3);
	c14_bis->Divide(6,3);
	c14_tris->Divide(6,3);
	c17->Divide(6,3);
        c17_bis->Divide(6,3);
        c17_tris->Divide(6,3);
	c8->Divide(3,1);
	c8_bis->Divide(3,1);
	c8_tris->Divide(3,1);
	c10->Divide(3,1);
	c15->Divide(3,1);
	c16->Divide(3,1);
	string mesi[30]={"Maggio2011","Giugno2011","Luglio2011","Agosto2011","Settembre2011","Ottobre2011","Novembre2011","Dicembre2011","Gennaio2012","Febbraio2012","Marzo2012","Aprile2012","Maggio2012","Giugno2012","Luglio2012","Agosto2012","Settembre2012","Ottobre2012","Novembre2012","Dicembre2012","Gennaio2013","Febbraio2013","Marzo2013","Aprile2013","Maggio2013","Giugno2013","Luglio2013","Agosto2013","Settembre2013","Ottobre2013"};
	cout<<argv[1]<<endl;
	string mese=argv[1]; 
	string nomefile1="../Risultati/"+mese+"/RisultatiMC.root";
	string nomefile2="../Risultati/"+mese+"/RisultatiDATI.root";
	TFile *file1 =TFile::Open(nomefile1.c_str());
	TFile *file2 =TFile::Open(nomefile2.c_str());
	TNtuple *ntupla1=(TNtuple*)file1->Get("pre");
	TNtuple *ntupla2=(TNtuple*)file2->Get("Pre");
	//pre-qual
	ntupla1->SetBranchAddress("Beta",&Beta);
	ntupla1->SetBranchAddress("R",&R);
	ntupla1->SetBranchAddress("EdepL1",&EdepL1);
	ntupla1->SetBranchAddress("EdepTOFU",&EdepTOFU);
	ntupla1->SetBranchAddress("EdepTOFD",&EdepTOFD);
	ntupla1->SetBranchAddress("EdepTrack",&EdepTrack);
	ntupla1->SetBranchAddress("Momentogen",&Momentogen);
	ntupla1->SetBranchAddress("Betagen",&Betagen);
	ntupla1->SetBranchAddress("BetaRICH_new",&BetaRICH);
	ntupla1->SetBranchAddress("Cutmask",&Cutmask);
	ntupla1->SetBranchAddress("Massagen",&Massagen);

	ntupla2->SetBranchAddress("Beta",&Beta);
	ntupla2->SetBranchAddress("EdepL1",&EdepL1);
	ntupla2->SetBranchAddress("EdepTOFU",&EdepTOFU);
	ntupla2->SetBranchAddress("EdepTOFD",&EdepTOFD);
	ntupla2->SetBranchAddress("EdepTrack",&EdepTrack);
	ntupla2->SetBranchAddress("BetaRICH_new",&BetaRICH);
	ntupla2->SetBranchAddress("Cutmask",&Cutmask);
	ntupla2->SetBranchAddress("R",&R);
	ntupla2->SetBranchAddress("Rcutoff",&Rcutoff);
	ntupla2->SetBranchAddress("Cutmask",&Cutmask);

	cout<<"**************************** BETA BINS TOF***********************************"<<endl;
	float B=0.4;
	float B1=0;
	float B2=0;
	float E=0.1;
	int binnum=0;
	float a=(log(0.9)-log(0.1))/18;
	float E2=exp(log(0.1)+1.5*a);
	float Betabins[18]={0.4};
	float Betacent[18]={0};
	float Ekincent[18]={0};
	while(B1<0.85){
		E=exp(log(0.1)+binnum*a);
		E2=exp(log(0.1)+(binnum+0.5)*a);
		B1=sqrt(1-1/(pow(E+1,2)));
		B2=sqrt(1-1/(pow(E2+1,2)));
		Betabins[binnum]=B1;
		Betacent[binnum]=B2;
		Ekincent[binnum]=1/pow(1-pow(B2,2),0.5)-1;
		binnum++;
	}
	for(int i=0;i<18;i++) cout<<Betabins[i]<<" "<<Betabins[i+1]-Betabins[i]<<endl;
	string TitoliTOF[18];
	for(int i=0;i<18;i++){
                ostringstream ss;
                ss<<Betabins[i];
                TitoliTOF[i]= ss.str();
                cout<<TitoliTOF[i]<<", ";
        }
        cout<<endl;

	cout<<"**************************** BETA BINS NaF***********************************"<<endl;
	a=(log(4.025)-log(0.666))/18;
	E2=exp(log(0.666)+1.5*a);
	float BetabinsNaF[18]={0.4};
	float BetacentNaF[18]={0};
	float EkincentNaF[18]={0};
	binnum=0;
	while(B1<0.98){
		E=exp(log(0.666)+binnum*a);
		E2=exp(log(0.666)+(binnum+0.5)*a);
		B1=sqrt(1-1/(pow(E+1,2)));
		B2=sqrt(1-1/(pow(E2+1,2)));
		BetabinsNaF[binnum]=B1;
		BetacentNaF[binnum]=B2;
		EkincentNaF[binnum]=1/pow(1-pow(B1,2),0.5)-1;
		binnum++;
	}
	for(int i=0;i<18;i++) cout<<BetabinsNaF[i]<<" "<<BetabinsNaF[i+1]-BetabinsNaF[i]<<endl;
	string TitoliNaF[18];
	for(int i=0;i<18;i++){
		ostringstream ss;
		ss<<BetabinsNaF[i];
		TitoliNaF[i]= ss.str();
		cout<<TitoliNaF[i]<<", ";
	}
	cout<<endl;
	cout<<"**************************** BETA BINS Agl***********************************"<<endl;
	a=(log(9.01)-log(2.57))/18;
	E2=exp(log(2.57)+1.5*a);
	float BetabinsAgl[18]={0.4};
	float BetacentAgl[18]={0};
	float EkincentAgl[18]={0};
	binnum=0;
	while(B1<0.995){
		E=exp(log(2.57)+binnum*a);
		E2=exp(log(2.57)+(binnum+0.5)*a);
		B1=sqrt(1-1/(pow(E+1,2)));
		B2=sqrt(1-1/(pow(E2+1,2)));
		BetabinsAgl[binnum]=B1;
		BetacentAgl[binnum]=B2;
		EkincentAgl[binnum]=1/pow(1-pow(B2,2),0.5)-1;
		binnum++;
	}
	for(int i=0;i<18;i++) cout<<BetabinsAgl[i]<<" "<<BetabinsAgl[i+1]-BetabinsAgl[i]<<endl;
	string TitoliAgl[18];
	for(int i=0;i<18;i++){
                ostringstream ss;
                ss<<BetabinsAgl[i];
                TitoliAgl[i]= ss.str();
                cout<<TitoliAgl[i]<<", ";
        }
        cout<<endl;

	//////////////////////////////////////////////////////
	cout<<"**************************** R BINS***********************************"<<endl;
	for(int i=0;i<24;i++)
	{
		float temp=i+7;
		bin[i]=0.1*pow(10,temp/9.5);
	}
	string TitoliR[24];
	for(int i=0;i<24;i++){
                ostringstream ss;
                ss<<bin[i];
                TitoliR[i]= ss.str();
                cout<<TitoliR[i]<<", ";
        }
        cout<<endl;
	double valorecent[24]={0.620376,0.79053,1.28364,1.63572, 2.08435, 2.65604, 3.38452,4.31281, 5.49571, 7.00304, 8.9238,11.3714, 14.4903,18.4646, 23.5289, 29.9823, 38.2058, 48.6846, 62.0376, 79.053, 100.735, 128.364,162.3776739189};

	for(int i=0;i<30;i++)	betacent[i]=0.4+(2*i/(double)100)+0.01;        
	////////////////////////////////////////////////////////////////////////
	TF1 *protons = new TF1("f1","pow((pow(x,2)/pow(0.938,2)/(1 + pow(x,2)/pow(0.938,2))),0.5)",0.1,100);
	TF1 *deutons = new TF1("f1","pow((pow(x,2)/pow(1.875,2)/(1 + pow(x,2)/pow(1.875,2))),0.5)",0.1,100);
	TF1 *RBeta = new TF1("f1","pow((pow(0.938,2)*(pow(x,2)/(1-pow(x,2)))),0.5)",0.1,0.999999999999999999999999999999);
	TF1 *RBeta_P = new TF1("f1","pow((pow(1.875,2)*(pow(x,2)/(1-pow(x,2)))),0.5)",0.1,0.999999999999999999999999999999);

	TH1F *RisoluzioniTOFU[30];
	TH1F *RisoluzioniTrack[30];
	TH1F *RisoluzioniTOFD[30];
	TH1F *RisoluzioniL1[30];
	TH1F *DistribuzioniTOFU_corr[30];
	TH1F *DistribuzioniTrack_corr[30];
	TH1F *DistribuzioniTOFD_corr[30];
	TH1F *DistribuzioniL1_corr[30];

	TH1F *RisoluzioniTOFU_D[30];
	TH1F *RisoluzioniTrack_D[30];
	TH1F *RisoluzioniTOFD_D[30];
	TH1F *RisoluzioniL1_D[30];

	TH1F *RisoluzioniBeta[30];
	TH1F *RisoluzioniBetaNaF[30];
	TH1F *RisoluzioniBetaAgl[30];
	TH1F *RisoluzioniR[24];
	TH1F *RisoluzioniBeta_R[24];
	TH1F *RisoluzioniBeta_R_D[24];	
	TH1F *RisoluzioniR_Beta[18];
	TH1F *RisoluzioniR_Beta_D[18];
	TH1F *RisoluzioniR_BetaNaF[18];
	TH1F *RisoluzioniR_BetaNaF_D[18];
	TH1F *RisoluzioniR_BetaAgl[18];
	TH1F *RisoluzioniR_BetaAgl_D[18];
	TH1F *RisoluzioniM_Beta[18];
        TH1F *RisoluzioniM_Beta_D[18];
        TH1F *RisoluzioniM_BetaNaF[18];
        TH1F *RisoluzioniM_BetaNaF_D[18];
        TH1F *RisoluzioniM_BetaAgl[18];
        TH1F *RisoluzioniM_BetaAgl_D[18];


	TH1F *DistribuzioniTOFU[30];
	TH1F *DistribuzioniTrack[30];
	TH1F *DistribuzioniTOFD[30];
	TH1F *DistribuzioniL1[30];

	TH1F *DistribuzioniTOFU_D[30];
	TH1F *DistribuzioniTrack_D[30];
	TH1F *DistribuzioniTOFD_D[30];
	TH1F *DistribuzioniL1_D[30];	

	TH2F * h=new TH2F("","",1000,0,1,1000,0,1);
	TH2F * h1=new TH2F("","",1000,0,1,1000,0,15);
	TH2F * h2=new TH2F("","",1000,0,1,1000,0,1);
	TH2F * h3=new TH2F("","",1000,0,1,1000,0,20);

	TH2F * BetavsR_TOF_D=new TH2F("","",1000,0,5,1000,0.4,1);
	TH2F * BetavsR_NaF_D=new TH2F("","",1000,0,20,1000,0.75,1);
	TH2F * BetavsR_Agl_D=new TH2F("","",1000,0,20,1000,0.95,1);	

	for(int i=0;i<30;i++){
		RisoluzioniTOFU_D[i]=new TH1F("","",150,0,1);
		RisoluzioniTrack_D[i]=new TH1F("","",150,0,20);
		RisoluzioniTOFD_D[i]=new TH1F("","",150,0,1);
		RisoluzioniL1_D[i]=new TH1F("","",150,0,20);
		DistribuzioniTOFU_D[i]=new TH1F("","",150,0,20);
		DistribuzioniTrack_D[i]=new TH1F("","",150,0,1);
		DistribuzioniTOFD_D[i]=new TH1F("","",150,0,20);
		DistribuzioniL1_D[i]=new TH1F("","",150,0,1);
		if(i<24) RisoluzioniBeta_R_D[i]=new TH1F("","",300,0,4);
		if(i<18) RisoluzioniR_Beta_D[i]=new TH1F("","",300,0,4);
		if(i<18) RisoluzioniR_BetaNaF_D[i]=new TH1F("","",200,0.2,4);
		if(i<18) RisoluzioniR_BetaAgl_D[i]=new TH1F("","",600,0.05,4);
		if(i<18) RisoluzioniM_Beta_D[i]=new TH1F("","",300,0,4);
                if(i<18) RisoluzioniM_BetaNaF_D[i]=new TH1F("","",200,0.2,4);
                if(i<18) RisoluzioniM_BetaAgl_D[i]=new TH1F("","",600,0.05,4);
	}
	cout<<"************ TITOLI *****************"<<endl;
	string TitoliBetaLin[30];
	string TitoliNaFLin[30];
        string TitoliAglLin[30];
	B1=0.4;
        for(int j=0; j<30;j++){
                        ostringstream ss;
                        ss<<B1;
                        TitoliBetaLin[j]= ss.str();
                        B1=B1+0.02;
                }
        B1=0.8;
        for(int j=0; j<30;j++){
                ostringstream ss;
                ss<<B1;
                TitoliNaFLin[j]= ss.str();
                B1=B1+0.2/30.;
        }
        B1=0.95;
        for(int j=0; j<30;j++){
                ostringstream ss;
                ss<<B1;
                TitoliAglLin[j]= ss.str();
                B1=B1+0.05/30.;
        }
	cout<<"*************************** DATA READING **********************************"<<endl;
	for(int i=0; i<ntupla2->GetEntries();i++) {
		int k = ntupla2->GetEvent(i);
		B1=0.4;
		B2=0.42;
		if(i%100000==0) cout<<i<<endl;
		BetavsR_TOF_D->Fill(R,Beta);
		if((((int)Cutmask)>>11)==512) BetavsR_NaF_D->Fill(R,BetaRICH);
		if((((int)Cutmask)>>11)==0) BetavsR_Agl_D->Fill(R,BetaRICH);
		h->Fill(Beta,EdepL1);
		h1->Fill(Beta,EdepTOFU);
		h2->Fill(Beta,EdepTrack);
		h3->Fill(Beta,EdepTOFD);
		Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Beta,2)),0.5)/Beta,2)),0.5);
		if((((int)Cutmask)>>11)==512||(((int)Cutmask)>>11)==0) Massa=pow(fabs(pow(fabs(R)*pow((1-pow(BetaRICH,2)),0.5)/BetaRICH,2)),0.5);
		for(int j=0; j<30;j++){
			if(Beta>B1&&Beta<=B2){
				if(EdepL1>0){
					RisoluzioniL1_D[j]->Fill(1/EdepL1);
					DistribuzioniL1_D[j]->Fill(EdepL1);
				}
				RisoluzioniTOFU_D[j]->Fill(1/EdepTOFU);
				DistribuzioniTOFU_D[j]->Fill(EdepTOFU);
				RisoluzioniTrack_D[j]->Fill(1/EdepTrack);
				DistribuzioniTrack_D[j]->Fill(EdepTrack);
				RisoluzioniTOFD_D[j]->Fill(1/EdepTOFD);
				DistribuzioniTOFD_D[j]->Fill(EdepTOFD);
			}
			B1=B1+0.02;
			B2=B2+0.02;	
		}
		if(EdepL1>0.04&&EdepL1<0.15) {
			for(int l=0; l<24;l++) if(R>bin[l]&&R<=bin[l+1]){
				RisoluzioniBeta_R_D[l]->Fill(1/Beta);
			}
		}
		for(int m=0; m<18;m++) if(Beta>Betabins[m]&&Beta<=Betabins[m+1]){
			RisoluzioniR_Beta_D[m]->Fill(1/R);
			RisoluzioniM_Beta_D[m]->Fill(1/Massa);
		}
		for(int m=0; m<18;m++) if(BetaRICH>BetabinsNaF[m]&&BetaRICH<=BetabinsNaF[m+1]&&(((int)Cutmask)>>11)==512){
			RisoluzioniR_BetaNaF_D[m]->Fill(1/R);
			RisoluzioniM_BetaNaF_D[m]->Fill(1/Massa);
		}
		for(int m=0; m<18;m++) if(BetaRICH>BetabinsAgl[m]&&BetaRICH<=BetabinsAgl[m+1]&&(((int)Cutmask)>>11)==0){
			RisoluzioniR_BetaAgl_D[m]->Fill(1/R);
			RisoluzioniM_BetaAgl_D[m]->Fill(1/Massa);

		}

	}
	
	for(int j=1; j<31;j++){
		for(int i=1;i<=RisoluzioniL1_D[j-1]->GetNbinsX();i++) { RisoluzioniL1_D[j-1]->SetBinContent(i, RisoluzioniL1_D[j-1]->GetBinContent(i)/ RisoluzioniL1_D[j-1]->GetEntries());
			RisoluzioniL1_D[j-1]->SetBinError(i, RisoluzioniL1_D[j-1]->GetBinError(i)/ RisoluzioniL1_D[j-1]->GetEntries());}			
		for(int i=1;i<=RisoluzioniTOFU_D[j-1]->GetNbinsX();i++){  RisoluzioniTOFU_D[j-1]->SetBinContent(i, RisoluzioniTOFU_D[j-1]->GetBinContent(i)/ RisoluzioniTOFU_D[j-1]->GetEntries());
			RisoluzioniTOFU_D[j-1]->SetBinError(i, RisoluzioniTOFU_D[j-1]->GetBinError(i)/ RisoluzioniTOFU_D[j-1]->GetEntries());}
		for(int L=1;L<=DistribuzioniTOFU_D[j-1]->GetNbinsX();L++) { DistribuzioniTOFU_D[j-1]->SetBinContent(L, DistribuzioniTOFU_D[j-1]->GetBinContent(L)/DistribuzioniTOFU_D[j-1]->GetEntries());
			DistribuzioniTOFU_D[j-1]->SetBinError(L, DistribuzioniTOFU_D[j-1]->GetBinError(L)/DistribuzioniTOFU_D[j-1]->GetEntries());}	
		for(int L=1;L<=DistribuzioniL1_D[j-1]->GetNbinsX();L++) { DistribuzioniL1_D[j-1]->SetBinContent(L, DistribuzioniL1_D[j-1]->GetBinContent(L)/DistribuzioniL1_D[j-1]->GetEntries());
			DistribuzioniL1_D[j-1]->SetBinError(L, DistribuzioniL1_D[j-1]->GetBinError(L)/DistribuzioniL1_D[j-1]->GetEntries());}
		for(int i=1;i<=RisoluzioniTrack_D[j-1]->GetNbinsX();i++) { RisoluzioniTrack_D[j-1]->SetBinContent(i, RisoluzioniTrack_D[j-1]->GetBinContent(i)/ RisoluzioniTrack_D[j-1]->GetEntries());
			RisoluzioniTrack_D[j-1]->SetBinError(i, RisoluzioniTrack_D[j-1]->GetBinError(i)/ RisoluzioniTrack_D[j-1]->GetEntries());}
		for(int L=1;L<=DistribuzioniTrack_D[j-1]->GetNbinsX();L++) { DistribuzioniTrack_D[j-1]->SetBinContent(L, DistribuzioniTrack_D[j-1]->GetBinContent(L)/DistribuzioniTrack_D[j-1]->GetEntries());
			DistribuzioniTrack_D[j-1]->SetBinError(L, DistribuzioniTrack_D[j-1]->GetBinError(L)/DistribuzioniTrack_D[j-1]->GetEntries());}	
		for(int i=1;i<=RisoluzioniTOFD_D[j-1]->GetNbinsX();i++) { RisoluzioniTOFD_D[j-1]->SetBinContent(i, RisoluzioniTOFD_D[j-1]->GetBinContent(i)/ RisoluzioniTOFD_D[j-1]->GetEntries());
			RisoluzioniTOFD_D[j-1]->SetBinError(i, RisoluzioniTOFD_D[j-1]->GetBinError(i)/ RisoluzioniTOFD_D[j-1]->GetEntries());}
		for(int L=1;L<=DistribuzioniTOFD_D[j-1]->GetNbinsX();L++) { DistribuzioniTOFD_D[j-1]->SetBinContent(L, DistribuzioniTOFD_D[j-1]->GetBinContent(L)/DistribuzioniTOFD_D[j-1]->GetEntries());
			DistribuzioniTOFD_D[j-1]->SetBinError(L, DistribuzioniTOFD_D[j-1]->GetBinError(L)/DistribuzioniTOFD_D[j-1]->GetEntries()); }
		if(j<24)
			for(int i=1;i<=RisoluzioniBeta_R_D[j-1]->GetNbinsX();i++) { RisoluzioniBeta_R_D[j-1]->SetBinContent(i, RisoluzioniBeta_R_D[j-1]->GetBinContent(i)/ RisoluzioniBeta_R_D[j-1]->GetEntries());
				RisoluzioniBeta_R_D[j-1]->SetBinError(i, RisoluzioniBeta_R_D[j-1]->GetBinError(i)/ RisoluzioniBeta_R_D[j-1]->GetEntries()); }
		if(j<18)
			for(int i=1;i<=RisoluzioniR_Beta_D[j-1]->GetNbinsX();i++) { RisoluzioniR_Beta_D[j-1]->SetBinContent(i, RisoluzioniR_Beta_D[j-1]->GetBinContent(i)/ RisoluzioniR_Beta_D[j-1]->GetEntries());
				RisoluzioniR_Beta_D[j-1]->SetBinError(i, RisoluzioniR_Beta_D[j-1]->GetBinError(i)/ RisoluzioniR_Beta_D[j-1]->GetEntries());}
		if(j<18)
			for(int i=1;i<=RisoluzioniR_BetaNaF_D[j-1]->GetNbinsX();i++) { RisoluzioniR_BetaNaF_D[j-1]->SetBinContent(i, RisoluzioniR_BetaNaF_D[j-1]->GetBinContent(i)/ RisoluzioniR_BetaNaF_D[j-1]->GetEntries());
				RisoluzioniR_BetaNaF_D[j-1]->SetBinError(i, RisoluzioniR_BetaNaF_D[j-1]->GetBinError(i)/ RisoluzioniR_BetaNaF_D[j-1]->GetEntries()); }
		if(j<18)
			for(int i=1;i<=RisoluzioniR_BetaAgl_D[j-1]->GetNbinsX();i++) { RisoluzioniR_BetaAgl_D[j-1]->SetBinContent(i, RisoluzioniR_BetaAgl_D[j-1]->GetBinContent(i)/ RisoluzioniR_BetaAgl_D[j-1]->GetEntries());
				RisoluzioniR_BetaAgl_D[j-1]->SetBinError(i, RisoluzioniR_BetaAgl_D[j-1]->GetBinError(i)/ RisoluzioniR_BetaAgl_D[j-1]->GetEntries()); }
		if(j<18)
                        for(int i=1;i<=RisoluzioniM_Beta_D[j-1]->GetNbinsX();i++) { RisoluzioniM_Beta_D[j-1]->SetBinContent(i, RisoluzioniM_Beta_D[j-1]->GetBinContent(i)/ RisoluzioniM_Beta_D[j-1]->GetEntries());
                                RisoluzioniM_Beta_D[j-1]->SetBinError(i, RisoluzioniM_Beta_D[j-1]->GetBinError(i)/ RisoluzioniM_Beta_D[j-1]->GetEntries());}
                if(j<18)
                        for(int i=1;i<=RisoluzioniM_BetaNaF_D[j-1]->GetNbinsX();i++) { RisoluzioniM_BetaNaF_D[j-1]->SetBinContent(i, RisoluzioniM_BetaNaF_D[j-1]->GetBinContent(i)/ RisoluzioniM_BetaNaF_D[j-1]->GetEntries());
                                RisoluzioniM_BetaNaF_D[j-1]->SetBinError(i, RisoluzioniM_BetaNaF_D[j-1]->GetBinError(i)/ RisoluzioniM_BetaNaF_D[j-1]->GetEntries()); }
                if(j<18)
                        for(int i=1;i<=RisoluzioniM_BetaAgl_D[j-1]->GetNbinsX();i++) { RisoluzioniM_BetaAgl_D[j-1]->SetBinContent(i, RisoluzioniM_BetaAgl_D[j-1]->GetBinContent(i)/ RisoluzioniM_BetaAgl_D[j-1]->GetEntries());
                                RisoluzioniM_BetaAgl_D[j-1]->SetBinError(i, RisoluzioniM_BetaAgl_D[j-1]->GetBinError(i)/ RisoluzioniM_BetaAgl_D[j-1]->GetEntries()); }

	}
	string Titolo;
	for(int j=1; j<30;j++){
		c->cd(j);
		Titolo="Beta TOF: "+TitoliBetaLin[j-1]+"-"+TitoliBetaLin[j];
		RisoluzioniL1_D[j-1]->SetTitle(Titolo.c_str());
		RisoluzioniL1_D[j-1]->GetXaxis()->SetTitle("Inverse E. dep.");
		RisoluzioniL1_D[j-1]->Draw();
		c_3->cd(j);
		DistribuzioniL1_D[j-1]->SetTitle(Titolo.c_str());
		DistribuzioniL1_D[j-1]->GetXaxis()->SetTitle("E. dep.");
		DistribuzioniL1_D[j-1]->Draw();

		c1->cd(j);
		Titolo="Beta TOF: "+TitoliBetaLin[j-1]+"-"+TitoliBetaLin[j];
                RisoluzioniTOFU_D[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniTOFU_D[j-1]->GetXaxis()->SetTitle("Inverse E. dep.");
		RisoluzioniTOFU_D[j-1]->Draw();
		c3->cd(j);
		DistribuzioniTOFU_D[j-1]->SetTitle(Titolo.c_str());
                DistribuzioniTOFU_D[j-1]->GetXaxis()->SetTitle("E. dep.");
		DistribuzioniTOFU_D[j-1]->Draw();

		c1_bis->cd(j);
		Titolo="Beta TOF: "+TitoliBetaLin[j-1]+"-"+TitoliBetaLin[j];
                RisoluzioniTrack_D[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniTrack_D[j-1]->GetXaxis()->SetTitle("Inverse E. dep.");
		RisoluzioniTrack_D[j-1]->Draw();
		c3_bis->cd(j);
		DistribuzioniTrack_D[j-1]->SetTitle(Titolo.c_str());
                DistribuzioniTrack_D[j-1]->GetXaxis()->SetTitle("E. dep.");
		DistribuzioniTrack_D[j-1]->Draw();

		c1_tris->cd(j);
		Titolo="Beta TOF: "+TitoliBetaLin[j-1]+"-"+TitoliBetaLin[j];
                RisoluzioniTOFD_D[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniTOFD_D[j-1]->GetXaxis()->SetTitle("Inverse E. dep.");
		RisoluzioniTOFD_D[j-1]->Draw();
		c3_tris->cd(j);
		DistribuzioniTOFD_D[j-1]->SetTitle(Titolo.c_str());
                DistribuzioniTOFD_D[j-1]->GetXaxis()->SetTitle("E. dep.");
		DistribuzioniTOFD_D[j-1]->Draw();
	}

	for(int i=0;i<30;i++){
		RisoluzioniL1[i]=new TH1F("","",150,0,20);
		RisoluzioniTOFU[i]=new TH1F("","",150,0,1);
		RisoluzioniTrack[i]=new TH1F("","",150,0,20);
		RisoluzioniTOFD[i]=new TH1F("","",150,0,1);
		DistribuzioniL1[i]=new TH1F("","",150,0,1);
		DistribuzioniTOFU[i]=new TH1F("","",150,0,20);
		DistribuzioniTrack[i]=new TH1F("","",150,0,1);
		DistribuzioniTOFD[i]=new TH1F("","",150,0,20);
		RisoluzioniBeta[i]=new TH1F("","",500,0,4);
		RisoluzioniBetaNaF[i]=new TH1F("","",160,-0.04,0.04);
		RisoluzioniBetaAgl[i]=new TH1F("","",500,-0.02,0.02);
		if(i<24) {
			RisoluzioniR[i]=new TH1F("","",1000,-1,1);
			RisoluzioniBeta_R[i]=new TH1F("","",300,0,4);
		}
		if(i<18) RisoluzioniR_Beta[i]=new TH1F("","",300,0,4);
		if(i<18) RisoluzioniR_BetaNaF[i]=new TH1F("","",200,0.2,4);
		if(i<18) RisoluzioniR_BetaAgl[i]=new TH1F("","",600,0.05,4);
		if(i<18) RisoluzioniM_Beta[i]=new TH1F("","",300,0,4);
                if(i<18) RisoluzioniM_BetaNaF[i]=new TH1F("","",200,0.2,4);
                if(i<18) RisoluzioniM_BetaAgl[i]=new TH1F("","",600,0.05,4);

	}
	cout<<"*************************** MC READING **********************************"<<endl;
	for(int i=0; i<ntupla1->GetEntries();i++) {
		int k = ntupla1->GetEvent(i);
		B1=0.4;
		B2=0.42;
		if(i%100000==0) cout<<i<<endl;
		Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Beta,2)),0.5)/Beta,2)),0.5);
		if((((int)Cutmask)>>11)==512||(((int)Cutmask)>>11)==0) Massa=pow(fabs(pow(fabs(R)*pow((1-pow(BetaRICH,2)),0.5)/BetaRICH,2)),0.5);
		if(Massagen<1){
			for(int j=0; j<30;j++){
				if(Beta>B1&&Beta<=B2){
					if(EdepL1>0){
						RisoluzioniL1[j]->Fill(1/EdepL1);
						DistribuzioniL1[j]->Fill(EdepL1);
					}
					RisoluzioniTOFU[j]->Fill(1/EdepTOFU);
					DistribuzioniTOFU[j]->Fill(EdepTOFU);                
					RisoluzioniTrack[j]->Fill(1/EdepTrack);
					DistribuzioniTrack[j]->Fill(EdepTrack);
					RisoluzioniTOFD[j]->Fill(1/EdepTOFD);
					DistribuzioniTOFD[j]->Fill(EdepTOFD);
				}
				if(Betagen>B1&&Betagen<=B1+(B2-B1)/3){
					RisoluzioniBeta[j]->Fill(1/Beta);
					mean_beta[j]=B1+(B2-B1)/6;

				}
				B1=B1+0.02;
				B2=B2+0.02;	
			}
			for(int l=0; l<23;l++) if(Momentogen>bin[l]&&Momentogen<=bin[l+1]&&Massagen>0.5&&Massagen<1){
				RisoluzioniR[l]->Fill(1/R-1/Momentogen);	}
			for(int l=0; l<24;l++) if(R>bin[l]&&R<=bin[l+1]&&Massagen>0.5&&Massagen<1){
				RisoluzioniBeta_R[l]->Fill(1/Beta);
			}
			for(int m=0; m<18;m++) if(Beta>Betabins[m]&&Beta<=Betabins[m+1]){
				RisoluzioniR_Beta[m]->Fill(1/R);
				RisoluzioniM_Beta[m]->Fill(1/Massa);
			}
			for(int m=0; m<18;m++) if(BetaRICH>BetabinsNaF[m]&&BetaRICH<=BetabinsNaF[m+1]&&(((int)Cutmask)>>11)==512){
				RisoluzioniR_BetaNaF[m]->Fill(1/R);
				RisoluzioniM_BetaNaF[m]->Fill(1/Massa);				
			}
			for(int m=0; m<18;m++) if(BetaRICH>BetabinsAgl[m]&&BetaRICH<=BetabinsAgl[m+1]&&(((int)Cutmask)>>11)==0){
				RisoluzioniR_BetaAgl[m]->Fill(1/R);
				RisoluzioniM_BetaAgl[m]->Fill(1/Massa);
			}

			B1=0.8;
			B2=0.8+0.2/30.;
			for(int j=0; j<30;j++){
				if(Betagen>B1&&Betagen<=B1+(B2-B1)/3&&((int)Cutmask>>11)==512) RisoluzioniBetaNaF[j]->Fill(1/BetaRICH-1/Betagen);
				mean_betaNaF[j]=B1+(B2-B1)/6;
				B1=B1+0.2/30.;
				B2=B2+0.2/30.;	
			}
			B1=0.95;
			B2=0.95+0.05/30.;
			for(int j=0; j<30;j++){
				if(Betagen>B1&&Betagen<=B1+(B2-B1)/3&&((int)Cutmask>>11)==0) RisoluzioniBetaAgl[j]->Fill(1/BetaRICH-1/Betagen);
				mean_betaAgl[j]=B1+(B2-B1)/6;
				B1=B1+0.05/30.;
				B2=B2+0.05/30.;

			}

		}



	}
	for(int j=1; j<31;j++){
		for(int i=1;i<=RisoluzioniTOFU[j-1]->GetNbinsX();i++) { RisoluzioniTOFU[j-1]->SetBinContent(i, RisoluzioniTOFU[j-1]->GetBinContent(i)/ RisoluzioniTOFU[j-1]->GetEntries());
			RisoluzioniTOFU[j-1]->SetBinError(i, RisoluzioniTOFU[j-1]->GetBinError(i)/ RisoluzioniTOFU[j-1]->GetEntries()); }			
		for(int i=1;i<=RisoluzioniL1[j-1]->GetNbinsX();i++) { RisoluzioniL1[j-1]->SetBinContent(i, RisoluzioniL1[j-1]->GetBinContent(i)/ RisoluzioniL1[j-1]->GetEntries());
			RisoluzioniL1[j-1]->SetBinError(i, RisoluzioniL1[j-1]->GetBinError(i)/ RisoluzioniL1[j-1]->GetEntries()); }
		for(int L=1;L<=DistribuzioniTOFU[j-1]->GetNbinsX();L++) { DistribuzioniTOFU[j-1]->SetBinContent(L, DistribuzioniTOFU[j-1]->GetBinContent(L)/DistribuzioniTOFU[j-1]->GetEntries());
			DistribuzioniTOFU[j-1]->SetBinError(L, DistribuzioniTOFU[j-1]->GetBinError(L)/DistribuzioniTOFU[j-1]->GetEntries()); }
		for(int L=1;L<=DistribuzioniL1[j-1]->GetNbinsX();L++) { DistribuzioniL1[j-1]->SetBinContent(L, DistribuzioniL1[j-1]->GetBinContent(L)/DistribuzioniL1[j-1]->GetEntries());
			DistribuzioniL1[j-1]->SetBinError(L, DistribuzioniL1[j-1]->GetBinError(L)/DistribuzioniL1[j-1]->GetEntries()); }
		for(int i=1;i<=RisoluzioniTrack[j-1]->GetNbinsX();i++) { RisoluzioniTrack[j-1]->SetBinContent(i, RisoluzioniTrack[j-1]->GetBinContent(i)/ RisoluzioniTrack[j-1]->GetEntries());
			RisoluzioniTrack[j-1]->SetBinError(i, RisoluzioniTrack[j-1]->GetBinError(i)/ RisoluzioniTrack[j-1]->GetEntries()); }
		for(int L=1;L<=DistribuzioniTrack[j-1]->GetNbinsX();L++) { DistribuzioniTrack[j-1]->SetBinContent(L, DistribuzioniTrack[j-1]->GetBinContent(L)/DistribuzioniTrack[j-1]->GetEntries());
			DistribuzioniTrack[j-1]->SetBinError(L, DistribuzioniTrack[j-1]->GetBinError(L)/DistribuzioniTrack[j-1]->GetEntries());}
		for(int i=1;i<=RisoluzioniTOFD[j-1]->GetNbinsX();i++) { RisoluzioniTOFD[j-1]->SetBinContent(i, RisoluzioniTOFD[j-1]->GetBinContent(i)/ RisoluzioniTOFD[j-1]->GetEntries());
			RisoluzioniTOFD[j-1]->SetBinError(i, RisoluzioniTOFD[j-1]->GetBinError(i)/ RisoluzioniTOFD[j-1]->GetEntries());}
		for(int L=1;L<=DistribuzioniTOFD[j-1]->GetNbinsX();L++) { DistribuzioniTOFD[j-1]->SetBinContent(L, DistribuzioniTOFD[j-1]->GetBinContent(L)/DistribuzioniTOFD[j-1]->GetEntries());
			DistribuzioniTOFD[j-1]->SetBinError(L, DistribuzioniTOFD[j-1]->GetBinError(L)/DistribuzioniTOFD[j-1]->GetEntries());}
		if(j<24)
			for(int i=1;i<=RisoluzioniBeta_R[j-1]->GetNbinsX();i++) { RisoluzioniBeta_R[j-1]->SetBinContent(i, RisoluzioniBeta_R[j-1]->GetBinContent(i)/ RisoluzioniBeta_R[j-1]->GetEntries());
				RisoluzioniBeta_R[j-1]->SetBinError(i, RisoluzioniBeta_R[j-1]->GetBinError(i)/ RisoluzioniBeta_R[j-1]->GetEntries()); }
		if(j<18)
			for(int i=1;i<=RisoluzioniR_Beta[j-1]->GetNbinsX();i++) { RisoluzioniR_Beta[j-1]->SetBinContent(i, RisoluzioniR_Beta[j-1]->GetBinContent(i)/ RisoluzioniR_Beta[j-1]->GetEntries());
				RisoluzioniR_Beta[j-1]->SetBinError(i, RisoluzioniR_Beta[j-1]->GetBinError(i)/ RisoluzioniR_Beta[j-1]->GetEntries());	}
		if(j<18)
			for(int i=1;i<=RisoluzioniR_BetaNaF[j-1]->GetNbinsX();i++) { RisoluzioniR_BetaNaF[j-1]->SetBinContent(i, RisoluzioniR_BetaNaF[j-1]->GetBinContent(i)/ RisoluzioniR_BetaNaF[j-1]->GetEntries());
				RisoluzioniR_BetaNaF[j-1]->SetBinError(i, RisoluzioniR_BetaNaF[j-1]->GetBinError(i)/ RisoluzioniR_BetaNaF[j-1]->GetEntries());	}
		if(j<18)
			for(int i=1;i<=RisoluzioniR_BetaAgl[j-1]->GetNbinsX();i++) { RisoluzioniR_BetaAgl[j-1]->SetBinContent(i, RisoluzioniR_BetaAgl[j-1]->GetBinContent(i)/ RisoluzioniR_BetaAgl[j-1]->GetEntries());
				RisoluzioniR_BetaAgl[j-1]->SetBinError(i, RisoluzioniR_BetaAgl[j-1]->GetBinError(i)/ RisoluzioniR_BetaAgl[j-1]->GetEntries());	}
		if(j<18)
                        for(int i=1;i<=RisoluzioniM_Beta[j-1]->GetNbinsX();i++) { RisoluzioniM_Beta[j-1]->SetBinContent(i, RisoluzioniM_Beta[j-1]->GetBinContent(i)/ RisoluzioniM_Beta[j-1]->GetEntries());
                                RisoluzioniM_Beta[j-1]->SetBinError(i, RisoluzioniM_Beta[j-1]->GetBinError(i)/ RisoluzioniM_Beta[j-1]->GetEntries());   }
                if(j<18)
                        for(int i=1;i<=RisoluzioniM_BetaNaF[j-1]->GetNbinsX();i++) { RisoluzioniM_BetaNaF[j-1]->SetBinContent(i, RisoluzioniM_BetaNaF[j-1]->GetBinContent(i)/ RisoluzioniM_BetaNaF[j-1]->GetEntries());
                                RisoluzioniM_BetaNaF[j-1]->SetBinError(i, RisoluzioniM_BetaNaF[j-1]->GetBinError(i)/ RisoluzioniM_BetaNaF[j-1]->GetEntries());  }
                if(j<18)
                        for(int i=1;i<=RisoluzioniM_BetaAgl[j-1]->GetNbinsX();i++) { RisoluzioniM_BetaAgl[j-1]->SetBinContent(i, RisoluzioniM_BetaAgl[j-1]->GetBinContent(i)/ RisoluzioniM_BetaAgl[j-1]->GetEntries());
                                RisoluzioniM_BetaAgl[j-1]->SetBinError(i, RisoluzioniM_BetaAgl[j-1]->GetBinError(i)/ RisoluzioniM_BetaAgl[j-1]->GetEntries());  }

	}

	///////////////////////BETA vs R /////////////////////////////////////////
	a1->cd();
	BetavsR_TOF_D->GetXaxis()->SetTitle("R [GV]");
	BetavsR_TOF_D->GetYaxis()->SetTitle("Beta TOF");
	BetavsR_TOF_D->Draw("col");
	protons->Draw("same");
	deutons->Draw("same");
	a2->cd();
	BetavsR_NaF_D->GetXaxis()->SetTitle("R [GV]");
	BetavsR_NaF_D->GetYaxis()->SetTitle("Beta RICH NaF");
	BetavsR_NaF_D->Draw("col");
	protons->Draw("same");
	deutons->Draw("same");
	a3->cd();
	BetavsR_Agl_D->GetXaxis()->SetTitle("R [GV]");
	BetavsR_Agl_D->GetYaxis()->SetTitle("Beta RICH Agl");
	BetavsR_Agl_D->Draw("col");
	protons->Draw("same");
	deutons->Draw("same");
	//////////////////////////////////////////////////////////////////////////	
	float PiccoBeta[30]={0};
	float PiccoBetaNaF[30]={0};
	float PiccoBetaAgl[30]={0};
	float PiccoR[30];  
	for(int j=1; j<31;j++){
		c->cd(j);
		//gPad->SetLogy();
		RisoluzioniL1[j-1]->SetLineColor(2);
		RisoluzioniL1[j-1]->Draw("same");
		c_3->cd(j);
		//gPad->SetLogy();
		DistribuzioniL1[j-1]->SetLineColor(2);
		DistribuzioniL1[j-1]->Draw("same");

		c1->cd(j);
		//gPad->SetLogy();
		RisoluzioniTOFU[j-1]->SetLineColor(2);
		RisoluzioniTOFU[j-1]->Draw("same");
		c3->cd(j);
		//gPad->SetLogy();
		DistribuzioniTOFU[j-1]->SetLineColor(2);
		DistribuzioniTOFU[j-1]->Draw("same");

		c1_bis->cd(j);
		//gPad->SetLogy();
		RisoluzioniTrack[j-1]->SetLineColor(2);
		RisoluzioniTrack[j-1]->Draw("same");
		c3_bis->cd(j);
		//gPad->SetLogy();
		DistribuzioniTrack[j-1]->SetLineColor(2);
		DistribuzioniTrack[j-1]->Draw("same");

		c1_tris->cd(j);
		//gPad->SetLogy();
		RisoluzioniTOFD[j-1]->SetLineColor(2);
		RisoluzioniTOFD[j-1]->Draw("same");
		c3_tris->cd(j);
		//gPad->SetLogy();
		DistribuzioniTOFD[j-1]->SetLineColor(2);
		DistribuzioniTOFD[j-1]->Draw("same");

		c7->cd(j);
		//gPad->SetLogy();
		Titolo="Beta Gen: "+TitoliBetaLin[j-1];
                RisoluzioniBeta[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniBeta[j-1]->GetXaxis()->SetTitle("Inverse Measured Beta");
		PiccoBeta[j-1]=RisoluzioniBeta[j-1]->GetBinCenter(RisoluzioniBeta[j-1]->GetMaximumBin());
		RisoluzioniBeta[j-1]->GetXaxis()->SetRangeUser(PiccoBeta[j-1]-0.5,PiccoBeta[j-1]+0.5);	
		RisoluzioniBeta[j-1]->Draw();

		c7_bis->cd(j);
		Titolo="Beta Gen: "+TitoliNaFLin[j-1];
                RisoluzioniBetaNaF[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniBetaNaF[j-1]->GetXaxis()->SetTitle("Inverse Measured Beta");
		PiccoBetaNaF[j-1]=RisoluzioniBetaNaF[j-1]->GetBinCenter(RisoluzioniBetaNaF[j-1]->GetMaximumBin());
		//RisoluzioniBetaNaF[j-1]->GetXaxis()->SetRangeUser(-0.1,0.1);
		RisoluzioniBetaNaF[j-1]->Draw();

		c7_tris->cd(j);
		Titolo="Beta Gen: "+TitoliNaFLin[j-1];
                RisoluzioniBetaAgl[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniBetaAgl[j-1]->GetXaxis()->SetTitle("Inverse Measured Beta");
		PiccoBetaAgl[j-1]=RisoluzioniBetaAgl[j-1]->GetBinCenter(RisoluzioniBetaAgl[j-1]->GetMaximumBin());
		RisoluzioniBetaAgl[j-1]->GetXaxis()->SetRangeUser(PiccoBetaAgl[j-1]-0.05,PiccoBetaAgl[j-1]+0.05);
		RisoluzioniBetaAgl[j-1]->Draw();


	}

	for(int j=1; j<24;j++){
		c9->cd(j);
		//gPad->SetLogy();
		Titolo="R Gen: "+TitoliR[j-1]+"-"+TitoliR[j];
                RisoluzioniR[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniR[j-1]->GetXaxis()->SetTitle("1/R_meas - 1/R_gen");
		PiccoR[j-1]=RisoluzioniR[j-1]->GetBinCenter(RisoluzioniR[j-1]->GetMaximumBin());
		RisoluzioniR[j-1]->GetXaxis()->SetRangeUser(PiccoR[j-1]-RisoluzioniR[j-1]->GetRMS(),PiccoR[j-1]+RisoluzioniR[j-1]->GetRMS());
		RisoluzioniR[j-1]->Draw();
	}
	for(int j=1; j<24;j++){	
		c11->cd(j);
		Titolo="R : "+TitoliR[j-1]+"-"+TitoliR[j];
                RisoluzioniBeta_R[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniBeta_R[j-1]->GetXaxis()->SetTitle("Inverse Measured Beta");
		RisoluzioniBeta_R[j-1]->SetLineColor(2);
		RisoluzioniBeta_R[j-1]->GetXaxis()->SetRangeUser(0.5,1.5);
		if(j<5) RisoluzioniBeta_R[j-1]->GetXaxis()->SetRangeUser(1,2);
		RisoluzioniBeta_R[j-1]->Draw();
		RisoluzioniBeta_R_D[j-1]->Draw("same");
	}
	for(int j=1; j<18;j++){
		c14->cd(j);
		Titolo="Beta TOF: "+TitoliTOF[j-1]+"-"+TitoliTOF[j];
                RisoluzioniR_Beta[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniR_Beta[j-1]->GetXaxis()->SetTitle("Inverse R");
		RisoluzioniR_Beta[j-1]->SetLineColor(2);
		RisoluzioniR_Beta[j-1]->GetXaxis()->SetRangeUser(0,4);
		RisoluzioniR_Beta[j-1]->Draw();
		RisoluzioniR_Beta_D[j-1]->Draw("same");
	}

	for(int j=1; j<18;j++){
		c14_bis->cd(j);
		Titolo="Beta NaF: "+TitoliNaF[j-1]+"-"+TitoliNaF[j];
                RisoluzioniR_BetaNaF[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniR_BetaNaF[j-1]->GetXaxis()->SetTitle("Inverse R");
		RisoluzioniR_BetaNaF[j-1]->SetLineColor(2);
		RisoluzioniR_BetaNaF[j-1]->GetXaxis()->SetRangeUser(0.2,1);
		RisoluzioniR_BetaNaF[j-1]->Draw();
		RisoluzioniR_BetaNaF_D[j-1]->Draw("same");
	}

	for(int j=1; j<18;j++){
		c14_tris->cd(j);
		Titolo="Beta Agl: "+TitoliAgl[j-1]+"-"+TitoliAgl[j];
                RisoluzioniR_BetaAgl[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniR_BetaAgl[j-1]->GetXaxis()->SetTitle("Inverse R");
		RisoluzioniR_BetaAgl[j-1]->SetLineColor(2);
		RisoluzioniR_BetaAgl[j-1]->GetXaxis()->SetRangeUser(0.05,0.5);
		RisoluzioniR_BetaAgl[j-1]->Draw();
		RisoluzioniR_BetaAgl_D[j-1]->Draw("same");
	}
	
	for(int j=1; j<18;j++){
                c17->cd(j);
		Titolo="Beta TOF: "+TitoliTOF[j-1]+"-"+TitoliTOF[j];
                RisoluzioniM_Beta[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniM_Beta[j-1]->GetXaxis()->SetTitle("Inverse Mass");
                RisoluzioniM_Beta[j-1]->SetLineColor(2);
                //RisoluzioniM_Beta[j-1]->GetXaxis()->SetRangeUser(0,4);
                RisoluzioniM_Beta[j-1]->Draw();
                RisoluzioniM_Beta_D[j-1]->Draw("same");
        }

        for(int j=1; j<18;j++){
                c17_bis->cd(j);
		Titolo="Beta NaF: "+TitoliNaF[j-1]+"-"+TitoliNaF[j];
                RisoluzioniM_BetaNaF[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniM_BetaNaF[j-1]->GetXaxis()->SetTitle("Inverse Mass");
                RisoluzioniM_BetaNaF[j-1]->SetLineColor(2);
                //RisoluzioniM_BetaNaF[j-1]->GetXaxis()->SetRangeUser(0.2,1);
                RisoluzioniM_BetaNaF[j-1]->Draw();
                RisoluzioniM_BetaNaF_D[j-1]->Draw("same");
        }

        for(int j=1; j<18;j++){
                c17_tris->cd(j);
		Titolo="Beta Agl: "+TitoliAgl[j-1]+"-"+TitoliAgl[j];
                RisoluzioniM_BetaAgl[j-1]->SetTitle(Titolo.c_str());
                RisoluzioniM_BetaAgl[j-1]->GetXaxis()->SetTitle("Inverse Mass");
                RisoluzioniM_BetaAgl[j-1]->SetLineColor(2);
                //RisoluzioniM_BetaAgl[j-1]->GetXaxis()->SetRangeUser(0.05,0.5);
                RisoluzioniM_BetaAgl[j-1]->Draw();
                RisoluzioniM_BetaAgl_D[j-1]->Draw("same");
        }

	//////////////////GAUSSIAN FITS//////////////////
	TF1 *f1_MC_L1[30];
	TF1 *f1_D_L1[30];
	TF1 *f1_MC_TOFU[30];
	TF1 *f1_D_TOFU[30];
	TF1 *f1_MC_TOFU_inv[30];
	TF1 *f1_D_TOFU_inv[30];
	TF1 *f1_MC_Track[30];
	TF1 *f1_D_Track[30];
	TF1 *f1_MC_Track_inv[30];
	TF1 *f1_D_Track_inv[30];
	TF1 *f1_MC_TOFD[30];
	TF1 *f1_D_TOFD[30];
	TF1 *f1_MC_TOFD_inv[30];
	TF1 *f1_D_TOFD_inv[30];
	TF1 *beta[30];
	TF1 *betaNaF[30];
	TF1 *betaAgl[30];
	TF1 *r[24];
	TF1 *beta_r_MC[24];
	TF1 *beta_r_D[24];	
	TF1 *r_beta_MC[24];
	TF1 *r_beta_D[24];
	TF1 *r_betaNaF_MC[24];
	TF1 *r_betaNaF_D[24];
	TF1 *r_betaAgl_MC[24];
	TF1 *r_betaAgl_D[24];
	TF1 *m_beta_MC[24];
        TF1 *m_beta_D[24];
        TF1 *m_betaNaF_MC[24];
        TF1 *m_betaNaF_D[24];
        TF1 *m_betaAgl_MC[24];
        TF1 *m_betaAgl_D[24];
	string numero[30]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29"};
	string gausMC="gausMC_";
	string gausD="gausD_";
	float mean_L1_MC[30];
	float mean_L1_D[30];
	float mean_TOFU_MC[30];
	float mean_TOFU_D[30];
	float mean_Track_MC[30];
	float mean_Track_D[30];
	float mean_TOFD_MC[30];
	float mean_TOFD_D[30];
	float mean_L1_D_inv[30];
	float mean_TOFU_D_inv[30];
	float mean_Track_D_inv[30];
	float mean_TOFD_D_inv[30];
	float sigma_L1_MC[30];
	float sigma_L1_D[30];
	float sigma_TOFU_MC[30];
	float sigma_TOFU_D[30];
	float sigma_Track_MC[30];
	float sigma_Track_D[30];
	float sigma_TOFD_MC[30];
	float sigma_TOFD_D[30];
	float sigma_L1_MC_err[30];
	float sigma_L1_D_err[30];
	float sigma_TOFU_MC_err[30];
	float sigma_TOFU_D_err[30];
	float sigma_Track_MC_err[30];
	float sigma_Track_D_err[30];
	float sigma_TOFD_MC_err[30];
	float sigma_TOFD_D_err[30];
	double sigma_beta[30]={0};
	double sigma_betaNaF[30]={0};
	double sigma_betaAgl[30]={0};
	double sigma_beta_err[30]={0};
	double mean_beta_err[30]={0};
	double mean_beta_R_D[24]={0};
	double sigma_beta_R_D[24]={0};
	double mean_beta_R_D_err[24]={0};
	double sigma_beta_R_D_err[24]={0};
	double mean_beta_R[24]={0};
	double sigma_beta_R[24]={0};
	double mean_beta_R_err[24]={0};
	double sigma_beta_R_err[24]={0};
	double sigma_R[24]={0};
	double sigma_R_err[24]={0};

	double mean_R_beta_D[18]={0};
	double sigma_R_beta_D[18]={0};
	double mean_R_beta_D_err[18]={0};
	double sigma_R_beta_D_err[18]={0};
	double mean_R_beta[18]={0};
	double sigma_R_beta[18]={0};
	double mean_R_beta_err[18]={0};
	double sigma_R_beta_err[18]={0};
	double mean_R_betaNaF_D[18]={0};
	double sigma_R_betaNaF_D[18]={0};
	double mean_R_betaNaF_D_err[18]={0};
	double sigma_R_betaNaF_D_err[18]={0};
	double mean_R_betaNaF[18]={0};
	double sigma_R_betaNaF[18]={0};
	double mean_R_betaNaF_err[18]={0};
	double sigma_R_betaNaF_err[18]={0};
	double mean_R_betaAgl_D[18]={0};
	double sigma_R_betaAgl_D[18]={0};
	double mean_R_betaAgl_D_err[18]={0};
	double sigma_R_betaAgl_D_err[18]={0};
	double mean_R_betaAgl[18]={0};
	double sigma_R_betaAgl[18]={0};
	double mean_R_betaAgl_err[18]={0};
	double sigma_R_betaAgl_err[18]={0};
	
	double mean_M_beta_D[18]={0};
        double sigma_M_beta_D[18]={0};
        double mean_M_beta_D_err[18]={0};
        double sigma_M_beta_D_err[18]={0};
        double mean_M_beta[18]={0};
        double sigma_M_beta[18]={0};
        double mean_M_beta_err[18]={0};
        double sigma_M_beta_err[18]={0};
        double mean_M_betaNaF_D[18]={0};
        double sigma_M_betaNaF_D[18]={0};
        double mean_M_betaNaF_D_err[18]={0};
        double sigma_M_betaNaF_D_err[18]={0};
        double mean_M_betaNaF[18]={0};
        double sigma_M_betaNaF[18]={0};
        double mean_M_betaNaF_err[18]={0};
        double sigma_M_betaNaF_err[18]={0};
        double mean_M_betaAgl_D[18]={0};
        double sigma_M_betaAgl_D[18]={0};
        double mean_M_betaAgl_D_err[18]={0};
        double sigma_M_betaAgl_D_err[18]={0};
        double mean_M_betaAgl[18]={0};
        double sigma_M_betaAgl[18]={0};
        double mean_M_betaAgl_err[18]={0};
        double sigma_M_betaAgl_err[18]={0};

	string nomefunz;
	TF1 *fitmean;
	float PiccoL1[30];
	float PiccoTOFU[30];
	float PiccoTrack[30];
	float PiccoTOFD[30];
	for(int j=0; j<30;j++) {

		PiccoL1[j]=RisoluzioniL1[j]->GetBinCenter(RisoluzioniL1[j]->GetMaximumBin());
		PiccoTOFU[j]=RisoluzioniTOFU[j]->GetBinCenter(RisoluzioniTOFU[j]->GetMaximumBin());
		PiccoTrack[j]=RisoluzioniTrack[j]->GetBinCenter(RisoluzioniTrack[j]->GetMaximumBin());
		PiccoTOFD[j]=RisoluzioniTOFD[j]->GetBinCenter(RisoluzioniTOFD[j]->GetMaximumBin());

		nomefunz=gausMC+"L1"+numero[j];
		f1_MC_L1[j] = new TF1(nomefunz.c_str(),"gaus",PiccoTrack[j]-2,PiccoTrack[j]+2);
		nomefunz=gausD+"L1"+numero[j];
		f1_D_L1[j] = new TF1(nomefunz.c_str(),"gaus",PiccoTrack[j]-2,PiccoTrack[j]+2);

		nomefunz=gausMC+"TOFU"+numero[j];
		f1_MC_TOFU[j] = new TF1(nomefunz.c_str(),"gaus",PiccoTOFU[j]-0.1,PiccoTOFU[j]+0.1);
		nomefunz=gausD+"TOFU"+numero[j];
		f1_D_TOFU[j] = new TF1(nomefunz.c_str(),"gaus",PiccoTOFU[j]-0.1,PiccoTOFU[j]+0.1);
		nomefunz=gausMC+"TOFU_inv"+numero[j];
		f1_D_TOFU_inv[j] = new TF1(nomefunz.c_str(),"gaus",0,20);

		nomefunz=gausMC+"Track"+numero[j];
		f1_MC_Track[j] = new TF1(nomefunz.c_str(),"gaus",PiccoTrack[j]-2,PiccoTrack[j]+2);
		nomefunz=gausD+"Track"+numero[j];
		f1_D_Track[j] = new TF1(nomefunz.c_str(),"gaus",PiccoTrack[j]-2,PiccoTrack[j]+2);
		nomefunz=gausMC+"Track_inv"+numero[j];
		f1_D_Track_inv[j] = new TF1(nomefunz.c_str(),"gaus",0,20);

		nomefunz=gausMC+"TOFD"+numero[j];
		f1_MC_TOFD[j] = new TF1(nomefunz.c_str(),"gaus",PiccoTOFD[j]-0.1,PiccoTOFD[j]+0.1);
		nomefunz=gausD+"TOFD"+numero[j];
		f1_D_TOFD[j] = new TF1(nomefunz.c_str(),"gaus",PiccoTOFD[j]-0.1,PiccoTOFD[j]+0.1);
		nomefunz=gausMC+"TOFD_inv"+numero[j];
		f1_D_TOFD_inv[j] = new TF1(nomefunz.c_str(),"gaus",0,20);

		f1_D_L1[j]->SetLineColor(4);
		f1_D_TOFU[j]->SetLineColor(4);
		f1_D_Track[j]->SetLineColor(4);
		f1_D_TOFD[j]->SetLineColor(4);

		//L1 Tracker
		nomefunz=gausMC+"L1"+numero[j];
		RisoluzioniL1[j]->Fit(nomefunz.c_str(),"","",PiccoL1[j]-2,PiccoL1[j]+3);
		nomefunz=gausD+"L1"+numero[j];
		RisoluzioniL1_D[j]->Fit(nomefunz.c_str(),"","",PiccoL1[j]-2,PiccoL1[j]+3);
		mean_L1_MC[j]=f1_MC_L1[j]->GetParameter(1);
		mean_L1_D[j]=f1_D_L1[j]->GetParameter(1);
		sigma_L1_MC[j]=f1_MC_L1[j]->GetParameter(2);
		sigma_L1_D[j]=f1_D_L1[j]->GetParameter(2);
		sigma_L1_MC_err[j]=f1_MC_L1[j]->GetParError(2);
		sigma_L1_D_err[j]=f1_D_L1[j]->GetParError(2);
		fitmean = new TF1("fitmean","gaus");
		DistribuzioniL1_D[j]->Fit("fitmean","R","",DistribuzioniL1_D[j]->GetBinCenter(DistribuzioniL1_D[j]->GetMaximumBin())-DistribuzioniL1_D[j]->GetRMS(),DistribuzioniL1_D[j]->GetBinCenter(DistribuzioniL1_D[j]->GetMaximumBin())+DistribuzioniL1_D[j]->GetRMS()/3);
		mean_L1_D_inv[j]=fitmean->GetParameter(1);
		delete fitmean;

		//UPPER TOF
		nomefunz=gausMC+"TOFU"+numero[j];
		RisoluzioniTOFU[j]->Fit(nomefunz.c_str(),"","",PiccoTOFU[j]-0.05,PiccoTOFU[j]+0.1);
		nomefunz=gausD+"TOFU"+numero[j];
		RisoluzioniTOFU_D[j]->Fit(nomefunz.c_str(),"","",PiccoTOFU[j]-0.05,PiccoTOFU[j]+0.1);
		mean_TOFU_MC[j]=f1_MC_TOFU[j]->GetParameter(1);
		mean_TOFU_D[j]=f1_D_TOFU[j]->GetParameter(1);
		sigma_TOFU_MC[j]=f1_MC_TOFU[j]->GetParameter(2);
		sigma_TOFU_D[j]=f1_D_TOFU[j]->GetParameter(2);
		sigma_TOFU_MC_err[j]=f1_MC_TOFU[j]->GetParError(2);
		sigma_TOFU_D_err[j]=f1_D_TOFU[j]->GetParError(2);

		nomefunz=gausMC+"TOFU_inv"+numero[j];
		DistribuzioniTOFU_D[j]->Fit(nomefunz.c_str(),"","",DistribuzioniTOFU_D[j]->GetBinCenter(DistribuzioniTOFU_D[j]->GetMaximumBin())-1,DistribuzioniTOFU_D[j]->GetBinCenter(DistribuzioniTOFU_D[j]->GetMaximumBin())+0.5);
		mean_TOFU_D_inv[j]=f1_D_TOFU_inv[j]->GetParameter(1);

		//Track
		nomefunz=gausMC+"Track"+numero[j];
		RisoluzioniTrack[j]->Fit(nomefunz.c_str(),"","",PiccoTrack[j]-2,PiccoTrack[j]+2);
		nomefunz=gausD+"Track"+numero[j];
		RisoluzioniTrack_D[j]->Fit(nomefunz.c_str(),"","",PiccoTrack[j]-2,PiccoTrack[j]+2);
		mean_Track_MC[j]=f1_MC_Track[j]->GetParameter(1);
		mean_Track_D[j]=f1_D_Track[j]->GetParameter(1);
		sigma_Track_MC[j]=f1_MC_Track[j]->GetParameter(2);
		sigma_Track_D[j]=f1_D_Track[j]->GetParameter(2);
		sigma_Track_MC_err[j]=f1_MC_Track[j]->GetParError(2);
		sigma_Track_D_err[j]=f1_D_Track[j]->GetParError(2);

		nomefunz=gausMC+"Track_inv"+numero[j];
		DistribuzioniTrack_D[j]->Fit(nomefunz.c_str(),"","",DistribuzioniTrack_D[j]->GetBinCenter(DistribuzioniTrack_D[j]->GetMaximumBin())-0.1,DistribuzioniTrack_D[j]->GetBinCenter(DistribuzioniTrack_D[j]->GetMaximumBin())+0.05);
		mean_Track_D_inv[j]=f1_D_Track_inv[j]->GetParameter(1);


		//LOWER TOF
		nomefunz=gausMC+"TOFD"+numero[j];
		RisoluzioniTOFD[j]->Fit(nomefunz.c_str(),"","",PiccoTOFD[j]-0.1,PiccoTOFD[j]+0.1);
		nomefunz=gausD+"TOFD"+numero[j];
		RisoluzioniTOFD_D[j]->Fit(nomefunz.c_str(),"","",PiccoTOFD[j]-0.1,PiccoTOFD[j]+0.1);
		mean_TOFD_MC[j]=f1_MC_TOFD[j]->GetParameter(1);
		mean_TOFD_D[j]=f1_D_TOFD[j]->GetParameter(1);
		sigma_TOFD_MC[j]=f1_MC_TOFD[j]->GetParameter(2);
		sigma_TOFD_D[j]=f1_D_TOFD[j]->GetParameter(2);
		sigma_TOFD_MC_err[j]=f1_MC_TOFD[j]->GetParError(2);
		sigma_TOFD_D_err[j]=f1_D_TOFD[j]->GetParError(2);

		nomefunz=gausMC+"TOFD_inv"+numero[j];
		DistribuzioniTOFD_D[j]->Fit(nomefunz.c_str(),"","",DistribuzioniTOFD_D[j]->GetBinCenter(DistribuzioniTOFD_D[j]->GetMaximumBin())-1,DistribuzioniTOFD_D[j]->GetBinCenter(DistribuzioniTOFD_D[j]->GetMaximumBin())+0.5);
		mean_TOFD_D_inv[j]=f1_D_TOFD_inv[j]->GetParameter(1);


		//Beta TOF
		beta[j]=new TF1("beta","gaus",-20,20);
		beta[j]->SetParameter(0,RisoluzioniBeta[j]->GetBinContent(RisoluzioniBeta[j]->GetMaximumBin()));
		beta[j]->SetParameter(1,RisoluzioniBeta[j]->GetMean());
		beta[j]->SetParameter(2,RisoluzioniBeta[j]->GetRMS());
		if(RisoluzioniBeta[j]->GetEntries()>1000) 
		{
			RisoluzioniBeta[j]->Fit("beta","","",PiccoBeta[j]-0.15,PiccoBeta[j]+0.06);
			sigma_beta[j]=beta[j]->GetParameter(2);
		}
		//Beta NaF
		betaNaF[j]=new TF1("betaNaF","gaus",-20,20);
		betaNaF[j]->SetParameter(0,RisoluzioniBetaNaF[j]->GetBinContent(RisoluzioniBetaNaF[j]->GetMaximumBin()));
		betaNaF[j]->SetParameter(1,RisoluzioniBetaNaF[j]->GetMean());
		betaNaF[j]->SetParameter(2,RisoluzioniBetaNaF[j]->GetRMS());
		if(RisoluzioniBetaNaF[j]->GetEntries()>1000)
		{
			RisoluzioniBetaNaF[j]->Fit("betaNaF","","",PiccoBetaNaF[j]-0.1,PiccoBetaAgl[j]+0.1);
			sigma_betaNaF[j]=betaNaF[j]->GetParameter(2);
		}
		//Beta Agl
		betaAgl[j]=new TF1("betaAgl","gaus",-20,20);
		betaAgl[j]->SetParameter(0,RisoluzioniBetaAgl[j]->GetBinContent(RisoluzioniBetaAgl[j]->GetMaximumBin()));
		betaAgl[j]->SetParameter(1,RisoluzioniBetaAgl[j]->GetMean());
		betaAgl[j]->SetParameter(2,RisoluzioniBetaAgl[j]->GetRMS());
		if(RisoluzioniBetaAgl[j]->GetEntries()>1000)
		{
			RisoluzioniBetaAgl[j]->Fit("betaAgl","","",0-0.005,0+0.005);
			sigma_betaAgl[j]=betaAgl[j]->GetParameter(2);
		}
	}
	float PiccoBeta_R[24];
	float PiccoR_Beta[18];
	float PiccoR_BetaNaF[18];
	float PiccoR_BetaAgl[18];
	float PiccoM_Beta[18];
        float PiccoM_BetaNaF[18];
        float PiccoM_BetaAgl[18];
	for(int j=0; j<24;j++){
		/// RIG Reso
		r[j]=new TF1("rig","gaus",0,20);
		r[j]->SetParameter(0,RisoluzioniR[j]->GetBinContent(RisoluzioniR[j]->GetMaximumBin()));
		r[j]->SetParameter(1,RisoluzioniR[j]->GetMean());
		r[j]->SetParameter(2,RisoluzioniR[j]->GetRMS());
		RisoluzioniR[j]->Fit("rig","","",RisoluzioniR[j]->GetBinCenter(RisoluzioniR[j]->GetMaximumBin())-RisoluzioniR[j]->GetRMS(),RisoluzioniR[j]->GetBinCenter(RisoluzioniR[j]->GetMaximumBin())+RisoluzioniR[j]->GetRMS());
		sigma_R[j]=r[j]->GetParameter(2);


		// BETA Reso (Measured R bins)
		PiccoBeta_R[j]=RisoluzioniBeta_R[j]->GetBinCenter(RisoluzioniBeta_R[j]->GetMaximumBin());
		beta_r_MC[j]=new TF1("betaMC","gaus",0,20);
		beta_r_D[j]=new TF1("betaD","gaus",0,20);
		beta_r_D[j]->SetLineColor(4);
		beta_r_MC[j]->SetParameter(0,RisoluzioniBeta_R[j]->GetBinContent(RisoluzioniBeta_R[j]->GetMaximumBin()));
		beta_r_MC[j]->SetParameter(1,RisoluzioniBeta_R[j]->GetMean());
		beta_r_MC[j]->SetParameter(2,RisoluzioniBeta_R[j]->GetRMS());
		beta_r_D[j]->SetParameter(0,RisoluzioniBeta_R_D[j]->GetBinContent(RisoluzioniBeta_R_D[j]->GetMaximumBin()));
		beta_r_D[j]->SetParameter(1,RisoluzioniBeta_R_D[j]->GetMean());
		beta_r_D[j]->SetParameter(2,RisoluzioniBeta_R_D[j]->GetRMS());
		if(j==0) {
			RisoluzioniBeta_R[j]->Fit("betaMC","","",PiccoBeta_R[j]-0.3,PiccoBeta_R[j]+0.10);
	                RisoluzioniBeta_R_D[j]->Fit("betaD","","",PiccoBeta_R[j]-0.3,PiccoBeta_R[j]+0.10);
		}
		else{
			RisoluzioniBeta_R[j]->Fit("betaMC","","",PiccoBeta_R[j]-0.15,PiccoBeta_R[j]+0.10);
			RisoluzioniBeta_R_D[j]->Fit("betaD","","",PiccoBeta_R[j]-0.15,PiccoBeta_R[j]+0.10);
		}
		mean_beta_R[j]=beta_r_MC[j]->GetParameter(1);
		sigma_beta_R[j]=beta_r_MC[j]->GetParameter(2);
		mean_beta_R_err[j]=beta_r_MC[j]->GetParError(1);
		sigma_beta_R_err[j]=beta_r_MC[j]->GetParError(2);
		mean_beta_R_D[j]=beta_r_D[j]->GetParameter(1);
		sigma_beta_R_D[j]=beta_r_D[j]->GetParameter(2);
		mean_beta_R_D_err[j]=beta_r_D[j]->GetParError(1);
		sigma_beta_R_D_err[j]=beta_r_D[j]->GetParError(2);


		// R Reso (Measured Beta bins)
		if(j<18){
			PiccoR_Beta[j]=RisoluzioniR_Beta[j]->GetBinCenter(RisoluzioniR_Beta[j]->GetMaximumBin());
			r_beta_MC[j]=new TF1("RMC","gaus",0,20);
			r_beta_D[j]=new TF1("RD","gaus",0,20);
			r_beta_D[j]->SetLineColor(4);
			r_beta_MC[j]->SetParameter(0,RisoluzioniR_Beta[j]->GetBinContent(RisoluzioniR_Beta[j]->GetMaximumBin()));
			r_beta_MC[j]->SetParameter(1,RisoluzioniR_Beta[j]->GetMean());
			r_beta_MC[j]->SetParameter(2,RisoluzioniR_Beta[j]->GetRMS());
			r_beta_D[j]->SetParameter(0,RisoluzioniR_Beta_D[j]->GetBinContent(RisoluzioniR_Beta_D[j]->GetMaximumBin()));
			r_beta_D[j]->SetParameter(1,RisoluzioniR_Beta_D[j]->GetMean());
			r_beta_D[j]->SetParameter(2,RisoluzioniR_Beta_D[j]->GetRMS());
			RisoluzioniR_Beta[j]->Fit("RMC","","",PiccoR_Beta[j]-RisoluzioniR_Beta[j]->GetRMS(),PiccoR_Beta[j]+RisoluzioniR_Beta[j]->GetRMS());
			RisoluzioniR_Beta_D[j]->Fit("RD","","",PiccoR_Beta[j]-RisoluzioniR_Beta[j]->GetRMS(),PiccoR_Beta[j]+RisoluzioniR_Beta[j]->GetRMS());
			mean_R_beta[j]=r_beta_MC[j]->GetParameter(1);
			sigma_R_beta[j]=r_beta_MC[j]->GetParameter(2);
			mean_R_beta_err[j]=r_beta_MC[j]->GetParError(1);
			sigma_R_beta_err[j]=r_beta_MC[j]->GetParError(2);
			mean_R_beta_D[j]=r_beta_D[j]->GetParameter(1);
			sigma_R_beta_D[j]=r_beta_D[j]->GetParameter(2);
			mean_R_beta_D_err[j]=r_beta_D[j]->GetParError(1);
			sigma_R_beta_D_err[j]=r_beta_D[j]->GetParError(2);

			PiccoR_BetaNaF[j]=RisoluzioniR_BetaNaF[j]->GetBinCenter(RisoluzioniR_BetaNaF[j]->GetMaximumBin());
			r_betaNaF_MC[j]=new TF1("RMCNaF","gaus",0,20);
			r_betaNaF_D[j]=new TF1("RDNaF","gaus",0,20);
			r_betaNaF_D[j]->SetLineColor(4);
			r_betaNaF_MC[j]->SetParameter(0,RisoluzioniR_BetaNaF[j]->GetBinContent(RisoluzioniR_BetaNaF[j]->GetMaximumBin()));
			r_betaNaF_MC[j]->SetParameter(1,RisoluzioniR_BetaNaF[j]->GetMean());
			r_betaNaF_MC[j]->SetParameter(2,RisoluzioniR_BetaNaF[j]->GetRMS());
			r_betaNaF_D[j]->SetParameter(0,RisoluzioniR_BetaNaF[j]->GetBinContent(RisoluzioniR_BetaNaF[j]->GetMaximumBin()));
			r_betaNaF_D[j]->SetParameter(1,RisoluzioniR_BetaNaF[j]->GetMean());
			r_betaNaF_D[j]->SetParameter(2,RisoluzioniR_BetaNaF[j]->GetRMS());
			RisoluzioniR_BetaNaF[j]->Fit("RMCNaF","","",PiccoR_BetaNaF[j]-RisoluzioniR_BetaNaF[j]->GetRMS(),PiccoR_BetaNaF[j]+RisoluzioniR_BetaNaF[j]->GetRMS());
			RisoluzioniR_BetaNaF_D[j]->Fit("RDNaF","","",PiccoR_BetaNaF[j]-RisoluzioniR_BetaNaF[j]->GetRMS(),PiccoR_BetaNaF[j]+RisoluzioniR_BetaNaF[j]->GetRMS());
			mean_R_betaNaF[j]=r_betaNaF_MC[j]->GetParameter(1);
			sigma_R_betaNaF[j]=r_betaNaF_MC[j]->GetParameter(2);
			mean_R_betaNaF_err[j]=r_betaNaF_MC[j]->GetParError(1);
			sigma_R_betaNaF_err[j]=r_betaNaF_MC[j]->GetParError(2);
			mean_R_betaNaF_D[j]=r_betaNaF_D[j]->GetParameter(1);
			sigma_R_betaNaF_D[j]=r_betaNaF_D[j]->GetParameter(2);
			mean_R_betaNaF_D_err[j]=r_betaNaF_D[j]->GetParError(1);
			sigma_R_betaNaF_D_err[j]=r_betaNaF_D[j]->GetParError(2);

			PiccoR_BetaAgl[j]=RisoluzioniR_BetaAgl[j]->GetBinCenter(RisoluzioniR_BetaAgl[j]->GetMaximumBin());
			r_betaAgl_MC[j]=new TF1("RMCAgl","gaus",0,20);
			r_betaAgl_D[j]=new TF1("RDAgl","gaus",0,20);
			r_betaAgl_D[j]->SetLineColor(4);
			r_betaAgl_MC[j]->SetParameter(0,RisoluzioniR_BetaAgl[j]->GetBinContent(RisoluzioniR_BetaAgl[j]->GetMaximumBin()));
			r_betaAgl_MC[j]->SetParameter(1,RisoluzioniR_BetaAgl[j]->GetMean());
			r_betaAgl_MC[j]->SetParameter(2,RisoluzioniR_BetaAgl[j]->GetRMS());
			r_betaAgl_D[j]->SetParameter(0,RisoluzioniR_BetaAgl[j]->GetBinContent(RisoluzioniR_BetaAgl[j]->GetMaximumBin()));
			r_betaAgl_D[j]->SetParameter(1,RisoluzioniR_BetaAgl[j]->GetMean());
			r_betaAgl_D[j]->SetParameter(2,RisoluzioniR_BetaAgl[j]->GetRMS());
			RisoluzioniR_BetaAgl[j]->Fit("RMCAgl","","",PiccoR_BetaAgl[j]-RisoluzioniR_BetaAgl[j]->GetRMS(),PiccoR_BetaAgl[j]+RisoluzioniR_BetaAgl[j]->GetRMS());
			RisoluzioniR_BetaAgl_D[j]->Fit("RDAgl","","",PiccoR_BetaAgl[j]-RisoluzioniR_BetaAgl[j]->GetRMS(),PiccoR_BetaAgl[j]+RisoluzioniR_BetaAgl[j]->GetRMS());
			mean_R_betaAgl[j]=r_betaAgl_MC[j]->GetParameter(1);
			sigma_R_betaAgl[j]=r_betaAgl_MC[j]->GetParameter(2);
			mean_R_betaAgl_err[j]=r_betaAgl_MC[j]->GetParError(1);
			sigma_R_betaAgl_err[j]=r_betaAgl_MC[j]->GetParError(2);
			mean_R_betaAgl_D[j]=r_betaAgl_D[j]->GetParameter(1);
			sigma_R_betaAgl_D[j]=r_betaAgl_D[j]->GetParameter(2);
			mean_R_betaAgl_D_err[j]=r_betaAgl_D[j]->GetParError(1);
			sigma_R_betaAgl_D_err[j]=r_betaAgl_D[j]->GetParError(2);
		}
		 if(j<18){
                        PiccoM_Beta[j]=RisoluzioniM_Beta[j]->GetBinCenter(RisoluzioniM_Beta[j]->GetMaximumBin());
                        m_beta_MC[j]=new TF1("MMC","gaus",0,20);
                        m_beta_D[j]=new TF1("MD","gaus",0,20);
                        m_beta_D[j]->SetLineColor(4);
                        m_beta_MC[j]->SetParameter(0,RisoluzioniM_Beta[j]->GetBinContent(RisoluzioniM_Beta[j]->GetMaximumBin()));
                        m_beta_MC[j]->SetParameter(1,RisoluzioniM_Beta[j]->GetMean());
                        m_beta_MC[j]->SetParameter(2,RisoluzioniM_Beta[j]->GetRMS());
                        m_beta_D[j]->SetParameter(0,RisoluzioniM_Beta_D[j]->GetBinContent(RisoluzioniM_Beta_D[j]->GetMaximumBin()));
                        m_beta_D[j]->SetParameter(1,RisoluzioniM_Beta_D[j]->GetMean());
                        m_beta_D[j]->SetParameter(2,RisoluzioniM_Beta_D[j]->GetRMS());
                        RisoluzioniM_Beta[j]->Fit("MMC","","",PiccoM_Beta[j]-RisoluzioniM_Beta[j]->GetRMS(),PiccoM_Beta[j]+RisoluzioniM_Beta[j]->GetRMS());
                        RisoluzioniM_Beta_D[j]->Fit("MD","","",PiccoM_Beta[j]-RisoluzioniM_Beta[j]->GetRMS(),PiccoM_Beta[j]+RisoluzioniM_Beta[j]->GetRMS());
                        mean_M_beta[j]=m_beta_MC[j]->GetParameter(1);
                        sigma_M_beta[j]=m_beta_MC[j]->GetParameter(2);
                        mean_M_beta_err[j]=m_beta_MC[j]->GetParError(1);
                        sigma_M_beta_err[j]=m_beta_MC[j]->GetParError(2);
                        mean_M_beta_D[j]=m_beta_D[j]->GetParameter(1);
                        sigma_M_beta_D[j]=m_beta_D[j]->GetParameter(2);
                        mean_M_beta_D_err[j]=m_beta_D[j]->GetParError(1);
                        sigma_M_beta_D_err[j]=m_beta_D[j]->GetParError(2);
			
			PiccoM_BetaNaF[j]=RisoluzioniM_BetaNaF[j]->GetBinCenter(RisoluzioniM_BetaNaF[j]->GetMaximumBin());
                        m_betaNaF_MC[j]=new TF1("MMCNaF","gaus",0,20);
                        m_betaNaF_D[j]=new TF1("MDNaF","gaus",0,20);
                        m_betaNaF_D[j]->SetLineColor(4);
                        m_betaNaF_MC[j]->SetParameter(0,RisoluzioniM_BetaNaF[j]->GetBinContent(RisoluzioniM_BetaNaF[j]->GetMaximumBin()));
                        m_betaNaF_MC[j]->SetParameter(1,RisoluzioniM_BetaNaF[j]->GetMean());
                        m_betaNaF_MC[j]->SetParameter(2,RisoluzioniM_BetaNaF[j]->GetRMS());
                        m_betaNaF_D[j]->SetParameter(0,RisoluzioniM_BetaNaF[j]->GetBinContent(RisoluzioniM_BetaNaF[j]->GetMaximumBin()));
                        m_betaNaF_D[j]->SetParameter(1,RisoluzioniM_BetaNaF[j]->GetMean());
                        m_betaNaF_D[j]->SetParameter(2,RisoluzioniM_BetaNaF[j]->GetRMS());
                        RisoluzioniM_BetaNaF[j]->Fit("MMCNaF","","",PiccoM_BetaNaF[j]-RisoluzioniM_BetaNaF[j]->GetRMS(),PiccoM_BetaNaF[j]+RisoluzioniM_BetaNaF[j]->GetRMS());
                        RisoluzioniM_BetaNaF_D[j]->Fit("MDNaF","","",PiccoM_BetaNaF[j]-RisoluzioniM_BetaNaF[j]->GetRMS(),PiccoM_BetaNaF[j]+RisoluzioniM_BetaNaF[j]->GetRMS());
                        mean_M_betaNaF[j]=m_betaNaF_MC[j]->GetParameter(1);
                        sigma_M_betaNaF[j]=m_betaNaF_MC[j]->GetParameter(2);
                        mean_M_betaNaF_err[j]=m_betaNaF_MC[j]->GetParError(1);
                        sigma_M_betaNaF_err[j]=m_betaNaF_MC[j]->GetParError(2);
                        mean_M_betaNaF_D[j]=m_betaNaF_D[j]->GetParameter(1);
                        sigma_M_betaNaF_D[j]=m_betaNaF_D[j]->GetParameter(2);
                        mean_M_betaNaF_D_err[j]=m_betaNaF_D[j]->GetParError(1);
                        sigma_M_betaNaF_D_err[j]=m_betaNaF_D[j]->GetParError(2);

                        PiccoM_BetaAgl[j]=RisoluzioniM_BetaAgl[j]->GetBinCenter(RisoluzioniM_BetaAgl[j]->GetMaximumBin());
                        m_betaAgl_MC[j]=new TF1("MMCAgl","gaus",0,20);
                        m_betaAgl_D[j]=new TF1("MDAgl","gaus",0,20);
                        m_betaAgl_D[j]->SetLineColor(4);
                        m_betaAgl_MC[j]->SetParameter(0,RisoluzioniM_BetaAgl[j]->GetBinContent(RisoluzioniM_BetaAgl[j]->GetMaximumBin()));
                        m_betaAgl_MC[j]->SetParameter(1,RisoluzioniM_BetaAgl[j]->GetMean());
                        m_betaAgl_MC[j]->SetParameter(2,RisoluzioniM_BetaAgl[j]->GetRMS());
                        m_betaAgl_D[j]->SetParameter(0,RisoluzioniM_BetaAgl[j]->GetBinContent(RisoluzioniM_BetaAgl[j]->GetMaximumBin()));
                        m_betaAgl_D[j]->SetParameter(1,RisoluzioniM_BetaAgl[j]->GetMean());
                        m_betaAgl_D[j]->SetParameter(2,RisoluzioniM_BetaAgl[j]->GetRMS());
                        RisoluzioniM_BetaAgl[j]->Fit("MMCAgl","","",PiccoM_BetaAgl[j]-RisoluzioniM_BetaAgl[j]->GetRMS(),PiccoM_BetaAgl[j]+RisoluzioniM_BetaAgl[j]->GetRMS());
                        RisoluzioniM_BetaAgl_D[j]->Fit("MDAgl","","",PiccoM_BetaAgl[j]-RisoluzioniM_BetaAgl[j]->GetRMS(),PiccoM_BetaAgl[j]+RisoluzioniM_BetaAgl[j]->GetRMS());
                        mean_M_betaAgl[j]=m_betaAgl_MC[j]->GetParameter(1);
                        sigma_M_betaAgl[j]=m_betaAgl_MC[j]->GetParameter(2);
                        mean_M_betaAgl_err[j]=m_betaAgl_MC[j]->GetParError(1);
                        sigma_M_betaAgl_err[j]=m_betaAgl_MC[j]->GetParError(2);
                        mean_M_betaAgl_D[j]=m_betaAgl_D[j]->GetParameter(1);
                        sigma_M_betaAgl_D[j]=m_betaAgl_D[j]->GetParameter(2);
                        mean_M_betaAgl_D_err[j]=m_betaAgl_D[j]->GetParError(1);
                        sigma_M_betaAgl_D_err[j]=m_betaAgl_D[j]->GetParError(2);
                }

	}

	///////////////////////////////////////////////
	/////////////// E. Dep. vs Beta ///////////////

	TGraph *EvsBetaL1=new TGraph();
	TGraph *EvsBetaTOFU=new TGraph();
	TGraph *EvsBetaTrack=new TGraph();
	TGraph *EvsBetaTOFD=new TGraph();

	for(int j=0; j<30;j++) {
		EvsBetaL1->SetPoint(j,betacent[j],mean_L1_D_inv[j]);
		EvsBetaTOFU->SetPoint(j,betacent[j],mean_TOFU_D_inv[j]);
		EvsBetaTrack->SetPoint(j,betacent[j],mean_Track_D_inv[j]);
		EvsBetaTOFD->SetPoint(j,betacent[j],mean_TOFD_D_inv[j]);
	}
	c_2->cd();
	h->Draw("col");
	EvsBetaL1->SetLineWidth(2);
        EvsBetaL1->SetLineColor(2);
	EvsBetaL1->Draw("sameC");
	c2->cd();
	EvsBetaTOFU->SetLineWidth(2);
	EvsBetaTOFU->SetLineColor(2);
	h1->Draw("col");
	EvsBetaTOFU->Draw("sameC");
	c2_bis->cd();
	EvsBetaTrack->SetLineWidth(2);
	EvsBetaTrack->SetLineColor(2);
	h2->Draw("col");
	EvsBetaTrack->Draw("sameC");
	c2_tris->cd();
	EvsBetaTOFD->SetLineWidth(2);
	EvsBetaTOFD->SetLineColor(2);
	h3->Draw("col");
	EvsBetaTOFD->Draw("sameC");
	////////////////////////////////////////////////

	////////////// CORREZIONE E.DEP.////////////////
	double CorrezioneL1[30];
	double CorrezioneTOFU[30];
	double CorrezioneTrack[30];
	double CorrezioneTOFD[30];
	TGraphErrors *diffL1=new TGraphErrors();
	TGraphErrors *diffTOFU=new TGraphErrors();
	TGraphErrors *diffTrack=new TGraphErrors();
	TGraphErrors *diffTOFD=new TGraphErrors();

	for(int j=0; j<30;j++) {
		CorrezioneL1[j]=1/(mean_L1_D[j]/mean_L1_MC[j]);
		diffL1->SetPoint(j,betacent[j],CorrezioneL1[j]);
		CorrezioneTOFU[j]=1/(mean_TOFU_D[j]/mean_TOFU_MC[j]);
		diffTOFU->SetPoint(j,betacent[j],CorrezioneTOFU[j]);
		CorrezioneTrack[j]=1/(mean_Track_D[j]/mean_Track_MC[j]);
		diffTrack->SetPoint(j,betacent[j],CorrezioneTrack[j]);
		CorrezioneTOFD[j]=1/(mean_TOFD_D[j]/mean_TOFD_MC[j]);
		diffTOFD->SetPoint(j,betacent[j],CorrezioneTOFD[j]);
	}
	diffL1->SetLineWidth(2);
	diffL1->SetLineColor(3);
	diffTOFU->SetLineWidth(2);
	diffTOFU->SetLineColor(2);
	diffTrack->SetLineWidth(2);
	diffTrack->SetLineColor(4);
	diffTOFD->SetLineWidth(2);
	diffTOFD->SetLineColor(6);
	diffL1->SetMarkerColor(3);
	diffTOFU->SetMarkerColor(2);
	diffTrack->SetMarkerColor(4);
	diffTOFD->SetMarkerColor(6);
	c4->cd();
	c4->SetGridx();
	c4->SetGridy();
	diffTOFU->GetXaxis()->SetRangeUser(0,1);
	diffTOFU->GetYaxis()->SetRangeUser(0.5,1.6);
	diffL1->SetTitle("L1 Tracker");
	diffTOFU->SetTitle("MC/Data Correction");
	diffTrack->SetTitle("Inner Tracker");
	diffTOFD->SetTitle("Lower TOF");
	diffTOFU->SetMarkerStyle(8);
	diffL1->SetMarkerStyle(8);
	diffTrack->SetMarkerStyle(8);
	diffTOFD->SetMarkerStyle(8);
	diffTOFU->SetLineStyle(2);
        diffL1->SetLineStyle(2);
        diffTrack->SetLineStyle(2);
        diffTOFD->SetLineStyle(2);
	diffTOFU->GetXaxis()->SetTitle("Beta TOF");
	diffTOFU->GetYaxis()->SetTitle("Inverse E. dep. (MC/Data)");
	diffTOFU->Draw("APC");
	diffL1->Draw("PCsame");
	diffTrack->Draw("PCsame");
	diffTOFD->Draw("PCsame");

	TSpline3 *CorrTOFU= new TSpline3("Cubic Spline",betacent,CorrezioneTOFU,30);
	TSpline3 *CorrTrack= new TSpline3("Cubic Spline",betacent,CorrezioneTrack,30);
	TSpline3 *CorrTOFD= new TSpline3("Cubic Spline",betacent,CorrezioneTOFD,30);

	for(int i=0;i<30;i++){
		DistribuzioniTOFU_corr[i]=new TH1F("","",150,0,20);
		DistribuzioniTrack_corr[i]=new TH1F("","",150,0,1);
		DistribuzioniTOFD_corr[i]=new TH1F("","",150,0,20);
	}

	for(int i=0; i<ntupla1->GetEntries();i++) {
		int k = ntupla1->GetEvent(i);
		B1=0.4;
		B2=0.42;
		if(i%100000==0) cout<<i<<endl;
		for(int j=0; j<30;j++){
			if(Beta>B1&&Beta<=B2&&Massagen>0.5&&Massagen<1){
				DistribuzioniTOFU_corr[j]->Fill(EdepTOFU*CorrTOFU->Eval(Beta));
				DistribuzioniTrack_corr[j]->Fill(EdepTrack*CorrTrack->Eval(Beta));
				DistribuzioniTOFD_corr[j]->Fill(EdepTOFD*CorrTOFD->Eval(Beta));
			}
			B1=B1+0.02;
			B2=B2+0.02;
		}

	}

	for(int j=1; j<31;j++){
		for(int L=1;L<=DistribuzioniTOFU_corr[j-1]->GetNbinsX();L++) DistribuzioniTOFU_corr[j-1]->SetBinContent(L, DistribuzioniTOFU_corr[j-1]->GetBinContent(L)/DistribuzioniTOFU_corr[j-1]->GetEntries());
		for(int L=1;L<=DistribuzioniTrack_corr[j-1]->GetNbinsX();L++) DistribuzioniTrack_corr[j-1]->SetBinContent(L, DistribuzioniTrack_corr[j-1]->GetBinContent(L)/DistribuzioniTrack_corr[j-1]->GetEntries());
		for(int L=1;L<=DistribuzioniTOFD_corr[j-1]->GetNbinsX();L++) DistribuzioniTOFD_corr[j-1]->SetBinContent(L, DistribuzioniTOFD_corr[j-1]->GetBinContent(L)/DistribuzioniTOFD_corr[j-1]->GetEntries());
	}

	for(int j=1; j<31;j++){
		c5->cd(j);
		//gPad->SetLogy();
		DistribuzioniTOFU_D[j-1]->Draw();
		DistribuzioniTOFU_corr[j-1]->SetLineColor(2);
		DistribuzioniTOFU_corr[j-1]->Draw("same");
		c5_bis->cd(j);
		//gPad->SetLogy();
		DistribuzioniTrack_D[j-1]->Draw();
		DistribuzioniTrack_corr[j-1]->SetLineColor(2);
		DistribuzioniTrack_corr[j-1]->Draw("same");
		c5_tris->cd(j);
		//gPad->SetLogy();
		DistribuzioniTOFD_D[j-1]->Draw();
		DistribuzioniTOFD_corr[j-1]->SetLineColor(2);
		DistribuzioniTOFD_corr[j-1]->Draw("same");
	}

	/////////////////////////////////////////////
	/////////////// BETA DATA VS MC /////////////
	TGraphErrors *diffBetaR=new TGraphErrors();
	double CorrezioneBetaR[24];
	for(int j=0; j<24;j++) {
		CorrezioneBetaR[j]=(mean_beta_R[j]/mean_beta_R_D[j]);
		diffBetaR->SetPoint(j,valorecent[j],CorrezioneBetaR[j]);
		diffBetaR->SetPointError(j,0,pow(pow(mean_beta_R_err[j]/CorrezioneBetaR[j],2)+pow(mean_beta_R_D_err[j]/CorrezioneBetaR[j],2),0.5)*CorrezioneBetaR[j]);
	}
	c12->cd();
	gPad->SetLogx();
	gPad->SetGridy();
	gPad->SetGridx();
	diffBetaR->GetXaxis()->SetRangeUser(0.1,100);
	diffBetaR->GetYaxis()->SetRangeUser(0.5,1.6);
	diffBetaR->SetTitle("Beta Peak (MC/Data)");
	diffBetaR->GetYaxis()->SetTitle("Beta Peak (MC/Data)");
	diffBetaR->GetXaxis()->SetTitle("R [GV]");
	diffBetaR->SetLineWidth(2);
	diffBetaR->SetMarkerStyle(8);
	diffBetaR->Draw("APL");
	/////////////////////////////////////////////
	//////////////// R DATA VS MC ///////////////
	TGraphErrors *diffRBeta=new TGraphErrors();
	double CorrezioneRBeta[18];
	for(int j=0; j<18;j++) {
		CorrezioneRBeta[j]=(mean_R_beta[j]/mean_R_beta_D[j]);
		diffRBeta->SetPoint(j,Betacent[j],CorrezioneRBeta[j]);
		diffRBeta->SetPointError(j,0,pow(pow(mean_R_beta_err[j]/CorrezioneRBeta[j],2)+pow(mean_R_beta_D_err[j]/CorrezioneRBeta[j],2),0.5)*CorrezioneRBeta[j]);
	}
	c15->cd(1);
	gPad->SetGridy();
	gPad->SetGridx();
	diffRBeta->GetXaxis()->SetRangeUser(0.1,1);
	diffRBeta->GetYaxis()->SetRangeUser(0.5,1.6);
	diffRBeta->SetTitle("R Peak (MC/Data)");
	diffRBeta->GetYaxis()->SetTitle("R Peak (MC/Data)");
	diffRBeta->GetXaxis()->SetTitle("Beta TOF");
	diffRBeta->SetLineWidth(2);
	diffRBeta->SetMarkerStyle(8);
	diffRBeta->Draw("APL");

	TGraphErrors *diffRBetaNaF=new TGraphErrors();
	double CorrezioneRBetaNaF[18];
	for(int j=0; j<18;j++) {
		CorrezioneRBetaNaF[j]=(mean_R_betaNaF[j]/mean_R_betaNaF_D[j]);
		diffRBetaNaF->SetPoint(j,BetacentNaF[j],CorrezioneRBetaNaF[j]);
		diffRBetaNaF->SetPointError(j,0,pow(pow(mean_R_betaNaF_err[j]/CorrezioneRBetaNaF[j],2)+pow(mean_R_betaNaF_D_err[j]/CorrezioneRBetaNaF[j],2),0.5)*CorrezioneRBetaNaF[j]);
	}
	c15->cd(2);
	gPad->SetGridy();
	gPad->SetGridx();
	diffRBetaNaF->GetXaxis()->SetRangeUser(0.8,1);
	diffRBetaNaF->GetYaxis()->SetRangeUser(0.5,1.6);
	diffRBetaNaF->SetTitle("R Peak (MC/Data)");
	diffRBetaNaF->GetYaxis()->SetTitle("R Peak (MC/Data)");
	diffRBetaNaF->GetXaxis()->SetTitle("Beta RICH NaF");
	diffRBetaNaF->SetLineWidth(2);
	diffRBetaNaF->SetMarkerStyle(8);
	diffRBetaNaF->Draw("APL");

	TGraphErrors *diffRBetaAgl=new TGraphErrors();
	double CorrezioneRBetaAgl[18];
	for(int j=0; j<18;j++) {
		CorrezioneRBetaAgl[j]=(mean_R_betaAgl[j]/mean_R_betaAgl_D[j]);
		diffRBetaAgl->SetPoint(j,BetacentAgl[j],CorrezioneRBetaAgl[j]);
		diffRBetaAgl->SetPointError(j,0,pow(pow(mean_R_betaAgl_err[j]/CorrezioneRBetaAgl[j],2)+pow(mean_R_betaAgl_D_err[j]/CorrezioneRBetaAgl[j],2),0.5)*CorrezioneRBetaAgl[j]);
	}
	c15->cd(3);
	gPad->SetGridy();
	gPad->SetGridx();
	diffRBetaAgl->GetXaxis()->SetRangeUser(0.95,1);
	diffRBetaAgl->GetYaxis()->SetRangeUser(0.5,1.6);
	diffRBetaAgl->SetTitle("R Peak (MC/Data)");
	diffRBetaAgl->GetYaxis()->SetTitle("R Peak (MC/Data)");
	diffRBetaAgl->GetXaxis()->SetTitle("Beta RICH Agl");
	diffRBetaAgl->SetLineWidth(2);
	diffRBetaAgl->SetMarkerStyle(8);
	diffRBetaAgl->Draw("APL");
	/////////////////////////////////////////////
	////////////// SIGMAS ///////////////////////
	cout<<"******************************* SIGMAS *********************************************"<<endl;
	TGraphErrors *SigmaL1=new TGraphErrors();
        TGraphErrors *SigmaL1_D=new TGraphErrors();
	TGraphErrors *SigmaTOFU=new TGraphErrors();
	TGraphErrors *SigmaTrack=new TGraphErrors();
	TGraphErrors *SigmaTOFD=new TGraphErrors();
	TGraphErrors *SigmaTOFU_D=new TGraphErrors();
	TGraphErrors *SigmaTrack_D=new TGraphErrors();
	TGraphErrors *SigmaTOFD_D=new TGraphErrors();
	TGraphErrors *SigmaBeta=new TGraphErrors();
	TGraphErrors *SigmaBetaNaF=new TGraphErrors();
	TGraphErrors *SigmaBetaAgl=new TGraphErrors();
	TGraphErrors *SigmaR=new TGraphErrors();
	TGraphErrors *SigmaInvBeta=new TGraphErrors();
	TGraphErrors *SigmaInvBetaNaF=new TGraphErrors();
	TGraphErrors *SigmaInvBetaAgl=new TGraphErrors();
	TGraphErrors *SigmaInvR=new TGraphErrors();
	TGraphErrors *ResoBeta=new TGraphErrors();
	TGraphErrors *ResoBetaNaF=new TGraphErrors();
	TGraphErrors *ResoBetaAgl=new TGraphErrors();
	TGraphErrors *ResoR=new TGraphErrors();
	TGraphErrors *SigmaBeta_R=new TGraphErrors();
	TGraphErrors *SigmaBeta_R_D=new TGraphErrors();
	TGraphErrors *SigmaR_Beta=new TGraphErrors();
	TGraphErrors *SigmaR_Beta_D=new TGraphErrors();	
	TGraphErrors *SigmaR_BetaNaF=new TGraphErrors();
	TGraphErrors *SigmaR_BetaNaF_D=new TGraphErrors();
	TGraphErrors *SigmaR_BetaAgl=new TGraphErrors();
	TGraphErrors *SigmaR_BetaAgl_D=new TGraphErrors();
	TGraphErrors *SigmaM_Beta=new TGraphErrors();
        TGraphErrors *SigmaM_Beta_D=new TGraphErrors();
	TGraphErrors *SigmaM_BetaNaF=new TGraphErrors();
        TGraphErrors *SigmaM_BetaNaF_D=new TGraphErrors();
        TGraphErrors *SigmaM_BetaAgl=new TGraphErrors();
        TGraphErrors *SigmaM_BetaAgl_D=new TGraphErrors();
	
	int p=0;
	for(int j=0; j<30;j++) {
		SigmaL1->SetPoint(j,betacent[j],sigma_L1_MC[j]);
                SigmaL1->SetPointError(j,0,sigma_L1_MC_err[j]);
		SigmaTOFU->SetPoint(j,betacent[j],sigma_TOFU_MC[j]);
		SigmaTOFU->SetPointError(j,0,sigma_TOFU_MC_err[j]);
		SigmaTrack->SetPoint(j,betacent[j],sigma_Track_MC[j]);
		SigmaTrack->SetPointError(j,0,sigma_Track_MC_err[j]);
		SigmaTOFD->SetPoint(j,betacent[j],sigma_TOFD_MC[j]);
		SigmaTOFD->SetPointError(j,0,sigma_TOFD_MC_err[j]);
		SigmaL1_D->SetPoint(j,betacent[j],sigma_L1_D[j]);
                SigmaL1_D->SetPointError(j,0,sigma_L1_D_err[j]);
		SigmaTOFU_D->SetPoint(j,betacent[j],sigma_TOFU_D[j]);
		SigmaTOFU_D->SetPointError(j,0,sigma_TOFU_D_err[j]);
		SigmaTrack_D->SetPoint(j,betacent[j],sigma_Track_D[j]);
		SigmaTrack_D->SetPointError(j,0,sigma_Track_D_err[j]);
		SigmaTOFD_D->SetPoint(j,betacent[j],sigma_TOFD_D[j]);
		SigmaTOFD_D->SetPointError(j,0,sigma_TOFD_D_err[j]);
		if(sigma_beta[j]!=0){
			SigmaBeta->SetPoint(p,1/PiccoBeta[j],pow(1/PiccoBeta[j],2)*sigma_beta[j]); 
			cout<<1/PiccoBeta[j]<<" "<<sigma_beta[j]<<" "<<p<<endl;	
			SigmaInvBeta->SetPoint(p,1/PiccoBeta[j],sigma_beta[j]);
			ResoBeta->SetPoint(p,1/PiccoBeta[j],pow(1/PiccoBeta[j],1)*sigma_beta[j]);
			p++;}
		
		SigmaBetaNaF->SetPoint(j,mean_betaNaF[j],pow(mean_beta[j],2)*sigma_betaNaF[j]);
		SigmaBetaAgl->SetPoint(j,mean_betaAgl[j],pow(mean_beta[j],2)*sigma_betaAgl[j]);
		SigmaInvBetaNaF->SetPoint(j,mean_betaNaF[j],sigma_betaNaF[j]);
		SigmaInvBetaAgl->SetPoint(j,mean_betaAgl[j],sigma_betaAgl[j]);
		ResoBetaNaF->SetPoint(j,mean_betaNaF[j],pow(mean_beta[j],1)*sigma_betaNaF[j]);
		ResoBetaAgl->SetPoint(j,mean_betaAgl[j],pow(mean_beta[j],1)*sigma_betaAgl[j]);
		if(j<24) {
			SigmaBeta_R->SetPoint(j,valorecent[j],sigma_beta_R[j]/sigma_beta_R[j]);
			SigmaBeta_R->SetPointError(j,0,sigma_beta_R_err[j]/sigma_beta_R[j]);
			SigmaBeta_R_D->SetPoint(j,valorecent[j],sigma_beta_R_D[j]/sigma_beta_R[j]);
			SigmaBeta_R_D->SetPointError(j,0,sigma_beta_R_D_err[j]/sigma_beta_R[j]);
		}
		if(j<17) {
			SigmaR_Beta->SetPoint(j,Betacent[j],sigma_R_beta[j]);
			SigmaR_Beta->SetPointError(j,0,sigma_R_beta_err[j]);
			SigmaR_Beta_D->SetPoint(j,Betacent[j],sigma_R_beta_D[j]);
			SigmaR_Beta_D->SetPointError(j,0,sigma_R_beta_D_err[j]);

			SigmaR_BetaNaF->SetPoint(j,BetacentNaF[j],sigma_R_betaNaF[j]);
			SigmaR_BetaNaF->SetPointError(j,0,sigma_R_betaNaF_err[j]);
			SigmaR_BetaNaF_D->SetPoint(j,BetacentNaF[j],sigma_R_betaNaF_D[j]);
			SigmaR_BetaNaF_D->SetPointError(j,0,sigma_R_betaNaF_D_err[j]);

			SigmaR_BetaAgl->SetPoint(j,BetacentAgl[j],sigma_R_betaAgl[j]);
			SigmaR_BetaAgl->SetPointError(j,0,sigma_R_betaAgl_err[j]);
			SigmaR_BetaAgl_D->SetPoint(j,BetacentAgl[j],sigma_R_betaAgl_D[j]);
			SigmaR_BetaAgl_D->SetPointError(j,0,sigma_R_betaAgl_D_err[j]);
			
			SigmaM_Beta->SetPoint(j,Ekincent[j],sigma_M_beta[j]);
                        SigmaM_Beta->SetPointError(j,0,sigma_M_beta_err[j]);
                        SigmaM_Beta_D->SetPoint(j,Ekincent[j],sigma_M_beta_D[j]);
                        SigmaM_Beta_D->SetPointError(j,0,sigma_M_beta_D_err[j]);
		
			SigmaM_BetaNaF->SetPoint(j,EkincentNaF[j],sigma_M_betaNaF[j]);
                        SigmaM_BetaNaF->SetPointError(j,0,sigma_M_betaNaF_err[j]);
                        SigmaM_BetaNaF_D->SetPoint(j,EkincentNaF[j],sigma_M_betaNaF_D[j]);
                        SigmaM_BetaNaF_D->SetPointError(j,0,sigma_M_betaNaF_D_err[j]);

                        SigmaM_BetaAgl->SetPoint(j,EkincentAgl[j],sigma_M_betaAgl[j]);
                        SigmaM_BetaAgl->SetPointError(j,0,sigma_M_betaAgl_err[j]);
                        SigmaM_BetaAgl_D->SetPoint(j,EkincentAgl[j],sigma_M_betaAgl_D[j]);
                        SigmaM_BetaAgl_D->SetPointError(j,0,sigma_M_betaAgl_D_err[j]);
		}
		SigmaM_BetaAgl->SetPoint(19,0,0);
	}
	for(int j=0; j<24;j++) if(sigma_R[j]!=0) SigmaInvR->SetPoint(j,valorecent[j],sigma_R[j]);
	for(int j=0; j<24;j++) if(sigma_R[j]!=0) SigmaR->SetPoint(j,valorecent[j],pow(valorecent[j],2)*sigma_R[j]);
	for(int j=0; j<24;j++) if(sigma_R[j]!=0) ResoR->SetPoint(j,valorecent[j],pow(valorecent[j],1)*sigma_R[j]);
	double PiccoBeta_Inv[30]={0};
	for(int j=0; j<30;j++) if(PiccoBeta[j]>=0.2) PiccoBeta_Inv[j]=1/PiccoBeta[j]; else PiccoBeta_Inv[j]=j/100.; 
	TSpline3 *SigmaBeta_spl= new TSpline3("Cubic Spline",PiccoBeta_Inv,sigma_beta,30);
	
	c_6->cd();
        c_6->SetGridx();
        c_6->SetGridy();
        SigmaL1->SetMarkerStyle(8);
        SigmaL1_D->SetMarkerStyle(8);
        SigmaL1->SetMarkerColor(2);
        SigmaL1->SetLineColor(2);
        SigmaL1_D->SetMarkerColor(4);
        SigmaL1_D->SetLineColor(4);
        SigmaL1->SetLineWidth(2);
        SigmaL1_D->SetLineWidth(2);
        SigmaL1_D->Draw("AP");
        SigmaL1_D->GetXaxis()->SetTitle("Beta TOF");
        SigmaL1_D->GetYaxis()->SetTitle("Sigma Inverse E. dep. (Layer 1 Tr.)");
        SigmaL1_D->GetXaxis()->SetTitleSize(0.045);
        SigmaL1_D->GetYaxis()->SetTitleSize(0.045);
        SigmaL1->Draw("sameP");	

	c6->cd();
	c6->SetGridx();
	c6->SetGridy();
	SigmaTOFU->SetMarkerStyle(8);
	SigmaTOFU_D->SetMarkerStyle(8);
	SigmaTOFU->SetMarkerColor(2);
	SigmaTOFU->SetLineColor(2);
	SigmaTOFU_D->SetMarkerColor(4);
        SigmaTOFU_D->SetLineColor(4);
	SigmaTOFU->SetLineWidth(2);
	SigmaTOFU_D->SetLineWidth(2);
	SigmaTOFU_D->Draw("AP");
	SigmaTOFU_D->GetXaxis()->SetTitle("Beta TOF");
	SigmaTOFU_D->GetYaxis()->SetTitle("Sigma Inverse E. dep. (Upper TOF)");
	SigmaTOFU_D->GetXaxis()->SetTitleSize(0.045);
        SigmaTOFU_D->GetYaxis()->SetTitleSize(0.045);
	SigmaTOFU->Draw("sameP");

	c6_bis->cd();
	c6_bis->SetGridx();
	c6_bis->SetGridy();
	SigmaTrack->SetMarkerStyle(8);
	SigmaTrack_D->SetMarkerStyle(8);
	SigmaTrack->SetMarkerColor(2);
	SigmaTrack->SetLineColor(2);
	SigmaTrack_D->SetMarkerColor(4);
        SigmaTrack_D->SetLineColor(4);
	SigmaTrack->SetLineWidth(2);
	SigmaTrack_D->SetLineWidth(2);
	SigmaTrack_D->GetXaxis()->SetTitle("Beta TOF");
        SigmaTrack_D->GetYaxis()->SetTitle("Sigma Inverse E. dep. (Inner Tracker)");
        SigmaTrack_D->GetXaxis()->SetTitleSize(0.045);
        SigmaTrack_D->GetYaxis()->SetTitleSize(0.045);
	SigmaTrack_D->Draw("AP");
	SigmaTrack->Draw("sameP");

	c6_tris->cd();
	c6_tris->SetGridx();
	c6_tris->SetGridy();
	SigmaTOFD->SetMarkerStyle(8);
	SigmaTOFD_D->SetMarkerStyle(8);
	SigmaTOFD->SetMarkerColor(2);
	SigmaTOFD->SetLineColor(2);
	SigmaTOFD_D->SetMarkerColor(4);
        SigmaTOFD_D->SetLineColor(4);
	SigmaTOFD->SetLineWidth(2);
	SigmaTOFD_D->SetLineWidth(2);
	SigmaTOFD_D->GetXaxis()->SetTitle("Beta TOF");
        SigmaTOFD_D->GetYaxis()->SetTitle("Sigma Inverse E. dep. (Lower TOF)");
        SigmaTOFD_D->GetXaxis()->SetTitleSize(0.045);
        SigmaTOFD_D->GetYaxis()->SetTitleSize(0.045);
	SigmaTOFD_D->Draw("AP");
	SigmaTOFD->Draw("sameP");

	c13->cd();
	c13->SetGridx();
	c13->SetGridy();
	c13->SetLogx();
	SigmaBeta_R->SetMarkerStyle(8);
	SigmaBeta_R_D->SetMarkerStyle(8);
	SigmaBeta_R->SetMarkerColor(2);
	SigmaBeta_R->SetLineColor(2);
	SigmaBeta_R->SetLineWidth(2);
	SigmaBeta_R_D->SetLineWidth(2);
	SigmaBeta_R_D->SetTitle("Sigma Inverse Beta (Data/MC)");
	SigmaBeta_R->SetTitle("Sigma Inverse Beta (MC)");
	SigmaBeta_R_D->GetXaxis()->SetTitle("R [GV]");
	SigmaBeta_R_D->GetYaxis()->SetTitle("Sigma Inverse Beta (Data/MC)");
	SigmaBeta_R_D->Draw("AP");
	SigmaBeta_R->Draw("sameP");

	c16->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaR_Beta->SetMarkerStyle(8);
	SigmaR_Beta_D->SetMarkerStyle(8);
	SigmaR_Beta->SetMarkerColor(2);
	SigmaR_Beta->SetLineColor(2);
	SigmaR_Beta->SetLineWidth(2);
	SigmaR_Beta_D->SetLineWidth(2);
	SigmaR_Beta_D->SetTitle("Sigma Inverse R (DATA)");
	SigmaR_Beta->SetTitle("Sigma Inverse R (MC)");
	SigmaR_Beta_D->GetXaxis()->SetTitle("Beta TOF");
	SigmaR_Beta_D->GetYaxis()->SetTitle("Sigma Inverse R [1/GV]");
	SigmaR_Beta_D->Draw("AP");
	SigmaR_Beta->Draw("sameP");
	c16->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaR_BetaNaF->SetMarkerStyle(8);
	SigmaR_BetaNaF_D->SetMarkerStyle(8);
	SigmaR_BetaNaF->SetMarkerColor(2);
	SigmaR_BetaNaF->SetLineColor(2);
	SigmaR_BetaNaF->SetLineWidth(2);
	SigmaR_BetaNaF_D->SetLineWidth(2);
	SigmaR_BetaNaF_D->SetTitle("Sigma Inverse R (DATA)");
	SigmaR_BetaNaF->SetTitle("Sigma Inverse R (MC)");
	SigmaR_BetaNaF_D->GetXaxis()->SetTitle("Beta RICH NaF");
	SigmaR_BetaNaF_D->GetYaxis()->SetTitle("Sigma Inverse R [1/GV]");
	SigmaR_BetaNaF_D->Draw("AP");
	SigmaR_BetaNaF->Draw("sameP");
	c16->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaR_BetaAgl->SetMarkerStyle(8);
	SigmaR_BetaAgl_D->SetMarkerStyle(8);
	SigmaR_BetaAgl->SetMarkerColor(2);
	SigmaR_BetaAgl->SetLineColor(2);
	SigmaR_BetaAgl->SetLineWidth(2);
	SigmaR_BetaAgl_D->SetLineWidth(2);
	SigmaR_BetaAgl_D->SetTitle("Sigma Inverse R (DATA)");
	SigmaR_BetaAgl->SetTitle("Sigma Inverse R (MC)");
	SigmaR_BetaAgl_D->GetXaxis()->SetTitle("Beta RICH Agl");
	SigmaR_BetaAgl_D->GetYaxis()->SetTitle("Sigma Inverse R [1/GV]");
	SigmaR_BetaAgl_D->Draw("AP");
	SigmaR_BetaAgl->Draw("sameP");

	c18->cd();
        gPad->SetGridx();
        gPad->SetGridy();
        gPad->SetLogx();
	SigmaM_Beta->SetMarkerStyle(8);
        SigmaM_Beta_D->SetMarkerStyle(4);
        SigmaM_Beta->SetMarkerColor(2);
        SigmaM_Beta->SetLineColor(2);
	SigmaM_Beta_D->SetMarkerColor(2);
        SigmaM_Beta_D->SetLineColor(2);
        SigmaM_Beta->SetLineWidth(2);
        SigmaM_Beta_D->SetLineWidth(2);
        SigmaM_BetaNaF->SetMarkerStyle(8);
        SigmaM_BetaNaF_D->SetMarkerStyle(4);
        SigmaM_BetaNaF->SetMarkerColor(3);
        SigmaM_BetaNaF->SetLineColor(3);
        SigmaM_BetaNaF_D->SetMarkerColor(3);
        SigmaM_BetaNaF_D->SetLineColor(3);
        SigmaM_BetaNaF->SetLineWidth(2);
        SigmaM_BetaNaF_D->SetLineWidth(2);
	SigmaM_BetaAgl->SetMarkerStyle(8);
        SigmaM_BetaAgl_D->SetMarkerStyle(4);
        SigmaM_BetaAgl->SetMarkerColor(4);
        SigmaM_BetaAgl->SetLineColor(4);
        SigmaM_BetaAgl_D->SetMarkerColor(4);
        SigmaM_BetaAgl_D->SetLineColor(4);
        SigmaM_BetaAgl->SetLineWidth(2);
        SigmaM_BetaAgl_D->SetLineWidth(2);
	SigmaM_Beta_D->SetTitle("Inverse Mass Resolution (DATA)");
        SigmaM_Beta->SetTitle("Inverse Mass Resolution (MC)");
        SigmaM_Beta_D->GetXaxis()->SetTitle("Kin. En. / nucl.");
	SigmaM_BetaAgl->GetXaxis()->SetRangeUser(0.05,10);
        SigmaM_Beta_D->GetYaxis()->SetTitle("Inverse Mass Resolution");
        SigmaM_BetaAgl->Draw("AP");
        SigmaM_Beta->Draw("sameP");
	SigmaM_BetaNaF_D->Draw("sameP");
        SigmaM_BetaNaF->Draw("sameP");
	SigmaM_BetaAgl_D->Draw("sameP");
        SigmaM_Beta_D->Draw("sameP");

	c8->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaInvBeta->SetLineColor(2);
	SigmaInvBeta->SetLineWidth(2);
	SigmaInvBeta->SetMarkerStyle(8);
	SigmaInvBeta->SetTitle("Sigma Inverse Beta TOF");
	SigmaInvBeta->Draw("AP");
	SigmaInvBeta->GetXaxis()->SetRangeUser(0.4,1.05);
	SigmaInvBeta->GetXaxis()->SetTitle("Beta TOF");
	SigmaBeta_spl->Draw("same");
	c8->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaBeta->SetLineColor(2);
	SigmaBeta->SetLineWidth(2);
	SigmaBeta->SetMarkerStyle(8);
	SigmaBeta->SetTitle("Sigma Beta TOF");
	SigmaBeta->GetXaxis()->SetTitle("Beta TOF");
	SigmaBeta->Draw("AP");
	SigmaBeta->GetXaxis()->SetRangeUser(0.4,1.05);
	c8->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	ResoBeta->SetLineColor(2);
	ResoBeta->SetLineWidth(2);
	ResoBeta->SetMarkerStyle(8);
	ResoBeta->SetTitle("Beta TOF Resolution");
	ResoBeta->GetXaxis()->SetTitle("Beta TOF");
	ResoBeta->Draw("AP");
	ResoBeta->GetXaxis()->SetRangeUser(0.4,1.05);	

	c8_bis->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaInvBetaNaF->SetLineColor(2);
	SigmaInvBetaNaF->SetLineWidth(2);
	SigmaInvBetaNaF->SetMarkerStyle(8);
	SigmaInvBetaNaF->GetXaxis()->SetRangeUser(0.8,1.05);
	SigmaInvBetaNaF->SetTitle("Sigma Inverse Beta RICH NaF");
	SigmaInvBetaNaF->GetXaxis()->SetTitle("Beta RICH (NaF)");
	SigmaInvBetaNaF->Draw("AP");
	c8_bis->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaBetaNaF->SetLineColor(2);
	SigmaBetaNaF->SetLineWidth(2);
	SigmaBetaNaF->SetMarkerStyle(8);
	SigmaBetaNaF->GetXaxis()->SetRangeUser(0.8,1.05);
	SigmaBetaNaF->SetTitle("Sigma Beta RICH NaF");
	SigmaBetaNaF->GetXaxis()->SetTitle("Beta RICH (NaF)");
	SigmaBetaNaF->Draw("AP");
	c8_bis->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	ResoBetaNaF->SetLineColor(2);
	ResoBetaNaF->SetLineWidth(2);
	ResoBetaNaF->SetMarkerStyle(8);
	ResoBetaNaF->GetXaxis()->SetRangeUser(0.8,1.05);
	ResoBetaNaF->SetTitle("Beta RICH NaF Resolution");
	ResoBetaNaF->GetXaxis()->SetTitle("Beta RICH (NaF)");
	ResoBetaNaF->Draw("AP");

	c8_tris->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaInvBetaAgl->SetLineColor(2);
	SigmaInvBetaAgl->SetLineWidth(2);
	SigmaInvBetaAgl->SetMarkerStyle(8);
	SigmaInvBetaAgl->GetXaxis()->SetRangeUser(0.94,1.01);
	SigmaInvBetaAgl->GetYaxis()->SetRangeUser(0.0002,0.002);
	SigmaInvBetaAgl->SetTitle("Sigma Inverse Beta RICH Agl");
	SigmaInvBetaAgl->GetXaxis()->SetTitle("Beta RICH (Agl)");
	SigmaInvBetaAgl->Draw("AP");
	c8_tris->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	SigmaBetaAgl->SetLineColor(2);
	SigmaBetaAgl->SetLineWidth(2);
	SigmaBetaAgl->SetMarkerStyle(8);
	SigmaBetaAgl->GetXaxis()->SetRangeUser(0.94,1.01);
	SigmaBetaAgl->SetTitle("Sigma Beta RICH Agl");
	SigmaBetaAgl->GetXaxis()->SetTitle("Beta RICH (Agl)");
	SigmaBetaAgl->Draw("AP");
	c8_tris->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	ResoBetaAgl->SetLineColor(2);
	ResoBetaAgl->SetLineWidth(2);
	ResoBetaAgl->SetMarkerStyle(8);
	ResoBetaAgl->GetXaxis()->SetRangeUser(0.94,1.01);
	ResoBetaAgl->SetTitle("Beta RICH Agl Resolution");
	ResoBetaAgl->GetXaxis()->SetTitle("Beta RICH (Agl)");
	ResoBetaAgl->Draw("AP");	

	c10->cd(1);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogx();
	SigmaInvR->SetLineColor(2);
	SigmaInvR->SetLineWidth(2);
	SigmaInvR->SetMarkerStyle(8);
	SigmaInvR->SetTitle("Sigma Inverse Rig. (Inner Tracker)");
	SigmaInvR->GetXaxis()->SetTitle("R [GV]");
	SigmaInvR->Draw("AP");
	c10->cd(2);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogx();
	gPad->SetLogy();
	SigmaR->SetLineColor(2);
	SigmaR->SetLineWidth(2);
	SigmaR->SetMarkerStyle(8);
	SigmaR->SetTitle("Sigma Rig. (Inner Tracker)");
	SigmaR->GetXaxis()->SetTitle("R [GV]");
	SigmaR->Draw("AP");
	c10->cd(3);
	gPad->SetGridx();
	gPad->SetGridy();
	gPad->SetLogx();
	ResoR->SetLineColor(2);
	ResoR->SetLineWidth(2);
	ResoR->SetMarkerStyle(8);
	ResoR->SetTitle("Rig. Resolution (Inner Tracker)");
	ResoR->GetXaxis()->SetTitle("R [GV]");
	ResoR->Draw("AP");
	/////////////////////////////////////////////
	/////// SPLINES
	double Beta_cent[30]; for (int j=0;j<30;j++) Beta_cent[j]=betacent[j];
        double Picco_Beta[30];for (int j=0;j<30;j++) Picco_Beta[j]=PiccoBeta_Inv[j];
        double betacent[30]; for (int j=0;j<30;j++) betacent[j]=mean_beta[j];
	double sigmaEL1Uinv[30]; for (int j=0;j<30;j++) sigmaEL1Uinv[j]=sigma_L1_MC[j];
        double sigmaEtofUinv[30]; for (int j=0;j<30;j++) sigmaEtofUinv[j]=sigma_TOFU_MC[j];
        double sigmaEtrackinv[30]; for (int j=0;j<30;j++) sigmaEtrackinv[j]=sigma_Track_MC[j];
        double sigmaETofDinv[30]; for (int j=0;j<30;j++) sigmaETofDinv[j]=sigma_TOFD_MC[j];
        double sigmabetainv[30]; for (int j=0;j<30;j++) sigmabetainv[j]=sigma_beta[j];
        double sigmaRinv[24];for (int j=0;j<24;j++) sigmaRinv[j]=sigma_R[j];
	double EL1[30]; for (int j=0;j<30;j++) EL1[j]=mean_L1_D_inv[j];
        double ETOFU[30]; for (int j=0;j<30;j++) ETOFU[j]=mean_TOFU_D_inv[j];
        double ETrack[30];for (int j=0;j<30;j++) ETrack[j]=mean_Track_D_inv[j];
        double ETOFD[30]; for (int j=0;j<30;j++) ETOFD[j]=mean_TOFD_D_inv[j];
        double CorrL1[30];for (int j=0;j<30;j++) CorrL1[j]=CorrezioneL1[j];
        double corr_TOFU[30];for (int j=0;j<30;j++) corr_TOFU[j]=CorrezioneTOFU[j];
        double corr_Track[30]; for (int j=0;j<30;j++) corr_Track[j]=CorrezioneTrack[j];
        double corr_TOFD[30];for (int j=0;j<30;j++) corr_TOFD[j]=CorrezioneTOFD[j];

	//TF1 *protons = new TF1("protons","pow((pow(x,2)/pow(0.938,2)/(1 + pow(x,2)/pow(0.938,2))),0.5)",0.1,100);
        //TF1 *deutons = new TF1(\"deutons","pow((pow(x,2)/pow(1.875,2)/(1 + pow(x,2)/pow(1.875,2))),0.5)",0.1,100);

	TSpline3 *Rig = new TSpline3("Rig",valorecent,sigmaRinv,23);
        TSpline3 *Beta = new TSpline3("beta",Picco_Beta,sigmabetainv,30);
        TSpline3 *eL1 = new TSpline3("eL1",Beta_cent,sigmaEL1Uinv,30);
        TSpline3 *etofu = new TSpline3("etofu",Beta_cent,sigmaEtofUinv,30);
        TSpline3 *etrack = new TSpline3("etrack",Beta_cent,sigmaEtrackinv,30);
        TSpline3 *etofd = new TSpline3("etofd",Beta_cent,sigmaETofDinv,30);
        TSpline3 *EdepL1beta = new TSpline3("EdepL1beta",Beta_cent,EL1,30);
        TSpline3 *EdepTOFbeta = new TSpline3("EdepTOFbeta",Beta_cent,ETOFU,30);
        TSpline3 *EdepTrackbeta = new TSpline3("EdepTrackbeta",Beta_cent,ETrack,30);
        TSpline3 *EdepTOFDbeta = new TSpline3("EdepTOFDbeta",Beta_cent,ETOFD,30);
        TSpline3 *Corr_L1 = new TSpline3("Corr_L1",Beta_cent,CorrL1,30);
        TSpline3 *Corr_TOFU = new TSpline3("Corr_TOFU",Beta_cent,corr_TOFU,30);
        TSpline3 *Corr_Track = new TSpline3("Corr_Track",Beta_cent,corr_Track,30);
        TSpline3 *Corr_TOFD = new TSpline3("Corr_TOFD",Beta_cent,corr_TOFD,30);

	///////////////
	////////////// OUTPUT ///////////////////////
	string nomefile="/home/AMS/fdimicco/fdimicco/CodesforAnalysis/CALIBRAZIONI/"+mese+".root";
	TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
	f_out->mkdir("Beta vs R");
	f_out->mkdir("Tracker L1");
	f_out->mkdir("Upper TOF");
	f_out->mkdir("Inner Tracker");
	f_out->mkdir("Lower TOF");
	f_out->mkdir("R & Beta");
	f_out->mkdir("Inverse Mass");
	f_out->mkdir("Fit Results");
	f_out->mkdir("Fit Results/Beta_R_DataMCTest");
	f_out->mkdir("Fit Results/Splines");
	f_out->cd("Beta vs R");
	a1->Write();
	a2->Write();
	a3->Write();
	f_out->cd("Tracker L1");	
	c->Write();
	c_2->Write();
	c_3->Write();
	f_out->cd("Upper TOF");
	c1->Write();
	c2->Write();	
	c3->Write();
	f_out->cd("Inner Tracker");
	c1_bis->Write();
	c2_bis->Write();
	c3_bis->Write();
	f_out->cd("Lower TOF");	
	c1_tris->Write();
	c3_tris->Write();
	c2_tris->Write();
	f_out->cd("R & Beta");
	c7->Write();
	c7_bis->Write();
	c7_tris->Write();
	c9->Write();
	c11->Write();
	c14->Write();
	c14_bis->Write();
	c14_tris->Write();
	f_out->cd("Inverse Mass");
	c17->Write();
        c17_bis->Write();
        c17_tris->Write();
	f_out->cd("Fit Results");
	c4->Write();
	c5->Write();
	c5_bis->Write();
	c5_tris->Write();
	c_6->Write();
	c6->Write();
	c6_bis->Write();
	c6_tris->Write();
	c8->Write();
	c8_bis->Write();
	c8_tris->Write();
	c10->Write();
	c18->Write();
	f_out->cd("Fit Results/Beta_R_DataMCTest");
	c12->Write();
	c13->Write();
	c15->Write();
	c16->Write();
	f_out->cd("Fit Results/Splines");
	Rig->Write("Rig");
        Beta->Write("beta");
        eL1->Write("eL1");
        etofu->Write("etofu");
        etrack ->Write("etrack");
        etofd->Write("etofd");
        EdepL1beta->Write("EdepL1beta");
        EdepTOFbeta->Write("EdepTOFbeta");
        EdepTrackbeta->Write("EdepTrackbeta");
        EdepTOFDbeta->Write("EdepTOFDbeta");
        Corr_L1->Write("Corr_L1");
        Corr_TOFU->Write("Corr_TOFU");
        Corr_Track->Write("Corr_Track");
        Corr_TOFD->Write("Corr_TOFD");

	f_out->Write();
	f_out->Close();
	/////////////////////////////////////////////
	//////////////// SCRITTURA SU FILE //////////
	nomefile="/home/AMS/fdimicco/fdimicco/CALIBRAZIONI/Functions_"+mese+".h";
	ofstream f(nomefile.c_str());
	f<<"#include \"TFile.h\""<<endl;
	f<<"#include \"TTree.h\""<<endl;
	f<<"#include \"TH1.h\""<<endl;
	f<<"#include \"TH2.h\""<<endl;
	f<<"#include \"TH3.h\""<<endl;
	f<<"#include \"TF2.h\""<<endl;
	f<<"#include <TVector3.h>"<<endl;
	f<<"#include <fstream>"<<endl;
	f<<"#include <sstream>"<<endl;
	f<<"#include <math.h>"<<endl;
	f<<"#include <cstring>"<<endl;
	f<<"#include <vector>"<<endl;
	f<<"#include \"TMath.h\""<<endl;
	f<<"#include <stdio.h>"<<endl;
	f<<"#include <iostream>"<<endl;
	f<<"#include <stdlib.h>"<<endl;
	f<<"#include <stdio.h>"<<endl;
	f<<"#include <stdarg.h>"<<endl;
	f<<endl;
	f<<"////////////// VALORI CENTRALI BINS //////////////////"<<endl;
	f<<"double Beta_cent[30]={";
	for (int j=0;j<30;j++) f<<betacent[j]<<",";
	f<<"};"<<endl;
	f<<"double PiccoBeta[30]={";
        for (int j=0;j<30;j++) f<<PiccoBeta_Inv[j]<<",";
        f<<"};"<<endl;
	f<<"double betacent[30]={";
	for (int j=0;j<30;j++) f<<mean_beta[j]<<",";
	f<<"};"<<endl;
	f<<"double valorecent[24]={";
	for (int j=0;j<24;j++) f<<valorecent[j]<<",";
	f<<"};"<<endl;
	f<<"///////////////////////////////////////////////////////"<<endl;
	f<<endl;

	f<<"////////////////// CORREZIONE R Mis:Gen //////////////////////"<<endl;
	f<<"double R_gen[34]={0.5633,       0.6490, 0.8449, 1.0408, 1.1755, 1.3347, 1.5306, 1.7510, 1.9469, 2.1551, 2.3510, 2.5347, 2.7551, 2.9878, 3.2204, 3.5143, 3.7347, 3.9429, 4.1755, 4.4204, 4.6653, 4.9469, 5.1918, 5.5224, 5.7918, 6.0122, 7.0000, 8.0000, 9.0000, 10.0000,        11.0000,        20.0000,        50.0000,        100.0000};"<<endl;

	f<<"double R_mis[34]={0.7306,       1.0000, 1.3367, 1.6902, 1.9764, 2.1279, 2.2626, 2.3805, 2.4310, 2.5320, 2.7172, 2.8182, 3.0034, 3.1886, 3.3232, 3.5926, 3.8114, 4.0303, 4.2660, 4.4680, 4.6532, 4.9226, 5.1414, 5.4613, 5.7643, 6.0337, 7.0000, 8.0000, 9.0000, 10.0000,        11.0000,        20.0000,        50.0000,        100.0000};"<<endl;
	f<<"//////////////////////////////////////////////////////////////"<<endl;

	f<<"////////////////// CORREZIONE RICH //////////////////////"<<endl;
	f<<"double R_rich[25]={3.18055,     3.57491,        4.01817,        4.51638,        5.07637,        5.70579,        6.41325,        7.20844,        8.10221,        9.10681,        10.236,         11.5051,        12.9317,        14.5351,        16.3373,        18.3629,        20.6398,        23.1989,        26.0753,        29.3084,        32.9424,        37.0269,        41.6179,        46.7781,        52.5781};"<<endl;

	f<<"double Corr_rich[25]={1.00213,  1.00045,        1.00006,        0.99960,        0.99930,        0.99921,        0.99903,        0.99895,        0.99894,        0.99888,        0.99890,        0.99887,        0.99885,        0.99882,        0.99887,        0.99883,        0.99881,        0.99883,        0.99886,        0.99885,        0.99880,        0.99888,        0.99884,        0.99883,        0.99888};"<<endl;
	f<<"//////////////////////////////////////////////////////////////"<<endl;

	f<<"////////////// SIGMA INVERSE //////////////////"<<endl;

	f<<"double sigmaEL1Uinv[30]={";
        for (int j=0;j<30;j++) f<<sigma_L1_MC[j]<<",";
        f<<"};"<<endl;
	f<<"double sigmaEtofUinv[30]={";
	for (int j=0;j<30;j++) f<<sigma_TOFU_MC[j]<<",";
	f<<"};"<<endl;
	f<<"double sigmaEtrackinv[30]={";
	for (int j=0;j<30;j++) f<<sigma_Track_MC[j]<<",";
	f<<"};"<<endl;
	f<<"double sigmaETofDinv[30]={";
	for (int j=0;j<30;j++) f<<sigma_TOFD_MC[j]<<",";
	f<<"};"<<endl;
	f<<"double sigmabetainv[30]={";
	for (int j=0;j<30;j++) f<<sigma_beta[j]<<",";
	f<<"};"<<endl;
	f<<"double sigmaRinv[24]={";
	for (int j=0;j<24;j++) f<<sigma_R[j]<<",";
	f<<"};"<<endl;
	f<<"///////////////////////////////////////////////////////"<<endl;
	f<<endl;

	f<<"////////////// CURVE TEORICHE //////////////////"<<endl;
	f<<"double EL1[30]={";
        for (int j=0;j<30;j++) f<<mean_L1_D_inv[j]<<",";
        f<<"};"<<endl;
	f<<"double ETOFU[30]={";
	for (int j=0;j<30;j++) f<<mean_TOFU_D_inv[j]<<",";
	f<<"};"<<endl;
	f<<"double ETrack[30]={";
	for (int j=0;j<30;j++) f<<mean_Track_D_inv[j]<<",";
	f<<"};"<<endl;
	f<<"double ETOFD[30]={";
	for (int j=0;j<30;j++) f<<mean_TOFD_D_inv[j]<<",";
	f<<"};"<<endl;
	f<<"TF1 *protons = new TF1(\"f1\",\"pow((pow(x,2)/pow(0.938,2)/(1 + pow(x,2)/pow(0.938,2))),0.5)\",0.1,100);"<<endl;
	f<<"TF1 *deutons = new TF1(\"f1\",\"pow((pow(x,2)/pow(1.875,2)/(1 + pow(x,2)/pow(1.875,2))),0.5)\",0.1,100);"<<endl;
	f<<"///////////////////////////////////////////////////////"<<endl;
	f<<endl;

	f<<"////////////// CORREZIONE E.DEP. MC //////////////////"<<endl;
	f<<"double CorrL1[30]={";
        for (int j=0;j<30;j++) f<<CorrezioneL1[j]<<",";
        f<<"};"<<endl;
	f<<"double CorrTOFU[30]={";
	for (int j=0;j<30;j++) f<<CorrezioneTOFU[j]<<",";
	f<<"};"<<endl;
	f<<"double CorrTrack[30]={";
	for (int j=0;j<30;j++) f<<CorrezioneTrack[j]<<",";
	f<<"};"<<endl;
	f<<"double CorrTOFD[30]={";
	for (int j=0;j<30;j++) f<<CorrezioneTOFD[j]<<",";
	f<<"};"<<endl;
	f<<"///////////////////////////////////////////////////////"<<endl;
	f<<endl;

	f<<"////////////// DEFINIZIONE SPLINES //////////////////"<<endl;
	f<<"TSpline3 *Rig = new TSpline3(\"Cubic Spline\",valorecent,sigmaRinv,23);"<<endl;
	f<<"TSpline3 *beta = new TSpline3(\"beta\",PiccoBeta,sigmabetainv,30);"<<endl;
	f<<"TSpline3 *eL1 = new TSpline3(\"Cubic Spline\",Beta_cent,sigmaEL1Uinv,30);"<<endl;
	f<<"TSpline3 *etofu = new TSpline3(\"Cubic Spline\",Beta_cent,sigmaEtofUinv,30);"<<endl;
	f<<"TSpline3 *etrack = new TSpline3(\"Cubic Spline\",Beta_cent,sigmaEtrackinv,30);"<<endl;
	f<<"TSpline3 *etofd = new TSpline3(\"Cubic Spline\",Beta_cent,sigmaETofDinv,30);"<<endl;
	f<<"TSpline3 *EdepL1beta = new TSpline3(\"Cubic Spline\",Beta_cent,EL1,30);"<<endl;
	f<<"TSpline3 *EdepTOFbeta = new TSpline3(\"Cubic Spline\",Beta_cent,ETOFU,30);"<<endl;
	f<<"TSpline3 *EdepTrackbeta = new TSpline3(\"Cubic Spline\",Beta_cent,ETrack,30);"<<endl;
	f<<"TSpline3 *EdepTOFDbeta = new TSpline3(\"Cubic Spline\",Beta_cent,ETOFD,30);"<<endl;
	f<<"TSpline3 *Corr_L1 = new TSpline3(\"Cubic Spline\",Beta_cent,CorrL1,30);"<<endl;
	f<<"TSpline3 *Corr_TOFU = new TSpline3(\"Cubic Spline\",Beta_cent,CorrTOFU,30);"<<endl;
	f<<"TSpline3 *Corr_Track = new TSpline3(\"Cubic Spline\",Beta_cent,CorrTrack,30);"<<endl;
	f<<"TSpline3 *Corr_TOFD = new TSpline3(\"Cubic Spline\",Beta_cent,CorrTOFD,30);"<<endl;
	f<<"TSpline3 *Rgenmis = new TSpline3(\"\",R_mis,R_gen,34);"<<endl;
	f<<"TSpline3 *CorrRICH = new TSpline3(\"\",R_rich,Corr_rich,25);"<<endl;
	f<<"///////////////////////////////////////////////////////"<<endl;
	f<<endl;

	f<<"void Functions_auto(){}"<<endl;
	f.close();
	/////////////////////////////////////////////
	return 1;
}
