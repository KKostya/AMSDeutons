#include "TH2.h"
#include "TH3.h"
#include <TVector3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "TCanvas.h"
#include "TLegend.h"
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
#include "TGraphErrors.h"
#include <cstring>
#include "../Functions_auto.h"
#include "Parte2/Definitions.h"
#include "Parte2/MCpreeff.h"
#include "Parte2/MCUnbiaseff.h"
#include "Parte2/MCQualeff.h"
#include "Parte2/MCQualCheck.h"
#include "Parte2/MCQualCheck2.h"
#include "Parte2/MCTrackeff.h"
#include "Parte2/MCpreSeleff.h"
#include "Parte2/MCpreCheck.h"
#include "Parte2/MigrationMatrix.h"
#include "Parte2/DATAUnbiaseff.h"
#include "Parte2/CorrelazionePreselezioni.h"
#include "Parte2/DATApreSeleff.h"
#include "Parte2/DATAQualeff.h"
#include "Parte2/DVSMCpreSeleff.h"
#include "Parte2/DVSMCQualeff2.h"
#include "Parte2/DVSMCTrackeff.h"
#include "Parte2/AcceptanceP.h"
#include "Parte2/CorrLAT.h"
#include "Parte2/ProtonFlux.h"
#include "FillIstogram.h"
using namespace std;

//PROVA

