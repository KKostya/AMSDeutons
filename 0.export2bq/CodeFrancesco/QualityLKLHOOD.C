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
#include "../Functions_auto.h"
#include <TMVA/Factory.h>
#include <TMVA/Reader.h>
#include <TMVA/Tools.h>

using namespace std;

float NAnticluster=0;
float Clusterinutili=0;
float ClusterTOFusati=0;
float ClusterTOFtotali=0;
float NTRDSegments=0;
float Massa=0;
float Beta=0;
float Betacorr=0;
float DiffR=0;
float ProbQ=0;
float layernonusati=0;
float residuoX=0;
float residuoY=0;
float fuoriX=0;
float fuoriY=0;
float CaricaTOF=0;
float CaricaTRD=0;
float CaricaTrack=0;
float EdepTOF=0;
float EdepTRD=0;
float EdepTrack=0;
float EdepTOFteo=0;
float R=0;
float probP=0;
float R_corr=0;
float probD=0;
float Chisquare=0;
float Momentogen=0;
float Betagen=0;
float clusterTOFfuori=0;
float clusterTrackfuori=0;
float clusterTRDfuori=0;
float DistTrack=0;
float DistTrack_p=0;
float ThetaTrack=0;
float PhiProjTrack=0;
float BetaRICH=0;
float PhiTrack=0;
float Dist5D=0;
float EdepTOFU=0;
float EdepTOFD=0;
float ThetaTOF=0;
float PhiTOF=0;
float PhiTRD=0;
float ThetaTRD=0;
float Massagen=0;
float LDiscr=0;
float LDiscriminant=0;
float RminTOF=0; float RminTrack=0; float RminTRD=0;
float P_ID=0;
float TOF_Up_Down=0;
float EdepL1=0;
float IsPrescaled=0;
float DiffTrackEdep=0;
float Track_Up_Down=0;
float BDTresponse=0;
float S=0;
float B=0;
float IsCharge1=0;
float Rcutoff=0;
float MassLimit=0.5;
float Cutmask=0;
TMVA::Reader *reader;

void BDTreader();

