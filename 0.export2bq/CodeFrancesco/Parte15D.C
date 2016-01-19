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
#include "Functions_auto.h"

using namespace std;

float R=0;
float Beta=0;
float BetaRICH=0;
float Rmin=0;
float X=0;
float YTOFU=0;
float YTrack=0;
float YTOFD=0;
float Rcutoff=0;
float LDiscriminant=0;
float Massa=0;
float BDT_response=0;
float D_TOF,D_Track,D_TRD,Discr=0;
float Zona=0;
int CUTMASK=0;
float Cutmask=0;
float Massagen=0;
float IsPrescaled=0;
float Latitude=0;
float EdepL1=0;
float Dist5D=0;
float Dist5D_P=0;

double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};
int fraz=1;
int avanzamento=0;

TH1F * Esposizione[11];
string numero[11]={"0","1","2","3","4","5","6","7","8","9","10"};
float Rcut[11]={18,18,16,14,12,10,8,6,4,2,1};
string tagli[10]={"Trigger","3of4 TOF","TRD Segments","Rigidity exists","Chi^2 R","Matching TOF","Matching TRD","In TRD Accept.","1 Particle","1 Tr. Track"};
string nome;
float DXWind[43];


TH1F * EffDistMCP = new TH1F("EffDistMCP","EffDistMCP",43,0,43);
TH1F * EffQualMCP = new TH1F("EffQualMCP","EffQualMCP",43,0,43);
TH1F * EffDistMCP_Beta = new TH1F("EffDistMCP_Beta","EffDistMCP_Beta",18,0,18);
TH1F * EffQualMCP_Beta = new TH1F("EffQualMCP_Beta","EffQualMCP_Beta",18,0,18);

int main()

