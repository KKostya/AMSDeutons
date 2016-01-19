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
#include "TGraphAsymmErrors.h"
#include "../Functions_auto.h"

using namespace std;

float R=0;
float Beta=0;
float BetaRICH=0;
float RminTOF=0;
float RminTrack=0;
float RminTRD=0;
float X=0;
float XTrack=0;
float XTRD=0;
float YTOFU=0;
float YTrack=0;
float YTOFD=0;
float LDiscriminant=0;
float Massagen=0;
float Massa=0;
float BDT_response=0;
float D_TOF,D_Track,D_TRD,Discr=0;
float Zona=0;
int CUTMASK=0;
float Cutmask=0;
float IsPrescaled=0;
float Latitude=0;
float EdepL1=0;
float Dist5D=0;
float Dist5D_P=0;
int fraz=1;
float Rcutoff=0;
double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};

int main(){
	TFile *file1 =TFile::Open("../Risultati/Dicembre2011/RisultatiMC.root");
	TFile *file2 =TFile::Open("../Risultati/Dicembre2011/RisultatiDATI.root");
	TNtuple *ntupla1=(TNtuple*)file1->Get("grandezzesepd");	
	TNtuple *ntupla2=(TNtuple*)file2->Get("grandezzesepd");
	
	ntupla1->SetBranchAddress("R",&R);
	ntupla1->SetBranchAddress("Beta",&Beta);
	ntupla1->SetBranchAddress("EdepL1",&EdepL1);
	ntupla1->SetBranchAddress("YTOFU",&YTOFU);
	ntupla1->SetBranchAddress("YTrack",&YTrack);
	ntupla1->SetBranchAddress("YTOFD",&YTOFD);
	ntupla1->SetBranchAddress("LDiscriminant",&LDiscriminant);
	ntupla1->SetBranchAddress("BDT_response",&BDT_response);
	ntupla1->SetBranchAddress("Cutmask",&Cutmask);
	ntupla1->SetBranchAddress("Dist5D",&Dist5D);
	ntupla1->SetBranchAddress("Dist5D_P",&Dist5D_P);
	ntupla1->SetBranchAddress("Massagen",&Massagen);
	
	ntupla2->SetBranchAddress("R",&R);
        ntupla2->SetBranchAddress("Beta",&Beta);
        ntupla2->SetBranchAddress("EdepL1",&EdepL1);
        ntupla2->SetBranchAddress("YTOFU",&YTOFU);
        ntupla2->SetBranchAddress("YTrack",&YTrack);
        ntupla2->SetBranchAddress("YTOFD",&YTOFD);
        ntupla2->SetBranchAddress("LDiscriminant",&LDiscriminant);
        ntupla2->SetBranchAddress("BDT_response",&BDT_response);
        ntupla2->SetBranchAddress("Cutmask",&Cutmask);
        ntupla2->SetBranchAddress("Dist5D",&Dist5D);
	ntupla2->SetBranchAddress("Dist5D_P",&Dist5D_P);	
	ntupla2->SetBranchAddress("Rcutoff",&Rcutoff);

	TH1F * MassP=new TH1F("","",80,0,3);
	TH1F * MassD=new TH1F("","",80,0,3);
	TH1F * Massdata=new TH1F("","",80,0,3);
	TH1F * MassPBDT=new TH1F("","",80,0,3);
	TH1F * MassDBDT=new TH1F("","",80,0,3);	
	TH1F * MassdataBDT=new TH1F("","",80,0,3);	
	TH1F * MassPDiscr=new TH1F("","",80,-1,1);
        TH1F * MassDDiscr=new TH1F("","",80,-1,1);
        TH1F * MassdataDiscr=new TH1F("","",80,-1,1);	
	//TF1 *RBeta = new TF1("f1","(0.938^2*(x^2/(1-x^2)))^0.5",0.1,0.999999999999999999999999999999);

	cout<<"************************************ LETTURA MC ***************************************************"<<endl;
	float avanzamento=0;
	float Discr=0;
	for(int i=0; i<ntupla1->GetEntries()/fraz;i++) {
		int k = ntupla1->GetEvent(i);
		if(100*(i/(float)(ntupla1->GetEntries()/fraz))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
		Discr=(Dist5D-Dist5D_P)/(Dist5D+Dist5D_P);
		if(Beta>0&&Beta<0.8&&R>0&&R<3.55&&EdepL1>0.04&&EdepL1<0.15){
			if(Massagen<1) {
				if(LDiscriminant>0.8) MassP->Fill(1/((R/Beta)*pow((1-pow(Beta,2)),0.5)));
				if(BDT_response>0.22) MassPBDT->Fill(1/((R/Beta)*pow((1-pow(Beta,2)),0.5)));
				if(LDiscriminant>0.8)  MassPDiscr->Fill(Discr);
			}
			if(Massagen>1) {
				if(LDiscriminant>0.8) MassD->Fill(1/((R/Beta)*pow((1-pow(Beta,2)),0.5)));
				if(BDT_response>0.22) MassDBDT->Fill(1/((R/Beta)*pow((1-pow(Beta,2)),0.5)));
				if(LDiscriminant>0.8)MassDDiscr->Fill(Discr);
			}
		}
	}
	cout<<"************************************ LETTURA DATI ***************************************************"<<endl;
	avanzamento=0;
        for(int i=0; i<ntupla2->GetEntries()/fraz;i++) {
                int k = ntupla2->GetEvent(i);
                if(100*(i/(float)(ntupla2->GetEntries()/fraz))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
                Discr=(Dist5D-Dist5D_P)/(Dist5D+Dist5D_P);
		if(Beta>0&&Beta<0.8&&R>0&&R<3.5&&EdepL1>0.04&&EdepL1<0.15/*RBeta->Eval(Beta)*/){
                                if(LDiscriminant>0.8) Massdata->Fill(1/((R/Beta)*pow((1-pow(Beta,2)),0.5)));
                                if(BDT_response>0.22) MassdataBDT->Fill(1/((R/Beta)*pow((1-pow(Beta,2)),0.5)));
				if(LDiscriminant>0.8) MassdataDiscr->Fill(Discr);
                }
        }
	
	cout<<"************************************ TEMPLATE FIT ***************************************************"<<endl;
	MassP->SetFillColor(2);
	MassD->SetFillColor(4);
	cout<<"cwe"<<endl;
	THStack *Y=new THStack("","");
	{   
		TH1F *ResultMass;
		TObjArray *Mass = new TObjArray(2);
		Mass->Add(MassP);
		Mass->Add(MassD);
		TFractionFitter* fit = new TFractionFitter(Massdata, Mass,"q");
		int s=fit->Fit();
		std::cout << "fit status: " << s << std::endl;
		double w1,w2,w3=1;
		double e1,e2,e3=1;
		if(s==0){
			fit->GetResult(0,w1,e1);
			fit->GetResult(1,w2,e2);
			cout<<w1<<" "<<w2<<" "<<w3<<endl;
			ResultMass = (TH1F*) fit->GetPlot();
			float itot= ResultMass->Integral();
			float i1 = MassP->Integral();
			float i2 = MassD->Integral();
			if(i1>0) for(int i=0; i<MassP->GetNbinsX();i++) MassP->SetBinContent(i,w1*MassP->GetBinContent(i)/i1*itot);
			if(i2>0) for(int i=0; i<MassD->GetNbinsX();i++) MassD->SetBinContent(i,w2*MassD->GetBinContent(i)/i2*itot);
			Y->Add(MassP);
			Y->Add(MassD);
		}
		if(s!=0){
			MassP->SetFillStyle(3001);
			MassD->SetFillStyle(3001);
			Y->Add(MassP);
			Y->Add(MassD);
		}

	}

	MassPBDT->SetFillColor(2);
        MassDBDT->SetFillColor(4);
        cout<<"cwe"<<endl;
        THStack *YBDT=new THStack("","");
        {
                TH1F *ResultMassBDT;
                TObjArray *MassBDT = new TObjArray(2);
                MassBDT->Add(MassPBDT);
                MassBDT->Add(MassDBDT);
                TFractionFitter* fit = new TFractionFitter(MassdataBDT, MassBDT,"q");
                int s=fit->Fit();
                std::cout << "fit status: " << s << std::endl;
                double w1,w2,w3=1;
                double e1,e2,e3=1;
                if(s==0){
                        fit->GetResult(0,w1,e1);
                        fit->GetResult(1,w2,e2);
                        cout<<w1<<" "<<w2<<" "<<w3<<endl;
                        ResultMassBDT = (TH1F*) fit->GetPlot();
                        float itot= ResultMassBDT->Integral();
                        float i1 = MassPBDT->Integral();
                        float i2 = MassDBDT->Integral();
                        if(i1>0) for(int i=0; i<MassPBDT->GetNbinsX();i++) MassPBDT->SetBinContent(i,w1*MassPBDT->GetBinContent(i)/i1*itot);
                        if(i2>0) for(int i=0; i<MassDBDT->GetNbinsX();i++) MassDBDT->SetBinContent(i,w2*MassDBDT->GetBinContent(i)/i2*itot);
                        YBDT->Add(MassPBDT);
                        YBDT->Add(MassDBDT);
                }
                if(s!=0){
                        MassPBDT->SetFillStyle(3001);
                        MassDBDT->SetFillStyle(3001);
                        YBDT->Add(MassPBDT);
                        YBDT->Add(MassDBDT);
                }

        }
	MassPDiscr->SetFillColor(2);
        MassDDiscr->SetFillColor(4);
        cout<<"cwe"<<endl;
        THStack *YDiscr=new THStack("","");
        {
                TH1F *ResultMassDiscr;
                TObjArray *MassDiscr = new TObjArray(2);
                MassDiscr->Add(MassPDiscr);
                MassDiscr->Add(MassDDiscr);
                TFractionFitter* fit = new TFractionFitter(MassdataDiscr, MassDiscr,"q");
                int s=fit->Fit();
                std::cout << "fit status: " << s << std::endl;
                double w1,w2,w3=1;
                double e1,e2,e3=1;
                if(s==0){
                        fit->GetResult(0,w1,e1);
                        fit->GetResult(1,w2,e2);
                        cout<<w1<<" "<<w2<<" "<<w3<<endl;
                        ResultMassDiscr = (TH1F*) fit->GetPlot();
                        float itot= ResultMassDiscr->Integral();
                        float i1 = MassPDiscr->Integral();
                        float i2 = MassDDiscr->Integral();
                        if(i1>0) for(int i=0; i<MassPDiscr->GetNbinsX();i++) MassPDiscr->SetBinContent(i,w1*MassPDiscr->GetBinContent(i)/i1*itot);
                        if(i2>0) for(int i=0; i<MassDDiscr->GetNbinsX();i++) MassDDiscr->SetBinContent(i,w2*MassDDiscr->GetBinContent(i)/i2*itot);
                        YDiscr->Add(MassPDiscr);
                        YDiscr->Add(MassDDiscr);
                }
                if(s!=0){
                        MassPDiscr->SetFillStyle(3001);
                        MassDDiscr->SetFillStyle(3001);
                        YDiscr->Add(MassPDiscr);
                        YDiscr->Add(MassDDiscr);
                }

        }

	TGraph *ContvsCut = new TGraph();
	TGraph *ContvsCutBDT = new TGraph();
	TGraph *ContvsCutDiscr = new TGraph();
	ContvsCut->SetTitle("Protons Contamination vs Cut");
	float efficienza1=0;float efficienza2=0; float efficienza1BDT=0;float efficienza2BDT=0; float efficienza1Discr=0;float efficienza2Discr=0;
	int g=0; int h=0; int l=0;
	for(int j=0;j<=MassP->GetNbinsX()+1;j++){
		efficienza1=0;
		efficienza2=0;
		efficienza1BDT=0;
		efficienza2BDT=0;
		efficienza1Discr=0;
                efficienza2Discr=0;
		double taglio=MassP->GetBinCenter(j);
		for(int i=0;i<MassP->GetNbinsX(); i++)
			if(MassP->GetBinCenter(i)<=taglio) {efficienza1=efficienza1+MassP->GetBinContent(i);}
		for(int i=0;i<MassD->GetNbinsX();i++)
			if(MassD->GetBinCenter(i)<=taglio) {efficienza2=efficienza2+MassD->GetBinContent(i);}
		for(int i=0;i<MassPBDT->GetNbinsX(); i++)
			if(MassPBDT->GetBinCenter(i)<=taglio) {efficienza1BDT=efficienza1BDT+MassPBDT->GetBinContent(i);}
		for(int i=0;i<MassDBDT->GetNbinsX();i++)
			if(MassDBDT->GetBinCenter(i)<=taglio) {efficienza2BDT=efficienza2BDT+MassDBDT->GetBinContent(i);}
		if(efficienza2>0&&efficienza1>0) {ContvsCut->SetPoint(g,efficienza2/MassD->Integral(),1-efficienza1/MassP->Integral());g++;}
                if(efficienza2BDT>0&&efficienza1BDT>0) {ContvsCutBDT->SetPoint(h,efficienza2BDT/MassDBDT->Integral(),1-efficienza1BDT/MassPBDT->Integral());h++;}
		taglio=MassPDiscr->GetBinCenter(j);
		for(int i=0;i<MassPDiscr->GetNbinsX(); i++)
                        if(MassPDiscr->GetBinCenter(i)<=taglio) {efficienza1Discr=efficienza1Discr+MassPDiscr->GetBinContent(i);}
                for(int i=0;i<MassDDiscr->GetNbinsX();i++)
                        if(MassDDiscr->GetBinCenter(i)<=taglio) {efficienza2Discr=efficienza2Discr+MassDDiscr->GetBinContent(i);}

		if(efficienza2Discr>0&&efficienza1Discr>0) {ContvsCutDiscr->SetPoint(l,efficienza2Discr/MassDDiscr->Integral(),1-efficienza1Discr/MassPDiscr->Integral());l++;}
	}


	TCanvas *c1 = new TCanvas("Invers Mass Distribution");
	c1->cd();
	Y->Draw();
	Massdata->Draw("epsame");
	
	TCanvas *c3 = new TCanvas("Invers Mass Distribution - BDT");
        c3->cd();
        YBDT->Draw();
        MassdataBDT->Draw("epsame");

	TCanvas *c4 = new TCanvas("Distance Discriminant Distribution");
        c4->cd();
        YDiscr->Draw();
        MassdataDiscr->Draw("epsame");

	TCanvas *c2 = new TCanvas("Contamination");
	c2->cd();	
	ContvsCut->SetLineColor(2);
	ContvsCut->SetLineWidth(2);
	ContvsCutBDT->SetLineColor(3);
	ContvsCutBDT->SetLineWidth(2);
	ContvsCutDiscr->SetLineColor(4);
        ContvsCutDiscr->SetLineWidth(2);
	ContvsCut->GetXaxis()->SetRangeUser(0,1);
	ContvsCut->GetYaxis()->SetRangeUser(0,1);
	ContvsCutDiscr->Draw("APL");
	ContvsCutBDT->Draw("PLsame");
	ContvsCut->Draw("PLsame");
	cout<<"**************************************************************************************** OUTPUT *****************************************************************************************"<<endl;
	string nomefile="./MassWindow.root";
	TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
	c1->Write();
	c3->Write();
	c4->Write();
	c2->Write();
	f_out->Write();
	f_out->Close();

}