int main()
{
	TFile *file1 =TFile::Open("../Risultati/Luglio2011/RisultatiMC.root");
	TFile *file2 =TFile::Open("../Risultati/Luglio2011/RisultatiDATI.root");
	TNtuple *ntupla1=(TNtuple*)file1->Get("grandezzequal");
	TNtuple *ntupla2=(TNtuple*)file2->Get("grandezzequal");
	//grandezzequal

	ntupla1->SetBranchAddress("NAnticluster",&NAnticluster);
	ntupla1->SetBranchAddress("NTRDSegments",&NTRDSegments);
	ntupla1->SetBranchAddress("Beta",&Beta);
	ntupla1->SetBranchAddress("R",&R);
	ntupla1->SetBranchAddress("Massa_gen",&Massagen);
	ntupla1->SetBranchAddress("ClusterTOFusati",&ClusterTOFusati);
	ntupla1->SetBranchAddress("ClusterTOFtotali",&ClusterTOFtotali);
	ntupla1->SetBranchAddress("Clusterinutili",&Clusterinutili);
	ntupla1->SetBranchAddress("Cutmask",&Cutmask);
	ntupla1->SetBranchAddress("DiffR",&DiffR);
	ntupla1->SetBranchAddress("ProbQ",&ProbQ);
	ntupla1->SetBranchAddress("layernonusati",&layernonusati);
	ntupla1->SetBranchAddress("residuoX",&residuoX);
	ntupla1->SetBranchAddress("residuoY",&residuoY);
	ntupla1->SetBranchAddress("fuoriX",&fuoriX);
	ntupla1->SetBranchAddress("fuoriY",&fuoriY);
	ntupla1->SetBranchAddress("Chisquare",&Chisquare);
	ntupla1->SetBranchAddress("EdepTOFU",&EdepTOFU);	
	ntupla1->SetBranchAddress("EdepTOFD",&EdepTOFD);
	ntupla1->SetBranchAddress("Dist5D",&Dist5D);
	ntupla1->SetBranchAddress("EdepL1",&EdepL1);
	ntupla1->SetBranchAddress("Track_Up_Down",&Track_Up_Down);
	ntupla1->SetBranchAddress("DiffTrackEdep",&DiffTrackEdep);
	ntupla1->SetBranchAddress("Momentogen",&Momentogen);
	ntupla1->SetBranchAddress("BDT_response",&BDTresponse);

	ntupla2->SetBranchAddress("NAnticluster",&NAnticluster);
	ntupla2->SetBranchAddress("NTRDSegments",&NTRDSegments);
	ntupla2->SetBranchAddress("Beta",&Beta);
	ntupla2->SetBranchAddress("R",&R);
	ntupla2->SetBranchAddress("Rcutoff",&Rcutoff);
	ntupla2->SetBranchAddress("Cutmask",&Cutmask);
	ntupla2->SetBranchAddress("ClusterTOFusati",&ClusterTOFusati);
	ntupla2->SetBranchAddress("ClusterTOFtotali",&ClusterTOFtotali);
	ntupla2->SetBranchAddress("Clusterinutili",&Clusterinutili);
	ntupla2->SetBranchAddress("DiffR",&DiffR);
	ntupla2->SetBranchAddress("ProbQ",&ProbQ);
	ntupla2->SetBranchAddress("layernonusati",&layernonusati);
	ntupla2->SetBranchAddress("residuoX",&residuoX);
	ntupla2->SetBranchAddress("residuoY",&residuoY);
	ntupla2->SetBranchAddress("fuoriX",&fuoriX);
	ntupla2->SetBranchAddress("fuoriY",&fuoriY);
	ntupla2->SetBranchAddress("Chisquare",&Chisquare);
	ntupla2->SetBranchAddress("EdepTOFU",&EdepTOFU);  
	ntupla2->SetBranchAddress("EdepTOFD",&EdepTOFD);
	ntupla2->SetBranchAddress("Dist5D",&Dist5D);
	ntupla2->SetBranchAddress("EdepL1",&EdepL1);
	ntupla2->SetBranchAddress("Track_Up_Down",&Track_Up_Down);
	ntupla2->SetBranchAddress("DiffTrackEdep",&DiffTrackEdep);
	ntupla2->SetBranchAddress("BDT_response",&BDTresponse);


	TCanvas *f=new TCanvas("R vs Rgen (BAD)");
	TCanvas *d=new TCanvas("Distr. R (TOT vs BAD)");
	d->Divide(6,3);
	TCanvas *d_bis=new TCanvas("Distr. Beta (TOT vs BAD)");
	d_bis->Divide(6,3);    
	TCanvas *d_tris=new TCanvas("Sigma distance R vs Beta");
	TCanvas *e=new TCanvas("Distr. Edep. Upper (TOT vs BAD)");
        e->Divide(6,3);
        TCanvas *e_bis=new TCanvas("Distr. Edep. Lower (TOT vs BAD)");
        e_bis->Divide(6,3);
	TCanvas * g1 = new TCanvas("Upper TOF E.dep. vs Beta (TOT vs BAD)");
	TCanvas * g2 = new TCanvas("Tracker E.dep. vs Beta (TOT vs BAD)");
	TCanvas * g3 = new TCanvas("Lower TOF E.dep. vs Beta (TOT vs BAD)");
	TCanvas * d1 = new TCanvas("NoCutoff vs Cutoff");
	TCanvas * d2 = new TCanvas("Template D: Data vs MC");
	TCanvas * d2_bis = new TCanvas("Template P: Data vs MC");
	d1->Divide(6,3);
	d2->Divide(6,3);
	d2_bis->Divide(6,3);
	TCanvas *c1[9];
	TH1F *grafico1[9]; 
	TH1F *grafico2[9]; 
	TH1F *grafico3[9];
	TH1F *RisoluzioniBeta[30];
	TH1F *RisoluzioniR[24];
	TH2F *RvsRgen_bad =new TH2F("","",500,0,5,500,0,5);
	TH2F *RvsRgen_sigma =new TH2F("","",500,0,5,500,0,5);
	TH2F *sigmagen_bad =new TH2F("","",500,0,30,500,0,30);
	for(int i=0;i<RvsRgen_sigma->GetNbinsX();i++)
                        for(int j=0;j<RvsRgen_sigma->GetNbinsY();j++){
                                R=RvsRgen_sigma->GetXaxis()->GetBinCenter(i);
				Momentogen=RvsRgen_sigma->GetYaxis()->GetBinCenter(j);
				if(R<Momentogen-1*pow(Momentogen,2)*Rig->Eval(Momentogen)||R>Momentogen+1*pow(Momentogen,2)*Rig->Eval(Momentogen))
                                                        RvsRgen_sigma->SetBinContent(i,j,1);
				//if(R<Momentogen-2*pow(Momentogen,2)*Rig->Eval(Momentogen)||R>Momentogen+2*pow(Momentogen,2)*Rig->Eval(Momentogen))
                                                        //RvsRgen_sigma->SetBinContent(i,j,2);
				//if(R<Momentogen-3*pow(Momentogen,2)*Rig->Eval(Momentogen)||R>Momentogen+3*pow(Momentogen,2)*Rig->Eval(Momentogen))
                                //                        RvsRgen_sigma->SetBinContent(i,j,3);
				if(R<Momentogen-6*pow(Momentogen,2)*Rig->Eval(Momentogen)||R>Momentogen+6*pow(Momentogen,2)*Rig->Eval(Momentogen))
                                                        RvsRgen_sigma->SetBinContent(i,j,4);

				}
	TH1F *Beta_[18];
	for(int n=0;n<18;n++) Beta_[n] =new TH1F("","",200,-0.5,1);
	TH1F *R_[18];
	for(int n=0;n<18;n++)   R_[n] =new TH1F("","",200,-3,3);
	TH1F *Beta_bad[18];
	for(int n=0;n<18;n++) Beta_bad[n]=new TH1F("","",200,-0.5,1);
	TH1F *R_bad[18];
	for(int n=0;n<18;n++)  R_bad[n]=new TH1F("","",200,-3,3);
	TH1F *Beta_bad_1[18];
	for(int n=0;n<18;n++) Beta_bad_1[n]=new TH1F("","",200,-0.5,1);
	TH1F *R_bad_1[18];
	for(int n=0;n<18;n++)  R_bad_1[n]=new TH1F("","",200,-3,3);
	TH1F *Beta_bad_2[5];
	for(int n=0;n<18;n++) Beta_bad_2[n]=new TH1F("","",200,-0.5,1);
	TH1F *R_bad_2[18];
	for(int n=0;n<18;n++)  R_bad_2[n]=new TH1F("","",200,-3,3);
	TH1F *Mass[18];
        for(int n=0;n<18;n++)  Mass[n]=new TH1F("","",50,0,1);
	TH1F *MassQ[18];
        for(int n=0;n<18;n++)  MassQ[n]=new TH1F("","",50,0,1);
	TH1F *RisoluzioniTOFU[18];
	for(int n=0;n<18;n++) RisoluzioniTOFU[n]=new TH1F("","",150,0,1);
	TH1F *RisoluzioniTOFU_bad[18];
        for(int n=0;n<18;n++) RisoluzioniTOFU_bad[n]=new TH1F("","",150,0,1);
	TH1F *RisoluzioniTOFU_bad_1[18];
        for(int n=0;n<18;n++) RisoluzioniTOFU_bad_1[n]=new TH1F("","",150,0,1);
	TH1F *RisoluzioniTOFD[18];
        for(int n=0;n<18;n++) RisoluzioniTOFD[n]=new TH1F("","",150,0,1);	
	TH1F *RisoluzioniTOFD_bad[18];
        for(int n=0;n<18;n++) RisoluzioniTOFD_bad[n]=new TH1F("","",150,0,1);
	TH1F *RisoluzioniTOFD_bad_1[18];
        for(int n=0;n<18;n++) RisoluzioniTOFD_bad_1[n]=new TH1F("","",150,0,1);
	TH2F * h1=new TH2F("","",1000,0,1,1000,0,15);
        TH2F * h2=new TH2F("","",1000,0,1,1000,0,1);
        TH2F * h3=new TH2F("","",1000,0,1,1000,0,20);
	TH2F * h1_bad=new TH2F("","",1000,0,1,1000,0,15);
        TH2F * h2_bad=new TH2F("","",1000,0,1,1000,0,1);
        TH2F * h3_bad=new TH2F("","",1000,0,1,1000,0,20);

	string Variables[9]={"N. Anti-clusters","Unused TOF Clusters","|Rup-Rdown|:R","Unused Tracker layers","Tracker: Y Hits without X","Track Chi^2","|E.dep(lower TOF) - E.dep(upper TOF)|","|E.dep(layer 2)-E.dep(layer 1)|","|E. dep.(tot)-E.dep.(track)|"};
	grafico1[0]=new TH1F("Anticl",Variables[0].c_str(),10,0,10);
	grafico1[1]=new TH1F("Un. TOF",Variables[1].c_str(),20,0,20);
	grafico1[2]=new TH1F("R Diff.",Variables[2].c_str(),50,0,1);
	grafico1[3]=new TH1F("Un. layers",Variables[3].c_str(),10,0,10);
	grafico1[4]=new TH1F("fuori X",Variables[4].c_str(),10,0,10);
	grafico1[5]=new TH1F("Track Chi^2",Variables[5].c_str(),50,0,25);
	grafico1[6]=new TH1F("TOF Up-Down",Variables[6].c_str(),200,0,100);
	grafico1[7]=new TH1F("Track Up-Down",Variables[7].c_str(),300,0,30);	    
	grafico1[8]=new TH1F("Track Edep: Tot - Track",Variables[8].c_str(),300,0,30);

	grafico2[0]=new TH1F("Anticl-good",Variables[0].c_str(),10,0,10);
	grafico2[1]=new TH1F("Un. TOF-good",Variables[1].c_str(),20,0,20);
	grafico2[2]=new TH1F("R Diff.-good",Variables[2].c_str(),50,0,1);
	grafico2[3]=new TH1F("Un. layers-good",Variables[3].c_str(),10,0,10);
	grafico2[4]=new TH1F("fuori X-good",Variables[4].c_str(),10,0,10);
	grafico2[5]=new TH1F("Track Chi^2-good",Variables[5].c_str(),50,0,25);
	grafico2[6]=new TH1F("TOF Up-Down-good",Variables[6].c_str(),200,0,100);
	grafico2[7]=new TH1F("Track Up-Down-good",Variables[7].c_str(),300,0,30);
	grafico2[8]=new TH1F("Track Edep: Tot - Track-good",Variables[8].c_str(),300,0,30);

	grafico3[0]=new TH1F("Anticl-He",Variables[0].c_str(),10,0,10);
	grafico3[1]=new TH1F("Un. TOF-He",Variables[1].c_str(),20,0,20);
	grafico3[2]=new TH1F("R Diff.-He",Variables[2].c_str(),50,0,1);
	grafico3[3]=new TH1F("Un. layers-He",Variables[3].c_str(),10,0,10);
	grafico3[4]=new TH1F("fuori X-He",Variables[4].c_str(),10,0,10);
	grafico3[5]=new TH1F("Track Chi^2-He",Variables[5].c_str(),50,0,25);
	grafico3[6]=new TH1F("TOF Up-Down-He",Variables[6].c_str(),200,0,100);
	grafico3[7]=new TH1F("Track Up-Down-He",Variables[7].c_str(),300,0,30);
	grafico3[8]=new TH1F("Track Edep: Tot - Track-good-He",Variables[8].c_str(),300,0,30);

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

	float Rcut[17]={0.6,0.6,0.67,0.68,0.7,0.72,0.75,0.8,0.85,1,1.1,1.17,1.22,1.4,1.6,1.7,1.8};
	TF1 *RBeta = new TF1("f1","pow((pow(0.938,2)*(pow(x,2)/(1-pow(x,2)))),0.5)",0.1,0.999999999999999999999999999999);
	TF1 *RBeta_P = new TF1("f1","pow((pow(1.875,2)*(pow(x,2)/(1-pow(x,2)))),0.5)",0.1,0.999999999999999999999999999999);

	TH1F * nocutoff[17];
	TH1F * cutoff[17];
	TH1F * cutoff_P[17];
	TH1F * cutoffMC[17];
	TH1F * cutoffMC_P[17];
	for(int z=0;z<17;z++){
		nocutoff[z] = new TH1F("","",100,0,4);
		cutoff[z] = new TH1F("","",100,0,4);
		cutoff_P[z] = new TH1F("","",100,0,4);
		cutoffMC[z] = new TH1F("","",100,0,4);
		cutoffMC_P[z] = new TH1F("","",100,0,4);
	}

	cout<<"************************************** TRAINING *****************************************************"<<endl;
	int avanzamento=0;
	for(int i=0; i<ntupla1->GetEntries();i++) {
		int k = ntupla1->GetEvent(i);
		if(100*(i/(float)(ntupla1->GetEntries()))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
		Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Beta,2)),0.5)/Beta,2)),0.5);
		IsCharge1=0;
		if(EdepL1>0.04&&EdepL1<0.15) IsCharge1=1;
		//Clusterinutili=ClusterTOFtotali-ClusterTOFusati;
		TOF_Up_Down=fabs(EdepTOFD-EdepTOFU);
		Betagen=(pow(pow(Momentogen/Massagen,2)/(1+pow(Momentogen/Massagen,2)),0.5));
		for(int m=0; m<18;m++) if(Beta>Betabins[m]&&Beta<=Betabins[m+1]&&Massagen<1&&R<4&&R>=0){
			R_[m]->Fill(1/R-1/Momentogen);
			Beta_[m]->Fill(1/Beta-1/Betagen);
			Mass[m]->Fill(1/Massa);
			RisoluzioniTOFU[m]->Fill(1/EdepTOFU);
			RisoluzioniTOFD[m]->Fill(1/EdepTOFD);
			if((1/Massa)<MassLimit){
				R_bad[m]->Fill(1/R-1/Momentogen);
                        	Beta_bad[m]->Fill(1/Beta-1/Betagen);
				RisoluzioniTOFU_bad[m]->Fill(1/EdepTOFU);
                        	RisoluzioniTOFD_bad[m]->Fill(1/EdepTOFD);
			}
		}
		if(Beta<0.75&&Beta>0&&(1/Massa)<MassLimit&&R<4&&R>=0&&IsPrescaled==0&&Massagen<1) {
				RvsRgen_bad->Fill(R,Momentogen);
				if(R<5){
				sigmagen_bad->Fill(fabs(R-Momentogen)/(pow(Momentogen,2)*Rig->Eval(Momentogen)),fabs(Beta-Betagen)/(pow(Beta,2)*beta->Eval(Beta)));
				}
		}
		if(Beta<0.75&&Beta>0&&(1/Massa)<MassLimit&&R<4&&R>=0&&IsPrescaled==0/*&&!(Momentogen<1.2&&R<1.5)*/){ 	
			if(Massagen<1&&Massagen>0.5)
			{
				grafico1[0]->Fill(NAnticluster);
				grafico1[1]->Fill(Clusterinutili);
				grafico1[2]->Fill(DiffR);
				grafico1[3]->Fill(layernonusati);
				grafico1[4]->Fill(fuoriX);
				grafico1[5]->Fill(Chisquare);
				grafico1[6]->Fill(TOF_Up_Down);
				grafico1[7]->Fill(Track_Up_Down);
				grafico1[8]->Fill(DiffTrackEdep);
			}
			if(Massagen<2&&Massagen>1.5)
			{
				grafico2[0]->Fill(NAnticluster);
				grafico2[1]->Fill(Clusterinutili);
				grafico2[2]->Fill(DiffR);
				grafico2[3]->Fill(layernonusati);
				grafico2[4]->Fill(fuoriX);
				grafico2[5]->Fill(Chisquare);
				grafico2[6]->Fill(TOF_Up_Down);
				grafico2[7]->Fill(Track_Up_Down);
				grafico2[8]->Fill(DiffTrackEdep);
			}
			if(Massagen<4.5&&Massagen>2.5&&IsCharge1==1)
			{
				grafico3[0]->Fill(NAnticluster);
				grafico3[1]->Fill(Clusterinutili);
				grafico3[2]->Fill(DiffR);
				grafico3[3]->Fill(layernonusati);
				grafico3[4]->Fill(fuoriX);
				grafico3[5]->Fill(Chisquare);
				grafico3[6]->Fill(TOF_Up_Down);
				grafico3[7]->Fill(Track_Up_Down);
				grafico3[8]->Fill(DiffTrackEdep);
			}

		}

	}

	/////////////////////////////////////////////////
	double X[9][1000];
	double Y[9][1000];
	double Y_2[9][1000];
	TSpline3 *Bkgnd[9]; 
	TSpline3 *Signal[9];

	// NORMALIZZAZIONE IN AREA

	for(int m=0;m<9;m++){
		int f=0;
		float area1=0;
		float area2=0;
		float area3=0;
		int entries1=grafico1[m]->GetEntries();
		int entries2=grafico2[m]->GetEntries();
		int entries3=grafico3[m]->GetEntries();
		cout<<"Tot entries 1: "<<entries1<<endl;
		cout<<"Tot entries 2: "<<entries2<<endl;
		cout<<"Tot entries 3: "<<entries3<<endl;
		cout<<"Bins 1: "<<grafico1[m]->GetNbinsX()<<endl;
		cout<<"Bins 2: "<<grafico2[m]->GetNbinsX()<<endl;
		cout<<"Bins 3: "<<grafico3[m]->GetNbinsX()<<endl;
		for(int i=0;i<=grafico1[m]->GetNbinsX()+1;i++){
			grafico1[m]->SetBinContent(i,grafico1[m]->GetBinContent(i)/(double)entries1);
			area1 = area1 + grafico1[m]->GetBinContent(i);
		}


		for(int i=0;i<=grafico2[m]->GetNbinsX()+1;i++){
			grafico2[m]->SetBinContent(i,grafico2[m]->GetBinContent(i)/(double)entries2);
			area2 = area2 + grafico2[m]->GetBinContent(i);
		}
		for(int i=0;i<=grafico3[m]->GetNbinsX()+1;i++){
			grafico3[m]->SetBinContent(i,grafico3[m]->GetBinContent(i)/(double)entries3);
			area3 = area3 + grafico3[m]->GetBinContent(i);
		}

		cout<<"Area1: "<<area1<<endl;
		cout<<"Area2: "<<area2<<endl;
		cout<<"Area3: "<<area3<<endl;

		////////////////////////////////////////
		///////////// DEFINING PDF ////////////////
		int g=0;
		for(int i=0;i<=grafico1[m]->GetNbinsX();i++){
			if(grafico1[m]->GetBinContent(i)>0){
				X[m][g]=grafico1[m]->GetBinLowEdge(i);
				Y[m][g]=grafico1[m]->GetBinContent(i);
				Y_2[m][g]=grafico2[m]->GetBinContent(i);
				g++;
			}
		}
		cout<<endl;
		Bkgnd[m]= new TSpline3("Cubic Spline",X[m],Y[m],g);
		Signal[m]=new TSpline3("Cubic Spline",X[m],Y_2[m],g);
		///////////////////////////////////////////



		c1[m] = new TCanvas(Variables[m].c_str());
		c1[m]->SetGridx();
		c1[m]->SetGridy();
		//c1[m]->SetLogy();
		c1[m]->cd();
		grafico1[m]->SetBarOffset(0.25);
		/*grafico3[m]->SetBarOffset(1.5);*/
		grafico1[m]->SetBarWidth(0.5);
                grafico2[m]->SetBarWidth(0.5);
		grafico2[m]->GetXaxis()->SetTitle(Variables[m].c_str());
		grafico2[m]->Draw("B");
		grafico1[m]->Draw("B,SAME");
		//grafico3[m]->Draw("SAME");
		grafico1[m]->SetFillColor(2);
		grafico2[m]->SetFillColor(4);
		grafico3[m]->SetFillColor(3);
		grafico3[m]->SetFillStyle(3001);
		Bkgnd[m]->SetLineWidth(2);
		Bkgnd[m]->SetLineColor(2);
	//	Bkgnd[m]->Draw("SAME");
		Signal[m]->SetLineWidth(2);
		Signal[m]->SetLineColor(4);
		//Signal[m]->Draw("SAME");
	}
	cout<<"************************************** TEST *****************************************************"<<endl;
	/////////////LKLHD CALCULATION//////////
	TCanvas *c2=new TCanvas("Likelihood response");
	TCanvas *c2_bis=new TCanvas("Likelihood + Dist. CUT response");
	TCanvas *c4=new TCanvas("BDT response");
	cout<<"Likelihood calculation..."<<endl;
	TH1F *Sl =new TH1F("Signal","Signal",50,0,1);
	TH1F *Bd =new TH1F("Bkgnd","Bkgnd",50,0,1);
	TH1F *He =new TH1F("Bkgnd","Bkgnd",50,0,1);
	TH1F *Sl_BDT =new TH1F("Signal","Signal",50,-1,1);
	TH1F *Bd_BDT =new TH1F("Bkgnd","Bkgnd",50,-1,1);
	TH1F *He_BDT =new TH1F("Bkgnd","Bkgnd",50,-1,1);		
	TH1F *Sl_old =new TH1F("Signal_old","Signal_old",50,0,1);
	TH1F *Bd_old =new TH1F("Bkgnd_old","Bkgnd_old",50,0,1);
	TH1F *He_old =new TH1F("He_old","He_old",50,0,1);
	TH1F *LKL_Data=new TH1F("Lk_Data","Signal",50,0,1);
	TH1F *BDT_Data=new TH1F("BDT_Data","Signal",50,-1,1);
	TH1F *LKLold_Data=new TH1F("Lkold_Data","Signal",50,0,1);
	TH2F *LkvsDist_P=new TH2F("LkvsDist_P","",500,0,1,500,0,100);
	TH2F *LkvsDist_D=new TH2F("LkvsDist_D","",500,0,1,500,0,100);
	float var[9]={0,0,0,0,0,0,0,0,0};
	BDTreader();
	avanzamento=0;
	int qu=0;
	for(int l=0; l<ntupla1->GetEntries();l++) {
		int k = ntupla1->GetEvent(l);
		IsCharge1=1;
		if(EdepL1>0.04&&EdepL1<0.15) IsCharge1=1;
		if(100*(l/(float)(ntupla1->GetEntries()))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
		Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Beta,2)),0.5)/Beta,2)),0.5);
		Betagen=(pow(pow(Momentogen/Massagen,2)/(1+pow(Momentogen/Massagen,2)),0.5));
		//Clusterinutili=fabs(ClusterTOFtotali-ClusterTOFusati);
		TOF_Up_Down=fabs(EdepTOFD-EdepTOFU);
		var[0]=NAnticluster;
		var[1]=Clusterinutili;
		var[2]=DiffR;
		var[3]=layernonusati;
		var[4]=fuoriX;
		var[5]=Chisquare;
		var[6]=TOF_Up_Down;
		var[7]=Track_Up_Down;
		var[8]=DiffTrackEdep;
		double L_true=1;
		double L_false=1;
		double L_true_old=1;
		double L_false_old=1;
		for(int m=0;m<6;m++)
		{
			L_false=L_false*Bkgnd[m]->Eval(var[m]);
			L_true=L_true*Signal[m]->Eval(var[m]);
		}
		for(int m=0;m<6;m++)
		{
			L_false_old=L_false_old*Bkgnd[m]->Eval(var[m]);
			L_true_old=L_true_old*Signal[m]->Eval(var[m]);
		}
		float L_Discr=(L_true/(L_false+L_true));
		float L_Discr_old=(L_true_old/(L_false_old+L_true_old));
		if(Beta<0.8&&Beta>0&&(1/Massa)<MassLimit&&R<4&&R>=0&&IsPrescaled==0&&IsCharge1==1)
		{
			BDTresponse=reader->EvaluateMVA("BDTmethod");
			if(Massagen<1&&Massagen>0.5){	    
				qu++;
				Bd->Fill(L_Discr);
				if(Dist5D<6) Bd_old->Fill(L_Discr_old);
				Bd_BDT->Fill(BDTresponse);
				LkvsDist_P->Fill(L_Discr,Dist5D);
			}
			if(Massagen<2&&Massagen>1.5){
				Sl->Fill(L_Discr);
				if(Dist5D<6) Sl_old->Fill(L_Discr_old);
				Sl_BDT->Fill(BDTresponse);	
				LkvsDist_D->Fill(L_Discr,Dist5D);
			}
			if(Massagen<4&&Massagen>2.5){
				He->Fill(L_Discr);
				if(Dist5D<6) He_old->Fill(L_Discr_old);
				He_BDT->Fill(BDTresponse);
			}

		}
		if(Massagen<1&&Beta<0.75&&(1/Massa)<MassLimit&&R<4&&R>=0){
			h1_bad->Fill(Beta,EdepTOFU);
                	h3_bad->Fill(Beta,EdepTOFD);	
		}
		for(int m=0; m<18;m++) if(Beta>Betabins[m]&&Beta<=Betabins[m+1]&&Massagen<1&&R<4&&R>=0){
                        if(Dist5D<6) MassQ[m]->Fill(1/Massa);
			if((1/Massa)<MassLimit&&L_Discr>0.8&&Dist5D<6){
                                R_bad_1[m]->Fill(1/R-1/Momentogen);
                                Beta_bad_1[m]->Fill(1/Beta-1/Betagen);
				RisoluzioniTOFU_bad_1[m]->Fill(1/EdepTOFU);
                                RisoluzioniTOFD_bad_1[m]->Fill(1/EdepTOFD);
                        }
                }
		
		if(IsCharge1==1&&L_Discr>0.8&&R<4&&R>=0)for(int z=0;z<17;z++) if(Beta>Betabins[z]&&Beta<Betabins[z+1]&&Massagen<2&&Massagen>1.5) cutoffMC[z]->Fill(pow(1/Massa,2));
		if(IsCharge1==1&&L_Discr>0.8&&R<4&&R>=0)for(int z=0;z<17;z++) if(Beta>Betabins[z]&&Beta<Betabins[z+1]&&Massagen<1&&Massagen>0.5) cutoffMC_P[z]->Fill(pow(1/Massa,2));
	}
	avanzamento=0;
	for(int l=0; l<ntupla2->GetEntries();l++) {
		int k = ntupla2->GetEvent(l);
		IsCharge1=0;
		if(EdepL1>0.04&&EdepL1<0.15) IsCharge1=1;
		if(100*(l/(float)(ntupla2->GetEntries()))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
		Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Beta,2)),0.5)/Beta,2)),0.5);
		//Clusterinutili=fabs(ClusterTOFtotali-ClusterTOFusati);
		TOF_Up_Down=fabs(EdepTOFD-EdepTOFU);
		Betagen=(pow(pow(Momentogen/Massagen,2)/(1+pow(Momentogen/Massagen,2)),0.5));
		var[0]=NAnticluster;
		var[1]=Clusterinutili;
		var[2]=DiffR;
		var[3]=layernonusati;
		var[4]=fuoriX;
		var[5]=Chisquare;
		var[6]=TOF_Up_Down;
		var[7]=Track_Up_Down;
		var[8]=DiffTrackEdep;
		double L_true=1;
		double L_false=1;
		double L_true_old=1;
		double L_false_old=1;
		for(int m=0;m<6;m++)
		{
			L_false=L_false*Bkgnd[m]->Eval(var[m]);
			L_true=L_true*Signal[m]->Eval(var[m]);
		}
		for(int m=0;m<6;m++)
		{
			L_false_old=L_false_old*Bkgnd[m]->Eval(var[m]);
			L_true_old=L_true_old*Signal[m]->Eval(var[m]);
		}
		float L_Discr=(L_true/(L_false+L_true));
		float L_Discr_old=(L_true_old/(L_false_old+L_true_old));
		if(Beta<0.75&&(1/Massa)<MassLimit){
			h1->Fill(Beta,EdepTOFU);
                	h3->Fill(Beta,EdepTOFD);
		}
		if(Beta<0.75&&Beta>0&&(1/Massa)<MassLimit&&R<4&&R>=0&&IsPrescaled==0&&IsCharge1==1)
		{
			LKL_Data->Fill(L_Discr);
			if(Dist5D<6) LKLold_Data->Fill(L_Discr_old);
			BDTresponse=reader->EvaluateMVA("BDTmethod");
			BDT_Data->Fill(BDTresponse); 
		}
		if(R>1.2*Rcutoff&&IsCharge1==1&&L_Discr>0.8&&R<4&&R>=0)
			for(int z=0;z<17;z++)
				if(Beta>Betabins[z]&&Beta<Betabins[z+1]) {nocutoff[z]->Fill(1/Massa);
					if(Rcutoff>1.2*RBeta->Eval(Beta)) cutoff[z]->Fill(pow(1/Massa,2));
				}
		if(R<1.2*Rcutoff&&IsCharge1==1&&L_Discr>0.8&&R<4&&R>=0)
			for(int z=0;z<17;z++)
				if(Beta>Betabins[z]&&Beta<Betabins[z+1]) {if(Rcutoff<0.7*RBeta_P->Eval(Beta)&&z<14) cutoff_P[z]->Fill(pow(1/Massa,2));
					if(Rcutoff<0.8*RBeta_P->Eval(Beta)&&z>=14) cutoff_P[z]->Fill(pow(1/Massa,2));	}
	}
	/////////////// DISTR. TOT E BAD //////////////////////
	g1->cd();
	h1->GetXaxis()->SetTitle("Beta TOF");
	h1->GetYaxis()->SetTitle("E. dep. Upper TOF");
	h1->SetTitle("MC protons with D-like Mass over Data");
	h1->Draw();
	h1_bad->SetMarkerColor(2);
	h1_bad->Draw("same");
	g3->cd();
	h3->GetXaxis()->SetTitle("Beta TOF");
        h3->GetYaxis()->SetTitle("E. dep. Lower TOF");
        h3->SetTitle("MC protons with D-like Mass over Data");
        h3->Draw();
        h3_bad->SetMarkerColor(2);
        h3_bad->Draw("same");
	f->cd();
	gPad->SetLogz();
	RvsRgen_bad->GetXaxis()->SetRangeUser(0.55,4.5);
	RvsRgen_bad->GetYaxis()->SetRangeUser(0,4.5);
	RvsRgen_bad->GetXaxis()->SetTitle("R [GV]");
	RvsRgen_bad->GetYaxis()->SetTitle("R gen [GV]");
	RvsRgen_bad->Draw();
	RvsRgen_sigma->SetLineColor(2);
	RvsRgen_sigma->Draw("same,CONT2");
	d_tris->cd();
	gPad->SetLogz();
        sigmagen_bad->GetXaxis()->SetRangeUser(0.55,4.5);
        sigmagen_bad->GetYaxis()->SetRangeUser(0,4.5);
        sigmagen_bad->GetXaxis()->SetTitle("(R-Rgen)/sigma");
        sigmagen_bad->GetYaxis()->SetTitle("(Beta-Betagen)/sigma");
        sigmagen_bad->Draw();

	string Titolo;
	for(int m=0; m<17;m++){
                d->cd(m+1);
                gPad->SetLogy();
                Titolo="Beta TOF: "+TitoliTOF[m]+"-"+TitoliTOF[m+1];
		R_[m]->SetTitle(Titolo.c_str());
		R_[m]->GetXaxis()->SetTitle("1/R_gen-1/R");
		R_bad[m]->SetLineColor(2);
                R_bad_1[m]->SetLineColor(3);
		R_[m]->Draw();
                R_bad[m]->Draw("same");
		//R_bad_1[m]->Draw("same");
        }
        for(int m=0; m<17;m++){
                d_bis->cd(m+1);
                gPad->SetLogy();
		Titolo="Beta TOF: "+TitoliTOF[m]+"-"+TitoliTOF[m+1];
                Beta_[m]->SetTitle(Titolo.c_str());
		Beta_[m]->GetXaxis()->SetTitle("1/Beta_gen-1/Beta");
                Beta_bad[m]->SetLineColor(2);
                Beta_bad_1[m]->SetLineColor(3);
		Beta_[m]->Draw();
                Beta_bad[m]->Draw("same");
		//Beta_bad_1[m]->Draw("same");
        }
	for(int m=0; m<17;m++){
                e->cd(m+1);
                gPad->SetLogy();
                Titolo="Beta TOF: "+TitoliTOF[m]+"-"+TitoliTOF[m+1];
		RisoluzioniTOFU[m]->GetXaxis()->SetTitle("Inverse E. dep.");
                RisoluzioniTOFU[m]->SetTitle(Titolo.c_str());
		RisoluzioniTOFU_bad[m]->SetLineColor(2);
                RisoluzioniTOFU_bad_1[m]->SetLineColor(3);
                RisoluzioniTOFU[m]->Draw();
                RisoluzioniTOFU_bad[m]->Draw("same");
                //RisoluzioniTOFU_bad_1[m]->Draw("same");
        }
        for(int m=0; m<17;m++){
                e_bis->cd(m+1);
                gPad->SetLogy();
		Titolo="Beta TOF: "+TitoliTOF[m]+"-"+TitoliTOF[m+1];
                RisoluzioniTOFD[m]->GetXaxis()->SetTitle("Inverse E. dep.");
		RisoluzioniTOFD[m]->SetTitle(Titolo.c_str());
               	RisoluzioniTOFD_bad[m]->SetLineColor(2);
                RisoluzioniTOFD_bad_1[m]->SetLineColor(3);
                RisoluzioniTOFD[m]->Draw();
                RisoluzioniTOFD_bad[m]->Draw("same");
                //RisoluzioniTOFD_bad_1[m]->Draw("same");
        }

	/////////////// MASSA QUAL ////////////////////////////
	TCanvas *c = new TCanvas("Distribuzioni Massa Inversa");
        c->Divide(6,3);
	TF1 *fitmean;
	TF1 *fitmeanQ;
        for(int m=0; m<18;m++){
                c->cd(m+1);
                gPad->SetLogy();
                Mass[m]->SetLineColor(4);
                MassQ[m]->SetLineColor(2);
		Mass[m]->Draw();
		MassQ[m]->Draw("same");
		fitmean = new TF1("fitmean","gaus");
		fitmean->SetLineColor(4);
		Mass[m]->Fit("fitmean","","",0,1);
		fitmeanQ = new TF1("fitmeanQ","gaus");
                fitmean->SetLineColor(2);
                MassQ[m]->Fit("fitmeanQ","","",0,0.8);
        }

	///////////////////////////////////////////////////////
	/////////////// LK VS DIST ////////////////////////////
	TCanvas *c7_bis=new TCanvas("Likelihood vs Distance");
	c7_bis->cd();
	gPad->SetLogy();
	LkvsDist_P->SetMarkerStyle(7);
	LkvsDist_P->SetMarkerColor(2);
	LkvsDist_D->Draw("col");
	LkvsDist_P->Draw("same");
	/////////////// TEMPLATE FIT //////////////////////////
	c2->cd();
	TObjArray *mc = new TObjArray(2);
	mc->Add(Sl);
	mc->Add(Bd);
	//mc->Add(He); 
	TFractionFitter* fit = new TFractionFitter(LKL_Data, mc);
	/*fit->Constrain(1,0.65,0.7);
	fit->Constrain(2,0.3,0.4);*/
	int status = fit->Fit();
	std::cout << "fit status: " << status << std::endl;
	float pesoP=0;
	float pesoD=0;
	if (status == 0) {                       // check on fit status
		double w1,e1,w2,e2,w3,e3=1;
		fit->GetResult(0,w1,e1);
		fit->GetResult(1,w2,e2);
		//fit->GetResult(2,w3,e3);
		TH1F * result = (TH1F*) fit->GetPlot();
		float itot= result->Integral();
		float i1 = Sl->Integral();
		float i2 = Bd->Integral();
		float i3 = He->Integral();
		cout<<itot<<endl;
		cout<<w1<<" "<<w2<<" "<<w3<<endl;
		pesoP=w2/i2*itot;
		pesoD=w1/i1*itot;
		for(int i=0; i<Sl->GetNbinsX();i++)
			Sl->SetBinContent(i,w1*Sl->GetBinContent(i)/i1*itot);
		for(int i=0; i<Bd->GetNbinsX();i++)
			Bd->SetBinContent(i,w2*Bd->GetBinContent(i)/i2*itot);
		//for(int i=0; i<He->GetNbinsX();i++)
		//	He->SetBinContent(i,w3*He->GetBinContent(i)/i3*itot);
		Sl->SetFillColor(4);
		He->SetFillColor(3);
		Sl->GetXaxis()->SetRangeUser(0,1);	
		Bd->SetFillColor(2);
		//Bd->Draw();
		//Sl->Draw("same");
		//He->Draw("same");
		THStack *hs= new THStack("hs","Likelihood response (stacked)");
		Sl->SetFillStyle(3001);
        	Bd->SetFillStyle(3001);
		hs->Add(Sl);
		hs->Add(Bd);
		//hs->Add(He);        
		LKL_Data->GetXaxis()->SetTitle("Likelihood response");
		LKL_Data->SetMarkerStyle(8);
		LKL_Data->Draw("ep");
		hs->Draw("same");
		result->SetLineColor(5);
		result->Draw("SAME");
	}
	if (status != 0) {
        Sl->SetFillColor(4);
        He->SetFillColor(3);
        Bd->SetFillColor(2);
        Sl->SetFillStyle(3001);
        He->SetFillStyle(3001);
        Bd->SetFillStyle(3001);
        Bd->Draw();
        Sl->Draw("same");
        //He->Draw("same");
        LKL_Data->SetMarkerStyle(8);
        LKL_Data->Draw("epsame");
        }

	c2_bis->cd();
	TH1F *Sl_old_weight =new TH1F("Signal_old","Signal_old",50,0,1);
        TH1F *Bd_old_weight =new TH1F("Bkgnd_old","Bkgnd_old",50,0,1);
	for(int i=0; i<Sl_old->GetNbinsX();i++)
          Sl_old_weight->SetBinContent(i,pesoD*Sl_old->GetBinContent(i));
          for(int i=0; i<Bd_old->GetNbinsX();i++)
          Bd_old_weight->SetBinContent(i,pesoP*Bd_old->GetBinContent(i));

	TObjArray *mc_old = new TObjArray(2);
	  mc_old->Add(Sl_old);
	  mc_old->Add(Bd_old);
	  //mc_old->Add(He_old);	
	  TFractionFitter* fit_old = new TFractionFitter(LKLold_Data, mc_old);
	  /*fit_old->Constrain(1,0.10,0.16);
	  fit_old->Constrain(2,0.03,0.06);
	  fit_old->Constrain(3,0.84,0.90);*/
	  int status_old =  fit_old->Fit();
	  std::cout << "fit status: " << status_old << std::endl;
	  if (status_old == 0) {                       // check on fit status
	  double w1,e1, w2,e2,w3,e3;
	  fit_old->GetResult(0,w1,e1);
	  fit_old->GetResult(1,w2,e2);
	  //fit_old->GetResult(2,w3,e3);	
	  TH1F * result = (TH1F*) fit_old->GetPlot();
	  float itot= result->Integral();
	  float i1 = Sl_old->Integral();
	  float i2 = Bd_old->Integral();
	  //float i3 = He_old->Integral();
	  cout<<itot<<endl;
	  for(int i=0; i<Sl_old->GetNbinsX();i++)
	  Sl_old->SetBinContent(i,w1*Sl_old->GetBinContent(i)/i1*itot);
	  for(int i=0; i<Bd_old->GetNbinsX();i++)
	  Bd_old->SetBinContent(i,w2*Bd_old->GetBinContent(i)/i2*itot);
	  //for(int i=0; i<He_old->GetNbinsX();i++)
	  //He_old->SetBinContent(i,w3*He_old->GetBinContent(i)/i3*itot);	
	  
	  Sl_old->SetFillColor(4);
	  Sl_old->GetXaxis()->SetRangeUser(0,1);
	  Bd_old->SetFillColor(2);
	  He_old->SetFillColor(3);
	  THStack *hs= new THStack("hs","Likelihood + Distance CUT response (stacked)");
	  Sl_old->SetFillStyle(3001);
	  Bd_old->SetFillStyle(3001);	
	  hs->Add(Sl_old);
	  hs->Add(Bd_old);
	  //hs->Add(He_old);
	LKLold_Data->GetXaxis()->SetTitle("Likelihood response");	
	 LKLold_Data->SetMarkerStyle(8); 	
	 LKLold_Data->Draw("ep");
	hs->Draw("same");
	//result->SetLineColor(7);
	//result->Draw("SAME"); 
	 }
	if (status_old != 0) {
        for(int i=0; i<Sl_old->GetNbinsX();i++) Sl_old->SetBinContent(i,pesoD*Sl_old->GetBinContent(i));
	for(int i=0; i<Bd_old->GetNbinsX();i++) Bd_old->SetBinContent(i,pesoP*Bd_old->GetBinContent(i));
	Sl_old->SetFillColor(4);
        He_old->SetFillColor(3);
        Bd_old->SetFillColor(2);
        Sl_old->SetFillStyle(3001);
        //He_old->SetFillStyle(3001);
        Bd_old->SetFillStyle(3001);
        Bd_old->Draw();
        Sl_old->Draw("same");
        //He_old->Draw("same");
        LKLold_Data->SetMarkerStyle(8);
        LKLold_Data->Draw("epsame");
        }

	c4->cd();
	TObjArray *mc_BDT = new TObjArray(2);
	  mc_BDT->Add(Sl_BDT);
	  mc_BDT->Add(Bd_BDT);
	  //mc_BDT->Add(He_BDT);
	  TFractionFitter* fit_BDT = new TFractionFitter(BDT_Data, mc_BDT);
	  int status_BDT = fit_BDT->Fit();
	  std::cout << "fit status: " << status_BDT << std::endl;
	  if (status_BDT == 0) {                       // check on fit status
	  double w1,e1, w2,e2,w3,e3;
	  fit_BDT->GetResult(0,w1,e1);
	  fit_BDT->GetResult(1,w2,e2);
	  //fit_BDT->GetResult(2,w3,e3);
	  TH1F * result = (TH1F*) fit_BDT->GetPlot();
	  float itot= result->Integral();
	  float i1 = Sl_BDT->Integral();
	  float i2 = Bd_BDT->Integral();
	  //float i3 = He_BDT->Integral();
	  cout<<itot<<endl;
	  cout<<w1<<" "<<w2<<" "<<w3<<endl;
	  for(int i=0; i<Sl_BDT->GetNbinsX();i++)
	  Sl_BDT->SetBinContent(i,w1*Sl_BDT->GetBinContent(i)/i1*itot);
	  cout<<i2<<endl;
	  for(int i=0; i<Bd_BDT->GetNbinsX();i++)
	  Bd_BDT->SetBinContent(i,w2*Bd_BDT->GetBinContent(i)/i2*itot);
	  /*for(int i=0; i<He_BDT->GetNbinsX();i++)
	  He_BDT->SetBinContent(i,w3*He_BDT->GetBinContent(i)/i3*itot);*/

	  Sl_BDT->SetFillColor(4);
	  He_BDT->SetFillColor(3);
	Bd_BDT->SetFillColor(2);
	THStack *hs= new THStack("hs","BDT response (stacked)");
	Sl_BDT->SetFillStyle(3001);
        Bd_BDT->SetFillStyle(3001);
	hs->Add(Sl_BDT);
	hs->Add(Bd_BDT);
	//hs->Add(He_BDT);   
	BDT_Data->GetXaxis()->SetTitle("BDT response");
	BDT_Data->SetMarkerStyle(8);
	BDT_Data->Draw("ep");
	hs->Draw("same");
	result->SetLineColor(5);
	result->Draw("SAME"); 
	}
	if (status_BDT != 0) {
	Sl_BDT->SetFillColor(4);
        He_BDT->SetFillColor(3);
	Bd_BDT->SetFillColor(2);
	Sl_BDT->SetFillStyle(3001);
        He_BDT->SetFillStyle(3001);
        Bd_BDT->SetFillStyle(3001);
	Bd_BDT->Draw();
	Sl_BDT->Draw("same");
        He_BDT->Draw("same");
	BDT_Data->SetMarkerStyle(8);
        BDT_Data->Draw("epsame");
	}
	//////////////////////////////////////////
	//////////////////// CUT OPTIMIZATION /////////

	TGraph *RPvsEff = new TGraph();
	RPvsEff->SetTitle("Likelihood (new Variables)");
	TGraph *RPvsEff_old = new TGraph();
	RPvsEff_old->SetTitle("Likelihood (old Variables)");
	TGraph *RPvsEff_BDT = new TGraph();
	RPvsEff_BDT->SetTitle("BDT");
	TGraph *EffvsCut = new TGraph();
	EffvsCut->SetTitle("Likelihood (new Variables)");
	TGraph *EffvsCut_old = new TGraph();
	EffvsCut_old->SetTitle("Likelihood (old Variables)");
	TGraph *EffvsCut_BDT = new TGraph();
	EffvsCut_BDT->SetTitle("BDT");
	TGraph *Ott = new TGraph();
	Ott->SetTitle("Likelihood (new Variables)");
	TGraph *Ott_old = new TGraph();
	Ott_old->SetTitle("Likelihood (old Variables)");
	TGraph *Ott_BDT = new TGraph();    
	Ott_BDT->SetTitle("BDT");
	float efficienza1=0;
	float efficienza2=0;
	float efficienza1_old=0;
	float efficienza2_old=0;
	float efficienza1_BDT=0;
	float efficienza2_BDT=0;
	for(int j=0;j<=Sl->GetNbinsX()+1;j++){
		double taglio=Sl->GetBinCenter(j);
		efficienza1=0;
		efficienza2=0;
		efficienza1=0;
		efficienza1_old=0;
		efficienza2_old=0;
		for(int i=Sl->GetNbinsX(); i>=0;i--)
			if(Sl->GetBinCenter(i)>=taglio) {efficienza1=efficienza1+Sl->GetBinContent(i);efficienza1_old=efficienza1_old+Sl_old_weight->GetBinContent(i); efficienza1_BDT=efficienza1_BDT+Sl_BDT->GetBinContent(i);}
		efficienza1=efficienza1/Sl->Integral();
		efficienza1_old=efficienza1_old/Sl->Integral();
		efficienza1_BDT=efficienza1_BDT/Sl_BDT->Integral();
		for(int i=Bd->GetNbinsX(); i>=0;i--)
			if(Bd->GetBinCenter(i)>=taglio) {efficienza2=efficienza2+Bd->GetBinContent(i);efficienza2_old=efficienza2_old+Bd_old_weight->GetBinContent(i);efficienza2_BDT=efficienza2_BDT+Bd_BDT->GetBinContent(i); }
		efficienza2=1-efficienza2/Bd->Integral();
		efficienza2_old=1-efficienza2_old/Bd->Integral();
		efficienza2_BDT=1-efficienza2_BDT/Bd_BDT->Integral();
		RPvsEff->SetPoint(j,efficienza1,efficienza2);
		RPvsEff_old->SetPoint(j,efficienza1_old,efficienza2_old);
		RPvsEff_BDT->SetPoint(j,efficienza1_BDT,efficienza2_BDT);
		EffvsCut->SetPoint(j,taglio,efficienza1);
		EffvsCut_old->SetPoint(j,taglio,efficienza1_old);
		EffvsCut_BDT->SetPoint(j,taglio,efficienza1_BDT);
		S=efficienza1*Sl->Integral(); B=182.601*(1-efficienza2)*Bd->Integral();
		if(S+B>0) Ott->SetPoint(j,taglio,S/pow(S+B,0.5));
		S=efficienza1_old*Sl_old->Integral(); B=182.601*(1-efficienza2_old)*Bd_old->Integral(); 
		if(S+B>0) Ott_old->SetPoint(j,taglio,S/pow(S+B,0.5));
		S=efficienza1_BDT*Sl_BDT->Integral(); B=182.601*(1-efficienza2_BDT)*Bd_BDT->Integral(); 
		if(S+B>0) Ott_BDT->SetPoint(j,taglio,S/pow(S+B,0.5));  
	}
	RPvsEff->GetXaxis()->SetTitle("Efficiency");
	RPvsEff->GetYaxis()->SetTitle("Background rejection");
	RPvsEff->SetLineColor(2);
	RPvsEff->SetLineWidth(2);
	RPvsEff_old->SetLineColor(4);
	RPvsEff_old->SetLineWidth(1);
	RPvsEff_BDT->SetLineColor(3);
	RPvsEff_BDT->SetLineWidth(2);
	EffvsCut->GetXaxis()->SetTitle("Cut");
	EffvsCut->GetYaxis()->SetTitle("Efficiency");
	EffvsCut->SetLineColor(2);
	EffvsCut->SetLineWidth(2);
	EffvsCut_old->SetLineColor(4);
	EffvsCut_old->SetLineWidth(1);
	EffvsCut_BDT->SetLineColor(3);
	EffvsCut_BDT->SetLineWidth(2);
	Ott->GetXaxis()->SetTitle("Cut");
	Ott->GetYaxis()->SetTitle("Significance (S/sqrt(S+B))");
	Ott->SetLineColor(2);
	Ott->SetLineWidth(2);
	Ott_old->SetLineColor(4);
	Ott_old->SetLineWidth(1);
	Ott_BDT->SetLineColor(3);
	Ott_BDT->SetLineWidth(2);
	RPvsEff->GetXaxis()->SetRangeUser(-1,1);
	RPvsEff->GetYaxis()->SetRangeUser(0.6,1);
	EffvsCut->GetXaxis()->SetRangeUser(-1,1);
	Ott->GetXaxis()->SetRangeUser(-1,1);
	Ott->GetYaxis()->SetRangeUser(0.1,200);
	TCanvas *c3=new TCanvas("R.P. vs Eff");
	c3->cd();
	c3->SetGridx();
	c3->SetGridy();
	RPvsEff->Draw("AL");
	RPvsEff_old->Draw("SAME");
	RPvsEff_BDT->Draw("SAME");
	TCanvas *c5=new TCanvas("Eff vs Cut");
	c5->cd();
	c5->SetGridx();
	c5->SetGridy();
	EffvsCut->Draw("AL");
	EffvsCut_old->Draw("SAME");
	EffvsCut_BDT->Draw("SAME");
	TCanvas *c6=new TCanvas("Cut Optimization");
	c6->cd();
	c6->SetGridx();
	c6->SetGridy();
	c6->SetLogy();
	Ott->Draw("AL");
	Ott_old->Draw("SAME");
	Ott_BDT->Draw("SAME");
	//////////////////////////////////////////////
	////////CUTOFF PLOTS////////////
	for(int z=0;z<17;z++){
		d1->cd(z+1);
		gPad->SetLogy();
		nocutoff[z]->Draw();
		cutoff[z]->Draw("same");
		d2->cd(z+1);
		gPad->SetLogy();

		for(int i=0;i<cutoff[z]->GetNbinsX();i++){
			cutoffMC[z]->SetBinContent(i,cutoff[z]->GetEntries()*(cutoffMC[z]->GetBinContent(i)/(double)cutoffMC[z]->GetEntries()));
		}


		cutoff[z]->SetMarkerStyle(8);
		cutoff[z]->SetMarkerSize(2);
		cutoff[z]->Draw("epsame");
		cutoffMC[z]->SetFillStyle(3001);
		cutoffMC[z]->SetLineWidth(2);
		cutoffMC[z]->SetLineColor(4);
		cutoffMC[z]->SetFillColor(4);
		cutoffMC[z]->Draw("same");
		//     TF1 *g3=new TF1("g3","gaus",0,120);	
		//     cutoff[z]->Fit("g3");
	}

	for(int z=0;z<17;z++){
		d2_bis->cd(z+1);
		gPad->SetLogy();

		for(int i=0;i<cutoff_P[z]->GetNbinsX();i++){
			cutoffMC_P[z]->SetBinContent(i,cutoff_P[z]->GetEntries()*(cutoffMC_P[z]->GetBinContent(i)/(double)cutoffMC_P[z]->GetEntries()));
		}


		cutoff_P[z]->SetMarkerStyle(8);
		cutoff_P[z]->Draw("epsame");
		cutoffMC_P[z]->SetFillStyle(3001);
		cutoffMC_P[z]->SetLineWidth(2);
		cutoffMC_P[z]->SetLineColor(4);
		cutoffMC_P[z]->SetFillColor(2);
		cutoffMC_P[z]->Draw("same");
		//     TF1 *g3=new TF1("g3","gaus",0,120);  
		//         //     cutoff[z]->Fit("g3");
	}

	////////////////////////////////
	/////////OUTPUT////////////
	string nomefile="./QualityVariables.root";
	TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
	f_out->mkdir("Bad Events Study");
	f_out->mkdir("Variables");
	f_out->mkdir("Distributions");
	f_out->mkdir("Performances");
	f_out->mkdir("Cutoff Templates");
	f_out->mkdir("Splines");
	f_out->cd("Variables");
	for(int m=0;m<9;m++) {c1[m]->Write();}
	f_out->cd("Bad Events Study");
	g1->Write();
	g3->Write();
	f->Write();
        d->Write();
        d_bis->Write();
        d_tris->Write();
	e->Write();
        e_bis->Write();
	f_out->cd("Distributions");
	c2->Write();
	c2_bis->Write();
	c4->Write();
	f_out->cd("Performances");
	c3->Write();
	c5->Write();
	c6->Write();
	c7_bis->Write();
	c->Write();
	f_out->cd("Cutoff Templates");
	d1->Write();
        d2->Write();
        d2_bis->Write();
	f_out->cd("Splines");
	string nome;
	string Spline="Spline: ";
	string signal="_SGNL";
	string bkgnd="_BKGND";
	for(int m=0;m<9;m++) {
		nome=Spline+Variables[m]+bkgnd;	 
		Bkgnd[m]->Write(nome.c_str());
		nome=Spline+Variables[m]+signal;
		Signal[m]->Write(nome.c_str());
	}
	f_out->Write();
	f_out->Close();
	////////////////////////////
	return 1;
}


void BDTreader()
{
        TMVA::Tools::Instance();
        reader = new TMVA::Reader( "V:Color:!Silent" );
        reader->AddVariable("NAnticluster", &NAnticluster);
        reader->AddVariable("Chisquare",&Chisquare);
        reader->AddVariable("layernonusati",&layernonusati);
        reader->AddVariable("NTofUsed := NTofClusters - NTofClustersusati",&Clusterinutili);
        reader->AddVariable("diffR := TMath::Abs(Rup-Rdown)/R",&DiffR);
        reader->AddVariable("TOF_Up_Down := TMath::Abs(Endep[2]+Endep[3]-Endep[0]-Endep[1])", &TOF_Up_Down);

        reader->BookMVA("BDTmethod", "../TMVA/QualityBDT_BDT.weights.xml");
}

