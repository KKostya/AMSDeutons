#include "TH2.h"
#include "TH3.h"
#include <TVector3.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <TMath.h>
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
#include "TMatrix.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF2.h"
#include <math.h>
#include <cstring>
#include <TGraphErrors.h>
#include "../Functions_auto.h"
#include <ctime>
#include <cstdlib>

using namespace std;

int main(){
cout<<"fe"<<endl;
int avanzamento =0;
int fraz=10;
float R;
float Beta_corr;
float EdepL1;
float RminTOF;
float RminTrack;
float RminTRD;
float XTOF;
float XTrack;
float XTRD;
float YTOF;
float YTrack;
float YTRD;
float LDiscriminant;
float BDT_response;
float Massagen;
float CUTMASK;
float IsPrescaled;
float Rcutoff;
float Latitude;
int binmin=0;
int binmax=11;
float Par=0.5;
float Massa=0;


TH2F * ProiezioniTOF[11];
TH2F * ProiezioniTrack[11];
TH2F * MassaTOF[11];
TH2F * MassaTrack[11];
float MassTOF[11][100][100]={{{0}}};
float MassTrack[11][100][100]={{{0}}};
int EvNum1[11][100][100]={{{0}}};
int EvNum2[11][100][100]={{{0}}};


string nome;
string ParLim[11]={"0.5-0.8","0.8-1.1","1.1-1.4","1.4-1.7","1.7-2.0","2.0-2.3","2.3-2.6","2.6-2.9","2.9-3.2","3.2-3.5","3.5-3.8"};
for(int k=binmin;k<binmax;k++) {
	nome="TOF Rtrue: "+ParLim[k];
	ProiezioniTOF[k]=new TH2F(nome.c_str(),nome.c_str(),1000,-40,40,1000,-40,40);
	nome="Tracker Rtrue: "+ParLim[k];
	ProiezioniTrack[k]=new TH2F(nome.c_str(),nome.c_str(),1000,-40,40,1000,-40,40);
	nome="Distrib. Massa (TOF)"+ParLim[k];
	MassaTOF[k]=new TH2F(nome.c_str(),nome.c_str(),100,-40,40,100,-40,40);
	nome="Distrib. Massa (Track)"+ParLim[k];
        MassaTrack[k]=new TH2F(nome.c_str(),nome.c_str(),100,-40,40,100,-40,40); 
}

TFile *file1 =TFile::Open("/home/AMS/fdimicco/fdimicco/Risultati/Febbraio2012/RisultatiMC.root");
    TFile *file2 =TFile::Open("/home/AMS/fdimicco/fdimicco/Risultati/Febbraio2012/RisultatiDATI.root");
    TNtuple *ntupla1=(TNtuple*)file1->Get("grandezzesepd");
    TNtuple *ntupla2=(TNtuple*)file2->Get("grandezzesepd");


 	ntupla1->SetBranchAddress("R",&R);
        ntupla1->SetBranchAddress("Beta_corr",&Beta_corr);
        ntupla1->SetBranchAddress("EdepL1",&EdepL1);
        ntupla1->SetBranchAddress("RminTOF",&RminTOF);
        ntupla1->SetBranchAddress("RminTrack",&RminTrack);
        ntupla1->SetBranchAddress("RminTRD",&RminTRD);
        ntupla1->SetBranchAddress("XTOF",&XTOF);
        ntupla1->SetBranchAddress("XTrack",&XTrack);
        ntupla1->SetBranchAddress("XTRD",&XTRD);
        ntupla1->SetBranchAddress("YTOF",&YTOF);
        ntupla1->SetBranchAddress("YTrack",&YTrack);
        ntupla1->SetBranchAddress("YTRD",&YTRD);
        ntupla1->SetBranchAddress("LDiscriminant",&LDiscriminant);
        ntupla1->SetBranchAddress("BDT_response",&BDT_response);
        ntupla1->SetBranchAddress("Massagen",&Massagen);
        ntupla1->SetBranchAddress("CUTMASK",&CUTMASK);
        ntupla1->SetBranchAddress("IsPrescaled",&IsPrescaled);

        ntupla2->SetBranchAddress("R",&R);
        ntupla2->SetBranchAddress("Beta_corr",&Beta_corr);
        ntupla2->SetBranchAddress("EdepL1",&EdepL1);
        ntupla2->SetBranchAddress("RminTOF",&RminTOF);
        ntupla2->SetBranchAddress("RminTrack",&RminTrack);
        ntupla2->SetBranchAddress("RminTRD",&RminTRD);
        ntupla2->SetBranchAddress("XTOF",&XTOF);
        ntupla2->SetBranchAddress("XTrack",&XTrack);
        ntupla2->SetBranchAddress("XTRD",&XTRD);
        ntupla2->SetBranchAddress("YTOF",&YTOF);
        ntupla2->SetBranchAddress("YTrack",&YTrack);
        ntupla2->SetBranchAddress("YTRD",&YTRD);
        ntupla2->SetBranchAddress("Rcutoff",&Rcutoff);
        ntupla2->SetBranchAddress("LDiscriminant",&LDiscriminant);
        ntupla2->SetBranchAddress("BDT_response",&BDT_response);
        ntupla2->SetBranchAddress("Latitude",&Latitude);
        ntupla2->SetBranchAddress("CUTMASK",&CUTMASK);
        ntupla2->SetBranchAddress("IsPrescaled",&IsPrescaled);

int x=0;
int y=0;	
for(int i=0; i<ntupla2->GetEntries()/fraz;i++) {
      	int n = ntupla2->GetEvent(i);
	if(100*(i/(float)(ntupla2->GetEntries()/fraz))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
	Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Beta_corr,2)),0.5)/Beta_corr,2)),0.5);
	if(IsPrescaled==0){	
		for(int k=binmin;k<binmax;k++){
   	     		Par=0.5+k*0.3;
	     		if(RminTOF>Par&&RminTOF<=Par+0.3){ ProiezioniTOF[k]->Fill(XTOF,YTOF);	 	
				
				x=(-((-40)-XTOF)/80)*100;
				y=(-((-40)-YTOF)/80)*100;
		        	if(Beta_corr<1){
					MassTOF[k][x][y]+=Massa;
					EvNum1[k][x][y]++;}
			}
			if(RminTOF>Par&&RminTOF<=Par+0.3) {ProiezioniTrack[k]->Fill(XTrack,YTrack); 
				x=(-((-40)-XTrack)/80)*100;
                                y=(-((-40)-YTrack)/80)*100;
                                if(Beta_corr<1){	
					MassTrack[k][x][y]+=Massa;
                               	 	EvNum2[k][x][y]++;}
			}		
				
			}		
		}
	}

