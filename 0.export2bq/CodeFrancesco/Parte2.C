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
float CUTMASK=0;
float IsPrescaled=0;
float Latitude=0;
float EdepL1=0;
double geomagC[11]={0,0.1,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95,1.15};

TH1F * Tempi;
TH1F * PrescaledMC;
TH1F * E_depL1;
TH1F * TplL1_P;
TH1F * TplL1_He;
TH1F * Y_TOF;
TH1F * Y_Track;
TH1F * Y_TRD;
TH1F * TplY_Track_P;
TH1F * TplY_Track_He;
TH1F * EffpreselMCP1;
TH1F * EffpreselMCP2;
TH1F * EffpreselMCP1_R;
TH1F * EffpreselMCP2_R;
TH2F * EffpreselMCD1;
TH2F * EffpreselMCD2;
TH2F * EffpreselMCD1_R;
TH2F * EffpreselMCD2_R;
TH1F * EffDistMCP;
TH1F * EffQualMCP;
TH1F * EffDistMCD;
TH1F * EffQualMCD;
TH1F * Unbias[11];
TH1F * UPreselected[11];
TH1F * PreselecteMC;
TH1F * UMC;
TH1F * PreselecteHL;
TH1F * UHL;
TH1F * PCountsD[10];
TH1F * PCountsQ[10];
TH1F * PCountsDPrim[10];
TH1F * PCountsQPrim[10];
TH1F * Esposizione[10];
TH2F * selezioni_P[10];
TH2F * selected_P[10];
TH2F * Discr1_T[11];
TH2F * Discr1_TMCP;
TH2F * Discr1_TMCD;
TH2F * Discr1_TMCHe;
TH2F * Discr2_T[11];
TH2F * Discr2_TMCP;
TH2F * Discr2_TMCD;
TH2F * Discr2_TMCHe;
TH2F * Discr3_T[11];
TH2F * Discr3_TMCP;
TH2F * Discr3_TMCD;
TH2F * Discr3_TMCHe;
TH1F * selezioni_PHL[10];
TH1F * selected_PHL[10];
TH1F * selezioni_DHL[10];
TH1F * selected_DHL[10];
TH1F * selezioni_PHLMC[10];
TH1F * selected_PHLMC[10];
TH2F * selezioni_DHLMC[10];
TH2F * selected_DHLMC[10];
TH2F * selezioniQ;
TH2F * selectedQD;
TH2F * selectedQDTOF;
TH2F * selectedQDTrack;
TH2F * selectedQDTRD;
TH2F * selectedQL;
TH2F * selectedQLD;
TH1F * selezioniQHL;
TH1F * selezioniQHL1;
TH1F * selezioniQHL2;
TH1F * selezioniQHL3;
TH1F * selezioniQHL4;

TH2F * selezioniQHLMC1;
TH2F * selezioniQHLMC2;
TH2F * selezioniQHLMC3;
TH2F * selezioniQHLMC4;
TH1F * selectedQDHL;
TH1F * selectedQLDHL;
TH1F * selectedQHL1;
TH1F * selectedQHL2;
TH1F * selectedQHL3;
TH1F * selectedQHL4;
TH2F * selectedQHLMC1;
TH2F * selectedQHLMC2;
TH2F * selectedQHLMC3;
TH2F * selectedQHLMC4;
TH1F * selectedQLHL;
TH1F * selezioniQHLMC;
TH1F * selectedQDHLMC;
TH1F * selectedQLHLMC;
TH1F * selectedQLDHLMC;
TH1F * selezioniQHL1_P;
TH1F * selezioniQHL2_P;
TH1F * selezioniQHL3_P;
TH1F * selezioniQHL4_P;
TH1F * selectedQHL1_P;
TH1F * selectedQHL2_P;
TH1F * selectedQHL3_P;
TH1F * selectedQHL4_P;
TH1F * selezioniQHLMC1_P;
TH1F * selezioniQHLMC2_P;
TH1F * selezioniQHLMC3_P;
TH1F * selezioniQHLMC4_P;
TH1F * selectedQHLMC1_P;
TH1F * selectedQHLMC2_P;
TH1F * selectedQHLMC3_P;
TH1F * selectedQHLMC4_P;
TH2F * PCountsLPrimLat;
TH2F * PCountsDPrimLat;
TH2F * ContCheckPTOF;
TH2F * ContCheckDTOF;

double Bisect(double a,double b, TF1 *e,TF1 *i){
	if(fabs(a-b)<0.001) return (a+b)/2;
	else{
	double c=(a+b)/2;
	if(((e->Eval(a)-i->Eval(a))>0&&(e->Eval(c)-i->Eval(c))<0)||((e->Eval(a)-i->Eval(a))<0&&(e->Eval(c)-i->Eval(c))>0)) Bisect(a,c,e,i);
	else Bisect(c,b,e,i);
	}
}

double TrovaZero(double a,double tau){
	TF1 *esp = new TF1 ("esp","exp(-x*[0])",0,1);
	TF1 *inv = new TF1 ("inv","[0]/x",0,1);
	esp->SetParameter(0,tau);
	inv->SetParameter(0,a);
	if(a==0||tau==0||fabs(a-1)<0.001) return a;	
	if(((esp->Eval(0.001)-inv->Eval(0.001))>0&&(esp->Eval(1)-inv->Eval(1))>0)||((esp->Eval(0.001)-inv->Eval(0.001))<0&&(esp->Eval(1)-inv->Eval(1))<0)){
	cout<<a<<" "<<tau<<" "<<endl;}
	return Bisect(0.001,1,esp,inv);
}

