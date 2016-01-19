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
float Beta_corr=0;
float BetaRICH=0;
float RminTOF=0;
float RminTrack=0;
float RminTRD=0;
float XTOF=0;
float XTrack=0;
float XTRD=0;
float YTOF=0;
float YTrack=0;
float YTRD=0;
float Rcutoff=0;
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
double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};

TH1F * E_depL1 = new TH1F("EdepL1","EdepL1",500,0,2);
TH1F * TplL1_P = new TH1F("TplL1_P","TplL1_P",500,0,2);
TH1F * TplL1_He = new TH1F("TplL1_He","TplL1_He",500,0,2);
TH1F * Y_TOF = new TH1F("YTOF","YTOF",1000,-10,50);
TH1F * TplY_Track_P = new TH1F("TplY_Track_P","TplY_Track_P",1000,-10,50);
TH1F * TplY_Track_He = new TH1F("TplY_Track_He","TplY_Track_He",1000,-10,50);
TH1F * Y_Track = new TH1F("YTrack","YTrack",1000,-10,50);
TH1F * Y_TRD = new TH1F("YTRD","YTRD",1000,-10,50);
TH1F * EffDistMCP = new TH1F("EffDistMCP","EffDistMCP",43,0,43);
TH1F * EffQualMCP = new TH1F("EffQualMCP","EffQualMCP",43,0,43);
TH2F * EffDistMCD = new TH2F("EffDistMCD","EffDistMCD",43,0,43,6,0,6);
TH2F * EffQualMCD = new TH2F("EffQualMCD","EffQualMCD",43,0,43,6,0,6);
TH1F * PCountsD[11];
TH1F * PCountsQ[11];
TH1F * PCountsDPrim[11];
TH1F * PCountsQPrim[11];
TH1F * Esposizione[11];
TH1F * Unbias[11];
TH1F * UPreselected[11];
TH1F * UnbiasMC= new TH1F("UMC","UMC",43,0,43);
TH1F * UPreselectedMC= new TH1F("PreselectedMC","PreselectedMC",43,0,43);
TH1F * UnbiasHL= new TH1F("UHL","UHL",43,0,43);
TH1F * UPreselectedHL= new TH1F("PreselectedHL","PreselectedHL",43,0,43);
TH2F * selezioni_P[10];
TH2F * selected_P[10];
TH1F * selezioni_PHL[10];
TH1F * selected_PHL[10];
TH1F * selezioni_DHL[10];
TH1F * selected_DHL[10];
TH1F * selezioni_PHLMC[10];
TH1F * selected_PHLMC[10];
TH2F * selezioni_DHLMC[10];
TH2F * selected_DHLMC[10];
TH2F * selezioniQ=new TH2F("selezioniQ","selezioniQ",43,0,43,11,0,11);
TH2F * selectedQD=new TH2F("selezioniQD","selezioniQD",43,0,43,11,0,11);
TH2F * selectedQDTOF=new TH2F("selezioniQDTOF","selezioniQDTOF",43,0,43,11,0,11);
TH2F * selectedQDTrack=new TH2F("selezioniQDTrack","selezioniQDTrack",43,0,43,11,0,11);
TH2F * selectedQDTRD=new TH2F("selezioniQDTRD","selezioniQDTRD",43,0,43,11,0,11);
TH2F * selectedQL=new TH2F("selezioniQL","selezioniQL",43,0,43,11,0,11);
TH2F * selectedQLD=new TH2F("selezioniQLD","selezioniQLD",43,0,43,11,0,11);
TH1F * selezioniQHL=new TH1F("selezioniQHL","selezioniQHL",43,0,43);
TH1F * selectedQDHL=new TH1F("selezioniQDHL","selezioniQDHL",43,0,43);
TH1F * selectedQLHL=new TH1F("selezioniQLHL","selezioniQLHL",43,0,43);
TH1F * selectedQLDHL=new TH1F("selezioniQLDHL","selezioniQLDHL",43,0,43);
TH1F * selezioniQHLMC=new TH1F("selezioniQHLMC","selezioniQHLMC",43,0,43);
TH1F * selectedQDHLMC=new TH1F("selezioniQDHLMC","selezioniQDHLMC",43,0,43);
TH1F * selectedQLHLMC=new TH1F("selezioniQLHLMC","selezioniQLHLMC",43,0,43);
TH1F * selectedQLDHLMC=new TH1F("selezioniQLDHLMC","selezioniQLDHLMC",43,0,43);
TH1F * selezioniQHL1=new TH1F("selezioniQHL1","selezioniQHL1",43,0,43);
TH1F * selezioniQHL2=new TH1F("selezioniQHL2","selezioniQHL2",43,0,43);
TH1F * selezioniQHL3=new TH1F("selezioniQHL3","selezioniQHL3",43,0,43);
TH1F * selezioniQHL4=new TH1F("selezioniQHL4","selezioniQHL4",43,0,43);
TH1F * selectedQHL1=new TH1F("selectedQHL1","selectedQHL1",43,0,43);
TH1F * selectedQHL2=new TH1F("selectedQHL2","selectedQHL2",43,0,43);
TH1F * selectedQHL3=new TH1F("selectedQHL3","selectedQHL3",43,0,43);
TH1F * selectedQHL4=new TH1F("selectedQHL4","selectedQHL4",43,0,43);
TH1F * selezioniQHL1_P=new TH1F("selezioniQHL1_P","selezioniQHL1_P",43,0,43);
TH1F * selezioniQHL2_P=new TH1F("selezioniQHL2_P","selezioniQHL2_P",43,0,43);
TH1F * selezioniQHL3_P=new TH1F("selezioniQHL3_P","selezioniQHL3_P",43,0,43);
TH1F * selezioniQHL4_P=new TH1F("selezioniQHL4_P","selezioniQHL4_P",43,0,43);
TH1F * selectedQHL1_P=new TH1F("selectedQHL1_P","selectedQHL1_P",43,0,43);
TH1F * selectedQHL2_P=new TH1F("selectedQHL2_P","selectedQHL2_P",43,0,43);
TH1F * selectedQHL3_P=new TH1F("selectedQHL3_P","selectedQHL3_P",43,0,43);
TH1F * selectedQHL4_P=new TH1F("selectedQHL4_P","selectedQHL4_P",43,0,43);
TH2F * selezioniQHLMC1=new TH2F("selezioniQHLMC1","selezioniQHLMC1",43,0,43,6,0,6);
TH2F * selezioniQHLMC2=new TH2F("selezioniQHLMC2","selezioniQHLMC2",43,0,43,6,0,6);
TH2F * selezioniQHLMC3=new TH2F("selezioniQHLMC3","selezioniQHLMC3",43,0,43,6,0,6);
TH2F * selezioniQHLMC4=new TH2F("selezioniQHLMC4","selezioniQHLMC4",43,0,43,6,0,6);
TH2F * selectedQHLMC1=new TH2F("selectedQHLMC1","selectedQHLMC1",43,0,43,6,0,6);
TH2F * selectedQHLMC2=new TH2F("selectedQHLMC2","selectedQHLMC2",43,0,43,6,0,6);
TH2F * selectedQHLMC3=new TH2F("selectedQHLMC3","selectedQHLMC3",43,0,43,6,0,6);
TH2F * selectedQHLMC4=new TH2F("selectedQHLMC4","selectedQHLMC4",43,0,43,6,0,6);
TH1F * selezioniQHLMC1_P=new TH1F("selezioniQHLMC1_P","selezioniQHLMC1_P",43,0,43);
TH1F * selezioniQHLMC2_P=new TH1F("selezioniQHLMC2_P","selezioniQHLMC2_P",43,0,43);
TH1F * selezioniQHLMC3_P=new TH1F("selezioniQHLMC3_P","selezioniQHLMC3_P",43,0,43);
TH1F * selezioniQHLMC4_P=new TH1F("selezioniQHLMC4_P","selezioniQHLMC4_P",43,0,43);
TH1F * selectedQHLMC1_P=new TH1F("selectedQHLMC1_P","selectedQHLMC1_P",43,0,43);
TH1F * selectedQHLMC2_P=new TH1F("selectedQHLMC2_P","selectedQHLMC2_P",43,0,43);
TH1F * selectedQHLMC3_P=new TH1F("selectedQHLMC3_P","selectedQHLMC3_P",43,0,43);
TH1F * selectedQHLMC4_P=new TH1F("selectedQHLMC4_P","selectedQHLMC4_P",43,0,43);
TH2F * PCountsDPrimLat=new TH2F("PCountsDPrimLat","PCountsDPrimLat",43,0,43,500,0,1.3);
TH2F * PCountsLPrimLat=new TH2F("PCountsLPrimLat","PCountsLPrimLat",43,0,43,500,0,1.3);
TH2F * Discr1_T[11];
TH2F * Discr1_T_Prim= new TH2F("Discr1_TPrim","Discr1_TPrim",100,0,40,18,0,18);
TH2F * Discr1_TMCP= new TH2F("Discr1_TMCP","Discr1_TMCP",100,0,40,18,0,18);
TH2F * Discr1_TMCD= new TH2F("Discr1_TMCD","Discr1_TMCD",100,0,40,18,0,18);
TH2F * Discr1_TMCHe= new TH2F("Discr1_TMCHe","Discr1_TMCHe",100,0,40,18,0,18);
TH2F * Discr2_T[11];
TH2F * Discr2_T_Prim= new TH2F("Discr2_TPrim","Discr2_TPrim",150,0,12,18,0,18);
TH2F * Discr2_TMCP= new TH2F("Discr2_TMCP","Discr2_TMCP",150,0,12,18,0,18);
TH2F * Discr2_TMCD= new TH2F("Discr2_TMCD","Discr2_TMCD",150,0,12,18,0,18);
TH2F * Discr2_TMCHe= new TH2F("Discr2_TMCHe","Discr2_TMCHe",150,0,12,18,0,18);
TH2F * Discr3_T[11];
TH2F * Discr3_T_Prim= new TH2F("Discr3_TPrim","Discr3_TPrim",150,0,12,18,0,18);
TH2F * Discr3_TMCP= new TH2F("Discr3_TMCP","Discr3_TMCP",150,0,12,18,0,18);
TH2F * Discr3_TMCD= new TH2F("Discr3_TMCD","Discr3_TMCD",150,0,12,18,0,18);
TH2F * Discr3_TMCHe= new TH2F("Discr3_TMCHe","Discr3_TMCHe",150,0,12,18,0,18);
TH2F * ContCheckDTOF= new TH2F("ContCheckDTOF","ContCheckDTOF",1000,-20,20,43,0,43);
TH2F * ContCheckPTOF= new TH2F("ContCheckPTOF","ContCheckPTOF",1000,-20,20,43,0,43);
string numero[11]={"0","1","2","3","4","5","6","7","8","9","10"};
float Rcut[11]={18,18,16,14,12,10,8,6,4,2,1};
string tagli[10]={"Trigger","3of4 TOF","TRD Segments","Rigidity exists","Chi^2 R","Matching TOF","Matching TRD","In TRD Accept.","1 Particle","1 Tr. Track"};
string nome;
float DXWind[43];