{


	for(int i=0;i<11;i++) {
		nome="Esposizione"+numero[i];
		Esposizione[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
	}

	cout<<"**************************** R BINS ***********************************"<<endl;
	float bin[44];
	float R_cent[43];
	float encinprot[43];
	float encindeut[43];
	float deltaencinprot[42];
	float deltaencindeut[42];
	for(int i=0;i<44;i++)
	{
		float temp=i+14;
		bin[i]=0.1*pow(10,temp/(9.5*2));
		if(i<43) {R_cent[i]=0.1*pow(10,(temp+0.5)/(9.5*2));
			encindeut[i]=pow(((1+pow((R_cent[i]/1.875),2))),0.5)-1;
			encinprot[i]=pow(((1+pow((R_cent[i]/0.938),2))),0.5)-1;
		}
		cout<<bin[i]<<endl;
	}

	for(int i=0;i<42;i++) {
		deltaencinprot[i]=encinprot[i+1]-encinprot[i];
		deltaencindeut[i]=encindeut[i+1]-encindeut[i];
	}
	cout<<"**************************** BETA BINS ***********************************"<<endl;
	float B=0.4;
	float B1=0;
	float B2=0;
	float E=0.1;
	int binnum=1;
	float a=(log(0.9)-log(0.1))/18;
	float E2=exp(log(0.1)+1.5*a);
	float Betabins[18]={0};
	float Betacent[18]={0};
	float encinbeta[18]={0};
	while(B<0.825){
		B=B+2*(pow(B,2)*beta->Eval(B));
		E=exp(log(0.1)+binnum*a);
		E2=exp(log(0.1)+(binnum+0.5)*a);
		B1=sqrt(1-1/(pow(E+1,2)));
		B2=sqrt(1-1/(pow(E2+1,2)));
		cout<<B<<" "<<binnum<<" "<<B1<<" "<<B2<<endl;
		Betabins[binnum-1]=B1;
		Betacent[binnum-1]=B2;
		encinbeta[binnum-1]=1/pow(1-pow(Betacent[binnum-1],2),0.5)-1;
		binnum++;
	}

	float avanzamento=0;
	float fraz=1;
	float Q=0;
	float temp=0;
	int Zona=0;
	int UnbiasPre=9;
	int effpreselMCP1[18]={0};
	int effpreselMCP2[18]={0};
	int effpreselMCD1[18]={0};
	int effpreselMCD2[18]={0};
	int effpreselMCP1_R[43]={0};
	int effpreselMCP2_R[43]={0};
	int effpreselMCD1_R[43]={0};
	int effpreselMCD2_R[43]={0};
	float tempi[11]={0};
	float Esposizionegeo[43][11]={{0}};
	int notpassed[10]={1022,1021,955,1,1007,799,959,799,187,187};
	float DistTOF,DistTrack,DistTRD=0;

	TFile *file1 =TFile::Open("./Risultati/Marzo2012/RisultatiMC.root");
	//TFile *file2 =TFile::Open("/home/AMS/fdimicco/fdimicco/Risultati/Giugno2011/RisultatiDATI.root");
	TNtuple *ntupla1=(TNtuple*)file1->Get("grandezzesepd");

	TH1F * PrescaledMC = new TH1F("PrescaledMC","PrescaledMC",43,0,43);
        TH1F * EffpreselMCP1= (TH1F*) file1->Get("efficienzagenbeta_P");
        TH2F * EffpreselMCD1= (TH2F*) file1->Get("efficienzagenbeta_D");
        TH1F * EffpreselMCP2= (TH1F*) file1->Get("preselectedbeta_P");
        TH2F * EffpreselMCD2= (TH2F*) file1->Get("preselectedbeta_D");
        TH1F * EffpreselMCP1_R =(TH1F*) file1->Get("tempi0");
        TH2F * EffpreselMCD1_R =(TH2F*) file1->Get("tempi0_D");
        TH1F * EffpreselMCP2_R =(TH1F*) file1->Get("preselezionate0");
        TH2F * EffpreselMCD2_R =(TH2F*) file1->Get("preselezionateD");
	//TH1F * Tempi=(TH1F*) file2->Get("Tempi");
	//TH2F * esposizionegeo  =(TH2F*) file2->Get("esposizionegeo");
	//for(int i=0;i<11;i++) for(int j=0;j<43;j++) Esposizione[i]->SetBinContent(j+1,esposizionegeo->GetBinContent(j+1,i)/(float)fraz);

	ntupla1->SetBranchAddress("R",&R);
        ntupla1->SetBranchAddress("Beta",&Beta);
        ntupla1->SetBranchAddress("EdepL1",&EdepL1);
        ntupla1->SetBranchAddress("Rmin",&Rmin);
        ntupla1->SetBranchAddress("X",&X);
        ntupla1->SetBranchAddress("YTOFU",&YTOFU);
        ntupla1->SetBranchAddress("YTrack",&YTrack);
        ntupla1->SetBranchAddress("YTOFD",&YTOFD);
        ntupla1->SetBranchAddress("LDiscriminant",&LDiscriminant);
        ntupla1->SetBranchAddress("BDT_response",&BDT_response);
        ntupla1->SetBranchAddress("Cutmask",&Cutmask);
	ntupla1->SetBranchAddress("Dist5D",&Dist5D);
	ntupla1->SetBranchAddress("Dist5D_P",&Dist5D_P);	
	
	cout<<"*********************** LETTURA MC *********************"<<endl;
	for(int i=0; i<ntupla1->GetEntries()/fraz;i++) {
        	int k = ntupla1->GetEvent(i);
        	if(100*(i/(float)(ntupla1->GetEntries()/fraz))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
		
		if((((int)Cutmask>>22)&1)==1) Massagen=0.938;
		for(int g=0;g<6;g++){
			if((((int)Cutmask>>(23+g))&1)==1) Massagen=(18570+g)/10000.;
		}
		
		if(Massagen<1){
                        if(Dist5D_P<4) {
					for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffDistMCP->Fill(K);}
					for(int m=0;m<18;m++) if(Beta<Betabins[m+1]&&Beta>Betabins[m]) EffDistMCP_Beta->Fill(m);
				     }	
                        if(LDiscriminant>0.8){ 
					for(int K=0;K<43;K++) if(R<bin[K+1]&&R>bin[K]) {EffQualMCP->Fill(K);}
					for(int m=0;m<18;m++) if(Beta<Betabins[m+1]&&Beta>Betabins[m]) EffQualMCP_Beta->Fill(m);
				     }
		}
	}

	cout<<"************************ OUTPUT ************************"<<endl;
	string nomefile="./Parte1.root";
	TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
	//Tempi->Write();
	PrescaledMC->Write();
	EffpreselMCP1->Write();
	EffpreselMCP2->Write();
	EffpreselMCP1_R->Write();
	EffpreselMCP2_R->Write();
	EffpreselMCD1->Write();
	EffpreselMCD2->Write();
	EffpreselMCD1_R->Write();
	EffpreselMCD2_R->Write();
	EffDistMCP->Write();
	EffDistMCP_Beta->Write();
	EffQualMCP->Write();
        EffQualMCP_Beta->Write();
	f_out->Write();
	f_out->Close();


	return 1;
}