int main()
{
TFile *file1 =TFile::Open("/home/AMS/fdimicco/fdimicco/Parte1.root");
cout<<"******************************************************************************** R BINS *********************************************************************************************************"<<endl;
float bin[44];
double R_cent[43];
float encinprot[43];
float encindeut[43];
float deltaencinprot[43];
float deltaencindeut[43];
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
for(int i=0;i<43;i++) {
        deltaencinprot[i]=(pow(((1+pow((bin[i+1]/0.938),2))),0.5)-1)-(pow(((1+pow((bin[i]/0.938),2))),0.5)-1);
        deltaencindeut[i]=(pow(((1+pow((bin[i+1]/1.875),2))),0.5)-1)-(pow(((1+pow((bin[i]/1.875),2))),0.5)-1);
}        
cout<<"******************************************************************************* BETA BINS *******************************************************************************************************"<<endl;
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
        

cout<<"********************************************************************************* LETTURA DATI ***************************************************************************************************"<<endl;
string numero[18]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17"};
string tagli[10]={"Trigger","3of4 TOF","TRD Segments","Rigidity exists","Chi^2 R","Matching TOF","Matching TRD","In TRD Accept.","1 Particle","1 Tr. Track"};
string nome;

Tempi = (TH1F *)file1->Get("Tempi");
PrescaledMC = (TH1F *)file1->Get("PrescaledMC");
E_depL1 = (TH1F *)file1->Get("EdepL1");
TplL1_P =  (TH1F *)file1->Get("TplL1_P");
TplL1_He =  (TH1F *)file1->Get("TplL1_He");
Y_TOF =  (TH1F *)file1->Get("YTOF");
Y_Track =  (TH1F *)file1->Get("YTrack");
Y_TRD =  (TH1F *)file1->Get("YTRD");
TplY_Track_P=  (TH1F *)file1->Get("TplY_Track_P");
TplY_Track_He=  (TH1F *)file1->Get("TplY_Track_He");
EffpreselMCP1= (TH1F*) file1->Get("efficienzagenbeta_P");
EffpreselMCD1= (TH2F*) file1->Get("efficienzagenbeta_D");
EffpreselMCP2= (TH1F*) file1->Get("preselectedbeta_P");
EffpreselMCD2= (TH2F*) file1->Get("preselectedbeta_D");
EffpreselMCP1_R =(TH1F*) file1->Get("tempi0");
EffpreselMCD1_R =(TH2F*) file1->Get("tempi0_D");
EffpreselMCP2_R =(TH1F*) file1->Get("preselezionate0");
EffpreselMCD2_R =(TH2F*) file1->Get("preselezionateD");


EffDistMCP=(TH1F *)file1->Get("EffDistMCP");
EffQualMCP=(TH1F *)file1->Get("EffQualMCP");
EffDistMCD=(TH1F *)file1->Get("EffDistMCD");
EffQualMCD=(TH1F *)file1->Get("EffQualMCD");
selezioniQ=(TH2F *)file1->Get("selezioniQ");
selectedQD=(TH2F *)file1->Get("selezioniQD");
selectedQDTOF=(TH2F *)file1->Get("selezioniQDTOF");
selectedQDTrack=(TH2F *)file1->Get("selezioniQDTrack");
selectedQDTRD=(TH2F *)file1->Get("selezioniQDTRD");
selectedQL=(TH2F *)file1->Get("selezioniQL");
selectedQLD=(TH2F *)file1->Get("selezioniQLD");
selezioniQHL=(TH1F *)file1->Get("selezioniQHL");
selezioniQHL1=(TH1F *)file1->Get("selezioniQHL1");
selezioniQHL2=(TH1F *)file1->Get("selezioniQHL2");
selezioniQHL3=(TH1F *)file1->Get("selezioniQHL3");
selezioniQHL4=(TH1F *)file1->Get("selezioniQHL4");
selectedQDHL=(TH1F *)file1->Get("selezioniQDHL");
selectedQLHL=(TH1F *)file1->Get("selezioniQLHL");
selectedQLDHL=(TH1F *)file1->Get("selezioniQLDHL");
selectedQHL1=(TH1F *)file1->Get("selectedQHL1");
selectedQHL2=(TH1F *)file1->Get("selectedQHL2");
selectedQHL3=(TH1F *)file1->Get("selectedQHL3");
selectedQHL4=(TH1F *)file1->Get("selectedQHL4");

selezioniQHL1_P=(TH1F *)file1->Get("selezioniQHL1_P");
selezioniQHL2_P=(TH1F *)file1->Get("selezioniQHL2_P");
selezioniQHL3_P=(TH1F *)file1->Get("selezioniQHL3_P");
selezioniQHL4_P=(TH1F *)file1->Get("selezioniQHL4_P");
selectedQHL1_P=(TH1F *)file1->Get("selectedQHL1_P");
selectedQHL2_P=(TH1F *)file1->Get("selectedQHL2_P");
selectedQHL3_P=(TH1F *)file1->Get("selectedQHL3_P");
selectedQHL4_P=(TH1F *)file1->Get("selectedQHL4_P");

selezioniQHLMC1=(TH2F *)file1->Get("selezioniQHLMC1");
selezioniQHLMC2=(TH2F *)file1->Get("selezioniQHLMC2");
selezioniQHLMC3=(TH2F *)file1->Get("selezioniQHLMC3");
selezioniQHLMC4=(TH2F *)file1->Get("selezioniQHLMC4");
selectedQHLMC1=(TH2F *)file1->Get("selectedQHLMC1");
selectedQHLMC2=(TH2F *)file1->Get("selectedQHLMC2");
selectedQHLMC3=(TH2F *)file1->Get("selectedQHLMC3");
selectedQHLMC4=(TH2F *)file1->Get("selectedQHLMC4");
selezioniQHLMC=(TH1F *)file1->Get("selezioniQHLMC");
selectedQDHLMC=(TH1F *)file1->Get("selezioniQDHLMC");
selectedQLHLMC=(TH1F *)file1->Get("selezioniQLHLMC");
selectedQLDHLMC=(TH1F *)file1->Get("selezioniQLDHLMC");

selezioniQHLMC1_P=(TH1F *)file1->Get("selezioniQHLMC1_P");
selezioniQHLMC2_P=(TH1F *)file1->Get("selezioniQHLMC2_P");
selezioniQHLMC3_P=(TH1F *)file1->Get("selezioniQHLMC3_P");
selezioniQHLMC4_P=(TH1F *)file1->Get("selezioniQHLMC4_P");
selectedQHLMC1_P=(TH1F *)file1->Get("selectedQHLMC1_P");
selectedQHLMC2_P=(TH1F *)file1->Get("selectedQHLMC2_P");
selectedQHLMC3_P=(TH1F *)file1->Get("selectedQHLMC3_P");
selectedQHLMC4_P=(TH1F *)file1->Get("selectedQHLMC4_P");


PCountsLPrimLat=(TH2F *)file1->Get("PCountsLPrimLat");
PCountsDPrimLat=(TH2F *)file1->Get("PCountsDPrimLat");
UMC=(TH1F *)file1->Get("UMC");
PreselecteMC=(TH1F *)file1->Get("PreselectedMC");
UHL=(TH1F *)file1->Get("UHL");
PreselecteHL=(TH1F *)file1->Get("PreselectedHL");
Discr1_TMCP=(TH2F *)file1->Get("Discr1_TMCP");
Discr1_TMCD=(TH2F *)file1->Get("Discr1_TMCD");
Discr1_TMCHe=(TH2F *)file1->Get("Discr1_TMCHe");
Discr2_TMCP=(TH2F *)file1->Get("Discr2_TMCP");
Discr2_TMCD=(TH2F *)file1->Get("Discr2_TMCD");
Discr2_TMCHe=(TH2F *)file1->Get("Discr2_TMCHe");
Discr3_TMCP=(TH2F *)file1->Get("Discr3_TMCP");
Discr3_TMCD=(TH2F *)file1->Get("Discr3_TMCD");
Discr3_TMCHe=(TH2F *)file1->Get("Discr3_TMCHe");
TH2F * Discr1_T_Prim=(TH2F *)file1->Get("Discr1_TPrim");
TH2F * Discr2_T_Prim=(TH2F *)file1->Get("Discr2_TPrim");
TH2F * Discr3_T_Prim=(TH2F *)file1->Get("Discr3_TPrim");
ContCheckPTOF=(TH2F *)file1->Get("ContCheckPTOF");
ContCheckDTOF=(TH2F *)file1->Get("ContCheckDTOF");
cout<<ContCheckPTOF<<" "<<ContCheckDTOF<<endl;
for(int i=0;i<11;i++) {
        nome="PCountsD"+numero[i];
        PCountsD[i]= (TH1F *)file1->Get(nome.c_str());
        nome="PCountsQ"+numero[i];
        PCountsQ[i]= (TH1F *)file1->Get(nome.c_str());
	nome="PCountsDPrim"+numero[i];
        PCountsDPrim[i]= (TH1F *)file1->Get(nome.c_str());
        nome="PCountsQPrim"+numero[i];
        PCountsQPrim[i]= (TH1F *)file1->Get(nome.c_str());
	nome="Esposizione"+numero[i];
        Esposizione[i]= (TH1F *)file1->Get(nome.c_str());
	nome="Unbias"+numero[i];
	Unbias[i]= (TH1F *)file1->Get(nome.c_str());
	nome="UPreselected"+numero[i];
        UPreselected[i]= (TH1F *)file1->Get(nome.c_str());
	nome="Discr1_T"+numero[i];
	Discr1_T[i]=(TH2F *)file1->Get(nome.c_str());
	nome="Discr2_T"+numero[i];
        Discr2_T[i]=(TH2F *)file1->Get(nome.c_str());
	nome="Discr3_T"+numero[i];
        Discr3_T[i]=(TH2F *)file1->Get(nome.c_str());
	if(i<10){
	nome="Selezioni"+tagli[i];
	selezioni_P[i]=(TH2F *)file1->Get(nome.c_str());
	nome="Selected"+tagli[i];
	selected_P[i]=(TH2F *)file1->Get(nome.c_str());
	nome="SelezioniHL"+tagli[i];
        selezioni_PHL[i]=(TH1F *)file1->Get(nome.c_str());
        nome="SelectedHL"+tagli[i];
        selected_PHL[i]=(TH1F *)file1->Get(nome.c_str());
	nome="SelezioniHL_D"+tagli[i];
        selezioni_DHL[i]=(TH1F *)file1->Get(nome.c_str());
        nome="SelectedHL_D"+tagli[i];
        selected_DHL[i]=(TH1F *)file1->Get(nome.c_str());
	nome="SelezioniHL_MC"+tagli[i];
        selezioni_PHLMC[i]=(TH1F *)file1->Get(nome.c_str());
        nome="SelectedHL_MC"+tagli[i];
        selected_PHLMC[i]=(TH1F *)file1->Get(nome.c_str());
	nome="SelezioniHL_MCD"+tagli[i];
        selezioni_DHLMC[i]=(TH2F *)file1->Get(nome.c_str());
        nome="SelectedHL_MCD"+tagli[i];
        selected_DHLMC[i]=(TH2F *)file1->Get(nome.c_str());
	}
	
}

cout<<"*************************************************************************************** TEMPLATES CHARGE *******************************************************************************************"<<endl;
cout<<"******* TEMPLATE QL1 ***********"<<endl;
TCanvas *c1=new TCanvas("Template QL1");
c1->cd(1);

THStack *QL1=new THStack("","");
TplL1_P->SetFillColor(2);
TplL1_He->SetFillColor(3);
E_depL1->GetXaxis()->SetRangeUser(0,0.9);
E_depL1->GetXaxis()->SetTitleSize(0.045);
E_depL1->GetXaxis()->SetTitle("L1 En. Dep. [keV]");
c1->SetLogy();
{
TH1F *ResultQL1;
        TObjArray *Tpl = new TObjArray(2);
        Tpl->Add(TplL1_P);
        Tpl->Add(TplL1_He);
        TFractionFitter* fit = new TFractionFitter(E_depL1, Tpl,"q");
	int s=fit->Fit();
        std::cout << "fit status: " << s << std::endl;
        double w1,w2,w3=1;
        double e1,e2,e3=1;
        if(s==0){
                fit->GetResult(0,w1,e1);
                fit->GetResult(1,w2,e2);
                cout<<w1<<" "<<w2<<" "<<w3<<endl;
                ResultQL1 = (TH1F*) fit->GetPlot();
                float itot= ResultQL1->Integral();
                float i1 = TplL1_P->Integral();
                float i2 = TplL1_He->Integral();
                if(i1>0) for(int i=0; i<TplL1_P->GetNbinsX();i++) TplL1_P->SetBinContent(i,w1*TplL1_P->GetBinContent(i)/i1*itot);
                if(i2>0) for(int i=0; i<TplL1_He->GetNbinsX();i++) TplL1_He->SetBinContent(i,w2*TplL1_He->GetBinContent(i)/i2*itot);
		QL1->Add(TplL1_P);
		QL1->Add(TplL1_He);
		E_depL1->Draw("ep");
		QL1->Draw("same");
		ResultQL1->SetLineColor(5);
		ResultQL1->Draw("SAME");
        }
        if(s!=0){
        TplL1_P->SetFillStyle(3001);
        TplL1_He->SetFillStyle(3001);
        QL1->Add(TplL1_P);
        QL1->Add(TplL1_He);
	E_depL1->Draw("ep");
        QL1->Draw("same");
	}
}
TCanvas *c2=new TCanvas("QL1 Helium cut");
c2->cd();
c2->SetGridx();
c2->SetGridy();

TGraph *ContvsCut = new TGraph();
ContvsCut->SetTitle("Protons Contamination vs Cut");
float efficienza1=0;float efficienza2=0;
for(int j=0;j<=TplL1_P->GetNbinsX()+1;j++){
        efficienza1=0;
        efficienza2=0;
	double taglio=TplL1_P->GetBinCenter(j);
	if(taglio>0.9) continue;
	for(int i=TplL1_P->GetNbinsX(); i>=0;i--)
            if(TplL1_P->GetBinCenter(i)>=taglio) {efficienza1=efficienza1+TplL1_P->GetBinContent(i);}
	for(int i=TplL1_He->GetNbinsX(); i>=0;i--)
            if(TplL1_He->GetBinCenter(i)>=taglio) {efficienza2=efficienza2+TplL1_He->GetBinContent(i);}
	ContvsCut->SetPoint(j,taglio,efficienza1/(float)efficienza2*100);  
}

ContvsCut->SetLineColor(2);
ContvsCut->SetLineWidth(2);
ContvsCut->GetXaxis()->SetRangeUser(0.2,0.9);
ContvsCut->GetXaxis()->SetTitle("L1 E.dep. Cut");
ContvsCut->GetXaxis()->SetTitleSize(0.045);
ContvsCut->GetYaxis()->SetTitle("P contam. in He Template");
ContvsCut->GetYaxis()->SetTitleSize(0.045);
ContvsCut->GetYaxis()->SetRangeUser(0,24);
ContvsCut->Draw("AC");

cout<<"******* TEMPLATE YTrack ***********"<<endl;
TCanvas *c3=new TCanvas("Template YTrack");
c3->cd(1);
c3->SetLogy();

TplY_Track_P->SetFillColor(2);
TplY_Track_He->SetFillColor(3);
cout<<"cwe"<<endl;
THStack *Y=new THStack("","");
{
	TH1F *ResultYTrack;
        TObjArray *TplY = new TObjArray(2);
        TplY->Add(TplY_Track_P);
        TplY->Add(TplY_Track_He);
        TFractionFitter* fit = new TFractionFitter(Y_Track, TplY,"q");
        int s=fit->Fit();
        std::cout << "fit status: " << s << std::endl;
        double w1,w2,w3=1;
        double e1,e2,e3=1;
        if(s==0){
                fit->GetResult(0,w1,e1);
                fit->GetResult(1,w2,e2);
                cout<<w1<<" "<<w2<<" "<<w3<<endl;
                ResultYTrack = (TH1F*) fit->GetPlot();
                float itot= ResultYTrack->Integral();
                float i1 = TplY_Track_P->Integral();
                float i2 = TplY_Track_He->Integral();
                if(i1>0) for(int i=0; i<TplY_Track_P->GetNbinsX();i++) TplY_Track_P->SetBinContent(i,w1*TplY_Track_P->GetBinContent(i)/i1*itot);
                if(i2>0) for(int i=0; i<TplY_Track_He->GetNbinsX();i++)TplY_Track_He->SetBinContent(i,w2*TplY_Track_He->GetBinContent(i)/i2*itot);
                Y->Add(TplY_Track_P);
                Y->Add(TplY_Track_He);
                Y_Track->Draw("ep");
                Y->Draw("same");
                ResultYTrack->SetLineColor(5);
                ResultYTrack->Draw("SAME");
        }
        if(s!=0){
        TplY_Track_P->SetFillStyle(3001);
        TplY_Track_He->SetFillStyle(3001);
        Y->Add(TplY_Track_P);
        Y->Add(TplY_Track_He);
        Y_Track->Draw("ep");
        Y->Draw("same");
        }

}
cout<<"Rapp. HE "<<TplY_Track_He->Integral(0,242,"")/(float)TplY_Track_He->Integral(242,990,"")*100<<endl;

cout<<"************************************************************************************ MC PRESELECTION EFFICIENCIES **********************************************************************************"<<endl;
TCanvas *c4=new TCanvas("MC Pres. Efficiency");
c4->Divide(2,1);
float EffpreselMCP[18]={0};
for(int i=0;i<17;i++) if(EffpreselMCP1->GetBinContent(i+1)>0) EffpreselMCP[i]=EffpreselMCP2->GetBinContent(i+1)/(float)EffpreselMCP1->GetBinContent(i+1);
float EffpreselMCD[18][6]={{0}};
for(int i=0;i<17;i++) for(int h=0;h<6;h++) if(EffpreselMCD2->GetBinContent(i+1,h+1)<EffpreselMCD1->GetBinContent(i+1,h+1)) 
								EffpreselMCD[i][h]=EffpreselMCD2->GetBinContent(i+1,h+1)/(float)EffpreselMCD1->GetBinContent(i+1,h+1);

float EffpreselMCP_R[43]={0};
for(int i=1;i<43;i++) EffpreselMCP_R[i]=EffpreselMCP2_R->GetBinContent(i+1)/(float)EffpreselMCP1_R->GetBinContent(i+1);
float EffpreselMCD_R[43][6]={{0}};
for(int i=4;i<43;i++) for(int h=0;h<6;h++) if(EffpreselMCD2_R->GetBinContent(i+1,h+1)<EffpreselMCD1_R->GetBinContent(i+1,h+1)) 
								EffpreselMCD_R[i][h]=EffpreselMCD2_R->GetBinContent(i+1,h+1)/(float)EffpreselMCD1_R->GetBinContent(i+1,h+1);
					
c4->cd(1);
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
TGraph * EffPreMCP_R = new TGraph();
for(int i=0;i<43;i++) EffPreMCP_R->SetPoint(i,R_cent[i],EffpreselMCP_R[i]); 
TGraph * EffPreMCD_R[6]; 
EffPreMCP_R->SetMarkerColor(2);
EffPreMCP_R->SetMarkerStyle(8);
EffPreMCP_R->SetLineColor(2);
EffPreMCP_R->SetLineWidth(2);
EffPreMCP_R->SetTitle("Efficienza Preselezioni MC (R bins)");
EffPreMCP_R->GetXaxis()->SetTitle("R [GV]");
EffPreMCP_R->GetYaxis()->SetTitle("Pres. Efficiency");
EffPreMCP_R->GetXaxis()->SetTitleSize(0.045);
EffPreMCP_R->GetYaxis()->SetTitleSize(0.045);
EffPreMCP_R->Draw("ACP");
for(int h=0;h<6;h++){
        EffPreMCD_R[h]= new TGraph();
        for(int i=1;i<43;i++) EffPreMCD_R[h]->SetPoint(i,R_cent[i],EffpreselMCD_R[i][h]);
        EffPreMCD_R[h]->SetMarkerColor(4);
        EffPreMCD_R[h]->SetMarkerStyle(h+3);
	EffPreMCD_R[h]->SetMarkerSize(2);
        EffPreMCD_R[h]->SetLineColor(4);
        EffPreMCD_R[h]->SetLineWidth(2);
        EffPreMCD_R[h]->Draw("CPsame");
}
c4->cd(2);
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
TGraph * EffPreMCP = new TGraph();
for(int i=0;i<17;i++) EffPreMCP->SetPoint(i,encinbeta[i],EffpreselMCP[i]);
TGraph * EffPreMCD[6]; 
EffPreMCP->SetMarkerColor(2);
EffPreMCP->SetMarkerStyle(8);
EffPreMCP->SetLineColor(2);
EffPreMCP->SetLineWidth(2);
EffPreMCP->SetTitle("Efficienza Preselezioni MC (Beta bins)");
EffPreMCP->GetXaxis()->SetTitle("Kin. En. / nucl. [GeV/nucl.]");
EffPreMCP->GetYaxis()->SetTitle("Pres. Efficiency");
EffPreMCP->GetXaxis()->SetTitleSize(0.045);
EffPreMCP->GetYaxis()->SetTitleSize(0.045);
EffPreMCP->Draw("ACP");
for(int h=0;h<6;h++){
         EffPreMCD[h]= new TGraph();
        for(int i=0;i<17;i++) EffPreMCD[h]->SetPoint(i,encinbeta[i],EffpreselMCD[i][h]);
        EffPreMCD[h]->SetMarkerColor(4);
        EffPreMCD[h]->SetMarkerStyle(h+3);
	EffPreMCD[h]->SetMarkerSize(2);
        EffPreMCD[h]->SetLineColor(4);
        EffPreMCD[h]->SetLineWidth(2);
        EffPreMCD[h]->Draw("CPsame");
}

cout<<"************************************************************************************* MC QUAL. SELECTION EFFICIENCIES ******************************************************************************"<<endl;
TCanvas *c5=new TCanvas("MC Qual. Sel. Efficiency");
c5->Divide(2,1);
float Eff_DistMCP[43]={0};
for(int i=1;i<43;i++) Eff_DistMCP[i]=EffDistMCP->GetBinContent(i+1)/(float)EffpreselMCP2_R->GetBinContent(i+1);

float Eff_QualMCP[43]={0};
for(int i=1;i<43;i++) Eff_QualMCP[i]=EffQualMCP->GetBinContent(i+1)/(float)EffpreselMCP2_R->GetBinContent(i+1);

float Eff_DistMCD[43][6]={{0}};
for(int i=1;i<43;i++) for(int h=0;h<6;h++) if(EffpreselMCD2_R->GetBinContent(i+1,h+1)>400) Eff_DistMCD[i][h]=EffDistMCD->GetBinContent(i+1,h+1)/(float)EffpreselMCD2_R->GetBinContent(i+1,h+1);

float Eff_QualMCD[43][6]={{0}};
for(int i=1;i<43;i++) for(int h=0;h<6;h++) if(EffpreselMCD2_R->GetBinContent(i+1,h+1)>400) Eff_QualMCD[i][h]=EffQualMCD->GetBinContent(i+1,h+1)/(float)EffpreselMCD2_R->GetBinContent(i+1,h+1);

c5->cd(1);
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
TGraph * EffDistanceMCP = new TGraph();
for(int i=1;i<43;i++) EffDistanceMCP->SetPoint(i,R_cent[i],Eff_DistMCP[i]);
TGraph * EffDistanceMCD[6]; 
EffDistanceMCP->SetMarkerColor(2);
EffDistanceMCP->SetMarkerStyle(8);
EffDistanceMCP->SetLineColor(2);
EffDistanceMCP->SetLineWidth(2);
EffDistanceMCP->SetTitle("Efficienza Distance Quality Selection MC (R bins)");
EffDistanceMCP->GetXaxis()->SetTitle("R [GV]");
EffDistanceMCP->GetYaxis()->SetTitle("Dist<4 Sel. Efficiency");
EffDistanceMCP->GetXaxis()->SetTitleSize(0.045);
EffDistanceMCP->GetYaxis()->SetTitleSize(0.045);
EffDistanceMCP->Draw("ACP");
for(int h=0;h<6;h++){
        EffDistanceMCD[h]= new TGraph();
        for(int i=1;i<43;i++) EffDistanceMCD[h]->SetPoint(i,R_cent[i],Eff_DistMCD[i][h]);
        EffDistanceMCD[h]->SetMarkerColor(4);
        EffDistanceMCD[h]->SetMarkerStyle(h);
        EffDistanceMCD[h]->SetMarkerSize(3);
	EffDistanceMCD[h]->SetLineColor(4);
        EffDistanceMCD[h]->SetLineWidth(2);
        EffDistanceMCD[h]->Draw("CPsame");
}

c5->cd(2);
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
TGraph * EffQualityMCP = new TGraph();
for(int i=1;i<43;i++) EffQualityMCP->SetPoint(i,R_cent[i],Eff_QualMCP[i]);
TGraph * EffQualityMCD[6];
EffQualityMCP->SetMarkerColor(2);	
EffQualityMCP->SetMarkerStyle(8);
EffQualityMCP->SetLineColor(2);
EffQualityMCP->SetLineWidth(2);
EffQualityMCP->GetXaxis()->SetTitle("R [GV]");
EffQualityMCP->GetYaxis()->SetTitle("L>0.95 Sel. Efficiency");
EffQualityMCP->GetXaxis()->SetTitleSize(0.045);
EffQualityMCP->GetYaxis()->SetTitleSize(0.045);
EffQualityMCP->Draw("ACP");
for(int h=0;h<6;h++){
        EffQualityMCD[h] = new TGraph();
        for(int i=1;i<43;i++) EffQualityMCD[h]->SetPoint(i,R_cent[i],Eff_QualMCD[i][h]);
        EffQualityMCD[h]->SetMarkerColor(4);
        EffQualityMCD[h]->SetMarkerStyle(h);
        EffQualityMCD[h]->SetMarkerSize(3);
        EffQualityMCD[h]->SetLineColor(4);
        EffQualityMCD[h]->SetLineWidth(2);
        EffQualityMCD[h]->Draw("CPsame");
}
cout<<"************************************************************************************** MC ACCEPTANCE CALCULATION ***********************************************************************************"<<endl;
TCanvas *c6=new TCanvas("MC Acceptance");
c6->Divide(2,1);
float eventiprova=0;
for(int i=1;i<43;i++) eventiprova+=EffpreselMCP1_R->GetBinContent(i+1);
float triggerbin=(pow(0.0308232619,-1))*eventiprova/43;
float eventiprova_D[6]={0};
for(int h=0;h<6;h++) for(int i=1;i<43;i++) eventiprova_D[h]+=EffpreselMCD1_R->GetBinContent(i+1,h+1);
float triggerbin_D[6];
for(int h=0;h<6;h++) triggerbin_D[h]=(pow(0.0242236931,-1))*eventiprova_D[h]/25;

float AcceptDistMCP[43]={0};
for(int i=1;i<43;i++) AcceptDistMCP[i]=Eff_DistMCP[i]*EffpreselMCP_R[i]*(EffpreselMCP1_R->GetBinContent(i+1)/triggerbin)*47.78;

float AcceptQualMCP[43]={0};
for(int i=1;i<43;i++) AcceptQualMCP[i]=Eff_QualMCP[i]*EffpreselMCP_R[i]*(EffpreselMCP1_R->GetBinContent(i+1)/triggerbin)*47.78;

float AcceptDistMCD[43][6]={{0}};
for(int h=0;h<6;h++) for(int i=1;i<43;i++) AcceptDistMCD[i][h]=Eff_DistMCD[i][h]*EffpreselMCD_R[i][h]*(EffpreselMCD1_R->GetBinContent(i+1,h+1)/triggerbin_D[h])*47.78;

float AcceptQualMCD[43][6]={{0}};
for(int h=0;h<6;h++) for(int i=1;i<43;i++) AcceptQualMCD[i][h]=Eff_QualMCD[i][h]*EffpreselMCD_R[i][h]*(EffpreselMCD1_R->GetBinContent(i+1,h+1)/triggerbin_D[h])*47.78;
					   
c6->cd(1);
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
TGraph * AcceptD_MCP = new TGraph();
for(int i=1;i<43;i++) AcceptD_MCP->SetPoint(i,R_cent[i],AcceptDistMCP[i]);
TGraph * AcceptD_MCD[6]; 
AcceptD_MCP->SetMarkerColor(2);
AcceptD_MCP->SetMarkerStyle(8);
AcceptD_MCP->SetLineColor(2);
AcceptD_MCP->SetLineWidth(2);
AcceptD_MCP->SetTitle("Accettanza MC Dist 3D");
AcceptD_MCP->GetXaxis()->SetTitle("R [GV]");
AcceptD_MCP->GetYaxis()->SetTitle("Acceptance [m^2 sr]");
AcceptD_MCP->GetXaxis()->SetTitleSize(0.045);
AcceptD_MCP->GetYaxis()->SetTitleSize(0.045);
AcceptD_MCP->Draw("ACP");
for(int h=0;h<6;h++){
        AcceptD_MCD[h]= new TGraph();
        for(int i=1;i<43;i++) AcceptD_MCD[h]->SetPoint(i,R_cent[i],AcceptDistMCD[i][h]);
        AcceptD_MCD[h]->SetMarkerColor(4);
        AcceptD_MCD[h]->SetMarkerStyle(h);
        AcceptD_MCD[h]->SetMarkerSize(3);
        AcceptD_MCD[h]->SetLineColor(4);
        AcceptD_MCD[h]->SetLineWidth(2);
        AcceptD_MCD[h]->Draw("CPsame");
}

c6->cd(2);
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
TGraph * AcceptQ_MCP = new TGraph();
for(int i=1;i<43;i++) AcceptQ_MCP->SetPoint(i,R_cent[i],AcceptQualMCP[i]);
TGraph * AcceptQ_MCD[6];
AcceptQ_MCP->SetMarkerColor(2);
AcceptQ_MCP->SetMarkerStyle(8);
AcceptQ_MCP->SetLineColor(2);
AcceptQ_MCP->SetLineWidth(2);
AcceptQ_MCP->SetTitle("Accettanza MC Qual. L");
AcceptQ_MCP->GetXaxis()->SetTitle("R [GV]");
AcceptQ_MCP->GetYaxis()->SetTitle("Acceptance [m^2 sr]");
AcceptQ_MCP->GetXaxis()->SetTitleSize(0.045);
AcceptQ_MCP->GetYaxis()->SetTitleSize(0.045);
AcceptQ_MCP->Draw("ACP");
for(int h=0;h<6;h++){
        AcceptQ_MCD[h]= new TGraph();
        for(int i=1;i<43;i++) AcceptQ_MCD[h]->SetPoint(i,R_cent[i],AcceptQualMCD[i][h]);
        AcceptQ_MCD[h]->SetMarkerColor(4);
        AcceptQ_MCD[h]->SetMarkerStyle(h);
        AcceptQ_MCD[h]->SetMarkerSize(3);
        AcceptQ_MCD[h]->SetLineColor(4);
        AcceptQ_MCD[h]->SetLineWidth(2);
        AcceptQ_MCD[h]->Draw("CPsame");
}

cout<<"***************************************************************************************** LATITUDE EFFECT  *****************************************************************************************"<<endl;
cout<<"******** PRES. CUT BY CUT *******"<<endl;

TCanvas *c10[10];
for(int i=0;i<10;i++) c10[i]= new TCanvas(tagli[i].c_str());
for(int i=0;i<10;i++) c10[i]->Divide(3,1);

float Sel_eff[10][43][11]={{{0}}};
TGraphAsymmErrors * SelEff[10][11];
for(int S=0;S<10;S++){
	c10[S]->cd(1);	
	gPad->SetLogx();
	gPad->SetGridx();
	gPad->SetGridy();
	for(int i=1;i<11;i++)
		for(int j=1;j<43;j++)	if(selezioni_P[S]->GetBinContent(j+1,i+1)>400) Sel_eff[S][j][i]= selected_P[S]->GetBinContent(j+1,i+1)/selezioni_P[S]->GetBinContent(j+1,i+1);
	for(int i=1;i<11;i++){
		int point=0;
		SelEff[S][i]=new TGraphAsymmErrors();
		for(int j=1;j<43;j++)	if(Sel_eff[S][j][i]>0) {SelEff[S][i]->SetPoint(point,R_cent[j],Sel_eff[S][j][i]);point++;}
		}
	for(int i=1;i<10;i++) {
        SelEff[S][i]->SetMarkerColor(i);
        SelEff[S][i]->SetMarkerStyle(8);
	}
	SelEff[S][10]->SetMarkerColor(14);
	SelEff[S][10]->SetMarkerStyle(8);
	SelEff[S][10]->GetXaxis()->SetTitle("R [GV]");
	nome=tagli[S]+": Geo. Zone Efficiency ";
	SelEff[S][10]->SetTitle(nome.c_str());
	SelEff[S][10]->GetXaxis()->SetTitleSize(0.045);
	SelEff[S][10]->Draw("AP");
	SelEff[S][10]->GetYaxis()->SetRangeUser(0,1.2);
	for(int i=1;i<10;i++) SelEff[S][i]->Draw("Psame");
}

cout<<"******** Correzione CUT BY CUT *******"<<endl;
double Tau_D[10][11]={{0}};
float HEeff1[10][11]={{0}};
float HEeff2[10][11]={{0}};
float HEeff[10][11]={{0}};
float Sel_eff_corr[10][43][11]={{{0}}};

for(int S=0;S<10;S++){
	for(int i=1;i<11;i++)
                for(int j=30;j<43;j++) {HEeff1[S][i]+=selezioni_P[S]->GetBinContent(j+1,i+1);HEeff2[S][i]+=selected_P[S]->GetBinContent(j+1,i+1);}
}
for(int S=0;S<10;S++)
        for(int i=1;i<11;i++){HEeff[S][i]=HEeff2[S][i]/HEeff1[S][i];}

for(int S=0;S<10;S++)
        for(int i=1;i<11;i++) Tau_D[S][i]=(HEeff[S][1])/HEeff[S][i]; //-log(HEeff[S][i]/HEeff[S][1])/HEeff[S][1]; //(HEeff[S][1]-HEeff[S][i])/(HEeff[S][1]*HEeff[S][i]); // (HEeff[S][1])/HEeff[S][i];// -log(HEeff[S][i]/HEeff[S][1])/HEeff[S][1];
	
for(int S=0;S<10;S++) cout<<tagli[S].c_str()<<" "<<Tau_D[S][10]<< endl; 

for(int S=0;S<10;S++){
	for(int i=1;i<11;i++)
                for(int j=1;j<43;j++) Sel_eff_corr[S][j][i]= /*Sel_eff[S][j][i]/(1-Tau_D[S][i]*Sel_eff[S][j][i]);*/  Sel_eff[S][j][i]*(Tau_D[S][i]);//*(1+Tau_D[S][i]); TrovaZero(Sel_eff[S][j][i],Tau_D[S][i]);
}


TGraphAsymmErrors * SelEffCorr[10][11];
TGraphAsymmErrors * CorrLAT[10];

for(int S=0;S<10;S++){
        c10[S]->cd(2);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
	for(int i=1;i<11;i++){
                int point=0;
                SelEffCorr[S][i]=new TGraphAsymmErrors();
                for(int j=1;j<43;j++)   {SelEffCorr[S][i]->SetPoint(point,R_cent[j],Sel_eff_corr[S][j][i]);point++;}
                }
	for(int i=1;i<10;i++) {
        SelEffCorr[S][i]->SetMarkerColor(i);
        SelEffCorr[S][i]->SetMarkerStyle(8);
        }
        SelEffCorr[S][10]->SetMarkerColor(14);
        SelEffCorr[S][10]->SetMarkerStyle(8);
	nome=tagli[S]+": Geo. Zone Efficiency (Corrected) ";
        SelEffCorr[S][10]->SetTitle(nome.c_str());
        SelEffCorr[S][10]->Draw("AP");
        SelEffCorr[S][10]->GetYaxis()->SetRangeUser(0,1.2);
         SelEffCorr[S][10]->GetXaxis()->SetTitle("R [GV]");
	 SelEffCorr[S][10]->GetXaxis()->SetTitleSize(0.045);
	for(int i=1;i<10;i++) SelEffCorr[S][i]->Draw("Psame");
	
	c10[S]->cd(3);
        gPad->SetGridx();
        gPad->SetGridy();
	CorrLAT[S]=new TGraphAsymmErrors();
	int point=0;
	for(int i=1;i<11;i++) {CorrLAT[S]->SetPoint(point,geomagC[i],(Tau_D[S][i]));point++;}
	CorrLAT[S]->GetYaxis()->SetRangeUser(0.9,2);
	CorrLAT[S]->GetYaxis()->SetTitle("Eff. Corr. Factor");
	CorrLAT[S]->GetXaxis()->SetTitle("Latitude");
	CorrLAT[S]->GetYaxis()->SetTitleSize(0.045);
        CorrLAT[S]->GetXaxis()->SetTitleSize(0.045);
	CorrLAT[S]->SetTitle("Correction Factor vs LAT.");
	CorrLAT[S]->SetMarkerColor(1);
	CorrLAT[S]->SetMarkerStyle(8);
	CorrLAT[S]->Draw("APC");
}
cout<<"******** PRES. FULL SET *******"<<endl;
TCanvas *c8=new TCanvas("Preselections (FULL SET) Lat. Eff.");
c8->Divide(2,1);
float effPresGeo[43][11]={{0}};
float effPresMC[43]={0}; 
float HEFSeff1[11]={0};
float HEFSeff2[11]={0};
float HEFSeff[11]={0};

for(int i=1;i<11;i++)
        for(int j=1;j<43;j++)    {effPresGeo[j][i]=UPreselected[i]->GetBinContent(j+1)/Unbias[i]->GetBinContent(j+1);
								   if(j>30) {HEFSeff1[i]+=Unbias[i]->GetBinContent(j+1); HEFSeff2[i]+=UPreselected[i]->GetBinContent(j+1);}
									}
for(int j=1;j<43;j++) effPresMC[j]=PreselecteMC->GetBinContent(j+1)/UMC->GetBinContent(j+1);


for(int i=1;i<11;i++) HEFSeff[i]=HEFSeff2[i]/HEFSeff1[i];
TGraphAsymmErrors * EffPresGeo[11];
for(int i=1;i<11;i++) EffPresGeo[i]=new TGraphAsymmErrors();
int p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) if(effPresGeo[j][i]>0) {EffPresGeo[i]->SetPoint(p,R_cent[j],effPresGeo[j][i]); p++;}
}
c8->cd(1);
gPad->SetGridx();
gPad->SetGridy();
for(int i=1;i<10;i++) {
        EffPresGeo[i]->SetMarkerColor(i);
        EffPresGeo[i]->SetMarkerStyle(8);
        }