int main()

{

for(int j=0;j<43;j++)
{
        if(j<=6) DXWind[j]=-0.5;
        if(j>6&&j<=13) DXWind[j]=-0.5;
        if(j>13&&j<=15) DXWind[j]=-1; 
        if(j>15) DXWind[j]=-4;
}

for(int j=0;j<10;j++){
		nome="Selezioni"+tagli[j];
		selezioni_P[j]=new TH2F(nome.c_str(),nome.c_str(),43,0,43,11,0,11);
		nome="Selected"+tagli[j];
                selected_P[j]=new TH2F(nome.c_str(),nome.c_str(),43,0,43,11,0,11);
		nome="SelezioniHL"+tagli[j];
		selezioni_PHL[j]=new TH1F(nome.c_str(),nome.c_str(),43,0,43);
		nome="SelectedHL"+tagli[j];
                selected_PHL[j]=new TH1F(nome.c_str(),nome.c_str(),43,0,43);
		nome="SelezioniHL_D"+tagli[j];
                selezioni_DHL[j]=new TH1F(nome.c_str(),nome.c_str(),43,0,43);
                nome="SelectedHL_D"+tagli[j];
                selected_DHL[j]=new TH1F(nome.c_str(),nome.c_str(),43,0,43);
		nome="SelezioniHL_MC"+tagli[j];
                selezioni_PHLMC[j]=new TH1F(nome.c_str(),nome.c_str(),43,0,43);
                nome="SelectedHL_MC"+tagli[j];
                selected_PHLMC[j]=new TH1F(nome.c_str(),nome.c_str(),43,0,43);
		nome="SelezioniHL_MCD"+tagli[j];
                selezioni_DHLMC[j]=new TH2F(nome.c_str(),nome.c_str(),43,0,43,6,0,6);
                nome="SelectedHL_MCD"+tagli[j];
                selected_DHLMC[j]=new TH2F(nome.c_str(),nome.c_str(),43,0,43,6,0,6);
}
	 


for(int i=0;i<11;i++) {
        nome="PCountsD"+numero[i];
        PCountsD[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
	nome="PCountsQ"+numero[i];
        PCountsQ[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
	nome="PCountsDPrim"+numero[i];
        PCountsDPrim[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
        nome="PCountsQPrim"+numero[i];
        PCountsQPrim[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
	nome="Esposizione"+numero[i];
        Esposizione[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
	nome="Unbias"+numero[i];
        Unbias[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
	nome="UPreselected"+numero[i];
        UPreselected[i]= new TH1F(nome.c_str(),nome.c_str(),43,0,43);
	nome="Discr1_T"+numero[i];
	Discr1_T[i]= new TH2F(nome.c_str(),nome.c_str(),100,0,40,18,0,18);
	nome="Discr2_T"+numero[i];
        Discr2_T[i]= new TH2F(nome.c_str(),nome.c_str(),150,0,12,18,0,18);
	nome="Discr3_T"+numero[i];
        Discr3_T[i]= new TH2F(nome.c_str(),nome.c_str(),150,0,12,18,0,18);
}

TFile *file1 =TFile::Open("./Risultati/Marzo2012/RisultatiMC.root");
    TFile *file2 =TFile::Open("./Risultati/Marzo2012/RisultatiDATI.root");
    TNtuple *ntupla1=(TNtuple*)file1->Get("grandezzesepd");
    TNtuple *ntupla2=(TNtuple*)file2->Get("grandezzesepd");
    TNtuple *ntupla3=(TNtuple*)file1->Get("grandezzesep");
    TNtuple *ntupla4=(TNtuple*)file2->Get("grandezzesep");
        
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
        ntupla1->SetBranchAddress("Cutmask",&Cutmask);

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
        ntupla2->SetBranchAddress("Cutmask",&Cutmask);

	ntupla3->SetBranchAddress("R",&R);
        ntupla3->SetBranchAddress("Beta_corr",&Beta_corr);
        ntupla3->SetBranchAddress("EdepL1",&EdepL1);
        ntupla3->SetBranchAddress("RminTOF",&RminTOF);
        ntupla3->SetBranchAddress("RminTrack",&RminTrack);
        ntupla3->SetBranchAddress("RminTRD",&RminTRD);
        ntupla3->SetBranchAddress("XTOF",&XTOF);
        ntupla3->SetBranchAddress("XTrack",&XTrack);
        ntupla3->SetBranchAddress("XTRD",&XTRD);
        ntupla3->SetBranchAddress("YTOF",&YTOF);
        ntupla3->SetBranchAddress("YTrack",&YTrack);
        ntupla3->SetBranchAddress("YTRD",&YTRD);
        ntupla3->SetBranchAddress("LDiscriminant",&LDiscriminant);
        ntupla3->SetBranchAddress("BDT_response",&BDT_response);
        ntupla3->SetBranchAddress("Massagen",&Massagen);
        ntupla3->SetBranchAddress("Cutmask",&Cutmask);

        ntupla4->SetBranchAddress("R",&R);
        ntupla4->SetBranchAddress("Beta_corr",&Beta_corr);
        ntupla4->SetBranchAddress("EdepL1",&EdepL1);
        ntupla4->SetBranchAddress("RminTOF",&RminTOF);
        ntupla4->SetBranchAddress("RminTrack",&RminTrack);
        ntupla4->SetBranchAddress("RminTRD",&RminTRD);
        ntupla4->SetBranchAddress("XTOF",&XTOF);
        ntupla4->SetBranchAddress("XTrack",&XTrack);
        ntupla4->SetBranchAddress("XTRD",&XTRD);
        ntupla4->SetBranchAddress("YTOF",&YTOF);
        ntupla4->SetBranchAddress("YTrack",&YTrack);
        ntupla4->SetBranchAddress("YTRD",&YTRD);
        ntupla4->SetBranchAddress("Rcutoff",&Rcutoff);
        ntupla4->SetBranchAddress("LDiscriminant",&LDiscriminant);
        ntupla4->SetBranchAddress("BDT_response",&BDT_response);
        ntupla4->SetBranchAddress("Latitude",&Latitude);
        ntupla4->SetBranchAddress("Cutmask",&Cutmask);
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

TH1F * Tempi=(TH1F*) file2->Get("Tempi");
TH1F * PrescaledMC = new TH1F("PrescaledMC","PrescaledMC",43,0,43);
TH1F * EffpreselMCP1= (TH1F*) file1->Get("efficienzagenbeta_P");
TH2F * EffpreselMCD1= (TH2F*) file1->Get("efficienzagenbeta_D");
TH1F * EffpreselMCP2= (TH1F*) file1->Get("preselectedbeta_P");
TH2F * EffpreselMCD2= (TH2F*) file1->Get("preselectedbeta_D");
TH1F * EffpreselMCP1_R =(TH1F*) file1->Get("tempi0");
TH2F * EffpreselMCD1_R =(TH2F*) file1->Get("tempi0_D");
TH1F * EffpreselMCP2_R =(TH1F*) file1->Get("preselezionate0");
TH2F * EffpreselMCD2_R =(TH2F*) file1->Get("preselezionateD");
TH2F * esposizionegeo  =(TH2F*) file2->Get("esposizionegeo");
for(int i=0;i<11;i++) for(int j=0;j<43;j++) Esposizione[i]->SetBinContent(j+1,esposizionegeo->GetBinContent(j+1,i)/(float)fraz);

for(int i=0; i<1/*ntupla2->GetEntries()/fraz*/;i++) {
        int k = ntupla4->GetEvent(i);
	if(100*(i/(float)(ntupla2->GetEntries()/fraz))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
	CUTMASK=((int)Cutmask&1023);
	if(((int)Cutmask>>10)&1==1) IsPrescaled=1; else IsPrescaled=0;
	DistTOF=pow(pow(XTOF,2)+pow(YTOF,2),0.5);
        DistTrack=pow(pow(XTrack,2)+pow(YTrack,2),0.5);
        DistTRD=pow(pow(XTRD,2)+pow(YTRD,2),0.5);
	Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Beta_corr,2)),0.5)/Beta_corr,2)),0.5);
	for(int z=0;z<12;z++){
                        double geo= geomag[z]  ;
                        double geo2=geomag[z+1];
                        if(Latitude>geo && Latitude<geo2) Zona=z;
        }
	///////////////// LAT EFFECT ////////////////////
	if(IsPrescaled==1){
	 
		 if((((int)CUTMASK>>0)&UnbiasPre)==UnbiasPre&&DistTOF<4&&DistTrack<4) {
					for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {if(R>Rcut[Zona]) {Unbias[Zona]->Fill(K); if((CUTMASK&1019)==1019) UPreselected[Zona]->Fill(K);}}
					for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {if(Latitude>1&&R>1.2*Rcutoff) {UnbiasHL->Fill(K); if((CUTMASK&1019)==1019) UPreselectedHL->Fill(K);}}
					}	
		 for(int S=0;S<10;S++)
			if((((int)CUTMASK>>0)&notpassed[S])==notpassed[S]&&DistTOF<4&&DistTrack<4){
                                        for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {
						if(R>Rcut[Zona]) {selezioni_P[S]->Fill(K,Zona);if((((int)CUTMASK>>S)&1==1)) selected_P[S]->Fill(K,Zona); }
						if(Latitude>1&&R>1.2*Rcutoff) {selezioni_PHL[S]->Fill(K);if((((int)CUTMASK>>S)&1==1)) selected_PHL[S]->Fill(K); }
						}
				}
	}
	/////////////////////////////////////////////////
	if(IsPrescaled==0){
		////////// TEMPLATES CHARGE /////////////
		if(-YTOF>-2&&-YTOF<3&&-YTrack>-1&&-YTrack<3&&-YTRD>-2&&-YTRD<2) Q=1;
		else if (-YTOF>22&&-YTOF<28&&-YTrack>12.5&&-YTrack<17&&-YTRD>10&&-YTRD<15) Q=2;
		else Q=0;
		if(Beta_corr>0.45&&Beta_corr<0.83&&R<4) {
				Y_TOF->Fill(-YTOF);
                                Y_Track->Fill(-YTrack);
                                Y_TRD->Fill(-YTRD);
				if(EdepL1>0.01) {
						E_depL1->Fill(EdepL1);
						if(Q==1) TplL1_P->Fill(EdepL1);
						if(Q==2) TplL1_He->Fill(EdepL1);
						if(EdepL1>0.04&&EdepL1<0.15) TplY_Track_P->Fill(-YTrack);
						if(EdepL1>0.58&&EdepL1<0.9) TplY_Track_He->Fill(-YTrack);
						}
		}
		////////////////////////////////////////
		///////////// QUAL. LAT. EFFECT ////////
		if(EdepL1>0.04&&EdepL1<0.15){
				for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {if(R>Rcut[Zona]) selezioniQ->Fill(K,Zona);if(Latitude>1&&R>1.2*Rcutoff)selezioniQHL->Fill(K); }
				if(DistTOF<4&&DistTrack<4)for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {
							if(R>Rcut[Zona]) selectedQD->Fill(K,Zona);
							if(Latitude>1&&R>1.2*Rcutoff) selectedQDHL->Fill(K);	
							}
				for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) if(R>Rcut[Zona]) {
														if(DistTOF<4) selectedQDTOF->Fill(K,Zona);
														if(DistTrack<4) selectedQDTrack->Fill(K,Zona);		
														if(DistTRD<4) selectedQDTRD->Fill(K,Zona);
							}
				if(LDiscriminant>0.95) for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {
							if(R>Rcut[Zona]) selectedQL->Fill(K,Zona);
							if(Latitude>1&&R>1.2*Rcutoff) selectedQLHL->Fill(K);
								}
				if(LDiscriminant>0.95&&DistTOF<4&&DistTrack<4) for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {
							 if(R>Rcut[Zona]) selectedQLD->Fill(K,Zona);
                                                         if(Latitude>1&&R>1.2*Rcutoff) selectedQLDHL->Fill(K);	
								} 	
		}
		////////////////////////////////////////
	        //////////// DISTANCE EFFICIENCIES CHECK /////////////////////
		if(fabs(YTOF)<3&&fabs(YTrack)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                                   if(XTOF<3&&XTOF>-3&&XTrack<3&&XTrack>-3)
                                                        {if(Latitude>1&&R>1.2*Rcutoff) {selezioniQHL1_P->Fill(K);if(DistTRD<4) selectedQHL1_P->Fill(K); } }

                 }
                 if(fabs(YTrack)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                                    if(XTrack<3&&XTrack>-3&&XTRD<3&&XTRD>-3)
                                                        {if(Latitude>1&&R>1.2*Rcutoff) {selezioniQHL2_P->Fill(K);if(DistTOF<4) selectedQHL2_P->Fill(K); } }

                 }
                if(fabs(YTOF)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                                    if(XTOF<3&&XTOF>-3&&XTRD<3&&XTRD>-3)
                                                        {if(Latitude>1&&R>1.2*Rcutoff) {selezioniQHL3_P->Fill(K);if(DistTrack<4)selectedQHL3_P->Fill(K); } }

                 }
                if(fabs(YTOF)<3&&fabs(YTrack)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                                       if(XTOF<3&&XTOF>-3&&XTrack<3&&XTrack>-3)
                                                        {if(Latitude>1&&R>1.2*Rcutoff) {selezioniQHL4_P->Fill(K);if(LDiscriminant>0.95) selectedQHL4_P->Fill(K); } }

                 }
		//////////////////////////////////////////////////////////////
	   	////////// PROTONS COUNTS / /////////////
		bool IsHe=false;
                if((fabs(YTOF)>5&&fabs(YTrack)>5&&fabs(YTRD)>5)) IsHe=true;
		if(DistTOF<4&&DistTrack<4)   
			for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {PCountsD[Zona]->Fill(K); if(R>1.2*Rcutoff) {PCountsDPrim[Zona]->Fill(K);PCountsDPrimLat->Fill(K,Latitude);}}
		if(!IsHe&&LDiscriminant>0.95)
			for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {PCountsQ[Zona]->Fill(K); if(R>1.2*Rcutoff) {PCountsQPrim[Zona]->Fill(K);PCountsLPrimLat->Fill(K,Latitude);}}
	   	/////////////////////////////////////////	
	}
	/////////////////////////// DEUTONI //////////////////////////////		
	int kD = ntupla2->GetEvent(i);
        CUTMASK=((int)Cutmask&1023);
        if(((int)Cutmask>>10)&1==1) IsPrescaled=1; else IsPrescaled=0;
	DistTOF=pow(pow(XTOF,2)+pow(YTOF,2),0.5);
        DistTrack=pow(pow(XTrack,2)+pow(YTrack,2),0.5);
        DistTRD=pow(pow(XTRD,2)+pow(YTRD,2),0.5);
	float Discr1=pow(pow(XTOF-5,2)+pow(YTOF,2)+pow(XTrack-5,2)+pow(YTrack,2)+pow(XTRD-5,2)+pow(YTRD,2),0.5);
	float Discr2=Massa;
	float Discr3=Massa;
	if(IsPrescaled==1) {
		bool cleanD=false;
		 for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                  if(XTOF<DXWind[K]&&XTOF>-3&&XTrack<DXWind[K]&&XTrack>-3&&XTRD<DXWind[K]&&XTRD>-3&&fabs(YTOF)<5&&fabs(YTrack)<5&&fabs(YTRD)<5) cleanD=true;
		
		  for(int S=0;S<10;S++)
                        if((((int)CUTMASK>>0)&notpassed[S])==notpassed[S]&&cleanD&&Beta_corr<0.85&&R<4){
                                     for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {
                                         if(Latitude>1&&R>1.2*Rcutoff) {selezioni_DHL[S]->Fill(K);if((((int)CUTMASK>>S)&1==1)) selected_DHL[S]->Fill(K); }
                                                }
                                }
		}
	if(IsPrescaled==0) {
		///////////// QUAL. EFFICIENCIES /////////////////
		if(Beta_corr<0.95&&R<4) {
		if(fabs(YTOF)<3&&fabs(YTrack)<3) {
				for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) 
						   if(XTOF<DXWind[K]&&XTOF>-3&&XTrack<DXWind[K]&&XTrack>-3)	
							{if(Latitude>1&&R>1.2*Rcutoff) {selezioniQHL1->Fill(K);if(DistTRD<4) selectedQHL1->Fill(K); } }

		 }
		 if(fabs(YTrack)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) 
						    if(XTrack<DXWind[K]&&XTrack>-3&&XTRD<DXWind[K]&&XTRD>-3)	
                                                        {if(Latitude>1&&R>1.2*Rcutoff) {selezioniQHL2->Fill(K);if(DistTOF<4) selectedQHL2->Fill(K); } }
                
                 }	
		if(fabs(YTOF)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) 
						    if(XTOF<DXWind[K]&&XTOF>-3&&XTRD<DXWind[K]&&XTRD>-3)	
                                                        {if(Latitude>1&&R>1.2*Rcutoff) {selezioniQHL3->Fill(K);if(DistTrack<4)selectedQHL3->Fill(K); } }
                
                 }
		if(fabs(YTOF)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
						       if(XTOF<DXWind[K]&&XTOF>-3&&XTRD<DXWind[K]&&XTRD>-3)	
                                                        {if(Latitude>1&&R>1.2*Rcutoff) {selezioniQHL4->Fill(K);if(LDiscriminant>0.95) selectedQHL4->Fill(K); } }

                 }

		}
		//////////////////////////////////////////////////
		///////////// TEMPLATES DISCR /////////////////////
		bool IsHe=false;
		if(((YTOF)<-10&&(YTrack)<-5&&(YTRD)<-5)) IsHe=true;
		if((DistTOF<4&&DistTrack<4)||IsHe){
	 		for(int m=0;m<17;m++) if(fabs(R)<bin[m+1]&&fabs(R)>bin[m]){
						 if(IsHe) Discr2=4*Massa;
						 Discr1_T[Zona]->Fill(Discr1,m);
						 Discr2_T[Zona]->Fill(Discr2,m);
						 if(R>1.2*Rcutoff) {Discr1_T_Prim->Fill(Discr1,m);
								    Discr2_T_Prim->Fill(Discr2,m);	
							}
						}
		}
		if(LDiscriminant>0.95&&((DistTOF<4&&DistTrack<4)||IsHe)){
		IsHe=false;
		if(((YTOF)<-10&&(YTrack)<-5&&(YTRD)<-5)) IsHe=true;
			for(int m=0;m<17;m++) if(fabs(R)<bin[m+1]&&fabs(R)>bin[m]){
				if(IsHe) Discr3=4*Massa;
                                                 Discr3_T[Zona]->Fill(Discr3,m);
                                                 if(R>1.2*Rcutoff) Discr3_T_Prim->Fill(Discr3,m);
                                   }                     

		}
		///////////////////////////////////////////////////
	}
	//////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////// MONTECARLO////////////////////////////////////////////////////////////////////////////
