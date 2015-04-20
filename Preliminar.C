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
float EdepTOF=0;
float EdepTRD=0;
float EdepTrack=0;
float EdepTOFteo=0;
float R=0;
float BetaRICH=0;
float Momentogen=0;
float Betagen=0;
float Beta_corr=0;
float bin[24];
float Qbest=0;
double betacent[30];
float B1,B2;
int main(){

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
TCanvas *c6=new TCanvas("sigma Edep TOF (inv)");
TCanvas *c6_bis=new TCanvas("sigma Edep Track (inv)");
TCanvas *c6_tris=new TCanvas("sigma Edep TRD (inv)");
TCanvas *c7=new TCanvas("Inverse Beta (TOF)");
TCanvas *c8=new TCanvas("Sigma Inverse Beta (TOF)");
TCanvas *c9=new TCanvas("Inverse R");
TCanvas *c10=new TCanvas("Sigma Inverse R");
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
c9->Divide(6,4);
TFile *file1 =TFile::Open("/home/AMS/fdimicco/fdimicco/Risultati/risultati/RisultatiMC.root");
TFile *file2 =TFile::Open("/home/AMS/fdimicco/fdimicco/Risultati/risultati/RisultatiDATI.root");
TNtuple *ntupla1=(TNtuple*)file1->Get("Qual");
TNtuple *ntupla2=(TNtuple*)file2->Get("Qual");
//pre-qual
ntupla1->SetBranchAddress("Beta",&Beta);
ntupla1->SetBranchAddress("Massa",&Massa);
ntupla1->SetBranchAddress("CaricaTrack",&CaricaTrack);
ntupla1->SetBranchAddress("CaricaTRD",&CaricaTRD);
ntupla1->SetBranchAddress("EdepTOF",&EdepTOF);
ntupla1->SetBranchAddress("EdepTRD",&EdepTRD);
ntupla1->SetBranchAddress("EdepTrack",&EdepTrack);
ntupla1->SetBranchAddress("Momentogen",&Momentogen);
ntupla1->SetBranchAddress("Betagen",&Betagen);
ntupla1->SetBranchAddress("BetaRICH",&BetaRICH);
ntupla1->SetBranchAddress("R",&R);
ntupla1->SetBranchAddress("Massagen",&Massagen);
ntupla1->SetBranchAddress("Qbest",&Qbest);

ntupla2->SetBranchAddress("Beta",&Beta);
ntupla2->SetBranchAddress("Massa",&Massa);
ntupla2->SetBranchAddress("CaricaTrack",&CaricaTrack);
ntupla2->SetBranchAddress("CaricaTRD",&CaricaTRD);
ntupla2->SetBranchAddress("EdepTOF",&EdepTOF);
ntupla2->SetBranchAddress("EdepTRD",&EdepTRD);
ntupla2->SetBranchAddress("EdepTrack",&EdepTrack);
ntupla2->SetBranchAddress("BetaRICH",&BetaRICH);
ntupla2->SetBranchAddress("R",&R);
ntupla2->SetBranchAddress("Qbest",&Qbest);

for(int i=0;i<24;i++)
{
        float temp=i+7;
	bin[i]=0.1*pow(10,temp/9.5);
}

double valorecent[24]={0.620376,0.79053,1.28364,1.63572, 2.08435, 2.65604, 3.38452,4.31281, 5.49571, 7.00304, 8.9238,11.3714, 14.4903,18.4646, 23.5289, 29.9823, 38.2058, 48.6846, 62.0376, 79.053, 100.735, 128.364,162.3776739189};

for(int i=0;i<30;i++)	betacent[i]=0.4+(2*i/(double)100)+0.01;        

TH1F *RisoluzioniTOF[30];
TH1F *RisoluzioniTrack[30];
TH1F *RisoluzioniTRD[30];
TH1F *DistribuzioniTOF_corr[30];
TH1F *DistribuzioniTrack_corr[30];
TH1F *DistribuzioniTRD_corr[30];

TH1F *RisoluzioniTOF_D[30];
TH1F *RisoluzioniTrack_D[30];
TH1F *RisoluzioniTRD_D[30];

TH1F *RisoluzioniBeta[30];
TH1F *RisoluzioniR[24];

TH1F *DistribuzioniTOF[30];
TH1F *DistribuzioniTrack[30];
TH1F *DistribuzioniTRD[30];

TH1F *DistribuzioniTOF_D[30];
TH1F *DistribuzioniTrack_D[30];
TH1F *DistribuzioniTRD_D[30];

TH2F * h1=new TH2F("","",1000,0,1,1000,0,15);
TH2F * h2=new TH2F("","",1000,0,1,1000,0,1);
TH2F * h3=new TH2F("","",1000,0,1,1000,0,20);


for(int i=0;i<30;i++){
RisoluzioniTOF_D[i]=new TH1F("","",150,0,1);
RisoluzioniTrack_D[i]=new TH1F("","",150,0,20);
RisoluzioniTRD_D[i]=new TH1F("","",150,0,1);
DistribuzioniTOF_D[i]=new TH1F("","",150,0,20);
DistribuzioniTrack_D[i]=new TH1F("","",150,0,1);
DistribuzioniTRD_D[i]=new TH1F("","",150,0,20);

}
for(int i=0; i<ntupla2->GetEntries();i++) {
        int k = ntupla2->GetEvent(i);
	B1=0.4;
	B2=0.42;
	if(i%100000==0) cout<<i<<endl;
	for(int j=0; j<30;j++){
			if(Beta>B1&&Beta<=B2&&Qbest<1.5){
				RisoluzioniTOF_D[j]->Fill(1/EdepTOF);
                                DistribuzioniTOF_D[j]->Fill(EdepTOF);
                                h1->Fill(Beta,EdepTOF);
				RisoluzioniTrack_D[j]->Fill(1/EdepTrack);
				DistribuzioniTrack_D[j]->Fill(EdepTrack);
                                h2->Fill(Beta,EdepTrack);
                                RisoluzioniTRD_D[j]->Fill(1/EdepTRD);
                                DistribuzioniTRD_D[j]->Fill(EdepTRD);
				h3->Fill(Beta,EdepTRD);
  				}
                                B1=B1+0.02;
				B2=B2+0.02;	
				}	
				
}

/*
for(int j=1; j<31;j++){
for(int i=0;i<RisoluzioniTOF_D[j-1]->GetNbinsX();i++) RisoluzioniTOF_D[j-1]->SetBinContent(i, RisoluzioniTOF_D[j-1]->GetBinContent(i)/ RisoluzioniTOF_D[j-1]->GetEntries());
for(int L=0;L<DistribuzioniTOF_D[j-1]->GetNbinsX();L++) DistribuzioniTOF_D[j-1]->SetBinContent(L, DistribuzioniTOF_D[j-1]->GetBinContent(L)/DistribuzioniTOF_D[j-1]->GetEntries());
for(int i=0;i<RisoluzioniTrack_D[j-1]->GetNbinsX();i++) RisoluzioniTrack_D[j-1]->SetBinContent(i, RisoluzioniTrack_D[j-1]->GetBinContent(i)/ RisoluzioniTrack_D[j-1]->GetEntries());
for(int L=0;L<DistribuzioniTrack_D[j-1]->GetNbinsX();L++) DistribuzioniTrack_D[j-1]->SetBinContent(L, DistribuzioniTrack_D[j-1]->GetBinContent(L)/DistribuzioniTrack_D[j-1]->GetEntries());
for(int i=0;i<RisoluzioniTRD_D[j-1]->GetNbinsX();i++) RisoluzioniTRD_D[j-1]->SetBinContent(i, RisoluzioniTRD_D[j-1]->GetBinContent(i)/ RisoluzioniTRD_D[j-1]->GetEntries());
for(int L=0;L<DistribuzioniTRD_D[j-1]->GetNbinsX();L++) DistribuzioniTRD_D[j-1]->SetBinContent(L, DistribuzioniTRD_D[j-1]->GetBinContent(L)/DistribuzioniTRD_D[j-1]->GetEntries());
}
*/
for(int j=1; j<31;j++){
c1->cd(j);
RisoluzioniTOF_D[j-1]->Draw();
c3->cd(j);
DistribuzioniTOF_D[j-1]->Draw();

c1_bis->cd(j);
RisoluzioniTrack_D[j-1]->Draw();
c3_bis->cd(j);
DistribuzioniTrack_D[j-1]->Draw();

c1_tris->cd(j);
RisoluzioniTRD_D[j-1]->Draw();
c3_tris->cd(j);
DistribuzioniTRD_D[j-1]->Draw();
}


for(int i=0;i<30;i++){
RisoluzioniTOF[i]=new TH1F("","",150,0,1);
RisoluzioniTrack[i]=new TH1F("","",150,0,20);
RisoluzioniTRD[i]=new TH1F("","",150,0,1);
DistribuzioniTOF[i]=new TH1F("","",150,0,20);
DistribuzioniTrack[i]=new TH1F("","",150,0,1);
DistribuzioniTRD[i]=new TH1F("","",150,0,20);
RisoluzioniBeta[i]=new TH1F("","",500,0,3);
if(i<24) RisoluzioniR[i]=new TH1F("","",1000,1/valorecent[i]-0.5,1/valorecent[i]+0.5);
}

for(int i=0; i<ntupla1->GetEntries();i++) {
        int k = ntupla1->GetEvent(i);
	B1=0.4;
	B2=0.42;
	if(i%100000==0) cout<<i<<endl;
	for(int j=0; j<30;j++){
			if(Beta>B1&&Beta<=B2&&Massagen>0.5&&Massagen<1){
				RisoluzioniTOF[j]->Fill(1/EdepTOF);
                		DistribuzioniTOF[j]->Fill(EdepTOF);                
				RisoluzioniTrack[j]->Fill(1/EdepTrack);
                                DistribuzioniTrack[j]->Fill(EdepTrack);
				RisoluzioniTRD[j]->Fill(1/EdepTRD);
 				DistribuzioniTRD[j]->Fill(EdepTRD);
				}
 			 if(Betagen>B1&&Betagen<=B1+(B2-B1)/3&&Massagen>0.5&&Massagen<1){
				RisoluzioniBeta[j]->Fill(1/Beta);
				}
                                B1=B1+0.02;
				B2=B2+0.02;	
				}
	for(int l=0; l<23;l++) if(Momentogen>bin[l]&&Momentogen<=bin[l+1]&&Massagen>0.5&&Massagen<1)
                                RisoluzioniR[l]->Fill(1/R);	
				
}
/*
for(int j=1; j<31;j++){
for(int i=0;i<RisoluzioniTOF[j-1]->GetNbinsX();i++) RisoluzioniTOF[j-1]->SetBinContent(i, RisoluzioniTOF[j-1]->GetBinContent(i)/ RisoluzioniTOF[j-1]->GetEntries());
for(int L=0;L<DistribuzioniTOF[j-1]->GetNbinsX();L++) DistribuzioniTOF[j-1]->SetBinContent(L, DistribuzioniTOF[j-1]->GetBinContent(L)/DistribuzioniTOF[j-1]->GetEntries());
for(int i=0;i<RisoluzioniTrack[j-1]->GetNbinsX();i++) RisoluzioniTrack[j-1]->SetBinContent(i, RisoluzioniTrack[j-1]->GetBinContent(i)/ RisoluzioniTrack[j-1]->GetEntries());
for(int L=0;L<DistribuzioniTrack[j-1]->GetNbinsX();L++) DistribuzioniTrack[j-1]->SetBinContent(L, DistribuzioniTrack[j-1]->GetBinContent(L)/DistribuzioniTrack[j-1]->GetEntries());
for(int i=0;i<RisoluzioniTRD[j-1]->GetNbinsX();i++) RisoluzioniTRD[j-1]->SetBinContent(i, RisoluzioniTRD[j-1]->GetBinContent(i)/ RisoluzioniTRD[j-1]->GetEntries());
for(int L=0;L<DistribuzioniTRD[j-1]->GetNbinsX();L++) DistribuzioniTRD[j-1]->SetBinContent(L, DistribuzioniTRD[j-1]->GetBinContent(L)/DistribuzioniTRD[j-1]->GetEntries());
}
*/
for(int j=1; j<31;j++){
c1->cd(j);
gPad->SetLogy();
RisoluzioniTOF[j-1]->SetLineColor(2);
RisoluzioniTOF[j-1]->Draw("same");
c3->cd(j);
gPad->SetLogy();
DistribuzioniTOF[j-1]->SetLineColor(2);
DistribuzioniTOF[j-1]->Draw("same");

c1_bis->cd(j);
gPad->SetLogy();
RisoluzioniTrack[j-1]->SetLineColor(2);
RisoluzioniTrack[j-1]->Draw("same");
c3_bis->cd(j);
gPad->SetLogy();
DistribuzioniTrack[j-1]->SetLineColor(2);
DistribuzioniTrack[j-1]->Draw("same");

c1_tris->cd(j);
gPad->SetLogy();
RisoluzioniTRD[j-1]->SetLineColor(2);
RisoluzioniTRD[j-1]->Draw("same");
c3_tris->cd(j);
gPad->SetLogy();
DistribuzioniTRD[j-1]->SetLineColor(2);
DistribuzioniTRD[j-1]->Draw("same");

c7->cd(j);
gPad->SetLogy();
RisoluzioniBeta[j-1]->SetLineColor(2);
RisoluzioniBeta[j-1]->Draw("same");
}

for(int j=1; j<25;j++){
c9->cd(j);
gPad->SetLogy();
RisoluzioniR[j-1]->SetLineColor(2);
RisoluzioniR[j-1]->Draw("same");
 }
//////////////////GAUSSIAN FITS//////////////////
TF1 *f1_MC_TOF[30];
TF1 *f1_D_TOF[30];
TF1 *f1_MC_Track[30];
TF1 *f1_D_Track[30];
TF1 *f1_MC_TRD[30];
TF1 *f1_D_TRD[30];
TF1 *beta[30];
TF1 *r[24];
string numero[30]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29"};
string gausMC="gausMC_";
string gausD="gausD_";
float mean_TOF_MC[30];
float mean_TOF_D[30];
float mean_Track_MC[30];
float mean_Track_D[30];
float mean_TRD_MC[30];
float mean_TRD_D[30];
float mean_TOF_D_inv[30];
float mean_Track_D_inv[30];
float mean_TRD_D_inv[30];
float sigma_TOF_MC[30];
float sigma_TOF_D[30];
float sigma_Track_MC[30];
float sigma_Track_D[30];
float sigma_TRD_MC[30];
float sigma_TRD_D[30];
float sigma_TOF_MC_err[30];
float sigma_TOF_D_err[30];
float sigma_Track_MC_err[30];
float sigma_Track_D_err[30];
float sigma_TRD_MC_err[30];
float sigma_TRD_D_err[30];
double sigma_beta[30]={0};
double mean_beta[30]={0};
double sigma_R[24]={0};
string nomefunz;
TF1 *fitmean;
for(int j=0; j<30;j++) {

nomefunz=gausMC+"TOF"+numero[j];
f1_MC_TOF[j] = new TF1(nomefunz.c_str(),"gaus",0,20);
nomefunz=gausD+"TOF"+numero[j];
f1_D_TOF[j] = new TF1(nomefunz.c_str(),"gaus",0,20);

nomefunz=gausMC+"Track"+numero[j];
f1_MC_Track[j] = new TF1(nomefunz.c_str(),"gaus",0,20);
nomefunz=gausD+"Track"+numero[j];
f1_D_Track[j] = new TF1(nomefunz.c_str(),"gaus",0,20);

nomefunz=gausMC+"TRD"+numero[j];
f1_MC_TRD[j] = new TF1(nomefunz.c_str(),"gaus",0,20);
nomefunz=gausD+"TRD"+numero[j];
f1_D_TRD[j] = new TF1(nomefunz.c_str(),"gaus",0,20);

f1_D_TOF[j]->SetLineColor(4);
f1_D_Track[j]->SetLineColor(4);
f1_D_TRD[j]->SetLineColor(4);

//TOF
f1_MC_TOF[j]->SetParameter(0,RisoluzioniTOF[j]->GetBinContent(RisoluzioniTOF[j]->GetMaximumBin())); 
f1_MC_TOF[j]->SetParameter(1,RisoluzioniTOF[j]->GetMean());
f1_MC_TOF[j]->SetParameter(2,RisoluzioniTOF[j]->GetRMS());
f1_D_TOF[j]->SetParameter(0,RisoluzioniTOF_D[j]->GetBinContent(RisoluzioniTOF_D[j]->GetMaximumBin()));
f1_D_TOF[j]->SetParameter(1,RisoluzioniTOF_D[j]->GetMean());
f1_D_TOF[j]->SetParameter(2,RisoluzioniTOF_D[j]->GetRMS());
nomefunz=gausMC+"TOF"+numero[j];
RisoluzioniTOF[j]->Fit(nomefunz.c_str());
nomefunz=gausD+"TOF"+numero[j];
RisoluzioniTOF_D[j]->Fit(nomefunz.c_str());
mean_TOF_MC[j]=f1_MC_TOF[j]->GetParameter(1);
mean_TOF_D[j]=f1_D_TOF[j]->GetParameter(1);
sigma_TOF_MC[j]=f1_MC_TOF[j]->GetParameter(2);
sigma_TOF_D[j]=f1_D_TOF[j]->GetParameter(2);
sigma_TOF_MC_err[j]=f1_MC_TOF[j]->GetParError(2);
sigma_TOF_D_err[j]=f1_D_TOF[j]->GetParError(2);
fitmean = new TF1("fitmean","gaus",DistribuzioniTOF_D[j]->GetBinCenter(DistribuzioniTOF_D[j]->GetMaximumBin())-DistribuzioniTOF_D[j]->GetRMS(),DistribuzioniTOF_D[j]->GetBinCenter(DistribuzioniTOF_D[j]->GetMaximumBin())+DistribuzioniTOF_D[j]->GetRMS()/2);
DistribuzioniTOF_D[j]->Fit("fitmean","R");
mean_TOF_D_inv[j]=fitmean->GetParameter(1);
delete fitmean;

//Track
f1_MC_Track[j]->SetParameter(0,RisoluzioniTrack[j]->GetBinContent(RisoluzioniTrack[j]->GetMaximumBin()));
f1_MC_Track[j]->SetParameter(1,RisoluzioniTrack[j]->GetMean());
f1_MC_Track[j]->SetParameter(2,RisoluzioniTrack[j]->GetRMS());
f1_D_Track[j]->SetParameter(0,RisoluzioniTrack_D[j]->GetBinContent(RisoluzioniTrack_D[j]->GetMaximumBin()));
f1_D_Track[j]->SetParameter(1,RisoluzioniTrack_D[j]->GetMean());
f1_D_Track[j]->SetParameter(2,RisoluzioniTrack_D[j]->GetRMS());
nomefunz=gausMC+"Track"+numero[j];
RisoluzioniTrack[j]->Fit(nomefunz.c_str());
nomefunz=gausD+"Track"+numero[j];
RisoluzioniTrack_D[j]->Fit(nomefunz.c_str());
mean_Track_MC[j]=f1_MC_Track[j]->GetParameter(1);
mean_Track_D[j]=f1_D_Track[j]->GetParameter(1);
sigma_Track_MC[j]=f1_MC_Track[j]->GetParameter(2);
sigma_Track_D[j]=f1_D_Track[j]->GetParameter(2);
sigma_Track_MC_err[j]=f1_MC_TOF[j]->GetParError(2);
sigma_Track_D_err[j]=f1_D_TOF[j]->GetParError(2);
fitmean = new TF1("fitmean","gaus",DistribuzioniTrack_D[j]->GetBinCenter(DistribuzioniTrack_D[j]->GetMaximumBin())-DistribuzioniTrack_D[j]->GetRMS(),DistribuzioniTrack_D[j]->GetBinCenter(DistribuzioniTrack_D[j]->GetMaximumBin())+DistribuzioniTrack_D[j]->GetRMS()/2);
DistribuzioniTrack_D[j]->Fit("fitmean","R");
mean_Track_D_inv[j]=fitmean->GetParameter(1);
delete fitmean;

//TRD
f1_MC_TRD[j]->SetParameter(0,RisoluzioniTRD[j]->GetBinContent(RisoluzioniTRD[j]->GetMaximumBin()));
f1_MC_TRD[j]->SetParameter(1,RisoluzioniTRD[j]->GetMean());
f1_MC_TRD[j]->SetParameter(2,RisoluzioniTRD[j]->GetRMS());
f1_D_TRD[j]->SetParameter(0,RisoluzioniTRD_D[j]->GetBinContent(RisoluzioniTRD_D[j]->GetMaximumBin()));
f1_D_TRD[j]->SetParameter(1,RisoluzioniTRD_D[j]->GetMean());
f1_D_TRD[j]->SetParameter(2,RisoluzioniTRD_D[j]->GetRMS());
nomefunz=gausMC+"TRD"+numero[j];
RisoluzioniTRD[j]->Fit(nomefunz.c_str());
nomefunz=gausD+"TRD"+numero[j];
RisoluzioniTRD_D[j]->Fit(nomefunz.c_str());
mean_TRD_MC[j]=f1_MC_TRD[j]->GetParameter(1);
mean_TRD_D[j]=f1_D_TRD[j]->GetParameter(1);
sigma_TRD_MC[j]=f1_MC_TRD[j]->GetParameter(2);
sigma_TRD_D[j]=f1_D_TRD[j]->GetParameter(2);
sigma_TRD_MC_err[j]=f1_MC_TOF[j]->GetParError(2);
sigma_TRD_D_err[j]=f1_D_TOF[j]->GetParError(2);
fitmean = new TF1("fitmean","gaus",DistribuzioniTRD_D[j]->GetBinCenter(DistribuzioniTRD_D[j]->GetMaximumBin())-DistribuzioniTRD_D[j]->GetRMS(),DistribuzioniTRD_D[j]->GetBinCenter(DistribuzioniTRD_D[j]->GetMaximumBin())+DistribuzioniTRD_D[j]->GetRMS()/2);
DistribuzioniTRD_D[j]->Fit("fitmean","R");
mean_TRD_D_inv[j]=fitmean->GetParameter(1);
delete fitmean;

//Beta
beta[j]=new TF1("beta","gaus",0,20);
beta[j]->SetParameter(0,RisoluzioniBeta[j]->GetBinContent(RisoluzioniBeta[j]->GetMaximumBin()));
beta[j]->SetParameter(1,RisoluzioniBeta[j]->GetMean());
beta[j]->SetParameter(2,RisoluzioniBeta[j]->GetRMS());
if(RisoluzioniBeta[j]->GetEntries()>300) 
	{
		RisoluzioniBeta[j]->Fit("beta");
		sigma_beta[j]=beta[j]->GetParameter(2);
		mean_beta[j]=1/beta[j]->GetParameter(1);
	}
}
for(int j=0; j<24;j++){
r[j]=new TF1("rig","gaus",0,20);
r[j]->SetParameter(0,RisoluzioniR[j]->GetBinContent(RisoluzioniR[j]->GetMaximumBin()));
r[j]->SetParameter(1,RisoluzioniR[j]->GetMean());
r[j]->SetParameter(2,RisoluzioniR[j]->GetRMS());
RisoluzioniR[j]->Fit("rig");
sigma_R[j]=r[j]->GetParameter(2);
}

///////////////////////////////////////////////
/////////////// E. Dep. vs Beta ///////////////

TGraph *EvsBetaTOF=new TGraph();
TGraph *EvsBetaTrack=new TGraph();
TGraph *EvsBetaTRD=new TGraph();
for(int j=0; j<30;j++) {
EvsBetaTOF->SetPoint(j,betacent[j],mean_TOF_D_inv[j]);
EvsBetaTrack->SetPoint(j,betacent[j],mean_Track_D_inv[j]);
EvsBetaTRD->SetPoint(j,betacent[j],mean_TRD_D_inv[j]);
}
c2->cd();
EvsBetaTOF->SetLineWidth(2);
EvsBetaTOF->SetLineColor(2);
h1->Draw("col");
EvsBetaTOF->Draw("sameC");
c2_bis->cd();
EvsBetaTrack->SetLineWidth(2);
EvsBetaTrack->SetLineColor(2);
h2->Draw("col");
EvsBetaTrack->Draw("sameC");
c2_tris->cd();
EvsBetaTRD->SetLineWidth(2);
EvsBetaTRD->SetLineColor(2);
h3->Draw("col");
EvsBetaTRD->Draw("sameC");
////////////////////////////////////////////////

////////////// CORREZIONE E.DEP.////////////////
double CorrezioneTOF[30];
double CorrezioneTrack[30];
double CorrezioneTRD[30];
TGraph *diffTOF=new TGraph();
TGraph *diffTrack=new TGraph();
TGraph *diffTRD=new TGraph();

for(int j=0; j<30;j++) {
CorrezioneTOF[j]=1/(mean_TOF_D[j]/mean_TOF_MC[j]);
diffTOF->SetPoint(j,betacent[j],CorrezioneTOF[j]);
CorrezioneTrack[j]=1/(mean_Track_D[j]/mean_Track_MC[j]);
diffTrack->SetPoint(j,betacent[j],CorrezioneTrack[j]);
CorrezioneTRD[j]=1/(mean_TRD_D[j]/mean_TRD_MC[j]);
diffTRD->SetPoint(j,betacent[j],CorrezioneTRD[j]);
}
diffTOF->SetLineWidth(2);
diffTOF->SetLineColor(2);
diffTrack->SetLineWidth(2);
diffTrack->SetLineColor(4);
diffTRD->SetLineWidth(2);
diffTRD->SetLineColor(6);
c4->cd();
c4->SetGridx();
c4->SetGridy();
diffTOF->GetXaxis()->SetRangeUser(0,1);
diffTOF->GetYaxis()->SetRangeUser(0.5,1.6);
diffTOF->SetTitle("TOF");
diffTrack->SetTitle("Tracker");
diffTRD->SetTitle("TRD");
diffTOF->Draw("APC");
diffTrack->Draw("same");
diffTRD->Draw("same");

TSpline3 *CorrTOF= new TSpline3("Cubic Spline",betacent,CorrezioneTOF,30);
TSpline3 *CorrTrack= new TSpline3("Cubic Spline",betacent,CorrezioneTrack,30);
TSpline3 *CorrTRD= new TSpline3("Cubic Spline",betacent,CorrezioneTRD,30);

for(int i=0;i<30;i++){
DistribuzioniTOF_corr[i]=new TH1F("","",150,0,20);
DistribuzioniTrack_corr[i]=new TH1F("","",150,0,1);
DistribuzioniTRD_corr[i]=new TH1F("","",150,0,20);
}

for(int i=0; i<ntupla1->GetEntries();i++) {
        int k = ntupla1->GetEvent(i);
        B1=0.4;
        B2=0.42;
        if(i%100000==0) cout<<i<<endl;
        for(int j=0; j<30;j++){
                        if(Beta>B1&&Beta<=B2&&Massagen>0.5&&Massagen<1){
                                DistribuzioniTOF_corr[j]->Fill(EdepTOF*CorrTOF->Eval(Beta));
                                DistribuzioniTrack_corr[j]->Fill(EdepTrack*CorrTrack->Eval(Beta));
                                DistribuzioniTRD_corr[j]->Fill(EdepTRD*CorrTRD->Eval(Beta));
                                }
                                B1=B1+0.02;
                                B2=B2+0.02;
                                }

}

for(int j=1; j<31;j++){
c5->cd(j);
gPad->SetLogy();
DistribuzioniTOF_D[j-1]->Draw();
DistribuzioniTOF_corr[j-1]->SetLineColor(2);
DistribuzioniTOF_corr[j-1]->Draw("same");
c5_bis->cd(j);
gPad->SetLogy();
DistribuzioniTrack_D[j-1]->Draw();
DistribuzioniTrack_corr[j-1]->SetLineColor(2);
DistribuzioniTrack_corr[j-1]->Draw("same");
c5_tris->cd(j);
gPad->SetLogy();
DistribuzioniTRD_D[j-1]->Draw();
DistribuzioniTRD_corr[j-1]->SetLineColor(2);
DistribuzioniTRD_corr[j-1]->Draw("same");
}

/////////////////////////////////////////////
////////////// SIGMAS ///////////////////////
TGraphErrors *SigmaTOF=new TGraphErrors();
TGraphErrors *SigmaTrack=new TGraphErrors();
TGraphErrors *SigmaTRD=new TGraphErrors();
TGraphErrors *SigmaTOF_D=new TGraphErrors();
TGraphErrors *SigmaTrack_D=new TGraphErrors();
TGraphErrors *SigmaTRD_D=new TGraphErrors();
TGraphErrors *SigmaBeta=new TGraphErrors();
TGraphErrors *SigmaR=new TGraphErrors();

for(int j=0; j<30;j++) {
SigmaTOF->SetPoint(j,betacent[j],sigma_TOF_MC[j]);
SigmaTOF->SetPointError(j,0,sigma_TOF_MC_err[j]);
SigmaTrack->SetPoint(j,betacent[j],sigma_Track_MC[j]);
SigmaTrack->SetPointError(j,0,sigma_Track_MC_err[j]);
SigmaTRD->SetPoint(j,betacent[j],sigma_TRD_MC[j]);
SigmaTRD->SetPointError(j,0,sigma_TRD_MC_err[j]);
SigmaTOF_D->SetPoint(j,betacent[j],sigma_TOF_D[j]);
SigmaTOF_D->SetPointError(j,0,sigma_TOF_D_err[j]);
SigmaTrack_D->SetPoint(j,betacent[j],sigma_Track_D[j]);
SigmaTrack_D->SetPointError(j,0,sigma_Track_D_err[j]);
SigmaTRD_D->SetPoint(j,betacent[j],sigma_TRD_D[j]);
SigmaTRD_D->SetPointError(j,0,sigma_TRD_D_err[j]);
if(sigma_beta[j]!=0) SigmaBeta->SetPoint(j,mean_beta[j],sigma_beta[j]);
}
for(int j=0; j<24;j++) SigmaR->SetPoint(j,valorecent[j],sigma_R[j]);
for(int j=0; j<30;j++) if(mean_beta[j]==0) mean_beta[j]=j/(double)100;
TSpline3 *SigmaBeta_spl= new TSpline3("Cubic Spline",mean_beta,sigma_beta,30);
for(int j=0; j<30;j++) {
c6->cd();
c6->SetGridx();
c6->SetGridy();
SigmaTOF->SetLineColor(2);
SigmaTOF->SetLineWidth(2);
SigmaTOF_D->SetLineWidth(2);
SigmaTOF_D->Draw("AP");
SigmaTOF->Draw("sameP");

c6_bis->cd();
c6_bis->SetGridx();
c6_bis->SetGridy();
SigmaTrack->SetLineColor(2);
SigmaTrack->SetLineWidth(2);
SigmaTrack_D->SetLineWidth(2);
SigmaTrack_D->Draw("AP");
SigmaTrack->Draw("sameP");

c6_tris->cd();
c6_tris->SetGridx();
c6_tris->SetGridy();
SigmaTRD->SetLineColor(2);
SigmaTRD->SetLineWidth(2);
SigmaTRD_D->SetLineWidth(2);
SigmaTRD_D->Draw("AP");
SigmaTRD->Draw("sameP");

c8->cd();
c8->SetGridx();
c8->SetGridy();
SigmaBeta->SetLineColor(2);
SigmaBeta->SetLineWidth(2);
SigmaBeta->SetMarkerStyle(8);
SigmaBeta->Draw("AP");
SigmaBeta_spl->Draw("same");
c10->cd();
c10->SetGridx();
c10->SetGridy();
SigmaR->SetLineColor(2);
SigmaR->SetLineWidth(2);
SigmaR->SetMarkerStyle(8);
SigmaR->Draw("AP");
}
/////////////////////////////////////////////
////////////// OUTPUT ///////////////////////
    string nomefile="/home/AMS/fdimicco/fdimicco/Splines.root";
    TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
    c1->Write();
    c1_bis->Write();
    c1_tris->Write();
    c3->Write();
    c3_bis->Write();
    c3_tris->Write();
    c2->Write();
    c2_bis->Write();
    c2_tris->Write();
    c4->Write();
    c5->Write();
    c5_bis->Write();
    c5_tris->Write();
    c6->Write();
    c6_bis->Write();
    c6_tris->Write();
    c7->Write();
    c8->Write();
    c9->Write();
    c10->Write();
    f_out->Write();
    f_out->Close();
/////////////////////////////////////////////
//////////////// SCRITTURA SU FILE //////////
ofstream f("Functions_auto.h");
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
f<<"double sigmaEtofinv[30]={";
for (int j=0;j<30;j++) f<<sigma_TOF_MC[j]<<",";
f<<"};"<<endl;
f<<"double sigmaEtrackinv[30]={";
for (int j=0;j<30;j++) f<<sigma_Track_MC[j]<<",";
f<<"};"<<endl;
f<<"double sigmaETRDinv[30]={";
for (int j=0;j<30;j++) f<<sigma_TRD_MC[j]<<",";
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
f<<"double ETOF[30]={";
for (int j=0;j<30;j++) f<<mean_TOF_D_inv[j]<<",";
f<<"};"<<endl;
f<<"double ETrack[30]={";
for (int j=0;j<30;j++) f<<mean_Track_D_inv[j]<<",";
f<<"};"<<endl;
f<<"double ETRD[30]={";
for (int j=0;j<30;j++) f<<mean_TRD_D_inv[j]<<",";
f<<"};"<<endl;
f<<"TF1 *protons = new TF1(\"f1\",\"((x)^2/0.938^2/(1 + (x)^2/0.938^2))^0.5\",0.1,100);"<<endl;
f<<"TF1 *deutons = new TF1(\"f1\",\"((x)^2/1.875^2/(1 + (x)^2/1.875^2))^0.5\",0,100);"<<endl;
f<<"TF1 *f1RICH = new TF1(\"f1\",\"((x - 3*(0.0615*x+0.002949283*x^2+0.0489))^2/0.9382^2/(1 + (x - 3*(0.0615*x+0.002949283*x^2+0.0489 ))^2/0.9382^2))^0.5 - 3*(9.9e-4*(x^3)/0.9382^2/(22.163375 + x^3/0.9382^2))\",0,100);"<<endl;
f<<"///////////////////////////////////////////////////////"<<endl;
f<<endl;

f<<"////////////// CORREZIONE E.DEP. MC //////////////////"<<endl;
f<<"double CorrTOF[30]={";
for (int j=0;j<30;j++) f<<CorrezioneTOF[j]<<",";
f<<"};"<<endl;
f<<"double CorrTrack[30]={";
for (int j=0;j<30;j++) f<<CorrezioneTrack[j]<<",";
f<<"};"<<endl;
f<<"double CorrTRD[30]={";
for (int j=0;j<30;j++) f<<CorrezioneTRD[j]<<",";
f<<"};"<<endl;
f<<"///////////////////////////////////////////////////////"<<endl;
f<<endl;

f<<"////////////// DEFINIZIONE SPLINES //////////////////"<<endl;
f<<"TSpline3 *Rig = new TSpline3(\"Cubic Spline\",valorecent,sigmaRinv,24);"<<endl;
f<<"TSpline3 *beta = new TSpline3(\"beta\",betacent,sigmabetainv,30);"<<endl;
f<<"TSpline3 *etof = new TSpline3(\"Cubic Spline\",Beta_cent,sigmaEtofinv,30);"<<endl;
f<<"TSpline3 *etrack = new TSpline3(\"Cubic Spline\",Beta_cent,sigmaEtrackinv,30);"<<endl;
f<<"TSpline3 *etrd = new TSpline3(\"Cubic Spline\",Beta_cent,sigmaETRDinv,30);"<<endl;
f<<"TSpline3 *EdepTOFbeta = new TSpline3(\"Cubic Spline\",Beta_cent,ETOF,30);"<<endl;
f<<"TSpline3 *EdepTrackbeta = new TSpline3(\"Cubic Spline\",Beta_cent,ETrack,30);"<<endl;
f<<"TSpline3 *EdepTRDbeta = new TSpline3(\"Cubic Spline\",Beta_cent,ETRD,30);"<<endl;
f<<"TSpline3 *Corr_TOF = new TSpline3(\"Cubic Spline\",Beta_cent,CorrTOF,30);"<<endl;
f<<"TSpline3 *Corr_Track = new TSpline3(\"Cubic Spline\",Beta_cent,CorrTrack,30);"<<endl;
f<<"TSpline3 *Corr_TRD = new TSpline3(\"Cubic Spline\",Beta_cent,CorrTRD,30);"<<endl;
f<<"TSpline3 *Rgenmis = new TSpline3(\"\",R_mis,R_gen,34);"<<endl;
f<<"TSpline3 *CorrRICH = new TSpline3(\"\",R_rich,Corr_rich,25);"<<endl;
f<<"///////////////////////////////////////////////////////"<<endl;
f<<endl;

f<<"void Functions_auto(){}"<<endl;
f.close();
/////////////////////////////////////////////
return 1;
}