int main(int argc, char * argv[])
{
cout<<"Month _ Indx _ Frac "<<endl;
//string percorso="/home/francesco/PhD/LocalCNAF/";
string percorso="/storage/gpfs_ams/ams/users/fdimicco/";
string frac=argv[3];
FRAC=atoi(argv[3]);
INDX=atoi(argv[2]);
string mese=argv[1];
cout<<"******************************************************************************** R BINS *********************************************************************************************************"<<endl;
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

cout<<"**************************** BETA BINS TOF***********************************"<<endl;
        float B=0.4;
        float B1=0;
        float B2=0;
        float E=0.1;
        int binnum=0;
        float a=(log(0.9)-log(0.1))/18;
        float E2=exp(log(0.1)+1.5*a);
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
        for(int i=0;i<18;i++) cout<<Betabins[i]<<" "<<Betabins[i+1]-Betabins[i]<<" "<<Ekincent[i]<<endl;
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

cout<<"******************************************************************************** ISTOGRAM FILLING ***********************************************************************************************"<<endl;
FillIstogram(INDX,frac,mese);
string nomefile=percorso + "/Risultati/risultati/"+mese+"_"+frac+"_P1.root";
TFile *file1 =TFile::Open(nomefile.c_str());
if(!file1){
        nomefile=percorso + "/Risultati/"+mese+"/"+mese+"_"+frac+"_P1.root";
        file1 =TFile::Open(nomefile.c_str());
        }

cout<<"******************************************************************************** ANALYSIS ********************************************************************************************************"<<endl;
MCpreeff(file1);
MCUnbiaseff(file1);
MCQualeff(file1);
MCQualCheck(file1);
MCQualCheck2(file1);
MCTrackeff(file1);
MCpreSeleff(file1);
Correlazione_Preselezioni(file1);
MCpreCheck();
MigrationMatrix();
DATAUnbiaseff(file1);
DATApreSeleff(file1);
DVSMCTrackeff(file1);
DATAQualeff(file1);
DVSMCpreSeleff(file1);
DVSMCQualeff2(file1);
AcceptanceP(file1);
CorrLAT(file1);
ProtonFlux(file1);
cout<<"************************************************************************************************ OUTPUT ********************************************************************************************"<<endl;
nomefile=percorso + "/CodesforAnalysis/Risultati/"+mese+".root";
TFile *f_out=new TFile(nomefile.c_str(), "RECREATE");
f_out->mkdir("MC Results");
f_out->mkdir("MC Results/Preselections");
f_out->mkdir("MC Results/Quality");
f_out->mkdir("Data-driven Results");
f_out->mkdir("Data-driven Results/Latitude Effect");
f_out->mkdir("Data-driven Results/Data vs MC");
f_out->mkdir("Data-driven Results/Data vs MC/Preselections");
f_out->mkdir("Data-driven Results/Data vs MC/Quality");
f_out->mkdir("Acceptance");
f_out->mkdir("P Flux");
f_out->mkdir("Export");
f_out->cd("MC Results");
f_out->cd("MC Results/Preselections");
c4->Write();
c11->Write();
c_7->Write();
c7->Write();
c8->Write();
c10->Write();
c13->Write();
for(int S=0;S<3;S++) c9[S]->Write();
c27->Write();
f_out->cd("MC Results/Quality");
c5->Write();
c6->Write();
c18->Write();
c19->Write();
f_out->cd("Data-driven Results");
c12->Write();
c28->Write();
f_out->cd("Data-driven Results/Latitude Effect");
for(int S=0;S<3;S++) c14[S]->Write();
c15->Write();
c16->Write();
c26->Write();
f_out->cd("Data-driven Results/Data vs MC");
f_out->cd("Data-driven Results/Data vs MC/Preselections");
for(int S=0;S<3;S++) c17[S]->Write();
f_out->cd("Data-driven Results/Data vs MC/Quality");
c20->Write();
c21->Write();
f_out->cd("Acceptance");
c22->Write();
f_out->cd("P Flux");
c23->Write();
c24->Write();
c25->Write();

f_out->cd("Export");
MigrMatrix->Write();
EffTrackerMCP_R_TH1F->Write();
EffTrackerMCP_TH1F->Write();
EffTrackerMCD_R_TH2F->Write();
EffTrackerMCD_TH2F->Write();
EffTOF_MCP_R_TH1F->Write();
EffTOF_MCP_TH1F->Write();
EffTOF_MCD_R_TH2F->Write();
EffTOF_MCD_TH2F->Write();
EffMCLikP_TH1F->Write();
EffMCLikD_TH2F->Write();
EffMCLikP_Beta_TH1F->Write();
EffMCLikD_Beta_TH2F->Write();
EffMCDistP_TH1F->Write();
EffMCDistD_TH2F->Write();
EffMCDistP_Beta_TH1F->Write();
EffMCDistD_Beta_TH2F->Write();
EffPreSelMCP_R_TH2F->Write();
EffPreSelMCP_TH2F->Write();
EffPreSelMCD_R_TH3F->Write();
EffPreSelMCD_TH3F->Write();
EffQualCheckMCP_TH1F->Write();
EffLik2CheckMCP_TH1F->Write();
EffDistCheckMCP_TH1F->Write();
for(int S=0;S<3;S++) CorrLAT_pre[S]->Write();
for(int S=0;S<3;S++) CorrLATpre_spl[S]->Write();
for(int S=0;S<3;S++) CorrLATpre_Spl[S]->Write();
CorrLAT_Lik->Write();
CorrLAT_Dist->Write();
CorrLAT_Dist_spl->Write();
CorrLAT_Dist_Spl->Write();
CorrLAT_Lik_spl->Write();
CorrLAT_Lik_Spl->Write();
DistDVSMC_P->Write("DistDVSMC_P");
LikDVSMC_P->Write("LikDVSMC_P");
LikDVSMC_P_Graph->Write();
DistDVSMC_P_Graph->Write();
LikDVSMC_P_graph->Write();
DistDVSMC_P_graph->Write();
for(int S=0;S<3;S++) PreDVSMC_P_Graph[S]->Write();
for(int S=0;S<3;S++) PreDVSMC_P[S]->Write();
AcceptPzone->Write();
CorrLAT_tot_spl->Write();
CorrLAT_pre_spl->Write();
CorrLAT_totM2->Write();
CorrLAT_preM2->Write();
for(int i=0;i<11;i++) P_Fluxgeo[i]->Write();
PFlux->Write();
P_Flux->Write();
P_Flux_pre->Write();
f_out->Write();
f_out->Close();

return 1;
}