avanzamento=0;
for(int i=0; i<1/*ntupla1->GetEntries()*/;i++) {
        int k = ntupla3->GetEvent(i);
	if(100*(i/(float)(ntupla1->GetEntries()))>avanzamento) {cout<<avanzamento<<endl;avanzamento++;}
	CUTMASK=((int)Cutmask&1023);
        if(((int)Cutmask>>10)&1==1) IsPrescaled=1; else IsPrescaled=0;
	Massa=pow(fabs(pow(fabs(R)*pow((1-pow(Beta_corr,2)),0.5)/Beta_corr,2)),0.5);
	DistTOF=pow(pow(XTOF,2)+pow(YTOF,2),0.5);
	DistTrack=pow(pow(XTrack,2)+pow(YTrack,2),0.5);
	DistTRD=pow(pow(XTRD,2)+pow(YTRD,2),0.5);
	if(IsPrescaled==1){
		if(Massagen<1){ 
			for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) PrescaledMC->Fill(K);
			if((((int)CUTMASK>>0)&UnbiasPre)==UnbiasPre&&DistTOF<4&&DistTrack<4) {
                                        for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {UnbiasMC->Fill(K); if((CUTMASK&1019)==1019) UPreselectedMC->Fill(K);}                                                                           }
			for(int S=0;S<10;S++)
                   		 if((((int)CUTMASK>>0)&notpassed[S])==notpassed[S]&&DistTOF<4&&DistTrack<4){
                                        for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {	
						selezioni_PHLMC[S]->Fill(K);if((((int)CUTMASK>>S)&1==1)) selected_PHLMC[S]->Fill(K);
			}
		  }
		}
	}
	if(IsPrescaled==0){
		if(Massagen<1){
			if(DistTOF<4&&DistTrack<4)	for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {EffDistMCP->Fill(K);}
			if(LDiscriminant>0.95) for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {EffQualMCP->Fill(K);}
			if(EdepL1>0.04&&EdepL1<0.15){
				for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) selezioniQHLMC->Fill(K);
				if(DistTOF<4&&DistTrack<4)   for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) selectedQDHLMC->Fill(K);
				if(LDiscriminant>0.95) for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) selectedQLHLMC->Fill(K);
				if(LDiscriminant>0.95&&DistTOF<4&&DistTrack<4)for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) selectedQLDHLMC->Fill(K);
				} 
		//////////// DISTANCE EFFICIENCIES CHECK /////////////////////
		if(fabs(YTOF)<3&&fabs(YTrack)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                                   if(XTOF<3&&XTOF>-3&&XTrack<3&&XTrack>-3)
                                                         {selezioniQHLMC1_P->Fill(K);if(DistTRD<4) selectedQHLMC1_P->Fill(K); }

                 }
                 if(fabs(YTrack)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                                    if(XTrack<3&&XTrack>-3&&XTRD<3&&XTRD>-3)
                                                        {selezioniQHLMC2_P->Fill(K);if(DistTOF<4) selectedQHLMC2_P->Fill(K); }

                 }
                if(fabs(YTOF)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                                    if(XTOF<3&&XTOF>-3&&XTRD<3&&XTRD>-3)
                                                        {selezioniQHLMC3_P->Fill(K);if(DistTrack<4)selectedQHLMC3_P->Fill(K);  }

                 }
                if(fabs(YTOF)<3&&fabs(YTrack)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                                       if(XTOF<3&&XTOF>-3&&XTrack<3&&XTrack>-3)
                                                        {selezioniQHLMC4_P->Fill(K);if(LDiscriminant>0.95) selectedQHLMC4_P->Fill(K);}

                 }

		//////////////////////////////////////////////////////////////	

			
		}
	}

	/////////////////////// DEUTONI //////////////////////////
	int kD = ntupla1->GetEvent(i);
	CUTMASK=((int)Cutmask&1023);
        if(((int)Cutmask>>10)&1==1) IsPrescaled=1; else IsPrescaled=0;
        DistTOF=pow(pow(XTOF,2)+pow(YTOF,2),0.5);
        DistTrack=pow(pow(XTrack,2)+pow(YTrack,2),0.5);
        DistTRD=pow(pow(XTRD,2)+pow(YTRD,2),0.5);
        float Discr1=pow(pow(XTOF-5,2)+pow(YTOF,2)+pow(XTrack-5,2)+pow(YTrack,2)+pow(XTRD-5,2)+pow(YTRD,2),0.5);
	float Discr2=Massa;
	float Discr3=Massa;
	/////////////////////// DEUTONI SEL: DATA VS MC ////////////////////
	if(IsPrescaled==1){
                 bool cleanD=false;
                 for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                  if(XTOF<DXWind[K]&&XTOF>-3&&XTrack<DXWind[K]&&XTrack>-3&&XTRD<DXWind[K]&&XTRD>-3&&fabs(YTOF)<5&&fabs(YTrack)<5&&fabs(YTRD)<5) cleanD=true;

		for(int S=0;S<10;S++)
                    if((((int)CUTMASK>>0)&notpassed[S])==notpassed[S]&&cleanD){
                                   for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]&&Massagen>1&&Massagen<2&&Beta_corr<0.85&&R<4) {
                                           selezioni_DHLMC[S]->Fill(K,10000*Massagen-18570);if((((int)CUTMASK>>S)&1==1)) selected_DHLMC[S]->Fill(K,10000*Massagen-18570);
                        }
                  }

        }
	///////////////////////////////////////////////////////////////////////
	if(IsPrescaled==0){
		if(Massagen>1&&Massagen<2){
                        if(DistTOF<4&&DistTrack<4)   for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {EffDistMCD->Fill(K,10000*Massagen-18570);}
                        if(LDiscriminant>0.95) for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]) {EffQualMCD->Fill(K,10000*Massagen-18570);}
		}	
		///////////// QUAL. EFFICIENCIES /////////////////
		if(Beta_corr<0.95&&R<4){
			if(fabs(YTOF)<3&&fabs(YTrack)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                        if(XTOF<DXWind[K]&&XTOF>-3&&XTrack<DXWind[K]&&XTrack>-3&&Massagen>1&&Massagen<2)                
					 	{selezioniQHLMC1->Fill(K,10000*Massagen-18570);  if(DistTRD<4) selectedQHLMC1->Fill(K,10000*Massagen-18570);}

                 	}
                 	if(fabs(YTrack)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                        if(XTrack<DXWind[K]&&XTrack>-3&&XTRD<DXWind[K]&&XTRD>-3&&Massagen>1&&Massagen<2)                
						 {selezioniQHLMC2->Fill(K,10000*Massagen-18570);if(DistTOF<4) selectedQHLMC2->Fill(K,10000*Massagen-18570); }

                 	}
                	if(fabs(YTOF)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                        if(XTOF<DXWind[K]&&XTOF>-3&&XTRD<DXWind[K]&&XTRD>-3&&Massagen>1&&Massagen<2)                
						{selezioniQHLMC3->Fill(K,10000*Massagen-18570);if(DistTrack<4)selectedQHLMC3->Fill(K,10000*Massagen-18570); }

                 	}
			if(fabs(YTOF)<3&&fabs(YTRD)<3) {
                                for(int K=0;K<43;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K])
                                        if(XTOF<DXWind[K]&&XTOF>-3&&XTRD<DXWind[K]&&XTRD>-3&&Massagen>1&&Massagen<2)                
							 {selezioniQHLMC4->Fill(K,10000*Massagen-18570);if(LDiscriminant>0.95) selectedQHLMC4->Fill(K,10000*Massagen-18570);  }

                        } 
	
			if(fabs(YTOF)<3){
				for(int K=0;K<18;K++) if(fabs(R)<bin[K+1]&&fabs(R)>bin[K]){
					if(Massagen>1&&Massagen<2) ContCheckDTOF->Fill(XTOF,K);
					if(Massagen>0&&Massagen<1) ContCheckPTOF->Fill(XTOF,K);
				}
						
			}
		}
		
		//////////////////////////////////////////////////	
	
	///////////// TEMPLATES DISCR /////////////////////
		bool IsHe=false;
        	if(((YTOF)<-10&&(YTrack)<-5&&(YTRD)<-5)) IsHe=true;
		if((DistTOF<4&&DistTrack<4)||IsHe){
			for(int m=0;m<17;m++)
				if(fabs(R)<bin[m+1]&&fabs(R)>bin[m]){
	   				if(IsHe) Discr2=4*Massa;
					if(Massagen<1) {Discr1_TMCP->Fill(Discr1,m);
	   						Discr2_TMCP->Fill(Discr2,m);}
					if(Massagen<2&&Massagen>1) {Discr1_TMCD->Fill(Discr1,m);	   
								    Discr2_TMCD->Fill(Discr2,m);}	
	   				if(Massagen<4&&Massagen>2) {Discr1_TMCHe->Fill(Discr1,m); 
								    Discr2_TMCHe->Fill(Discr2,m);}		
					}
		}
		if(LDiscriminant>0.95&&((DistTOF<4&&DistTrack<4)||IsHe)){
		IsHe=false;
		if(((YTOF)<-10&&(YTrack)<-5&&(YTRD)<-5)) IsHe=true;
			for(int m=0;m<17;m++)
                                if(fabs(R)<bin[m+1]&&fabs(R)>bin[m]){
					if(IsHe) Discr3=4*Massa;
					if(Massagen<1) Discr3_TMCP->Fill(Discr3,m);
					if(Massagen<2&&Massagen>1) Discr3_TMCD->Fill(Discr3,m);
					if(Massagen<4&&Massagen>2) Discr3_TMCHe->Fill(Discr3,m);
				}
		}
	///////////////////////////////////////////////////
	}                                        
	//////////////////////////////////////////////////////////
}