cout<<"************************ PLOT DISTRIBUZIONI ************"<<endl;
for(int k=binmin;k<binmax;k++)
	for(int x=0;x<100;x++)
                   for(int j=0;j<100;j++) if(EvNum1[k][x][j]>0) MassaTOF[k]->SetBinContent(x,j,MassTOF[k][x][j]/(float)EvNum1[k][x][j]);
					  else MassaTOF[k]->SetBinContent(x,j,0);
for(int k=binmin;k<binmax;k++)
        for(int x=0;x<100;x++)
                   for(int j=0;j<100;j++) if(EvNum2[k][x][j]>0) MassaTrack[k]->SetBinContent(x,j,MassTrack[k][x][j]/(float)EvNum2[k][x][j]);
                                          else MassaTrack[k]->SetBinContent(x,j,0);


TCanvas *c1[11];

for(int k=binmin;k<binmax;k++){
	nome="Distrib. Massa (TOF)"+ParLim[k];
	c1[k]=new TCanvas(nome.c_str());
	c1[k]->cd();
	MassaTOF[k]->GetXaxis()->SetRangeUser(-20,20);
	MassaTOF[k]->GetYaxis()->SetRangeUser(-20,20);
	MassaTOF[k]->GetZaxis()->SetRangeUser(0,4);
	MassaTOF[k]->Draw("col");
	}

TCanvas *c2[11];

for(int k=binmin;k<binmax;k++){
        nome="Distrib. Massa (Track)"+ParLim[k];
        c2[k]=new TCanvas(nome.c_str());
        c2[k]->cd();
        MassaTrack[k]->GetXaxis()->SetRangeUser(-20,20);
        MassaTrack[k]->GetYaxis()->SetRangeUser(-20,20);
        MassaTrack[k]->GetZaxis()->SetRangeUser(0,4);
	MassaTrack[k]->Draw("col");
        }
	

cout<<"************************ OUTPUT ************************"<<endl;
string nomefile="/home/AMS/fdimicco/fdimicco/Proiezioni.root";
TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
f_out->mkdir("Proiezioni Dati - TOF");
f_out->cd("Proiezioni Dati - TOF");
for(int k=binmin;k<binmax;k++) 
	{ProiezioniTOF[k]->GetXaxis()->SetRangeUser(-20,20);ProiezioniTOF[k]->GetYaxis()->SetRangeUser(-20,20); ProiezioniTOF[k]->Write();}
f_out->mkdir("Proiezioni Dati - Track");
f_out->cd("Proiezioni Dati - Track");
for(int k=binmin;k<binmax;k++)
        {ProiezioniTrack[k]->GetXaxis()->SetRangeUser(-20,20);ProiezioniTrack[k]->GetYaxis()->SetRangeUser(-20,20); ProiezioniTrack[k]->Write();}
f_out->mkdir("Distribuzioni Massa - TOF");
f_out->cd("Distribuzioni Massa - TOF");
for(int k=binmin;k<binmax;k++) c1[k]->Write();
f_out->mkdir("Distribuzioni Massa - Track");
f_out->cd("Distribuzioni Massa - Track");
for(int k=binmin;k<binmax;k++) c2[k]->Write();

f_out->Write();
f_out->Close();

}