EffPresGeo[10]->SetTitle("Preselection Efficiencies");
EffPresGeo[10]->GetXaxis()->SetTitle("R [GV]");
EffPresGeo[10]->SetMarkerColor(14);
EffPresGeo[10]->SetMarkerStyle(8);
EffPresGeo[10]->Draw("AP"); 
EffPresGeo[10]->GetYaxis()->SetRangeUser(0,1.2);
for(int i=1;i<10;i++) EffPresGeo[i]->Draw("Psame");

cout<<"******** Correzione FULL SET *******"<<endl;
double correzioneLAT[11]={1,1,1,1,1,1,1,1,1,1,1};
float effPresGeo_corr[43][11]={{0}};

for(int i=1;i<11;i++){ for(int S=0;S<10;S++) {correzioneLAT[i]*=(Tau_D[S][i]);}}
for(int i=1;i<11;i++)
        for(int j=1;j<43;j++) effPresGeo_corr[j][i]=effPresGeo[j][i]*correzioneLAT[i];//effPresGeo[j][i]/(1-(correzioneLAT[i]-1)*effPresGeo[j][i]);// TrovaZero(effPresGeo[j][i],correzioneLAT[i]-1); 

TGraphAsymmErrors * EffPresGeoCorr[11];
for(int i=1;i<11;i++) EffPresGeoCorr[i]=new TGraphAsymmErrors();
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) if(effPresGeo_corr[j][i]>0) {EffPresGeoCorr[i]->SetPoint(p,R_cent[j],effPresGeo_corr[j][i]); p++;}
}
c8->cd(2);
gPad->SetGridx();
gPad->SetGridy();
for(int i=1;i<10;i++) {
        EffPresGeoCorr[i]->SetMarkerColor(i);
        EffPresGeoCorr[i]->SetMarkerStyle(8);
        }
EffPresGeoCorr[10]->SetTitle("Preselection Efficiencies");
EffPresGeoCorr[10]->GetXaxis()->SetTitle("R [GV]");
EffPresGeoCorr[10]->SetMarkerColor(14);
EffPresGeoCorr[10]->SetMarkerStyle(8);
EffPresGeoCorr[10]->Draw("AP");
EffPresGeoCorr[10]->GetYaxis()->SetRangeUser(0,1.2);
for(int i=1;i<10;i++) EffPresGeoCorr[i]->Draw("Psame");

cout<<"******** Efficienze geo QUALITY *******"<<endl;
TCanvas *c27=new TCanvas("Distance Selections Geo CUT BY CUT");
c27->Divide(3,1);
TCanvas *c11=new TCanvas("Quality Selections Geo Efficiencies");
c11->Divide(2,1);
TCanvas *c30=new TCanvas("Quality L&D Geo Efficiencies");
c30->Divide(2,1);
float Sel_effQLMC[43]={0};
float Sel_effQDMC[43]={0};
float Sel_effQLDMC[43]={0};

for(int j=1;j<43;j++) {Sel_effQLMC[j]= selectedQLHLMC->GetBinContent(j+1)/selezioniQHLMC->GetBinContent(j+1);
                       Sel_effQDMC[j]= selectedQDHLMC->GetBinContent(j+1)/selezioniQHLMC->GetBinContent(j+1);
		       Sel_effQLDMC[j]= selectedQLDHLMC->GetBinContent(j+1)/selezioniQHLMC->GetBinContent(j+1);	
			}


float effQualDGeo[43][11]={{0}};
float effQualDGeoTOF[43][11]={{0}};
float effQualDGeoTrack[43][11]={{0}};
float effQualDGeoTRD[43][11]={{0}};
float effQualLGeo[43][11]={{0}};
float effQualLDGeo[43][11]={{0}};

for(int i=1;i<11;i++)
        for(int j=1;j<43;j++) {
				effQualDGeo[j][i]=selectedQD->GetBinContent(j+1,i+1)/selezioniQ->GetBinContent(j+1,i+1);
				effQualDGeoTOF[j][i]=selectedQDTOF->GetBinContent(j+1,i+1)/selezioniQ->GetBinContent(j+1,i+1);
				effQualDGeoTrack[j][i]=selectedQDTrack->GetBinContent(j+1,i+1)/selezioniQ->GetBinContent(j+1,i+1);
				effQualDGeoTRD[j][i]=selectedQDTRD->GetBinContent(j+1,i+1)/selezioniQ->GetBinContent(j+1,i+1);
				effQualLGeo[j][i]=selectedQL->GetBinContent(j+1,i+1)/selezioniQ->GetBinContent(j+1,i+1);
				effQualLDGeo[j][i]=selectedQLD->GetBinContent(j+1,i+1)/selezioniQ->GetBinContent(j+1,i+1);
				}	

TGraphAsymmErrors * EffQualDGeo[11];
for(int i=1;i<11;i++) EffQualDGeo[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualDGeoTOF[11];
for(int i=1;i<11;i++) EffQualDGeoTOF[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualDGeoTrack[11];
for(int i=1;i<11;i++) EffQualDGeoTrack[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualDGeoTRD[11];
for(int i=1;i<11;i++) EffQualDGeoTRD[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualLGeo[11];
for(int i=1;i<11;i++) EffQualLGeo[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualLDGeo[11];
for(int i=1;i<11;i++) EffQualLDGeo[i]=new TGraphAsymmErrors();
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualDGeo[i]->SetPoint(p,R_cent[j],effQualDGeo[j][i]); p++;}
}
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualDGeoTOF[i]->SetPoint(p,R_cent[j],effQualDGeoTOF[j][i]); p++;}
}
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualDGeoTrack[i]->SetPoint(p,R_cent[j],effQualDGeoTrack[j][i]); p++;}
}
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualDGeoTRD[i]->SetPoint(p,R_cent[j],effQualDGeoTRD[j][i]); p++;}
}

p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualLGeo[i]->SetPoint(p,R_cent[j],effQualLGeo[j][i]); p++;}
}
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualLDGeo[i]->SetPoint(p,R_cent[j],effQualLDGeo[j][i]); p++;}
}

c27->cd(1);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualDGeoTOF[i]->SetMarkerColor(i);
        EffQualDGeoTOF[i]->SetMarkerStyle(8);
        }
EffQualDGeoTOF[10]->SetTitle("Quality 3D Selection (TOF) Efficiencies");
EffQualDGeoTOF[10]->GetXaxis()->SetTitle("R [GV]");
EffQualDGeoTOF[10]->SetMarkerColor(14);
EffQualDGeoTOF[10]->SetMarkerStyle(8);
EffQualDGeoTOF[10]->Draw("AP");
EffQualDGeoTOF[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualDGeoTOF[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualDGeoTOF[i]->Draw("Psame");
c27->cd(2);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualDGeoTrack[i]->SetMarkerColor(i);
        EffQualDGeoTrack[i]->SetMarkerStyle(8);
        }
EffQualDGeoTrack[10]->SetTitle("Quality 3D Selection (Track) Efficiencies");
EffQualDGeoTrack[10]->GetXaxis()->SetTitle("R [GV]");
EffQualDGeoTrack[10]->SetMarkerColor(14);
EffQualDGeoTrack[10]->SetMarkerStyle(8);
EffQualDGeoTrack[10]->Draw("AP");
EffQualDGeoTrack[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualDGeoTrack[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualDGeoTrack[i]->Draw("Psame");
c27->cd(3);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualDGeoTRD[i]->SetMarkerColor(i);
        EffQualDGeoTRD[i]->SetMarkerStyle(8);
        }
EffQualDGeoTRD[10]->SetTitle("Quality 3D Selection (TRD) Efficiencies");
EffQualDGeoTRD[10]->GetXaxis()->SetTitle("R [GV]");
EffQualDGeoTRD[10]->SetMarkerColor(14);
EffQualDGeoTRD[10]->SetMarkerStyle(8);
EffQualDGeoTRD[10]->Draw("AP");
EffQualDGeoTRD[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualDGeoTRD[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualDGeoTRD[i]->Draw("Psame");

c11->cd(1);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualDGeo[i]->SetMarkerColor(i);
        EffQualDGeo[i]->SetMarkerStyle(8);
        }
EffQualDGeo[10]->SetTitle("Quality 3D Selection (TOT) Efficiencies");
EffQualDGeo[10]->GetXaxis()->SetTitle("R [GV]");
EffQualDGeo[10]->SetMarkerColor(14);
EffQualDGeo[10]->SetMarkerStyle(8);
EffQualDGeo[10]->Draw("AP");
EffQualDGeo[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualDGeo[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualDGeo[i]->Draw("Psame");

c11->cd(2);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualLGeo[i]->SetMarkerColor(i);
        EffQualLGeo[i]->SetMarkerStyle(8);
        }
EffQualLGeo[10]->SetTitle("Quality Likelihood Efficiencies");
EffQualLGeo[10]->GetXaxis()->SetTitle("R [GV]");
EffQualLGeo[10]->SetMarkerColor(14);
EffQualLGeo[10]->SetMarkerStyle(8);
EffQualLGeo[10]->Draw("AP");
EffQualLGeo[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualLGeo[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualLGeo[i]->Draw("Psame");

c30->cd(1);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualLDGeo[i]->SetMarkerColor(i);
        EffQualLDGeo[i]->SetMarkerStyle(8);
        }
EffQualLDGeo[10]->SetTitle("Quality L&D Efficiencies");
EffQualLDGeo[10]->GetXaxis()->SetTitle("R [GV]");
EffQualLDGeo[10]->SetMarkerColor(14);
EffQualLDGeo[10]->SetMarkerStyle(8);
EffQualLDGeo[10]->Draw("AP");
EffQualLDGeo[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualLDGeo[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualLDGeo[i]->Draw("Psame");

cout<<"******** Correzione QUALITY *******"<<endl;
TCanvas *c12=new TCanvas("Quality Selections Geo Efficiencies - Corr.");
c12->Divide(2,2);
TCanvas *c28=new TCanvas("Quality Selections Geo CUT BY CUT - Corr.");
c28->Divide(3,2);


double Tau_DQL[11]={0};
float HEeff1QL[11]={0};
float HEeff2QL[11]={0};
float HEeffQL[11]={0};
double Tau_DQD[11]={0};
double Tau_DQDTOF[11]={0};
double Tau_DQDTrack[11]={0};
double Tau_DQDTRD[11]={0};
float HEeff1QD[11]={0};
float HEeff2QD[11]={0};
float HEeffQD[11]={0};
float HEeffQDTOF[11]={0};
float HEeffQDTrack[11]={0};
float HEeffQDTRD[11]={0};
float HEeff2QDTOF[11]={0};
float HEeff2QDTrack[11]={0};
float HEeff2QDTRD[11]={0};



for(int i=1;i<11;i++)
                for(int j=30;j<43;j++) {HEeff1QL[i]+=selezioniQ->GetBinContent(j+1,i+1);HEeff2QL[i]+=selectedQL->GetBinContent(j+1,i+1);
					HEeff1QD[i]+=selezioniQ->GetBinContent(j+1,i+1);HEeff2QD[i]+=selectedQD->GetBinContent(j+1,i+1);				
					HEeff2QDTOF[i]+=selectedQDTOF->GetBinContent(j+1,i+1);HEeff2QDTrack[i]+=selectedQDTrack->GetBinContent(j+1,i+1);HEeff2QDTRD[i]+=selectedQDTRD->GetBinContent(j+1,i+1);
					}
for(int i=1;i<11;i++){
	HEeffQL[i]=HEeff2QL[i]/HEeff1QL[i];
	HEeffQD[i]=HEeff2QD[i]/HEeff1QD[i];	
	HEeffQDTOF[i]=HEeff2QDTOF[i]/HEeff1QD[i];
	HEeffQDTrack[i]=HEeff2QDTrack[i]/HEeff1QD[i];
	HEeffQDTRD[i]=HEeff2QDTRD[i]/HEeff1QD[i];
}

for(int i=1;i<11;i++) {Tau_DQL[i]=(HEeffQL[1])/HEeffQL[i];
		       Tau_DQD[i]=(HEeffQD[1])/HEeffQD[i];	
		       Tau_DQDTOF[i]=(HEeffQDTOF[1])/HEeffQDTOF[i];
			Tau_DQDTrack[i]=(HEeffQDTrack[1])/HEeffQDTrack[i];
			Tau_DQDTRD[i]=(HEeffQDTRD[1])/HEeffQDTRD[i];
}

TGraphAsymmErrors * EffQualDGeoCorr[11];
for(int i=1;i<11;i++) EffQualDGeoCorr[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualDGeoCorrTOF[11];
for(int i=1;i<11;i++) EffQualDGeoCorrTOF[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualDGeoCorrTrack[11];
for(int i=1;i<11;i++) EffQualDGeoCorrTrack[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualDGeoCorrTRD[11];
for(int i=1;i<11;i++) EffQualDGeoCorrTRD[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualLGeoCorr[11];
for(int i=1;i<11;i++) EffQualLGeoCorr[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * EffQualLDGeoCorr[11];
for(int i=1;i<11;i++) EffQualLDGeoCorr[i]=new TGraphAsymmErrors();

float effQualDGeoCorr[43][11]={{0}};
float effQualDGeoCorrTOF[43][11]={{0}};
float effQualDGeoCorrTrack[43][11]={{0}};
float effQualDGeoCorrTRD[43][11]={{0}};
float effQualLGeoCorr[43][11]={{0}};
float effQualLDGeoCorr[43][11]={{0}};

for(int i=1;i<11;i++)
        for(int j=1;j<43;j++) { effQualDGeoCorr[j][i]=Tau_DQD[i]*effQualDGeo[j][i]; //(1+(Tau_DQD[i]-1)*(HEeffQD[i]/effQualDGeo[j][i]))*effQualDGeo[j][i];
				effQualDGeoCorrTOF[j][i]=Tau_DQDTOF[i]*effQualDGeoTOF[j][i];
				effQualDGeoCorrTrack[j][i]=Tau_DQDTrack[i]*effQualDGeoTrack[j][i];
				effQualDGeoCorrTRD[j][i]=Tau_DQDTRD[i]*effQualDGeoTRD[j][i];
				effQualLGeoCorr[j][i]=Tau_DQL[i]*effQualLGeo[j][i]; //(1+(Tau_DQL[i]-1)*(HEeffQL[i]/effQualLGeo[j][i]))*effQualLGeo[j][i]; 
				effQualLDGeoCorr[j][i]=Tau_DQDTOF[i]*Tau_DQDTrack[i]*Tau_DQL[i]*effQualLDGeo[j][i];
				}
p=0;			       
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualDGeoCorr[i]->SetPoint(p,R_cent[j],effQualDGeoCorr[j][i]); p++;}}
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualDGeoCorrTOF[i]->SetPoint(p,R_cent[j],effQualDGeoCorrTOF[j][i]); p++;}}
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualDGeoCorrTrack[i]->SetPoint(p,R_cent[j],effQualDGeoCorrTrack[j][i]); p++;}}
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualDGeoCorrTRD[i]->SetPoint(p,R_cent[j],effQualDGeoCorrTRD[j][i]); p++;}}
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualLGeoCorr[i]->SetPoint(p,R_cent[j],effQualLGeoCorr[j][i]); p++;}}
p=0;
for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) {EffQualLDGeoCorr[i]->SetPoint(p,R_cent[j],effQualLDGeoCorr[j][i]); p++;}}


TGraphAsymmErrors * CorrLatQD = new TGraphAsymmErrors();
TGraphAsymmErrors * CorrLatQDCBC = new TGraphAsymmErrors();
TGraphAsymmErrors * CorrLatQDTOF = new TGraphAsymmErrors();
TGraphAsymmErrors * CorrLatQDTrack = new TGraphAsymmErrors();
TGraphAsymmErrors * CorrLatQDTRD = new TGraphAsymmErrors();
TGraphAsymmErrors * CorrLatQL = new TGraphAsymmErrors();
int point=0;
for(int i=1;i<11;i++) {CorrLatQD->SetPoint(point,geomagC[i],(Tau_DQD[i]));point++;}
point=0;
for(int i=1;i<11;i++) {CorrLatQDCBC->SetPoint(point,geomagC[i],(Tau_DQDTOF[i])*(Tau_DQDTrack[i]));point++;}
point=0;
for(int i=1;i<11;i++) {CorrLatQDTOF->SetPoint(point,geomagC[i],(Tau_DQDTOF[i]));point++;}
point=0;
for(int i=1;i<11;i++) {CorrLatQDTrack->SetPoint(point,geomagC[i],(Tau_DQDTrack[i]));point++;}
point=0;
for(int i=1;i<11;i++) {CorrLatQDTRD->SetPoint(point,geomagC[i],(Tau_DQDTRD[i]));point++;}
point=0;
for(int i=1;i<11;i++) {CorrLatQL->SetPoint(point,geomagC[i],(Tau_DQL[i]));point++;}