//for(int K=0;K<43;K++) EffpreselMCP2_R->SetBinContent(K,EffpreselMCP2_R->GetBinContent(K)*10);

cout<<"************************ OUTPUT ************************"<<endl;
string nomefile="/home/AMS/fdimicco/fdimicco/Parte1.root";
TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
Tempi->Write();
PrescaledMC->Write();
E_depL1->Write();
TplL1_P->Write();
TplL1_He->Write();
Y_TOF->Write();
Y_Track->Write();
Y_TRD->Write();
TplY_Track_P->Write();
TplY_Track_He->Write();
EffpreselMCP1->Write();
EffpreselMCP2->Write();
EffpreselMCP1_R->Write();
EffpreselMCP2_R->Write();
EffpreselMCD1->Write();
EffpreselMCD2->Write();
EffpreselMCD1_R->Write();
EffpreselMCD2_R->Write();
EffDistMCP->Write();
EffQualMCP->Write();
EffDistMCD->Write();
EffQualMCD->Write();
for(int S=0;S<10;S++)  selezioni_P[S]->Write();
for(int S=0;S<10;S++)  selected_P[S]->Write();
for(int i=0;i<11;i++) Unbias[i]->Write();
for(int i=0;i<11;i++) UPreselected[i]->Write();
UnbiasMC->Write();
UPreselectedMC->Write();
UnbiasHL->Write();
UPreselectedHL->Write();
for(int i=0;i<11;i++) PCountsD[i]->Write();
for(int i=0;i<11;i++) PCountsQ[i]->Write();
for(int i=0;i<11;i++) Esposizione[i]->Write();
for(int i=0;i<11;i++) PCountsDPrim[i]->Write();
for(int i=0;i<11;i++) PCountsQPrim[i]->Write();
selezioniQ->Write();
selectedQD->Write();
selectedQDTOF->Write();
selectedQDTrack->Write();
selectedQDTRD->Write();
selectedQL->Write();
selectedQLD->Write();
PCountsDPrimLat->Write();
PCountsLPrimLat->Write();
for(int S=0;S<10;S++)  selezioni_PHL[S]->Write();
for(int S=0;S<10;S++)  selected_PHL[S]->Write();
for(int S=0;S<10;S++)  selezioni_DHL[S]->Write();
for(int S=0;S<10;S++)  selected_DHL[S]->Write();
for(int S=0;S<10;S++)  selezioni_PHLMC[S]->Write();
for(int S=0;S<10;S++)  selected_PHLMC[S]->Write();
for(int S=0;S<10;S++)  selezioni_DHLMC[S]->Write();
for(int S=0;S<10;S++)  selected_DHLMC[S]->Write();
selezioniQHLMC->Write();
selectedQDHLMC->Write();
selectedQLHLMC->Write();
selectedQLDHLMC->Write();
selezioniQHL->Write();
selectedQDHL->Write();
selectedQLHL->Write();
selectedQLDHL->Write();
for(int i=0;i<11;i++) Discr1_T[i]->Write();
Discr1_TMCP->Write();
Discr1_TMCD->Write();
Discr1_TMCHe->Write();
Discr1_T_Prim->Write();
for(int i=0;i<11;i++) Discr2_T[i]->Write();
Discr2_TMCP->Write();
Discr2_TMCD->Write();
Discr2_TMCHe->Write();
Discr2_T_Prim->Write();
for(int i=0;i<11;i++) Discr3_T[i]->Write();
Discr3_TMCP->Write();
Discr3_TMCD->Write();
Discr3_TMCHe->Write();
Discr3_T_Prim->Write();
ContCheckDTOF->Write();
ContCheckPTOF->Write();
selezioniQHL1->Write(); selezioniQHL2->Write(); selezioniQHL3->Write(); selezioniQHL4->Write();
selectedQHL1->Write(); selectedQHL2->Write(); selectedQHL3->Write(); selectedQHL4->Write();
selezioniQHLMC1->Write(); selezioniQHLMC2->Write(); selezioniQHLMC3->Write(); selezioniQHLMC4->Write();
selectedQHLMC1->Write(); selectedQHLMC2->Write(); selectedQHLMC3->Write(); selectedQHLMC4->Write();
selezioniQHL1_P->Write(); selezioniQHL2_P->Write(); selezioniQHL3_P->Write(); selezioniQHL4_P->Write();
selectedQHL1_P->Write(); selectedQHL2_P->Write(); selectedQHL3_P->Write(); selectedQHL4_P->Write();
selezioniQHLMC1_P->Write(); selezioniQHLMC2_P->Write(); selezioniQHLMC3_P->Write(); selezioniQHLMC4_P->Write();
selectedQHLMC1_P->Write(); selectedQHLMC2_P->Write(); selectedQHLMC3_P->Write(); selectedQHLMC4_P->Write();

f_out->Write();
f_out->Close();

}