c28->cd(1);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualDGeoCorrTOF[i]->SetMarkerColor(i);
        EffQualDGeoCorrTOF[i]->SetMarkerStyle(8);
        }
EffQualDGeoCorrTOF[10]->SetTitle("Quality Distance Selection (TOF) Efficiencies (Corrected)");
EffQualDGeoCorrTOF[10]->GetXaxis()->SetTitle("R [GV]");
EffQualDGeoCorrTOF[10]->SetMarkerColor(14);
EffQualDGeoCorrTOF[10]->SetMarkerStyle(8);
EffQualDGeoCorrTOF[10]->Draw("AP");
EffQualDGeoCorrTOF[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualDGeoCorrTOF[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualDGeoCorrTOF[i]->Draw("Psame");

c28->cd(2);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualDGeoCorrTrack[i]->SetMarkerColor(i);
        EffQualDGeoCorrTrack[i]->SetMarkerStyle(8);
        }
EffQualDGeoCorrTrack[10]->SetTitle("Quality Distance Selection (Tracker) Efficiencies (Corrected)");
EffQualDGeoCorrTrack[10]->GetXaxis()->SetTitle("R [GV]");
EffQualDGeoCorrTrack[10]->SetMarkerColor(14);
EffQualDGeoCorrTrack[10]->SetMarkerStyle(8);
EffQualDGeoCorrTrack[10]->Draw("AP");
EffQualDGeoCorrTrack[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualDGeoCorrTrack[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualDGeoCorrTrack[i]->Draw("Psame");

c28->cd(3);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualDGeoCorrTRD[i]->SetMarkerColor(i);
        EffQualDGeoCorrTRD[i]->SetMarkerStyle(8);
        }
EffQualDGeoCorrTRD[10]->SetTitle("Quality Distance Selection (TRD) Efficiencies (Corrected)");
EffQualDGeoCorrTRD[10]->GetXaxis()->SetTitle("R [GV]");
EffQualDGeoCorrTRD[10]->SetMarkerColor(14);
EffQualDGeoCorrTRD[10]->SetMarkerStyle(8);
EffQualDGeoCorrTRD[10]->Draw("AP");
EffQualDGeoCorrTRD[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualDGeoCorrTRD[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualDGeoCorrTRD[i]->Draw("Psame");

c28->cd(4);
gPad->SetGridx();
gPad->SetGridy();
CorrLatQDTOF->SetMarkerColor(1);
CorrLatQDTOF->SetMarkerStyle(8);
CorrLatQDTOF->SetTitle("Latitude Correction Factors (TOF)");
CorrLatQDTOF->GetXaxis()->SetTitle("Latitude");
CorrLatQDTOF->GetXaxis()->SetTitleSize(0.045);
CorrLatQDTOF->GetYaxis()->SetRangeUser(-0.1,1.4);
CorrLatQDTOF->Draw("APC");

c28->cd(5);
gPad->SetGridx();
gPad->SetGridy();
CorrLatQDTrack->SetMarkerColor(1);
CorrLatQDTrack->SetMarkerStyle(8);
CorrLatQDTrack->SetTitle("Latitude Correction Factors (Tracker)");
CorrLatQDTrack->GetXaxis()->SetTitle("Latitude");
CorrLatQDTrack->GetXaxis()->SetTitleSize(0.045);
CorrLatQDTrack->GetYaxis()->SetRangeUser(-0.1,1.4);
CorrLatQDTrack->Draw("APC");

c28->cd(6);
gPad->SetGridx();
gPad->SetGridy();
CorrLatQDTRD->SetMarkerColor(1);
CorrLatQDTRD->SetMarkerStyle(8);
CorrLatQDTRD->SetTitle("Latitude Correction Factors (TRD)");
CorrLatQDTRD->GetXaxis()->SetTitle("Latitude");
CorrLatQDTRD->GetXaxis()->SetTitleSize(0.045);
CorrLatQDTRD->GetYaxis()->SetRangeUser(-0.1,1.4);
CorrLatQDTRD->Draw("APC");

c12->cd(1);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualDGeoCorr[i]->SetMarkerColor(i);
        EffQualDGeoCorr[i]->SetMarkerStyle(8);
        }
EffQualDGeoCorr[10]->SetTitle("Quality 3D Selection Efficiencies (Corrected)");
EffQualDGeoCorr[10]->GetXaxis()->SetTitle("R [GV]");
EffQualDGeoCorr[10]->SetMarkerColor(14);
EffQualDGeoCorr[10]->SetMarkerStyle(8);
EffQualDGeoCorr[10]->Draw("AP");
EffQualDGeoCorr[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualDGeoCorr[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualDGeoCorr[i]->Draw("Psame");

c12->cd(2);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualLGeoCorr[i]->SetMarkerColor(i);
        EffQualLGeoCorr[i]->SetMarkerStyle(8);
        }
EffQualLGeoCorr[10]->SetTitle("Quality Likelihood Efficiencies (Corrected)");
EffQualLGeoCorr[10]->GetXaxis()->SetTitle("R [GV]");
EffQualLGeoCorr[10]->SetMarkerColor(14);
EffQualLGeoCorr[10]->SetMarkerStyle(8);
EffQualLGeoCorr[10]->Draw("AP");
EffQualLGeoCorr[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualLGeoCorr[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualLGeoCorr[i]->Draw("Psame");

c12->cd(3);
gPad->SetGridx();
gPad->SetGridy();
CorrLatQD->SetMarkerColor(1);
CorrLatQD->SetMarkerStyle(8);
CorrLatQDCBC->SetMarkerColor(2);
CorrLatQDCBC->SetMarkerStyle(8);
CorrLatQD->SetTitle("Latitude Correction Factors");
CorrLatQD->GetXaxis()->SetTitle("Latitude");
CorrLatQD->GetXaxis()->SetTitleSize(0.045);
CorrLatQD->Draw("APC");
CorrLatQDCBC->Draw("PCsame");

c12->cd(4);
gPad->SetGridx();
gPad->SetGridy();
CorrLatQL->SetMarkerColor(1);
CorrLatQL->SetMarkerStyle(8);
CorrLatQL->SetTitle("Latitude Correction Factors");
CorrLatQL->GetXaxis()->SetTitle("Latitude");
CorrLatQL->GetXaxis()->SetTitleSize(0.045);
CorrLatQL->Draw("APC");

c30->cd(2);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffQualLDGeoCorr[i]->SetMarkerColor(i);
        EffQualLDGeoCorr[i]->SetMarkerStyle(8);
        }
EffQualLDGeoCorr[10]->SetTitle("Quality L&D Efficiencies (Corrected)");
EffQualLDGeoCorr[10]->GetXaxis()->SetTitle("R [GV]");
EffQualLDGeoCorr[10]->SetMarkerColor(14);
EffQualLDGeoCorr[10]->SetMarkerStyle(8);
EffQualLDGeoCorr[10]->Draw("AP");
EffQualLDGeoCorr[10]->GetYaxis()->SetRangeUser(0,1.2);
EffQualLDGeoCorr[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffQualLDGeoCorr[i]->Draw("Psame");


cout<<"********* TOTAL EFFECT EVALUATION **************"<<endl;
TCanvas *c13=new TCanvas("Total Correction");
c13->Divide(2,1);
TGraphAsymmErrors *Lat_EffD=new TGraphAsymmErrors();
TGraphAsymmErrors *Lat_EffL=new TGraphAsymmErrors();
float Espos_R[43]={0};
for(int i=1;i<11;i++)
        for(int j=0;j<43;j++)  {
                Espos_R[j]+=Esposizione[i]->GetBinContent(j);
}
float EffmeanL[11]={1,1,1,1,1,1,1,1,1,1,1};
float EffmeanD[11]={1,1,1,1,1,1,1,1,1,1,1};

for(int i=1;i<11;i++) for(int S=0;S<10;S++) {EffmeanL[i]*=HEeff[S][i];EffmeanD[i]*=HEeff[S][i];}
for(int i=1;i<11;i++) {EffmeanL[i]*=HEeffQL[i]; EffmeanD[i]*=HEeffQD[i];}
point=0;
for(int i=1;i<11;i++) {Lat_EffD->SetPoint(point,geomagC[i],(correzioneLAT[i]*Tau_DQD[i]));Lat_EffL->SetPoint(point,geomagC[i],(correzioneLAT[i]*Tau_DQL[i]));point++;}

TF1 * LatEff_D=new TF1("LatEffD","pol4",0.1,1.5);
TF1 * LatEff_L=new TF1("LatEffL","pol4",0.1,1.5);

Lat_EffD->Fit("LatEffD","q");
Lat_EffL->Fit("LatEffL","q");

float unoL,unoD=0;
float dueL,dueD=0;
float CorrLatTOTL[43]={0};
float CorrLatTOTD[43]={0};

/////////// METODO 1 ///////////////////
for(int j=1;j<43;j++){

	unoL=0;
	unoD=0;
	dueL=0;
	dueD=0;
	for(int i=1;i<PCountsDPrimLat->GetNbinsY();i++){
			unoL+=PCountsLPrimLat->GetBinContent(j+1,i+1)*LatEff_L->Eval(PCountsLPrimLat->GetYaxis()->GetBinCenter(i+1));
			unoD+=PCountsDPrimLat->GetBinContent(j+1,i+1)*LatEff_D->Eval(PCountsLPrimLat->GetYaxis()->GetBinCenter(i+1));
			dueL+=PCountsLPrimLat->GetBinContent(j+1,i+1);
			dueD+=PCountsDPrimLat->GetBinContent(j+1,i+1);
			}
	if(dueL>0) CorrLatTOTL[j]=unoL/dueL; 
	if(dueD>0) CorrLatTOTD[j]=unoD/dueD; 
}
//for(int j=1;j<43;j++) cout<<CorrLatTOTL[j]<<" ";
//cout<<endl;
/////////////////////////////////////////
//for(int j=1;j<43;j++) CorrLatTOTL[j]=0;
//for(int j=1;j<43;j++) CorrLatTOTD[j]=0;
/////////// METODO 2 ////////////////////
/*for(int j=1;j<43;j++){
	for(int i=1;i<11;i++){
		CorrLatTOTL[j]+=(correzioneLAT[i]*Tau_DQL[i])*Esposizione[i]->GetBinContent(j);
		CorrLatTOTD[j]+=(correzioneLAT[i]*Tau_DQD[i])*Esposizione[i]->GetBinContent(j);
		}
}
for(int j=1;j<43;j++){
	CorrLatTOTL[j]=CorrLatTOTL[j]/(float)Espos_R[j];
	CorrLatTOTD[j]=CorrLatTOTD[j]/(float)Espos_R[j];
}
for(int j=1;j<43;j++) cout<<CorrLatTOTL[j]<<" ";
cout<<endl;*/
/////////////////////////////////////////	
TGraphAsymmErrors *Lat_CorrD=new TGraphAsymmErrors();
TGraphAsymmErrors *Lat_CorrL=new TGraphAsymmErrors();

for(int j=1;j<43;j++){
	Lat_CorrD->SetPoint(j-1,R_cent[j],CorrLatTOTD[j]);
	Lat_CorrL->SetPoint(j-1,R_cent[j],CorrLatTOTL[j]);
}

c13->cd(1);
gPad->SetGridx();
gPad->SetGridy();
LatEff_D->SetLineColor(2);
LatEff_L->SetLineColor(4);
Lat_EffD->SetMarkerStyle(8);
Lat_EffD->SetMarkerColor(2);
Lat_EffD->Draw("AP");
Lat_EffD->GetXaxis()->SetTitle("Latitude");
Lat_EffD->GetXaxis()->SetTitleSize(0.045);
Lat_EffD->GetYaxis()->SetTitle("Total Corr. Factor");
Lat_EffD->GetYaxis()->SetTitleSize(0.045);
Lat_EffL->SetMarkerStyle(8);
Lat_EffL->SetMarkerColor(4);
Lat_EffL->Draw("Psame");
LatEff_D->Draw("same");
LatEff_L->Draw("same");

c13->cd(2);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
Lat_CorrD->SetLineColor(2);
Lat_CorrD->SetMarkerColor(2);
Lat_CorrD->SetMarkerStyle(8);
Lat_CorrL->SetLineColor(4);
Lat_CorrL->SetMarkerColor(4);
Lat_CorrL->SetMarkerStyle(8);
Lat_CorrD->GetXaxis()->SetTitle("R [GV]");
Lat_CorrD->GetXaxis()->SetTitleSize(0.045);
Lat_CorrD->GetYaxis()->SetTitle("Total Corr. Factor");
Lat_CorrD->GetYaxis()->SetTitleSize(0.045);
Lat_CorrD->Draw("APC");
Lat_CorrL->Draw("PCsame");

TCanvas * c18 = new TCanvas("Full set Selections Geo");
c18->Divide(2,2);
TGraphAsymmErrors * EffFS_D[11];
for(int i=1;i<11;i++) EffFS_D[i]=new TGraphAsymmErrors();

TGraphAsymmErrors * EffFS_L[11];
for(int i=1;i<11;i++) EffFS_L[i]=new TGraphAsymmErrors();

TGraphAsymmErrors * EffFS_DCorr[11];
for(int i=1;i<11;i++) EffFS_DCorr[i]=new TGraphAsymmErrors();

TGraphAsymmErrors * EffFS_LCorr[11];
for(int i=1;i<11;i++) EffFS_LCorr[i]=new TGraphAsymmErrors();

for(int i=1;i<11;i++)
        for(int j=1;j<43;j++) EffFS_D[i]->SetPoint(j-1,R_cent[j],effQualDGeo[j][i]*effPresGeo[j][i]);
for(int i=1;i<11;i++)
        for(int j=1;j<43;j++) EffFS_L[i]->SetPoint(j-1,R_cent[j],effQualLGeo[j][i]*effPresGeo[j][i]);

for(int i=1;i<11;i++)
        for(int j=1;j<43;j++) EffFS_DCorr[i]->SetPoint(j-1,R_cent[j],effQualDGeoCorr[j][i]*effPresGeo[j][i]*correzioneLAT[i]);

for(int i=1;i<11;i++)
        for(int j=1;j<43;j++) EffFS_LCorr[i]->SetPoint(j-1,R_cent[j],effQualLGeoCorr[j][i]*effPresGeo[j][i]*correzioneLAT[i]);
c18->cd(1);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffFS_D[i]->SetMarkerColor(i);
        EffFS_D[i]->SetMarkerStyle(8);
        }
EffFS_D[10]->SetTitle("Quality Likelihood Efficiencies (Corrected)");
EffFS_D[10]->GetXaxis()->SetTitle("R [GV]");
EffFS_D[10]->SetMarkerColor(14);
EffFS_D[10]->SetMarkerStyle(8);
EffFS_D[10]->Draw("AP");
EffFS_D[10]->GetYaxis()->SetRangeUser(0,1.2);
EffFS_D[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffFS_D[i]->Draw("Psame");

c18->cd(2);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffFS_L[i]->SetMarkerColor(i);
        EffFS_L[i]->SetMarkerStyle(8);
        }
EffFS_L[10]->SetTitle("Quality Likelihood Efficiencies (Corrected)");
EffFS_L[10]->GetXaxis()->SetTitle("R [GV]");
EffFS_L[10]->SetMarkerColor(14);
EffFS_L[10]->SetMarkerStyle(8);
EffFS_L[10]->Draw("AP");
EffFS_L[10]->GetYaxis()->SetRangeUser(0,1.2);
EffFS_L[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffFS_L[i]->Draw("Psame");
c18->cd(3);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffFS_DCorr[i]->SetMarkerColor(i);
        EffFS_DCorr[i]->SetMarkerStyle(8);
        }
EffFS_DCorr[10]->SetTitle("Quality Likelihood Efficiencies (Corrected)");
EffFS_DCorr[10]->GetXaxis()->SetTitle("R [GV]");
EffFS_DCorr[10]->SetMarkerColor(14);
EffFS_DCorr[10]->SetMarkerStyle(8);
EffFS_DCorr[10]->Draw("AP");
EffFS_DCorr[10]->GetYaxis()->SetRangeUser(0,1.2);
EffFS_DCorr[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffFS_DCorr[i]->Draw("Psame");

c18->cd(4);
gPad->SetGridx();
gPad->SetGridy();
gPad->SetLogx();
for(int i=1;i<10;i++) {
        EffFS_LCorr[i]->SetMarkerColor(i);
        EffFS_LCorr[i]->SetMarkerStyle(8);
        }
EffFS_LCorr[10]->SetTitle("Quality Likelihood Efficiencies (Corrected)");
EffFS_LCorr[10]->GetXaxis()->SetTitle("R [GV]");
EffFS_LCorr[10]->SetMarkerColor(14);
EffFS_LCorr[10]->SetMarkerStyle(8);
EffFS_LCorr[10]->Draw("AP");
EffFS_LCorr[10]->GetYaxis()->SetRangeUser(0,1.2);
EffFS_LCorr[10]->GetYaxis()->SetTitleSize(0.045);
for(int i=1;i<10;i++) EffFS_LCorr[i]->Draw("Psame");
cout<<"********************************************************************************************** DATA VS MC ******************************************************************************************"<<endl;
cout<<"******** PRES. CUT BY CUT *******"<<endl;
TCanvas *c15[10];
for(int i=0;i<10;i++) {nome=tagli[i]+"HL"; c15[i]= new TCanvas(nome.c_str()); c15[i]->Divide(1,2);}

float Sel_effHL[10][43]={{0}};
float Sel_effHL_err[10][43]={{0}};
float Sel_effHLD[10][43]={{0}};
float Sel_effHLD_err[10][43]={{0}};
TGraphAsymmErrors * SelEffHL[10];
TGraphAsymmErrors * SelEffHLD[10];
float Sel_effHLMC[10][43]={{0}};
float Sel_effHLMC_err[10][43]={{0}};
TGraphAsymmErrors * SelEffHLMC[10];
float Sel_effHLMCD[10][43][6]={{{0}}};
float Sel_effHLMCD_err[10][43][6]={{{0}}};
TGraphAsymmErrors * SelEffHLMCD[10][6];

for(int S=0;S<10;S++){
        for(int j=1;j<43;j++)   if(selezioni_PHL[S]->GetBinContent(j+1)>400) {Sel_effHL[S][j]= selected_PHL[S]->GetBinContent(j+1)/selezioni_PHL[S]->GetBinContent(j+1);
        								    Sel_effHL_err[S][j]= pow(selected_PHL[S]->GetBinContent(j+1),0.5)/selected_PHL[S]->GetBinContent(j+1)*Sel_effHL[S][j];}
	for(int j=1;j<18;j++)   if(selezioni_DHL[S]->GetBinContent(j+1)>400) {Sel_effHLD[S][j]= selected_DHL[S]->GetBinContent(j+1)/selezioni_DHL[S]->GetBinContent(j+1);
                                                                            Sel_effHLD_err[S][j]= pow(selected_DHL[S]->GetBinContent(j+1),0.5)/selected_DHL[S]->GetBinContent(j+1)*Sel_effHLD[S][j];}
	
	for(int j=1;j<43;j++)   if(selezioni_PHLMC[S]->GetBinContent(j+1)>400) {Sel_effHLMC[S][j]= selected_PHLMC[S]->GetBinContent(j+1)/selezioni_PHLMC[S]->GetBinContent(j+1);
									      Sel_effHLMC_err[S][j]=pow(selected_PHLMC[S]->GetBinContent(j+1),0.5)/selected_PHLMC[S]->GetBinContent(j+1)*Sel_effHLMC[S][j];} 	
	for(int h=0;h<6;h++)
	for(int j=1;j<43;j++)   if(selezioni_DHLMC[S]->GetBinContent(j+1,h+1)>40) {Sel_effHLMCD[S][j][h]= selected_DHLMC[S]->GetBinContent(j+1,h+1)/selezioni_DHLMC[S]->GetBinContent(j+1,h+1);
                                                                  Sel_effHLMCD_err[S][j][h]=pow(selected_DHLMC[S]->GetBinContent(j+1,h+1),0.5)/selected_DHLMC[S]->GetBinContent(j+1,h+1)*Sel_effHLMCD[S][j][h];}
	
	int point=0;
        SelEffHL[S]=new TGraphAsymmErrors();
        for(int j=1;j<43;j++)   if(Sel_effHL[S][j]>0) {SelEffHL[S]->SetPoint(point,R_cent[j],Sel_effHL[S][j]*(Tau_D[S][10])); 
							SelEffHL[S]->SetPointError(point,0,0,Sel_effHL_err[S][j],Sel_effHL_err[S][j]);	point++;}
	point=0;
        SelEffHLD[S]=new TGraphAsymmErrors();
        for(int j=1;j<43;j++)   if(Sel_effHLD[S][j]>0) {SelEffHLD[S]->SetPoint(point,R_cent[j],Sel_effHLD[S][j]*(Tau_D[S][10])); 
                                                        SelEffHLD[S]->SetPointError(point,0,0,Sel_effHLD_err[S][j],Sel_effHLD_err[S][j]);  point++;}	
	point=0;
        SelEffHLMC[S]=new TGraphAsymmErrors();
	for(int j=1;j<43;j++)   if(Sel_effHLMC[S][j]>0) {SelEffHLMC[S]->SetPoint(point,R_cent[j],Sel_effHLMC[S][j]);
							 SelEffHLMC[S]->SetPointError(point,0,0,Sel_effHLMC_err[S][j],Sel_effHLMC_err[S][j]);	 point++;}

	for(int h=0;h<6;h++){
        point=0;
	SelEffHLMCD[S][h]=new TGraphAsymmErrors();
        for(int j=1;j<43;j++)   if(Sel_effHLMCD[S][j][h]>0) {SelEffHLMCD[S][h]->SetPoint(point,R_cent[j],Sel_effHLMCD[S][j][h]);
                                                         SelEffHLMCD[S][h]->SetPointError(point,0,0,Sel_effHLMCD_err[S][j][h],Sel_effHLMCD_err[S][j][h]);    point++;}
	}
        c15[S]->cd(1);
	gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
	SelEffHL[S]->SetMarkerColor(2);
        SelEffHL[S]->SetLineColor(2);
	SelEffHL[S]->SetMarkerStyle(8);
	SelEffHLMC[S]->SetMarkerColor(2);
        SelEffHLMC[S]->SetLineColor(2);
	SelEffHLMC[S]->SetMarkerStyle(25);
	SelEffHLMC[S]->GetXaxis()->SetTitle("R [GV]");
	nome="Efficienza selezione "+tagli[S]+": MC vs H.L. Data";
        SelEffHL[S]->SetTitle(nome.c_str());
        SelEffHL[S]->Draw("AP");
	SelEffHLMC[S]->Draw("Psame");
        SelEffHL[S]->GetYaxis()->SetRangeUser(0,1.2);

	c15[S]->cd(2);
        gPad->SetLogx();
        gPad->SetGridx();
        gPad->SetGridy();
	SelEffHLD[S]->SetMarkerColor(4);
	SelEffHLD[S]->SetLineColor(4);
        SelEffHLD[S]->SetMarkerStyle(8);
	SelEffHLD[S]->GetXaxis()->SetTitle("R [GV]");
        nome="Efficienza selezione "+tagli[S]+": MC vs H.L. Data";
        SelEffHLD[S]->SetTitle(nome.c_str());
	SelEffHLD[S]->Draw("AP");
	SelEffHLD[S]->GetYaxis()->SetRangeUser(0,1.2);
	for(int h=0;h<6;h++){
                SelEffHLMCD[S][h]->SetMarkerColor(4);
                SelEffHLMCD[S][h]->SetLineColor(4);
		SelEffHLMCD[S][h]->SetMarkerStyle(h);
		SelEffHLMCD[S][h]->GetXaxis()->SetTitle("R [GV]");
		SelEffHLMCD[S][h]->GetYaxis()->SetRangeUser(0,1.2);
		SelEffHLMCD[S][h]->SetTitle(nome.c_str());
                SelEffHLMCD[S][h]->Draw("Psame");
        }
	SelEffHLMCD[S][1]->Draw("AP");
	for(int h=0;h<6;h++) SelEffHLMCD[S][h]->Draw("Psame");
	SelEffHLD[S]->Draw("Psame");
}

cout<<"******** PRES. FULL SET *******"<<endl;
TCanvas * c29= new TCanvas("Preselections (FULL SET)");

float effPresHL[43]={0};
for(int j=1;j<43;j++) effPresHL[j]=PreselecteHL->GetBinContent(j+1)/UHL->GetBinContent(j+1);

float PresTOT[43]={1};
for(int j=1;j<43;j++) PresTOT[j]=1;
for(int S=0;S<10;S++) for(int j=1;j<43;j++)  if(S!=2) PresTOT[j]*=Sel_effHL[S][j]*(Tau_D[S][10])/Sel_effHLMC[S][j];

float PresTOTMC[43]={1};
for(int j=1;j<43;j++) PresTOTMC[j]=1;
for(int S=0;S<10;S++) for(int j=1;j<43;j++)  if(S!=2) PresTOTMC[j]*=Sel_effHLMC[S][j];

for(int j=1;j<43;j++) cout<<PresTOT[j]<<endl;
TGraphAsymmErrors * EffPresHL =new TGraphAsymmErrors();
TGraphAsymmErrors * EffPresMC =new TGraphAsymmErrors();
TGraphAsymmErrors * PresTot =new TGraphAsymmErrors();
TGraphAsymmErrors * PresTotMC =new TGraphAsymmErrors();

p=0;
for(int j=1;j<43;j++) if(effPresHL[j]>0) {EffPresHL->SetPoint(p,R_cent[j],correzioneLAT[10]*effPresHL[j]/effPresMC[j]);p++;}
p=0;
for(int j=1;j<43;j++) if(effPresMC[j]>0) {EffPresMC->SetPoint(p,R_cent[j],effPresMC[j]/effPresMC[j]); p++;}
p=0;
for(int j=1;j<43;j++)  {PresTot->SetPoint(p,R_cent[j],PresTOT[j]);p++;}
p=0;
for(int j=1;j<43;j++)  {PresTotMC->SetPoint(p,R_cent[j],PresTOTMC[j]);p++;}



c29->cd();
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
EffPresMC->SetMarkerStyle(25);
EffPresMC->SetMarkerColor(2);
EffPresMC->SetLineColor(2);
EffPresMC->GetXaxis()->SetTitle("R [GV]");
EffPresMC->GetYaxis()->SetRangeUser(0,1.2);
EffPresMC->Draw("AP");
EffPresHL->SetMarkerStyle(8);
EffPresHL->SetMarkerColor(2);
EffPresHL->SetLineColor(2);
EffPresHL->Draw("Psame");
PresTot->SetMarkerStyle(4);
PresTot->SetMarkerColor(2);
PresTot->SetLineColor(2);
PresTot->Draw("Psame");
PresTotMC->SetMarkerStyle(5);
PresTotMC->SetMarkerColor(2);
PresTotMC->SetLineColor(2);
//PresTotMC->Draw("Psame");
cout<<"******** QUALITY DISTANCE SELECTIONS IND. CHECK *******"<<endl;
TCanvas *c26 = new TCanvas("Quality Selections CUT BY CUT - PROTONS");
c26->Divide(2,2);

float SelEffDTOFMC_P[43]={0};
float SelEffDTrackMC_P[43]={0};
float SelEffDTRDMC_P[43]={0};
float SelEffLMC_P[43]={0};
float SelEffDTOFMC_err_P[43]={0};
float SelEffDTrackMC_err_P[43]={0};
float SelEffDTRDMC_err_P[43]={0};
float SelEffLMC_err_P[43]={0};

for(int j=1;j<43;j++) {
                       if(selezioniQHLMC2_P->GetBinContent(j+1)>100) {SelEffDTOFMC_P[j]= selectedQHLMC2_P->GetBinContent(j+1)/selezioniQHLMC2_P->GetBinContent(j+1);
                                        SelEffDTOFMC_err_P[j] = pow(selectedQHLMC2_P->GetBinContent(j+1),0.5)/selectedQHLMC2_P->GetBinContent(j+1)*SelEffDTOFMC_P[j];}

                       if(selezioniQHLMC3_P->GetBinContent(j+1)>100) {SelEffDTrackMC_P[j]= selectedQHLMC3_P->GetBinContent(j+1)/selezioniQHLMC3_P->GetBinContent(j+1);
                                        SelEffDTrackMC_err_P[j] = pow(selectedQHLMC3_P->GetBinContent(j+1),0.5)/selectedQHLMC3_P->GetBinContent(j+1)*SelEffDTrackMC_P[j];}
                       if(selezioniQHLMC1_P->GetBinContent(j+1)>100) {SelEffDTRDMC_P[j]= selectedQHLMC1_P->GetBinContent(j+1)/selezioniQHLMC1_P->GetBinContent(j+1);
                                        SelEffDTRDMC_err_P[j] = pow(selectedQHLMC1_P->GetBinContent(j+1),0.5)/selectedQHLMC1_P->GetBinContent(j+1)*SelEffDTRDMC_P[j];}
                        }

TGraphAsymmErrors * SeleffDTOFMC_P= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffDTrackMC_P= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffDTRDMC_P= new TGraphAsymmErrors();

point=0;
for(int j=1;j<43;j++)   if(SelEffDTOFMC_P[j]>0) {SeleffDTOFMC_P->SetPoint(point,R_cent[j],SelEffDTOFMC_P[j]/SelEffDTOFMC_P[j]);
                                               SeleffDTOFMC_P->SetPointError(point,0,0,SelEffDTOFMC_err_P[j]/SelEffDTOFMC_P[j],SelEffDTOFMC_err_P[j]/SelEffDTOFMC_P[j]);  point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffDTrackMC_P[j]>0) {SeleffDTrackMC_P->SetPoint(point,R_cent[j],SelEffDTrackMC_P[j]/SelEffDTrackMC_P[j]);
                                                  SeleffDTrackMC_P->SetPointError(point,0,0,SelEffDTrackMC_err_P[j]/SelEffDTrackMC_P[j],SelEffDTrackMC_err_P[j]/SelEffDTrackMC_P[j]);point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffDTRDMC_P[j]>0) {SeleffDTRDMC_P->SetPoint(point,R_cent[j],SelEffDTRDMC_P[j]/SelEffDTRDMC_P[j]);
                                                SeleffDTRDMC_P->SetPointError(point,0,0,SelEffDTRDMC_err_P[j]/SelEffDTRDMC_P[j],SelEffDTRDMC_err_P[j]/SelEffDTRDMC_P[j]); point++;}




float SelEffDTOF_P[43]={0};
float SelEffDTrack_P[43]={0};
float SelEffDTRD_P[43]={0};
float SelEffL_P[43]={0};
float SelEffDTOF_err_P[43]={0};
float SelEffDTrack_err_P[43]={0};
float SelEffDTRD_err_P[43]={0};
float SelEffL_err_P[43]={0};

for(int j=1;j<43;j++) {
                       if(selezioniQHL2_P->GetBinContent(j+1)>100) {SelEffDTOF_P[j]= selectedQHL2_P->GetBinContent(j+1)/selezioniQHL2_P->GetBinContent(j+1);
                                        SelEffDTOF_err_P[j] = pow(selectedQHL2_P->GetBinContent(j+1),0.5)/selectedQHL2_P->GetBinContent(j+1)*SelEffDTOF_P[j];}

                       if(selezioniQHL3_P->GetBinContent(j+1)>100) {SelEffDTrack_P[j]= selectedQHL3_P->GetBinContent(j+1)/selezioniQHL3_P->GetBinContent(j+1);
                                        SelEffDTrack_err_P[j] = pow(selectedQHL3_P->GetBinContent(j+1),0.5)/selectedQHL3_P->GetBinContent(j+1)*SelEffDTrack_P[j];}
                       if(selezioniQHL1_P->GetBinContent(j+1)>100) {SelEffDTRD_P[j]= selectedQHL1_P->GetBinContent(j+1)/selezioniQHL1_P->GetBinContent(j+1);
                                        SelEffDTRD_err_P[j] = pow(selectedQHL1_P->GetBinContent(j+1),0.5)/selectedQHL1_P->GetBinContent(j+1)*SelEffDTRD_P[j];}
                        }

TGraphAsymmErrors * SeleffDTOF_P= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffDTrack_P= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffDTRD_P= new TGraphAsymmErrors();

point=0;
for(int j=1;j<43;j++)   if(SelEffDTOF_P[j]>0) {SeleffDTOF_P->SetPoint(point,R_cent[j],SelEffDTOF_P[j]*(Tau_DQDTOF[10])/SelEffDTOFMC_P[j]);
                                               SeleffDTOF_P->SetPointError(point,0,0,SelEffDTOF_err_P[j]/SelEffDTOFMC_P[j],SelEffDTOF_err_P[j]/SelEffDTOFMC_P[j]);  point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffDTrack_P[j]>0) {SeleffDTrack_P->SetPoint(point,R_cent[j],SelEffDTrack_P[j]*(Tau_DQDTrack[10])/SelEffDTrackMC_P[j]);
                                                  SeleffDTrack_P->SetPointError(point,0,0,SelEffDTrack_err_P[j]/SelEffDTrackMC_P[j],SelEffDTrack_err_P[j]/SelEffDTrackMC_P[j]);point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffDTRD_P[j]>0) {SeleffDTRD_P->SetPoint(point,R_cent[j],SelEffDTRD_P[j]*(Tau_DQDTRD[10])/SelEffDTRDMC_P[j]);
                                                SeleffDTRD_P->SetPointError(point,0,0,SelEffDTRD_err_P[j]/SelEffDTRDMC_P[j],SelEffDTRD_err_P[j]/SelEffDTRDMC_P[j]); point++;}


float SelEffD_P[43]={0};
float SelEffD_err_P[43]={0};

for(int j=0;j<43;j++) SelEffD_P[j]=((Tau_DQDTOF[10])*(Tau_DQDTrack[10]))*(SelEffDTOF_P[j]/SelEffDTOFMC_P[j])*(SelEffDTrack_P[j]/SelEffDTrackMC_P[j]);

TGraphAsymmErrors * SeleffD_P= new TGraphAsymmErrors();
point=0;
for(int j=1;j<43;j++)   if(SelEffD_P[j]>0) {SeleffD_P->SetPoint(point,R_cent[j],SelEffD_P[j]);point++;}


cout<<"******** QUALITY SELECTIONS PROTONS *******"<<endl;

TCanvas *c16 = new TCanvas("Quality Selections TOTAL - PROTONS");
c16->Divide(2,1);
TCanvas *c31 = new TCanvas("Quality Selections L&D - PROTONS");

float Sel_effQL[43]={0};
float Sel_effQD[43]={0};
float Sel_effQLD[43]={0};
float Sel_effQL_err[43]={0};
float Sel_effQD_err[43]={0};
float Sel_effQLD_err[43]={0};

for(int j=1;j<43;j++) {Sel_effQL[j]= selectedQLHL->GetBinContent(j+1)/selezioniQHL->GetBinContent(j+1);               
                       Sel_effQL_err[j] = pow(selectedQLHL->GetBinContent(j+1),0.5)/selectedQLHL->GetBinContent(j+1)*Sel_effQL[j];
		       Sel_effQD[j]= selectedQDHL->GetBinContent(j+1)/selezioniQHL->GetBinContent(j+1);
		       Sel_effQD_err[j] = pow(selectedQDHL->GetBinContent(j+1),0.5)/selectedQDHL->GetBinContent(j+1)*Sel_effQD[j];	
		       Sel_effQLD[j]= selectedQLDHL->GetBinContent(j+1)/selezioniQHL->GetBinContent(j+1);
                       Sel_effQLD_err[j] = pow(selectedQLDHL->GetBinContent(j+1),0.5)/selectedQLDHL->GetBinContent(j+1)*Sel_effQLD[j];	
			}
 
TGraphAsymmErrors * SeleffQL= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffQD= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffQLD= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffQLMC= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffQDMC= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffQLDMC= new TGraphAsymmErrors();
TGraphAsymmErrors * RatioQLD= new TGraphAsymmErrors();

for(int i=1;i<11;i++) Tau_DQD[i]=(Tau_DQDTOF[i])*(Tau_DQDTrack[i]);

point=0;
for(int j=1;j<43;j++)   if(Sel_effQLMC[j]>0) {SeleffQLMC->SetPoint(point,R_cent[j],Sel_effQLMC[j]/Sel_effQLMC[j]); point++;}
point=0;
for(int j=1;j<43;j++)   if(Sel_effQDMC[j]>0) {SeleffQDMC->SetPoint(point,R_cent[j],Sel_effQDMC[j]/Sel_effQDMC[j]); point++;}
point=0;
for(int j=1;j<43;j++)   if(Sel_effQLDMC[j]>0) {SeleffQLDMC->SetPoint(point,R_cent[j],Sel_effQLDMC[j]/Sel_effQLDMC[j]); point++;}
point=0;
for(int j=1;j<43;j++)   if(Sel_effQL[j]>0) {SeleffQL->SetPoint(point,R_cent[j],Sel_effQL[j]*(Tau_DQL[10])/Sel_effQLMC[j]);
			   SeleffQL->SetPointError(point,0,0,Sel_effQL_err[j]/Sel_effQL[j],Sel_effQL_err[j]/Sel_effQL[j]); point++;}
point=0;
for(int j=1;j<43;j++)   if(Sel_effQD[j]>0) {SeleffQD->SetPoint(point,R_cent[j],Sel_effQD[j]*(Tau_DQD[10])/Sel_effQDMC[j]);
						SeleffQD->SetPointError(point,0,0,Sel_effQD_err[j]/Sel_effQD[j],Sel_effQD_err[j]/Sel_effQD[j]); point++;}
point=0;
for(int j=1;j<43;j++)   if(Sel_effQLD[j]>0) {SeleffQLD->SetPoint(point,R_cent[j],Sel_effQLD[j]*(Tau_DQD[10]*Tau_DQL[10])/Sel_effQLDMC[j]);
                                                SeleffQLD->SetPointError(point,0,0,Sel_effQLD_err[j]/Sel_effQLD[j],Sel_effQLD_err[j]/Sel_effQLD[j]); point++;}
point=0;

/////////// SMOOTHING E ESTRAZIONE TREND//////////////////
double ratioL_smooth[43]={0};
double ratioD_smooth[43]={0};

for(int j=1;j<43;j++){
        ratioL_smooth[j]=Sel_effQL[j]*(Tau_DQL[10])/Sel_effQLMC[j];
        ratioD_smooth[j]=Sel_effQD[j]*(Tau_DQD[10])/Sel_effQDMC[j];
}
ratioL_smooth[0]=ratioL_smooth[1];
ratioD_smooth[0]=ratioD_smooth[1];
for(int j=3;j<41;j++){
	
	ratioL_smooth[j]=(ratioL_smooth[j]+ratioL_smooth[j-1]+ratioL_smooth[j+1]+ratioL_smooth[j-2]+ratioL_smooth[j+2])/5;
	ratioD_smooth[j]=(ratioD_smooth[j]+ratioD_smooth[j-1]+ratioD_smooth[j+1]+ratioD_smooth[j-2]+ratioD_smooth[j+2])/5;
	
}
TSpline3 *ratioL = new TSpline3("ratioL",R_cent,ratioL_smooth,43);
TSpline3 *ratioD = new TSpline3("ratioD",R_cent,ratioD_smooth,43);

point=0;
for(int j=1;j<43;j++)   if(Sel_effQLD[j]>0) {RatioQLD->SetPoint(point,R_cent[j],ratioL->Eval(R_cent[j])*ratioD->Eval(R_cent[j]));point++;}
/////////////////////////////////////////////////////////

float DMCL[43]={0};
float DMCD[43]={0};

for(int j=1;j<43;j++){
	DMCL[j]=ratioL->Eval(R_cent[j]);
	DMCD[j]=ratioD->Eval(R_cent[j]);
}

c16->cd(2);
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
SeleffQLMC->SetMarkerColor(2);
SeleffQLMC->SetMarkerStyle(25);
SeleffQL->SetMarkerColor(2);
SeleffQL->SetLineColor(2);
SeleffQL->SetMarkerStyle(8);
SeleffQLMC->GetYaxis()->SetRangeUser(0,1.2);
SeleffQLMC->GetXaxis()->SetTitle("R [GV]");
SeleffQLMC->Draw("AP");
SeleffQL->Draw("Psame");
ratioL->SetLineWidth(2);
ratioL->SetLineColor(2);
ratioL->Draw("same");
c16->cd(1);
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
SeleffQDMC->SetMarkerColor(2);
SeleffQDMC->SetMarkerStyle(25);
SeleffQD->SetMarkerColor(2);
SeleffQD->SetLineColor(2);
SeleffQD->SetMarkerStyle(8);
SeleffQDMC->GetYaxis()->SetRangeUser(0,1.2);
SeleffQDMC->Draw("AP");
SeleffQDMC->GetXaxis()->SetTitle("R [GV]");
SeleffQD->Draw("Psame");
ratioD->SetLineWidth(2);
ratioD->SetLineColor(2);
ratioD->Draw("same");

c31->cd();
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
SeleffQLDMC->SetMarkerColor(2);
SeleffQLDMC->SetMarkerStyle(25);
SeleffQLD->SetMarkerColor(2);
SeleffQLD->SetLineColor(2);
SeleffQLD->SetMarkerStyle(8);
SeleffQLDMC->GetYaxis()->SetRangeUser(0,1.2);
SeleffQLDMC->Draw("AP");
SeleffQLDMC->GetXaxis()->SetTitle("R [GV]");
SeleffQLD->Draw("Psame");
RatioQLD->SetLineColor(2);
RatioQLD->SetLineWidth(2);
RatioQLD->Draw("same");

c26->cd(1);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffDTOF_P->SetTitle("Sel. Distanza (TOF): Data vs MC");
SeleffDTOF_P->SetMarkerColor(2);
SeleffDTOF_P->SetLineColor(2);
SeleffDTOF_P->SetMarkerStyle(8);
SeleffDTOFMC_P->SetMarkerColor(2);
SeleffDTOFMC_P->SetMarkerStyle(25);
SeleffDTOF_P->Draw("AP");
SeleffDTOF_P->GetYaxis()->SetRangeUser(0,1.2);
SeleffDTOF_P->GetXaxis()->SetTitle("R [GV]");
SeleffDTOFMC_P->Draw("Psame");

c26->cd(2);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffDTrack_P->SetTitle("Sel. Distanza (Tracker): Data vs MC");
SeleffDTrack_P->SetMarkerColor(2);
SeleffDTrack_P->SetLineColor(2);
SeleffDTrack_P->SetMarkerStyle(8);
SeleffDTrackMC_P->SetMarkerColor(2);
SeleffDTrackMC_P->SetMarkerStyle(25);
SeleffDTrack_P->Draw("AP");
SeleffDTrack_P->GetYaxis()->SetRangeUser(0,1.2);
SeleffDTrack_P->GetXaxis()->SetTitle("R [GV]");
SeleffDTrackMC_P->Draw("Psame");

c26->cd(3);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffDTRD_P->SetTitle("Sel. Distanza (TRD): Data vs MC");
SeleffDTRD_P->SetMarkerColor(2);
SeleffDTRD_P->SetLineColor(2);
SeleffDTRD_P->SetMarkerStyle(8);
SeleffDTRDMC_P->SetMarkerColor(2);
SeleffDTRDMC_P->SetMarkerStyle(25);
SeleffDTRD_P->Draw("AP");
SeleffDTRD_P->GetYaxis()->SetRangeUser(0,1.2);
SeleffDTRD_P->GetXaxis()->SetTitle("R [GV]");
SeleffDTRDMC_P->Draw("Psame");

c26->cd(4);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffD_P->SetTitle("Sel. Distanza: Data vs MC");
SeleffD_P->SetMarkerColor(2);
SeleffD_P->SetLineColor(2);
SeleffD_P->SetMarkerStyle(7);
SeleffDTOFMC_P->SetMarkerColor(2);
SeleffDTOFMC_P->SetMarkerStyle(25);
SeleffD_P->Draw("AP");
SeleffQD->Draw("Psame");
SeleffD_P->GetYaxis()->SetRangeUser(0,1.2);
SeleffD_P->GetXaxis()->SetTitle("R [GV]");
SeleffDTOFMC_P->Draw("Psame");




cout<<"******** DEUTONS WINDOW CONT. CHECK *******"<<endl;
TH1F * XProtons[43];
TH1F * XDeutons[43];
for(int j=0;j<18;j++) {
	XProtons[j]=new TH1F("","",1000,-20,20);
	XDeutons[j]=new TH1F("","",1000,-20,20);
	
	for(int n=0;n<ContCheckPTOF->GetNbinsX();n++){
		XProtons[j]->SetBinContent(n+1,ContCheckPTOF->GetBinContent(n+1,j+1));
		XDeutons[j]->SetBinContent(n+1,ContCheckDTOF->GetBinContent(n+1,j+1));
		}
	}
TCanvas *c22=new TCanvas("Deutons window Cont. Check");
c22->Divide(6,3);

for(int j=0;j<18;j++) {
	c22->cd(j+1);
	XProtons[j]->SetFillStyle(3001);
	XProtons[j]->SetFillColor(2);
	XDeutons[j]->SetFillStyle(3001);
        XDeutons[j]->SetFillColor(4);
	XProtons[j]->GetXaxis()->SetTitle("X");
	XProtons[j]->GetXaxis()->SetRangeUser(-6,6);
	XProtons[j]->GetYaxis()->SetRangeUser(0,1000);
	XProtons[j]->Draw();
	XDeutons[j]->Draw("same");
}	
cout<<"******** QUALITY SELECTIONS DEUTONS *******"<<endl;

TCanvas *c20 = new TCanvas("Quality Selections CUT BY CUT - DEUTONS");
c20->Divide(2,2);

float SelEffDTOFMC[43][6]={{0}};
float SelEffDTrackMC[43][6]={{0}};
float SelEffDTRDMC[43][6]={{0}};
float SelEffLMC[43][6]={{0}};
float SelEffDTOFMC_err[43][6]={{0}};
float SelEffDTrackMC_err[43][6]={{0}};
float SelEffDTRDMC_err[43][6]={{0}};
float SelEffLMC_err[43][6]={{0}};

for(int h=0;h<6;h++)
for(int j=1;j<18;j++) {
                       if(selezioniQHLMC2->GetBinContent(j+1,h+1)>100) {SelEffDTOFMC[j][h]= selectedQHLMC2->GetBinContent(j+1,h+1)/selezioniQHLMC2->GetBinContent(j+1,h+1);
                                        SelEffDTOFMC_err[j][h] = pow(selectedQHLMC2->GetBinContent(j+1,h+1),0.5)/selectedQHLMC2->GetBinContent(j+1,h+1)*SelEffDTOFMC[j][h];}

                       if(selezioniQHLMC3->GetBinContent(j+1,h+1)>100) {SelEffDTrackMC[j][h]= selectedQHLMC3->GetBinContent(j+1,h+1)/selezioniQHLMC3->GetBinContent(j+1,h+1);
                                        SelEffDTrackMC_err[j][h] = pow(selectedQHLMC3->GetBinContent(j+1,h+1),0.5)/selectedQHLMC3->GetBinContent(j+1,h+1)*SelEffDTrackMC[j][h];}   
                       if(selezioniQHLMC1->GetBinContent(j+1,h+1)>100) {SelEffDTRDMC[j][h]= selectedQHLMC1->GetBinContent(j+1,h+1)/selezioniQHLMC1->GetBinContent(j+1,h+1);
                                        SelEffDTRDMC_err[j][h] = pow(selectedQHLMC1->GetBinContent(j+1,h+1),0.5)/selectedQHLMC1->GetBinContent(j+1,h+1)*SelEffDTRDMC[j][h];}

                        if(selezioniQHLMC4->GetBinContent(j+1,h+1)>100) {SelEffLMC[j][h]= selectedQHLMC4->GetBinContent(j+1,h+1)/selezioniQHLMC4->GetBinContent(j+1,h+1);
                                        SelEffLMC_err[j][h] = pow(selectedQHLMC4->GetBinContent(j+1,h+1),0.5)/selectedQHLMC4->GetBinContent(j+1,h+1)*SelEffLMC[j][h];}
                        }

float SelEffDTOF[43]={0};
float SelEffDTrack[43]={0};
float SelEffDTRD[43]={0};
float SelEffL[43]={0};
float SelEffDTOF_err[43]={0};
float SelEffDTrack_err[43]={0};
float SelEffDTRD_err[43]={0};
float SelEffL_err[43]={0};

for(int j=1;j<18;j++) {
                       if(selezioniQHL2->GetBinContent(j+1)>400) {SelEffDTOF[j]= selectedQHL2->GetBinContent(j+1)/selezioniQHL2->GetBinContent(j+1);
                                        SelEffDTOF_err[j] = pow(selectedQHL2->GetBinContent(j+1),0.5)/selectedQHL2->GetBinContent(j+1)*SelEffDTOF[j];}

                       if(selezioniQHL3->GetBinContent(j+1)>400) {SelEffDTrack[j]= selectedQHL3->GetBinContent(j+1)/selezioniQHL3->GetBinContent(j+1);
                                        SelEffDTrack_err[j] = pow(selectedQHL3->GetBinContent(j+1),0.5)/selectedQHL3->GetBinContent(j+1)*SelEffDTrack[j];}
                       if(selezioniQHL1->GetBinContent(j+1)>400) {SelEffDTRD[j]= selectedQHL1->GetBinContent(j+1)/selezioniQHL1->GetBinContent(j+1);
                                        SelEffDTRD_err[j] = pow(selectedQHL1->GetBinContent(j+1),0.5)/selectedQHL1->GetBinContent(j+1)*SelEffDTRD[j];}

                        if(selezioniQHL4->GetBinContent(j+1)>400) {SelEffL[j]= selectedQHL4->GetBinContent(j+1)/selezioniQHL4->GetBinContent(j+1);
                                        SelEffL_err[j] = pow(selectedQHL4->GetBinContent(j+1),0.5)/selectedQHL4->GetBinContent(j+1)*SelEffL[j];}
                        }



TGraphAsymmErrors * SeleffDTOFMC= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffDTrackMC= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffDTRDMC= new TGraphAsymmErrors();
TGraphAsymmErrors * SeleffLMC= new TGraphAsymmErrors();

point=0;
for(int j=1;j<43;j++)   if(SelEffDTOFMC[j][1]>0) {SeleffDTOFMC->SetPoint(point,R_cent[j],SelEffDTOFMC[j][1]/SelEffDTOFMC[j][1]); 
					       SeleffDTOFMC->SetPointError(point,0,0,SelEffDTOFMC_err[j][1]/SelEffDTOFMC[j][1],SelEffDTOFMC_err[j][1]/SelEffDTOFMC[j][1]);	point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffDTrackMC[j][1]>0) {SeleffDTrackMC->SetPoint(point,R_cent[j],SelEffDTrackMC[j][1]/SelEffDTrackMC[j][1]); 
						  SeleffDTrackMC->SetPointError(point,0,0,SelEffDTrackMC_err[j][1]/SelEffDTrackMC[j][1],SelEffDTrackMC_err[j][1]/SelEffDTrackMC[j][1]);point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffDTRDMC[j][1]>0) {SeleffDTRDMC->SetPoint(point,R_cent[j],SelEffDTRDMC[j][1]/SelEffDTRDMC[j][1]); 
						SeleffDTRDMC->SetPointError(point,0,0,SelEffDTRDMC_err[j][1]/SelEffDTRDMC[j][1],SelEffDTRDMC_err[j][1]/SelEffDTRDMC[j][1]); point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffLMC[j][1]>0) {SeleffLMC->SetPoint(point,R_cent[j],SelEffLMC[j][1]/SelEffLMC[j][1]); 
					      SeleffLMC->SetPointError(point,0,0,SelEffLMC_err[j][1]/SelEffLMC[j][1],SelEffLMC_err[j][1]/SelEffLMC[j][1]); point++;}

TGraphAsymmErrors * SeleffDTOF[6];
TGraphAsymmErrors * SeleffDTrack[6];
TGraphAsymmErrors * SeleffDTRD[6];
TGraphAsymmErrors * SeleffL[6];

for(int h=0;h<6;h++){
	SeleffDTOF[h]= new TGraphAsymmErrors();
	SeleffDTrack[h]= new TGraphAsymmErrors();
	SeleffDTRD[h]= new TGraphAsymmErrors();
	SeleffL[h]= new TGraphAsymmErrors();

point=0;
for(int j=1;j<43;j++)   if(SelEffDTOF[j]>0) {SeleffDTOF[h]->SetPoint(point,R_cent[j],SelEffDTOF[j]*(Tau_DQDTOF[10])/SelEffDTOFMC[j][h]);
                               SeleffDTOF[h]->SetPointError(point,0,0,SelEffDTOF_err[j]/SelEffDTOFMC[j][h],SelEffDTOF_err[j]/SelEffDTOFMC[j][h]); point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffDTrack[j]>0) {SeleffDTrack[h]->SetPoint(point,R_cent[j],SelEffDTrack[j]*(Tau_DQDTrack[10])/SelEffDTrackMC[j][h]);
                                SeleffDTrack[h]->SetPointError(point,0,0,SelEffDTrack_err[j]/SelEffDTrackMC[j][h],SelEffDTrack_err[j]/SelEffDTOFMC[j][h]); point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffDTRD[j]>0) {SeleffDTRD[h]->SetPoint(point,R_cent[j],SelEffDTRD[j]*(Tau_DQDTRD[10])/SelEffDTRDMC[j][h]);
                                SeleffDTRD[h]->SetPointError(point,0,0,SelEffDTRD_err[j]/SelEffDTRDMC[j][h],SelEffDTRD_err[j]/SelEffDTRDMC[j][h]); point++;}
point=0;
for(int j=1;j<43;j++)   if(SelEffL[j]>0) {SeleffL[h]->SetPoint(point,R_cent[j],SelEffL[j]*(Tau_DQL[10])/SelEffLMC[j][h]);
                                SeleffL[h]->SetPointError(point,0,0,SelEffL_err[j]/SelEffLMC[j][h],SelEffL_err[j]/SelEffLMC[j][h]);point++;}


}


c20->cd(1);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffDTOFMC->SetTitle("Sel. Distanza (TOF): Data vs MC");
SeleffDTOFMC->SetMarkerColor(4);
SeleffDTOFMC->SetMarkerStyle(8);
SeleffDTOFMC->Draw("AP");
SeleffDTOFMC->GetYaxis()->SetRangeUser(0,1.2);
SeleffDTOFMC->GetXaxis()->SetTitle("R [GV]");
for(int h=0;h<6;h++){
	SeleffDTOF[h]->SetMarkerColor(4);
	SeleffDTOF[h]->SetMarkerStyle(h);
	SeleffDTOF[h]->Draw("Psame");
}

c20->cd(2);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffDTrackMC->SetTitle("Sel. Distanza (Tracker): Data vs MC");
SeleffDTrackMC->SetMarkerColor(4);
SeleffDTrackMC->SetLineColor(4);
SeleffDTrackMC->SetMarkerStyle(8);
SeleffDTrackMC->Draw("AP");
SeleffDTrackMC->GetYaxis()->SetRangeUser(0,1.2);
SeleffDTrackMC->GetXaxis()->SetTitle("R [GV]");
for(int h=0;h<6;h++){
        SeleffDTrack[h]->SetMarkerColor(4);
        SeleffDTrack[h]->SetMarkerStyle(h);
        SeleffDTrack[h]->Draw("Psame");
}


c20->cd(3);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffDTRDMC->SetTitle("Sel. Distanza (TRD): Data vs MC");
SeleffDTRDMC->SetMarkerColor(4);
SeleffDTRDMC->SetLineColor(4);
SeleffDTRDMC->SetMarkerStyle(8);
SeleffDTRDMC->Draw("AP");
SeleffDTRDMC->GetYaxis()->SetRangeUser(0,1.2);
SeleffDTRDMC->GetXaxis()->SetTitle("R [GV]");
for(int h=0;h<6;h++){
        SeleffDTRD[h]->SetMarkerColor(4);
        SeleffDTRD[h]->SetMarkerStyle(h);
        SeleffDTRD[h]->Draw("Psame");
}

c20->cd(4);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffLMC->SetTitle("Sel. Likelihood: Data vs MC");
SeleffLMC->SetMarkerColor(4);
SeleffLMC->SetLineColor(4);
SeleffLMC->SetMarkerStyle(8);
SeleffLMC->Draw("AP");
SeleffLMC->GetYaxis()->SetRangeUser(0,1.2);
SeleffLMC->GetXaxis()->SetTitle("R [GV]");
for(int h=0;h<6;h++){
        SeleffL[h]->SetMarkerColor(4);
        SeleffL[h]->SetMarkerStyle(h);
        SeleffL[h]->Draw("Psame");
}

cout<<"******** QUALITY SELECTIONS DEUTONS (TOT)*******"<<endl;

TCanvas *c21 = new TCanvas("Quality Selections - DEUTONS (TOT)");
c21->Divide(2,1);
float SelEffD[43]={0};
float SelEffD_err[43]={0};

for(int j=0;j<43;j++) SelEffD[j]=((Tau_DQDTOF[10])*(Tau_DQDTrack[10]))*(SelEffDTOF[j]/SelEffDTOFMC[j][1])*(SelEffDTrack[j]/SelEffDTrackMC[j][1]);

TGraphAsymmErrors * SeleffD= new TGraphAsymmErrors();
point=0;
for(int j=1;j<43;j++)   if(SelEffD[j]>0) {SeleffD->SetPoint(point,R_cent[j],SelEffD[j]);point++;}

TF1 * QDMC_D=new TF1("QDMC_D","pol4",0.01,5);
TF1 * QDMC_L=new TF1("QDMC_L","pol4",0.01,5);

SeleffD->Fit("QDMC_D","q");
SeleffL[1]->Fit("QDMC_L","q");

float QDMCL[43]={0};
float QDMCD[43]={0};

for(int j=1;j<43;j++){
        QDMCL[j]=QDMC_L->Eval(R_cent[j]);
        QDMCD[j]=QDMC_D->Eval(R_cent[j]);
}


c21->cd(1);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffD->SetTitle("Sel. Distanza: Data vs MC");
SeleffD->SetMarkerColor(4);
SeleffD->SetLineColor(4);
SeleffD->SetMarkerStyle(8);
SeleffDTOFMC->SetMarkerColor(4);
SeleffDTOFMC->SetMarkerStyle(25);
SeleffD->Draw("AP");
SeleffD->GetYaxis()->SetRangeUser(0,1.2);
SeleffD->GetXaxis()->SetTitle("R [GV]");
SeleffDTOFMC->Draw("Psame");
QDMC_D->SetLineWidth(2);
QDMC_D->SetLineColor(4);
QDMC_D->Draw("same");

c21->cd(2);
gPad->SetLogx();
gPad->SetGridy();
gPad->SetGridx();
SeleffL[1]->SetTitle("Sel. Likelihood: Data vs MC");
SeleffL[1]->SetMarkerColor(4);
SeleffL[1]->SetLineColor(4);
SeleffL[1]->SetMarkerStyle(8);
SeleffLMC->SetMarkerColor(4);
SeleffLMC->SetMarkerStyle(25);
SeleffL[1]->Draw("AP");
SeleffL[1]->GetYaxis()->SetRangeUser(0,1.2);
SeleffL[1]->GetXaxis()->SetTitle("R [GV]");
SeleffLMC->Draw("Psame");
QDMC_L->SetLineWidth(2);
QDMC_L->SetLineColor(4);
QDMC_L->Draw("same");

cout<<"********************************************************************************************** PROTONS FLUX ****************************************************************************************"<<endl;
TCanvas *c7=new TCanvas("P Flux");
c7->Divide(2,1);
TCanvas *c17=new TCanvas("P Flux: Lik. vs Dist ratio");
TCanvas *c14=new TCanvas("P Flux - Total Correction");
c14->Divide(2,1);
float PFlux_D[43][11];
float PFlux_Q[43][11];
int Prim_PD[43]={0};
int Prim_PQ[43]={0};
float PFlux_DPrim[43]={0};
float PFlux_QPrim[43]={0};
float PFlux_DPrim_Nocorr[43]={0};
float PFlux_QPrim_Nocorr[43]={0};
float potenza=2.7;

for(int i=1;i<11;i++)
	for(int j=1;j<43;j++) PFlux_D[j][i]=correzioneLAT[i]*(Tau_DQD[i])*PCountsD[i]->GetBinContent(j+1)/(DMCD[j]*AcceptDistMCP[j]*Tempi->GetBinContent(i)*deltaencinprot[j]); 

for(int i=1;i<11;i++)
        for(int j=1;j<43;j++) PFlux_Q[j][i]=correzioneLAT[i]*(Tau_DQL[i])*PCountsQ[i]->GetBinContent(j+1)/(DMCL[j]*AcceptQualMCP[j]*Tempi->GetBinContent(i)*deltaencinprot[j]);
        
for(int i=1;i<11;i++)
	for(int j=1;j<43;j++)  {
		Prim_PD[j]+=PCountsDPrim[i]->GetBinContent(j+1);
		Prim_PQ[j]+=PCountsQPrim[i]->GetBinContent(j+1);
		}		

for(int j=1;j<43;j++) {
	PFlux_QPrim[j]=(CorrLatTOTL[j])*Prim_PQ[j]/(DMCL[j]*AcceptQualMCP[j]*Espos_R[j]*deltaencinprot[j]);
	PFlux_DPrim[j]=(CorrLatTOTD[j])*Prim_PD[j]/(DMCD[j]*AcceptDistMCP[j]*Espos_R[j]*deltaencinprot[j]);
}

for(int j=1;j<43;j++) {
        PFlux_QPrim_Nocorr[j]=/*CorrLatTOTL[j]*/Prim_PQ[j]/(DMCL[j]*AcceptQualMCP[j]*Espos_R[j]*deltaencinprot[j]);
        PFlux_DPrim_Nocorr[j]=/*CorrLatTOTD[j]*/Prim_PD[j]/(DMCD[j]*AcceptDistMCP[j]*Espos_R[j]*deltaencinprot[j]);
}

TGraphAsymmErrors * PFluxgeoD[11];
for(int i=1;i<11;i++) PFluxgeoD[i]=new TGraphAsymmErrors();
TGraphAsymmErrors * PFluxgeoQ[11];
for(int i=1;i<11;i++) PFluxgeoQ[i]=new TGraphAsymmErrors();

for(int i=1;i<11;i++){
        for(int j=1;j<43;j++) PFluxgeoD[i]->SetPoint(j-1,encinprot[j],PFlux_D[j][i]*pow(encinprot[j],potenza));
	for(int j=1;j<43;j++) PFluxgeoQ[i]->SetPoint(j-1,encinprot[j],PFlux_Q[j][i]*pow(encinprot[j],potenza));
}

TGraphAsymmErrors * PFluxD=new TGraphAsymmErrors();
TGraphAsymmErrors * PFluxQ=new TGraphAsymmErrors();

for(int j=1;j<43;j++){
	PFluxD->SetPoint(j-1,encinprot[j],PFlux_DPrim[j]*pow(encinprot[j],potenza));
	PFluxQ->SetPoint(j-1,encinprot[j],PFlux_QPrim[j]*pow(encinprot[j],potenza));
}

TGraphAsymmErrors * PFluxD_Nocorr=new TGraphAsymmErrors();
TGraphAsymmErrors * PFluxQ_Nocorr=new TGraphAsymmErrors();

for(int j=1;j<43;j++){
        PFluxD_Nocorr->SetPoint(j-1,encinprot[j],PFlux_DPrim_Nocorr[j]*pow(encinprot[j],potenza));
        PFluxQ_Nocorr->SetPoint(j-1,encinprot[j],PFlux_QPrim_Nocorr[j]*pow(encinprot[j],potenza));
}

c7->cd(1);
gPad->SetLogx();
gPad->SetLogy();
gPad->SetGridx();
gPad->SetGridy();
for(int i=1;i<10;i++) {
	PFluxgeoD[i]->SetMarkerColor(i);
	PFluxgeoD[i]->SetLineColor(i);
	PFluxgeoD[i]->SetMarkerStyle(8);
	}
PFluxD->SetTitle("P Fluxes (Dist)");
PFluxD->GetXaxis()->SetTitle("Kin. En./nucl [GeV/nucl]");
PFluxgeoD[10]->SetMarkerColor(14);
PFluxgeoD[10]->SetLineColor(14);
PFluxgeoD[10]->SetMarkerStyle(8);
PFluxD->Draw("APC");
for(int i=1;i<11;i++) PFluxgeoD[i]->Draw("PCsame");
PFluxD->SetMarkerStyle(2);
PFluxD->SetMarkerColor(2);
PFluxD->SetLineWidth(4);
PFluxQ->SetMarkerStyle(2);
PFluxQ->SetMarkerColor(2);
PFluxQ->SetLineWidth(4);
PFluxD_Nocorr->SetMarkerStyle(2);
PFluxD_Nocorr->SetMarkerColor(4);
PFluxQ_Nocorr->SetMarkerStyle(2);
PFluxQ_Nocorr->SetMarkerColor(4);

TGraph* galprop3P=new TGraph();
TGraph* galprop3P2=new TGraph();
float x,y=0;
int j=0;
{
ifstream fp("./Galprop/Trotta2011/Def/new_P200.txt");
while (!fp.eof()){
fp>>x>>y;
if(x/1e3>0.05&&x/1e3<=100)
galprop3P->SetPoint(j,x/1e3,y*1e7*pow(x/1e3,potenza));
j++;
	}
}

j=0;
{
ifstream fp("./Galprop/Trotta2011/Def/new_P1250.txt");
while (!fp.eof()){
fp>>x>>y;
if(x/1e3>0.05&&x/1e3<=100)
galprop3P2->SetPoint(j,x/1e3,y*1e7*pow(x/1e3,potenza));
j++;
	}
}

galprop3P->Draw("sameC");
galprop3P2->Draw("sameC");

c7->cd(2);
gPad->SetLogx();
gPad->SetLogy();
gPad->SetGridx();
gPad->SetGridy();
for(int i=1;i<10;i++) {
        PFluxgeoQ[i]->SetMarkerColor(i);
        PFluxgeoQ[i]->SetMarkerStyle(8);
        PFluxgeoQ[i]->SetLineColor(i);
	}
PFluxQ->SetTitle("P Fluxes (Qual)");
PFluxQ->GetXaxis()->SetTitle("Kin. En./nucl [GeV/nucl]");
PFluxgeoQ[10]->SetMarkerColor(14);
PFluxgeoQ[10]->SetLineColor(14);
PFluxgeoQ[10]->SetMarkerStyle(8);
PFluxQ->Draw("APC");
for(int i=1;i<11;i++) PFluxgeoQ[i]->Draw("CPsame");
galprop3P->Draw("sameC");
galprop3P2->Draw("sameC");

c14->cd(1);
gPad->SetLogx(); 
gPad->SetLogy();
gPad->SetGridx();
gPad->SetGridy();
PFluxD->SetTitle("P Fluxes Correction (Distance)");
PFluxD->GetXaxis()->SetTitle("Kin. En./nucl [GeV/nucl]");
PFluxD->Draw("APC");
PFluxgeoD[10]->Draw("CPsame");
PFluxD_Nocorr->Draw("PCsame");
galprop3P->Draw("sameC");
galprop3P2->Draw("sameC");

c14->cd(2);
gPad->SetLogx();
gPad->SetLogy();
gPad->SetGridx();
gPad->SetGridy();
PFluxQ->SetTitle("P Fluxes Correction (Qual)");
PFluxQ->GetXaxis()->SetTitle("Kin. En./nucl [GeV/nucl]");
PFluxQ->Draw("APC");
PFluxgeoQ[10]->Draw("CPsame");
PFluxQ_Nocorr->Draw("PCsame");
galprop3P->Draw("sameC");
galprop3P2->Draw("sameC");

c17->cd();
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();

TGraphAsymmErrors * PStratRatio = new TGraphAsymmErrors();
for(int j=1;j<43;j++){
	PStratRatio->SetPoint(j-1,encinprot[j],PFlux_QPrim[j]/PFlux_DPrim[j]);
}

PStratRatio->SetMarkerStyle(2);
PStratRatio->SetMarkerColor(2);
PStratRatio->SetTitle("Strategies Ratio: Qual/Dist");
PStratRatio->Draw("AP");


TCanvas * c9 = new TCanvas("Exposure Time vs R");    
c9->cd();
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
TGraph * EsposizioneR =new TGraph();
for(int j=0;j<43;j++) EsposizioneR->SetPoint(j,R_cent[j],Espos_R[j]);
EsposizioneR->SetTitle("Exposure Time (R)");
EsposizioneR->GetYaxis()->SetTitle("Exposure time [s]");
EsposizioneR->GetXaxis()->SetTitle("R [GV]");
EsposizioneR->SetMarkerColor(2);
EsposizioneR->SetMarkerStyle(8);
EsposizioneR->Draw("AP");

cout<<"*********************************************************************************** DEUTERONS TEMPLATE *********************************************************************************************"<<endl;
cout<<"**************** Discr. 1 ********************"<<endl;
TH1F * Discr1_Templ[17][11];
TH1F * Discr1_TemplMCP[17];
TH1F * Discr1_TemplMCD[17];
TH1F * Discr1_TemplMCHe[17];

for(int i=0;i<11;i++) for(int m=0;m<17;m++) Discr1_Templ[m][i]=new TH1F("","",100,0,40);

for(int m=0;m<17;m++) {
	Discr1_TemplMCP[m]=new TH1F("","",100,0,40);
	Discr1_TemplMCD[m]=new TH1F("","",100,0,40);
	Discr1_TemplMCHe[m]=new TH1F("","",100,0,40);
}

for(int i=1;i<11;i++) 
		for(int m=0;m<17;m++)
 				for(int j=1;j<Discr1_T[i]->GetNbinsX();j++){
 					Discr1_Templ[m][i]->SetBinContent(j,Discr1_T[i]->GetBinContent(j,m+1));
					}
		
		for(int m=0;m<17;m++)
                                for(int j=1;j<Discr1_T_Prim->GetNbinsX();j++){
                                        Discr1_Templ[m][0]->SetBinContent(j,Discr1_T_Prim->GetBinContent(j,m+1));
                                        }

for(int m=0;m<17;m++)
                                for(int j=1;j<Discr1_TMCP->GetNbinsX();j++){
                                        Discr1_TemplMCP[m]->SetBinContent(j,Discr1_TMCP->GetBinContent(j,m+1));
                                        Discr1_TemplMCD[m]->SetBinContent(j,Discr1_TMCD->GetBinContent(j,m+1));
					Discr1_TemplMCHe[m]->SetBinContent(j,Discr1_TMCHe->GetBinContent(j,m+1));
					}


TCanvas * c19[11][18];
for(int i=0;i<11;i++)
	for(int m=0;m<18;m++)
		{
		nome="Templates Zona "+numero[i]+": Bin "+numero[m];
		if(i==0) nome="Templates Primaries: Bin "+numero[m];
		c19[i][m]= new TCanvas(nome.c_str());
		}

TFractionFitter * fitT[18][11]={{NULL}};
TObjArray *Tpl[18][11]={{NULL}};
int s1[18][11]={{0}};
float Err1[18][11]={{0}};
TH1F *Discr1_TemplMCPW[18][11];
TH1F *Discr1_TemplMCDW[18][11];
TH1F *Discr1_TemplMCHeW[18][11];
bool He=false;

for(int i=0;i<1;i++) for(int m=0;m<17;m++) {
	He=false;
	c19[i][m]->cd();
	if(Discr1_Templ[m][i]->Integral(50,100)>0.01*Discr1_Templ[m][i]->Integral(0,100)) He=true;
	Discr1_Templ[m][i]->GetXaxis()->SetTitle("Distance Discriminant");
	Discr1_Templ[m][i]->GetXaxis()->SetTitleSize(0.045);
	Discr1_TemplMCPW[m][i]=new TH1F("","",100,0,40);
	Discr1_TemplMCDW[m][i]=new TH1F("","",100,0,40);
	Discr1_TemplMCHeW[m][i]=new TH1F("","",100,0,40);	
	Discr1_TemplMCPW[m][i]->SetFillStyle(3001);
	Discr1_TemplMCDW[m][i]->SetFillStyle(3001);
	Discr1_TemplMCHeW[m][i]->SetFillStyle(3001);
	Discr1_TemplMCPW[m][i]->SetFillColor(2);
        Discr1_TemplMCDW[m][i]->SetFillColor(4);
        Discr1_TemplMCHeW[m][i]->SetFillColor(3);
	gPad->SetLogy();
	
		TH1F *Result;
		THStack *Stack=new THStack("","");
		Tpl[m][i] = new TObjArray(2);
		Tpl[m][i]->Add(Discr1_TemplMCP[m]);
		Tpl[m][i]->Add(Discr1_TemplMCD[m]);
		if(He) Tpl[m][i]->Add(Discr1_TemplMCHe[m]);
		fitT[m][i] = new TFractionFitter(Discr1_Templ[m][i], Tpl[m][i],"q");
                if(He){ 
			fitT[m][i]->Constrain(0,0.5,1.0);
                	fitT[m][i]->Constrain(1,0.0,1.0);
			fitT[m][i]->Constrain(2,0.0,1.0);
			fitT[m][i]->SetRangeX(0,100);
			}
		else {
			fitT[m][i]->Constrain(0,0,1);
                        fitT[m][i]->Constrain(1,0,1);
			fitT[m][i]->SetRangeX(0,50);
		}
		s1[m][i]=1;//fitT[m][i]->Fit();
		double w1,w2,w3=0;
        	double e1,e2,e3=0;
		if(s1[m][i]==0){
			fitT[m][i]->GetResult(0,w1,e1);
	                fitT[m][i]->GetResult(1,w2,e2);
        	        if(He) fitT[m][i]->GetResult(2,w3,e3);
			Result = (TH1F*) fitT[m][i]->GetPlot();
	                float itot= Result->Integral();
        	        float i1 = Discr1_TemplMCP[m]->Integral();
                	float i2 = Discr1_TemplMCD[m]->Integral();
			float i3=0;
			if(He) i3 = Discr1_TemplMCHe[m]->Integral();
			if(i1>0) for(int j=0; j<Discr1_TemplMCP[m]->GetNbinsX();j++) Discr1_TemplMCPW[m][i]->SetBinContent(j,w1*Discr1_TemplMCP[m]->GetBinContent(j)/i1*itot);
			if(i2>0) for(int j=0; j<Discr1_TemplMCD[m]->GetNbinsX();j++) Discr1_TemplMCDW[m][i]->SetBinContent(j,w2*Discr1_TemplMCD[m]->GetBinContent(j)/i2*itot);
			if(i3>0) for(int j=0; j<Discr1_TemplMCHe[m]->GetNbinsX();j++) Discr1_TemplMCHeW[m][i]->SetBinContent(j,w3*Discr1_TemplMCHe[m]->GetBinContent(j)/i3*itot);
			Stack->Add(Discr1_TemplMCPW[m][i]);
			Stack->Add(Discr1_TemplMCDW[m][i]);
			if(He) Stack->Add(Discr1_TemplMCHeW[m][i]);
			Discr1_Templ[m][i]->SetMarkerStyle(8);		
			Stack->Draw();
			Discr1_Templ[m][i]->Draw("epsame");
			Result->SetLineColor(5);
			Result->SetLineWidth(2);
                	Result->Draw("SAME");
			float Cov01=fitT[m][i]->GetFitter()->GetCovarianceMatrixElement(0,1);
			float Cov02=fitT[m][i]->GetFitter()->GetCovarianceMatrixElement(0,2);
			float Cov12=fitT[m][i]->GetFitter()->GetCovarianceMatrixElement(1,2);
			float Sigma=pow((pow(e2/w2,2)+pow(e1/w1,2))/2,0.5);
			Err1[m][i]= Sigma*Discr1_TemplMCD[m]->Integral();
			cout<<w1<<" "<<e1<<endl;
			cout<<w2<<" "<<e2<<endl;
			cout<<w3<<" "<<e3<<endl;
			}
		else{
			cout<<"Zona: "<<i<<" Bin: "<<m<<endl;
			Discr1_Templ[m][i]->SetMarkerStyle(8);
			Discr1_Templ[m][i]->Draw("ep");
			Discr1_TemplMCP[m]->Draw("same");
			Discr1_TemplMCD[m]->Draw("same");
			if(He) Discr1_TemplMCHe[m]->Draw("same");
		}
	
}
	
cout<<"**************** Discr. 2 ********************"<<endl;
TH1F * Discr2_Templ[17][11];
TH1F * Discr2_TemplMCP[17];
TH1F * Discr2_TemplMCD[17];
TH1F * Discr2_TemplMCHe[17];

for(int i=0;i<11;i++) for(int m=0;m<17;m++) Discr2_Templ[m][i]=new TH1F("","",150,0,12);

for(int m=0;m<17;m++) {
        Discr2_TemplMCP[m]=new TH1F("","",150,0,12);
        Discr2_TemplMCD[m]=new TH1F("","",150,0,12);
        Discr2_TemplMCHe[m]=new TH1F("","",150,0,12);
}
        
for(int i=1;i<11;i++)
                for(int m=0;m<17;m++)
                                for(int j=1;j<Discr2_T[i]->GetNbinsX();j++){
                                        Discr2_Templ[m][i]->SetBinContent(j,Discr2_T[i]->GetBinContent(j,m+1));
                                        }

                for(int m=0;m<17;m++)
                                for(int j=1;j<Discr2_T_Prim->GetNbinsX();j++){
                                        Discr2_Templ[m][0]->SetBinContent(j,Discr2_T_Prim->GetBinContent(j,m+1));
                                        }

for(int m=0;m<17;m++)
                                for(int j=1;j<Discr2_TMCP->GetNbinsX();j++){
                                        Discr2_TemplMCP[m]->SetBinContent(j,Discr2_TMCP->GetBinContent(j,m+1));
                                        Discr2_TemplMCD[m]->SetBinContent(j,Discr2_TMCD->GetBinContent(j,m+1));
                                        Discr2_TemplMCHe[m]->SetBinContent(j,Discr2_TMCHe->GetBinContent(j,m+1));
                                        }

TCanvas * c23[11][18];
for(int i=0;i<11;i++)
        for(int m=0;m<18;m++)
                {
                nome="Templates Zona  "+numero[i]+": Bin "+numero[m];
                if(i==0) nome="Templates Primaries:  Bin "+numero[m];
                c23[i][m]= new TCanvas(nome.c_str());
                }

TFractionFitter * fitT2[18][11]={{NULL}};
TObjArray *Tpl2[18][11]={{NULL}};
int s2[18][11]={{0}};
float Err2[18][11]={{0}};
TH1F *Discr2_TemplMCPW[18][11];
TH1F *Discr2_TemplMCDW[18][11];
TH1F *Discr2_TemplMCHeW[18][11];
He=false;
for(int i=0;i<1;i++) for(int m=0;m<17;m++) {
        He=false;
        c23[i][m]->cd();
        if(Discr2_Templ[m][i]->Integral(60,150)>0.01*Discr2_Templ[m][i]->Integral(0,150)) He=true;
        Discr2_Templ[m][i]->GetXaxis()->SetTitle("Mass");
        Discr2_Templ[m][i]->GetXaxis()->SetTitleSize(0.045);
        Discr2_TemplMCPW[m][i]=new TH1F("","",150,0,12);
        Discr2_TemplMCDW[m][i]=new TH1F("","",150,0,12);
        Discr2_TemplMCHeW[m][i]=new TH1F("","",150,0,12);
        Discr2_TemplMCPW[m][i]->SetFillStyle(3001);
        Discr2_TemplMCDW[m][i]->SetFillStyle(3001);
        Discr2_TemplMCHeW[m][i]->SetFillStyle(3001);
        Discr2_TemplMCPW[m][i]->SetFillColor(2);
        Discr2_TemplMCDW[m][i]->SetFillColor(4);
        Discr2_TemplMCHeW[m][i]->SetFillColor(3);
        gPad->SetLogy();
	TH1F *Result;
                THStack *Stack=new THStack("","");
                Tpl2[m][i] = new TObjArray(2);
                Tpl2[m][i]->Add(Discr2_TemplMCP[m]);
                Tpl2[m][i]->Add(Discr2_TemplMCD[m]);
                if(He) Tpl2[m][i]->Add(Discr2_TemplMCHe[m]);
                fitT2[m][i] = new TFractionFitter(Discr2_Templ[m][i], Tpl2[m][i],"q");
                if(He){
                        fitT2[m][i]->Constrain(0,0.5,1.0);
                        fitT2[m][i]->Constrain(1,0.0,1.0);
                        fitT2[m][i]->Constrain(2,0.0,1.0);
                        fitT2[m][i]->SetRangeX(0,150);
                        }
                else {
                        fitT2[m][i]->Constrain(0,0,1);
                        fitT2[m][i]->Constrain(1,0,1);
                        fitT2[m][i]->SetRangeX(0,60);
                }
                s2[m][i]=1;//fitT2[m][i]->Fit();
                double w1,w2,w3=0;
                double e1,e2,e3=0;
		if(s2[m][i]==0){
                        fitT2[m][i]->GetResult(0,w1,e1);
                        fitT2[m][i]->GetResult(1,w2,e2);
                        if(He) fitT2[m][i]->GetResult(2,w3,e3);
                        Result = (TH1F*) fitT2[m][i]->GetPlot();
                        float itot= Result->Integral();
                        float i1 = Discr2_TemplMCP[m]->Integral();
                        float i2 = Discr2_TemplMCD[m]->Integral();
                        float i3=0;
                        if(He) i3 = Discr2_TemplMCHe[m]->Integral();
                        if(i1>0) for(int j=0; j<Discr2_TemplMCP[m]->GetNbinsX();j++) Discr2_TemplMCPW[m][i]->SetBinContent(j,w1*Discr2_TemplMCP[m]->GetBinContent(j)/i1*itot);
                        if(i2>0) for(int j=0; j<Discr2_TemplMCD[m]->GetNbinsX();j++) Discr2_TemplMCDW[m][i]->SetBinContent(j,w2*Discr2_TemplMCD[m]->GetBinContent(j)/i2*itot);
                        if(i3>0) for(int j=0; j<Discr2_TemplMCHe[m]->GetNbinsX();j++) Discr2_TemplMCHeW[m][i]->SetBinContent(j,w3*Discr2_TemplMCHe[m]->GetBinContent(j)/i3*itot);
                        Stack->Add(Discr2_TemplMCPW[m][i]);
                        Stack->Add(Discr2_TemplMCDW[m][i]);
                        if(He) Stack->Add(Discr2_TemplMCHeW[m][i]);
                        Discr2_Templ[m][i]->SetMarkerStyle(8);
                        Stack->Draw();
                        Discr2_Templ[m][i]->Draw("epsame");
                        Result->SetLineColor(5);
                        Result->SetLineWidth(2);
                        Result->Draw("SAME");
                        float Cov01=fitT2[m][i]->GetFitter()->GetCovarianceMatrixElement(0,1);
                        float Cov02=fitT2[m][i]->GetFitter()->GetCovarianceMatrixElement(0,2);
                        float Cov12=fitT2[m][i]->GetFitter()->GetCovarianceMatrixElement(1,2);
			float Sigma=pow((pow(e2/w2,2)+pow(e1/w1,2))/2,0.5);
                        Err2[m][i]= Sigma*Discr2_TemplMCD[m]->Integral();
			cout<<w1<<" "<<e1<<endl;
                        cout<<w2<<" "<<e2<<endl;
                        cout<<w3<<" "<<e3<<endl;

			}
                else{
                        cout<<"Zona: "<<i<<" Bin: "<<m<<endl;
                        Discr2_Templ[m][i]->SetMarkerStyle(8);
                        Discr2_Templ[m][i]->Draw("ep");
                        Discr2_TemplMCP[m]->Draw("same");
                        Discr2_TemplMCD[m]->Draw("same");
                        if(He) Discr2_TemplMCHe[m]->Draw("same");
                }

}


cout<<"**************** Discr. 3 ********************"<<endl;
TH1F * Discr3_Templ[17][11];
TH1F * Discr3_TemplMCP[17];
TH1F * Discr3_TemplMCD[17];
TH1F * Discr3_TemplMCHe[17];

for(int i=0;i<11;i++) for(int m=0;m<17;m++) Discr3_Templ[m][i]=new TH1F("","",150,0,12);

for(int m=0;m<17;m++) {
        Discr3_TemplMCP[m]=new TH1F("","",150,0,12);
        Discr3_TemplMCD[m]=new TH1F("","",150,0,12);
        Discr3_TemplMCHe[m]=new TH1F("","",150,0,12);
}

for(int i=1;i<11;i++)
                for(int m=0;m<17;m++)
                                for(int j=1;j<Discr3_T[i]->GetNbinsX();j++){
                                        Discr3_Templ[m][i]->SetBinContent(j,Discr3_T[i]->GetBinContent(j,m+1));
                                        }

                for(int m=0;m<17;m++)
                                for(int j=1;j<Discr3_T_Prim->GetNbinsX();j++){
                                        Discr3_Templ[m][0]->SetBinContent(j,Discr3_T_Prim->GetBinContent(j,m+1));
                                        }

for(int m=0;m<17;m++)
                                for(int j=1;j<Discr3_TMCP->GetNbinsX();j++){
                                        Discr3_TemplMCP[m]->SetBinContent(j,Discr3_TMCP->GetBinContent(j,m+1));
                                        Discr3_TemplMCD[m]->SetBinContent(j,Discr3_TMCD->GetBinContent(j,m+1));
                                        Discr3_TemplMCHe[m]->SetBinContent(j,Discr3_TMCHe->GetBinContent(j,m+1));
                                        }

TCanvas * c24[11][18];
for(int i=0;i<11;i++)
        for(int m=0;m<18;m++)
                {
                nome="Templates Zona  "+numero[i]+": Bin  "+numero[m];
                if(i==0) nome="Templates Primaries:  Bin  "+numero[m];
                c24[i][m]= new TCanvas(nome.c_str());
                }

TFractionFitter * fitT3[18][11]={{NULL}};
TObjArray *Tpl3[18][11]={{NULL}};
int s3[18][11]={{0}};
float Err3[18][11]={{0}};
TH1F *Discr3_TemplMCPW[18][11];
TH1F *Discr3_TemplMCDW[18][11];
TH1F *Discr3_TemplMCHeW[18][11];
He=false;
for(int i=0;i<1;i++) for(int m=0;m<17;m++) {
        He=false;
        c24[i][m]->cd();
       	if(Discr3_Templ[m][i]->Integral(60,150)>0.001*Discr3_Templ[m][i]->Integral(10,150)) He=true;
        Discr3_Templ[m][i]->GetXaxis()->SetTitle("Mass");
        Discr3_Templ[m][i]->GetXaxis()->SetTitleSize(0.045);
        Discr3_TemplMCPW[m][i]=new TH1F("","",150,0,12);
        Discr3_TemplMCDW[m][i]=new TH1F("","",150,0,12);
        Discr3_TemplMCHeW[m][i]=new TH1F("","",150,0,12);
        Discr3_TemplMCPW[m][i]->SetFillStyle(3001);
        Discr3_TemplMCDW[m][i]->SetFillStyle(3001);
        Discr3_TemplMCHeW[m][i]->SetFillStyle(3001);
        Discr3_TemplMCPW[m][i]->SetFillColor(2);
        Discr3_TemplMCDW[m][i]->SetFillColor(4);
        Discr3_TemplMCHeW[m][i]->SetFillColor(3);
        gPad->SetLogy();
        TH1F *Result;
                THStack *Stack=new THStack("","");
                Tpl3[m][i] = new TObjArray(2);
                Tpl3[m][i]->Add(Discr3_TemplMCP[m]);
                Tpl3[m][i]->Add(Discr3_TemplMCD[m]);
                if(He) Tpl3[m][i]->Add(Discr3_TemplMCHe[m]);
                fitT3[m][i] = new TFractionFitter(Discr3_Templ[m][i], Tpl3[m][i],"q");
                if(He){
                       // fitT3[m][i]->Constrain(0,0.0,1.0);
                       // fitT3[m][i]->Constrain(1,0.0,1.0);
                       // fitT3[m][i]->Constrain(2,0.0,1.0);
                       //fitT3[m][i]->SetRangeX(0,40);
                        }
                else {
                        fitT3[m][i]->Constrain(0,0,1);
                        fitT3[m][i]->Constrain(1,0,1);
                        fitT3[m][i]->SetRangeX(0,150);
                }
                s3[m][i]=1;//fitT3[m][i]->Fit();
                double w1,w2,w3=0;
                double e1,e2,e3=0;
                if(s3[m][i]==0){
                        fitT3[m][i]->GetResult(0,w1,e1);
                        fitT3[m][i]->GetResult(1,w2,e2);
                        if(He) fitT3[m][i]->GetResult(2,w3,e3);
			Result = (TH1F*) fitT3[m][i]->GetPlot();
                        float itot= Result->Integral();
                        float i1 = Discr3_TemplMCP[m]->Integral();
                        float i2 = Discr3_TemplMCD[m]->Integral();
                        float i3=0;
                        if(He) i3 = Discr3_TemplMCHe[m]->Integral();
                        if(i1>0) for(int j=0; j<Discr3_TemplMCP[m]->GetNbinsX();j++) Discr3_TemplMCPW[m][i]->SetBinContent(j,w1*Discr3_TemplMCP[m]->GetBinContent(j)/i1*itot);
                        if(i2>0) for(int j=0; j<Discr3_TemplMCD[m]->GetNbinsX();j++) Discr3_TemplMCDW[m][i]->SetBinContent(j,w2*Discr3_TemplMCD[m]->GetBinContent(j)/i2*itot);
                        if(i3>0) for(int j=0; j<Discr3_TemplMCHe[m]->GetNbinsX();j++) Discr3_TemplMCHeW[m][i]->SetBinContent(j,w3*Discr3_TemplMCHe[m]->GetBinContent(j)/i3*itot);
                        Stack->Add(Discr3_TemplMCPW[m][i]);
                        Stack->Add(Discr3_TemplMCDW[m][i]);
                        if(He) Stack->Add(Discr3_TemplMCHeW[m][i]);
                        Discr3_Templ[m][i]->SetMarkerStyle(8);
                        Stack->Draw();
                        Discr3_Templ[m][i]->Draw("epsame");
                        Result->SetLineColor(5);
                        Result->SetLineWidth(2);
                        Result->Draw("SAME");
        		float Cov01=fitT3[m][i]->GetFitter()->GetCovarianceMatrixElement(0,1);
                        float Cov02=fitT3[m][i]->GetFitter()->GetCovarianceMatrixElement(0,2);
                        float Cov12=fitT3[m][i]->GetFitter()->GetCovarianceMatrixElement(1,2);
			float Sigma=pow((pow(e2/w2,2)+pow(e1/w1,2))/2,0.5);
                        Err3[m][i]= Sigma*Discr3_TemplMCD[m]->Integral();
			}

                else{
                        cout<<"Zona: "<<i<<" Bin: "<<m<<endl;
                        Discr3_Templ[m][i]->SetMarkerStyle(8);
                        Discr3_Templ[m][i]->Draw("ep");
                        Discr3_TemplMCP[m]->Draw("same");
                        Discr3_TemplMCD[m]->Draw("same");
                        if(He) Discr3_TemplMCHe[m]->Draw("same");
                }

}

cout<<"****************************************************************************************** DEUTERONS FLUX ******************************************************************************************"<<endl;
TCanvas * c25 = new TCanvas("Deuterons Flux");

TGraphAsymmErrors * Discr_1 =new TGraphAsymmErrors();
Discr_1->SetTitle("Quality Distance + Distance Discr.");
TGraphAsymmErrors * Discr_2 =new TGraphAsymmErrors();
Discr_2->SetTitle("Quality Distance + Mass Discr.");
TGraphAsymmErrors * Discr_3 =new TGraphAsymmErrors();
Discr_3->SetTitle("Quality Likelihood + Mass Discr.");

point = 0;
for(int m=1;m<17;m++) if(s1[m][0]==0&&Err1[m][0]<Discr1_TemplMCDW[m][0]->Integral()) 
					{//QDMCD[m]=1;
					Discr_1->SetPoint(point,encindeut[m],(CorrLatTOTD[m])*Discr1_TemplMCDW[m][0]->Integral()/(QDMCD[m]*AcceptDistMCD[m][1]*Espos_R[m]*deltaencindeut[m]));
				       Discr_1->SetPointError(point,0,0,Err1[m][0]/(QDMCD[m]*AcceptDistMCD[m][1]*Espos_R[m]*deltaencindeut[m]),Err1[m][0]/(QDMCD[m]*AcceptDistMCD[m][1]*Espos_R[m]*deltaencindeut[m]));
				       point++;}
point = 0;
for(int m=1;m<17;m++) if(s2[m][0]==0&&Err2[m][0]<Discr2_TemplMCDW[m][0]->Integral()) 
				       {//QDMCD[m]=1;
					Discr_2->SetPoint(point,encindeut[m],(CorrLatTOTD[m])*Discr2_TemplMCDW[m][0]->Integral()/(QDMCD[m]*AcceptDistMCD[m][1]*Espos_R[m]*deltaencindeut[m])); 
				       Discr_2->SetPointError(point,0,0,Err2[m][0]/(QDMCD[m]*AcceptDistMCD[m][1]*Espos_R[m]*deltaencindeut[m]),Err2[m][0]/(QDMCD[m]*AcceptDistMCD[m][1]*Espos_R[m]*deltaencindeut[m]));
                                       point++;}

point = 0;
for(int m=1;m<17;m++) if(s3[m][0]==0&&Err3[m][0]<Discr3_TemplMCDW[m][0]->Integral()) 
				       {//QDMCL[m]=1;
					Discr_3->SetPoint(point,encindeut[m],(CorrLatTOTL[m])*Discr3_TemplMCDW[m][0]->Integral()/(QDMCL[m]*AcceptQualMCD[m][1]*Espos_R[m]*deltaencindeut[m])); 
				       Discr_3->SetPointError(point,0,0,Err3[m][0]/(QDMCL[m]*AcceptQualMCD[m][1]*Espos_R[m]*deltaencindeut[m]),Err3[m][0]/(QDMCL[m]*AcceptQualMCD[m][1]*Espos_R[m]*deltaencindeut[m]));	
				       point++;}

TGraph *galprop32=new TGraph();
TGraph *galprop3=new TGraph();
{
	j=0;
	ifstream fp("./Galprop/Trotta2011/Def/new_D.txt");
	while (!fp.eof()){
		fp>>x>>y;
		galprop32->SetPoint(j,x/1e3,y*2e7);
		j++;
	}
	galprop32->GetYaxis()->SetRangeUser(1e-1,1e3);
	galprop32->GetXaxis()->SetRangeUser(1e-1,10);
}
{
	j=0;
	ifstream fp("./Galprop/Trotta2011/Def/new_D1250.txt");
	while (!fp.eof()){
		fp>>x>>y;
		galprop3->SetPoint(j,x/1e3,y*2e7);
		j++;
	}
	galprop3->GetYaxis()->SetRangeUser(1e-1,1e3);
	galprop3->GetXaxis()->SetRangeUser(1e-1,10);
}

c25->cd();
gPad->SetLogx();
gPad->SetGridx();
gPad->SetGridy();
Discr_1->SetMarkerStyle(8);
Discr_1->SetMarkerColor(2);
Discr_2->SetMarkerStyle(8);
Discr_2->SetMarkerColor(3);
Discr_3->SetMarkerStyle(8);
Discr_3->SetMarkerColor(4);
Discr_1->GetYaxis()->SetRangeUser(1e-1,1e3);
Discr_1->GetXaxis()->SetRangeUser(1e-1,10);
Discr_3->Draw("AP");
galprop32->Draw("PLsame");
galprop3->Draw("PLsame");
Discr_1->Draw("Psame");
Discr_2->Draw("Psame");
Discr_1->Draw("Psame");
cout<<"************************************************************************************************ OUTPUT ********************************************************************************************"<<endl;
string nomefile="/home/AMS/fdimicco/fdimicco/Parte2.root";
TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
f_out->mkdir("Layer 1 Charge");
f_out->mkdir("MC Acceptance");
f_out->mkdir("Latitude Effect");
f_out->mkdir("HL Data vs MC");
f_out->mkdir("P Fluxes");
f_out->mkdir("Deuterons Template fits");
f_out->cd("Deuterons Template fits");
f_out->mkdir("Deuterons Template fits/Discr_1_Templates");
f_out->mkdir("Deuterons Template fits/Discr_2_Templates");
f_out->mkdir("Deuterons Template fits/Discr_3_Templates");
f_out->mkdir("Deuterons Counts");
f_out->cd("Layer 1 Charge");
c1->Write();
c2->Write();
c3->Write();
f_out->cd("MC Acceptance");
c4->Write();
c5->Write();
c6->Write();
f_out->cd("Latitude Effect");
c8->Write();
for(int S=0;S<10;S++) c10[S]->Write();
c27->Write();
c28->Write();
c11->Write();
c30->Write();
c12->Write();
c13->Write();
c18->Write();
c14->Write();
f_out->cd("HL Data vs MC");
for(int S=0;S<10;S++) c15[S]->Write();
c29->Write();
c16->Write();
c31->Write();
c26->Write();
c22->Write();
c20->Write();
c21->Write();
f_out->cd("P Fluxes");
c9->Write();
c7->Write();
c17->Write();
f_out->cd("Deuterons Template fits/Discr_1_Templates");
f_out->mkdir("Deuterons Template fits/Discr_1_Templates/PrimSec_Geo");
for(int i=1;i<11;i++){nome="Deuterons Template fits/Discr_1_Templates/PrimSec_Geo/Zona"+numero[i]; f_out->mkdir(nome.c_str()); f_out->cd(nome.c_str());
			for(int m=0;m<18;m++) c19[i][m]->Write();	
	       	 } 
f_out->mkdir("Deuterons Template fits/Discr_1_Templates/Primaries");
f_out->cd("Deuterons Template fits/Discr_1_Templates/Primaries");
for(int m=0;m<17;m++) c19[0][m]->Write();

f_out->cd("Deuterons Template fits/Discr_2_Templates");
f_out->mkdir("Deuterons Template fits/Discr_2_Templates/PrimSec_Geo");
for(int i=1;i<11;i++){nome="Deuterons Template fits/Discr_2_Templates/PrimSec_Geo/Zona"+numero[i]; f_out->mkdir(nome.c_str()); f_out->cd(nome.c_str());
                        for(int m=0;m<18;m++) c23[i][m]->Write();
                 }
f_out->mkdir("Deuterons Template fits/Discr_2_Templates/Primaries");
f_out->cd("Deuterons Template fits/Discr_2_Templates/Primaries");
for(int m=0;m<17;m++) c23[0][m]->Write();

f_out->cd("Deuterons Template fits/Discr_3_Templates");
f_out->mkdir("Deuterons Template fits/Discr_3_Templates/PrimSec_Geo");
for(int i=1;i<11;i++){nome="Deuterons Template fits/Discr_3_Templates/PrimSec_Geo/Zona"+numero[i]; f_out->mkdir(nome.c_str()); f_out->cd(nome.c_str());
                        for(int m=0;m<18;m++) c24[i][m]->Write();
                 }
f_out->mkdir("Deuterons Template fits/Discr_3_Templates/Primaries");
f_out->cd("Deuterons Template fits/Discr_3_Templates/Primaries");
for(int m=0;m<17;m++) c24[0][m]->Write();
f_out->cd("Deuterons Counts");
c25->Write();
f_out->Write();
f_out->Close();

}
