#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF2.h"
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

double bin[24];
float tempobin[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
float tempobingeo[24][11];
int U_time;
float Latitude;
int zonageo;
float Rcutoff;
float CaricaTOF=0;
float CaricaTRD=0;
float CaricaTrack=0;
float ProbQ=0;
float Qbest=0;
std::vector<float> * Endep = 0;
int layernonusati=0;
int NAnticluster=0;
int NTRDSegments=0;
int NTofClusters=0;
int NTofClustersusati=0;
double Rup=0;
double Rdown=0;
double R=0;
std::vector<float> * chiq = 0;
std::vector<float> * R_ = 0;
float residuoY=0;
float residuoX=0;
int fuoriY=0;
int fuoriX=0;
int clusterTOFfuori=0;
int clusterTrackfuori=0;
int clusterTRDfuori=0;
float Beta=0;
float Betacorr=0;
float Beta_corr=0;
float BetaRICH=-1;
float Massa=0;
float EdepTRD=0;
int NTRDclusters=0;
float Livetime;
int a,b,c,d,e,f,g,h,l,m,n,o,p,q,r,s,t,u,v=0;
int a1,b1,c1,d1,e1=0;
int alpha,Gamma,delta,alpha1,gamma1,delta1=0;
int a2=0;
float EndepTOF;
std::vector<float> * TRDclusters = 0;
std::vector<double> * ResiduiX;
std::vector<double> * ResiduiY;
float Chisquare=0; 
float endepostatrack=0;
int NTrackHits=0;
std::vector<float> * clusterTrack = 0;
int protoni[23][11];
int primari[23][11];
int primari_RICH_MC[23];
int primari_RICH[23];
int PROTONI[23];
int DEUTONI[23];
int primari_D[23][11];
int primari_bkgnd[23][11];
int deutoni[23][11];
int background[23];
int Template_D[23];
int background_He[23];
int background_el[23];
int background_pos[23];
int preselezionate[23][11];
int pres_unbias[23][11];
int preselected[23][11];
int quality[23][11];
int quality_D[23];
int Unbiascounts[23];
int Unbias_geo[23][11];
double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};
int tbeg,tend;
double tempozona[11]={0,0,0,0,0,0,0,0,0,0,0};
int contasecondi[11]={0,0,0,0,0,0,0,0,0,0,0};
int zona;
float Time[11]={0,0,0,0,0,0,0,0,0,0,0};
float Massa_gen,Momento_gen,Beta_gen;
int efficienzagen[23];
int efficienzagen_D[23];
int efficienzagen_He[23];
int efficienzagen_el[23];
int efficienzagen_pos[23];
float Etot=0;
float R_corr=0;
int rig;
int bet;
int Particle_ID=0;
double probP,probD;
double matricervsbeta[100][100];
double matricervsbetad[100][100];
float ThetaTOF=0;
float PhiTOF=0;
float ThetaTrack=0;
float PhiTrack=0;
float ThetaTRD=0;
float PhiTRD=0;
float PhiProjTOF=0;
float PhiProjTrack=0;
float PhiProjTRD=0;
float CooTOF[3]={0,0,0};
float CooTrack[3]={0,0,0};
float CooTRD[3]={0,0,0};
float RGDT=0;
float BT=0;
float distR=0;
float distB=0;
float distETOF=0;
float distETrack=0;
float distETRD=0;
float DistTOF=0;
float DistTrack=0;
float DistTRD=0;
float Dist1=1000000;
float Dist2=1000000;
float Dist3=1000000;
float CooTOF_p[3]={0,0,0};
float CooTrack_p[3]={0,0,0};
float CooTRD_p[3]={0,0,0};
float RminTOF=0;
float RminTrack=0;
float RminTRD=0;
float RminTOF_P=0;
float RminTrack_P=0;
float RminTRD_P=0;
float DistTOF_P=DistTOF;
float DistTrack_P=DistTrack;
float DistTRD_P=DistTRD;
float PhiProjTOF_P=0;
float PhiProjTrack_P=0;
float PhiProjTRD_P=0;
float pi=3.14159265358979312e+00;
float EdepTOF=0;
float EdepTrack=0;
float E_depTRD=0;
int DR1,DR2,DR3=0;
float PSCALTOF=0;
float PSCALTrack=0;
float PSCALTRD=0;
float PSCALTOF2=0;
float PSCALTrack2=0;
float PSCALTRD2=0;
float PSCALTOF3=0;
float PSCALTrack3=0;
float PSCALTRD3=0;
float passo=0.01;
float DistanzaTOT=0;
long double L_fakeD=0;
long double L_trueD=0;
long double LDiscriminant=0;
double LSignal=0;
double LBkgnd=0;
float Unbias=0;
long double trueD=0;
long double fakeD=0;
float Pres_Unbias=0;
float Preselected=0;
float R_pre=0;
bool Quality(TTree *albero,int i)
{
	int k = albero->GetEvent(i);
	 bool selection = true;
if(Beta<0) selection=false;
//QUALITY
if(NAnticluster>0)  selection = false; else f++;
if(NTRDSegments<1)  selection = false; else g++;
if((NTofClusters-NTofClustersusati)>0)  selection = false; else h++;
if(fabs(Rup-Rdown)/R>0.2)  selection = false; else l++;
if(ProbQ<0.43) selection = false; else m++;
//CONTROLLOFIT
a2=0;
for(int j=0;j<6;j++)
        if((*chiq)[j]<0||(*chiq)[j]>15||fabs((*R_)[j]-R)/R>0.2) a2++;
if(a2>0) selection = false; else n++;
fuoriX=0;
fuoriY=0;
for(int layer=0;layer<7;layer++) {
	if((*ResiduiY)[layer]<-200) fuoriY++;
	if((*ResiduiX)[layer]<-200&&(*ResiduiY)[layer]>-200) fuoriX++;	
	}
if(layernonusati>0) selection = false; else s++;
if(fuoriX>2) selection = false; else o++;
if(Chisquare>3) selection = false; else r++;
//CARICA-non più usate: mancata calibrazione sui dati per TOF, correlate con Edep
//if(fabs(CaricaTOF-Qbest)>0.1) selection  = false; else t++;
//if(fabs(CaricaTRD-Qbest)>0.17) selection = false; else v++;
//if(fabs(CaricaTrack-Qbest)>0.1) selection = false; else u++;
selection=true;
///////Matter or Antimatter
if (R<0) selection=false;
////////////////////////////
R=fabs(R);
/////////////////////////// Calcolo LIKELIHOOD ////////////////////////////
L_fakeD=ProbP_DiffR_P->Eval(fabs(Rup-Rdown)/R)*ProbP_Anticl->Eval(NAnticluster)*ProbP_clTOF->Eval(NTofClusters-NTofClustersusati)*ProbP_layer->Eval(layernonusati)*ProbP_fuoriX->Eval(fuoriX)*ProbP_Chi2->Eval(Chisquare);
L_trueD=ProbD_DiffR_D->Eval(fabs(Rup-Rdown)/R)*ProbD_Anticl->Eval(NAnticluster)*ProbD_clTOF->Eval(NTofClusters-NTofClustersusati)*ProbD_layer->Eval(layernonusati)*ProbD_fuoriX->Eval(fuoriX)*ProbD_Chi2->Eval(Chisquare);
if((1-L_trueD/(L_fakeD+L_trueD))>0.2) selection=false; 
///////////////////////////////////////////////////////////////////////////
/////////////////////////// Correzione R e Beta ///////////////////////////
EdepTOF=((*Endep)[0]+(*Endep)[1]+(*Endep)[2]+(*Endep)[3])/4;
EdepTrack=endepostatrack/NTrackHits;
E_depTRD=EdepTRD/NTRDclusters;
EndepTOF=((*Endep)[0]+(*Endep)[1]+(*Endep)[2]+(*Endep)[3])/4;
Etot=E_Beta_m->Eval(Beta_corr,Massa);
Beta_corr=Betacorr;//Beta_E_m->Eval(Etot+4*1e-3*EndepTOF+1e-6*EdepTRD+120/32*1e-6*endepostatrack,Massa);      
R_corr=R;//Beta_corr*(Etot+7*(2*1e-3*EndepTOF+NTRDclusters*1e-6*EdepTRD+120/32*1e-6*endepostatrack));
Massa=pow(fabs(pow(fabs(R_corr)*pow((1-pow(Beta_corr,2)),0.5)/Beta_corr,2)),0.5);
//////////////////////////////////////////////////////////////////////

//=true: Disattiva selezione/////
selection=selection;
////////////////////////////////
return selection;

}

float CalcolaRmin(float Min,float Max, TSpline *E, float X, float Y, float Z, TF1 *RBETA){
					
			if((Max-Min)<0.01) return (Max-Min)/2;
			float Max_m=Max;			
			Max=(Max-Min)/2;
			float bt_min=RBETA->Eval(Min);
			float bt_max=RBETA->Eval(Max);				
float G_min=2*(Min-X)+2*(E->Eval(bt_min)-Y)*((E->Eval(bt_min+RBETA->Eval(Min+0.01))-E->Eval(bt_min))/0.01)+2*(bt_min-Z)*((RBETA->Eval(Min+0.01)-bt_min)/0.01);
float G_max=2*(Max-X)+2*(E->Eval(bt_max)-Y)*((E->Eval(bt_max+RBETA->Eval(Max+0.01))-E->Eval(bt_max))/0.01)+2*(bt_max-Z)*((RBETA->Eval(Max+0.01)-bt_max)/0.01);
		         	if(G_min*G_max<0) return CalcolaRmin(Min,Max,E,X,Y,Z,RBETA);
				else return CalcolaRmin(Max,Max_m,E,X,Y,Z,RBETA);
}

		



void Nuovasel(float RG,float M, TF1 *RBETA){
                        RGDT=0;
                        BT=0;
                        distR=0;
                        distB=0;
                        distETOF=0;
                        distETrack=0;
                        distETRD=0;
                        DistTOF=0;
                        DistTrack=0;
                        DistTRD=0;
                        DR1=0; DR2=0; DR3=0;
                        for(int P=0;P<3;P++) CooTOF[P]=0;
                        for(int P=0;P<3;P++) CooTrack[P]=0;

      	      //////////////////// CALCOLO DISTANZA /////////////////////////           
		   Dist1=1000000;
                        Dist2=1000000;
                        Dist3=1000000;
                        for(int z=0;z<1e6;z++){
                                passo=0.01;
                                BT=RBETA->Eval(RGDT);
                                distR=(RGDT-RG)/(pow(RG,2)*Rig->Eval(RG));
                                distB=(BT-Beta_corr)/(pow(Beta_corr,2)*beta->Eval(Beta_corr));
                                distETOF=(EdepTOFbeta->Eval(BT)-EdepTOF)/(pow(EdepTOFbeta->Eval(BT),2)*etof->Eval(BT));
                                distETrack=(EdepTrackbeta->Eval(BT)-EdepTrack)/(pow(EdepTrackbeta->Eval(BT),2)*etrack->Eval(BT));
                                distETRD=(EdepTRDbeta->Eval(BT)-E_depTRD)/(pow(EdepTRDbeta->Eval(BT),2)*etrd->Eval(BT));

                                DistTOF=pow(pow(distR,2)+pow(distB,2)+pow(distETOF,2),0.5);
                                DistTrack=pow(pow(distR,2)+pow(distB,2)+pow(distETrack,2),0.5);
                                DistTRD=pow(pow(distR,2)+pow(distB,2)+pow(distETRD,2),0.5);
                                if(DistTOF<Dist1) { DR1=0;Dist1=DistTOF; CooTOF[0]=distETOF; CooTOF[1]=distB; CooTOF[2]=distR; RminTOF=RGDT;}
                                else DR1++;
                                if(DistTrack<Dist2) { DR2=0;Dist2=DistTrack; CooTrack[0]=distETrack; CooTrack[1]=distB; CooTrack[2]=distR; RminTrack=RGDT;}
                                else DR2++;
                                if(DistTRD<Dist3) { DR3=0;Dist3=DistTRD; CooTRD[0]=distETRD; CooTRD[1]=distB; CooTRD[2]=distR; RminTRD=RGDT;}
                                else DR3++;
                                if(DR1>10&&DR2>10&&DR3>10) break;
                                RGDT=RGDT+passo;

                                }
		/////////////////////////////////////////////////////////////////

		   PhiTOF=acos(CooTOF[2]/pow(pow(CooTOF[0],2)+pow(CooTOF[2],2),0.5));
                        if(CooTOF[0]<0) PhiTOF=2*pi-PhiTOF;
                        ThetaTOF=acos(CooTOF[1]/Dist1);
                        if(CooTOF[2]<0) ThetaTOF=2*pi-ThetaTOF;
                        PhiTrack=acos(CooTrack[2]/pow(pow(CooTrack[0],2)+pow(CooTrack[2],2),0.5));
                        if(CooTrack[0]<0) PhiTrack=2*pi-PhiTrack;
                        ThetaTrack=acos(CooTrack[1]/Dist2);
                        if(CooTrack[2]<0) ThetaTrack=2*pi-ThetaTrack;
                        PhiTRD=acos(CooTRD[2]/pow(pow(CooTRD[0],2)+pow(CooTRD[2],2),0.5));
                        if(CooTRD[0]<0) PhiTRD=2*pi-PhiTRD;
                        ThetaTRD=acos(CooTRD[1]/Dist3);
                        if(CooTRD[2]<0) ThetaTRD=2*pi-ThetaTRD;
                        DistTOF=Dist1;
                        DistTrack=Dist2;
                        DistTRD=Dist3;
		   /////////////////////////// VETTORE TANGENTE ///////////////////////////////////
		             float TanTOF[3]={0,0,0};
                        float TanTrack[3]={0,0,0};
                        float TanTRD[3]={0,0,0};
        TanTOF[0]=(EdepTOFbeta->Eval(RBETA->Eval(RminTOF+passo))-EdepTOFbeta->Eval(RBETA->Eval(RminTOF)))/(pow(EdepTOFbeta->Eval(RBETA->Eval(RminTOF)),2)*etof->Eval(RBETA->Eval(RminTOF)));
        TanTrack[0]=(EdepTrackbeta->Eval(RBETA->Eval(RminTrack+passo))-EdepTrackbeta->Eval(RBETA->Eval(RminTrack)))/(pow(EdepTrackbeta->Eval(RBETA->Eval(RminTrack)),2)*etrack->Eval(RBETA->Eval(RminTrack)));
        TanTRD[0]=(EdepTRDbeta->Eval(RBETA->Eval(RminTRD+passo))-EdepTRDbeta->Eval(RBETA->Eval(RminTRD)))/(pow(EdepTRDbeta->Eval(RBETA->Eval(RminTRD)),2)*etrd->Eval(RBETA->Eval(RminTRD)));
        TanTOF[1]=(RBETA->Eval(RminTOF+passo)-RBETA->Eval(RminTOF))/(pow(Beta_corr,2)*beta->Eval(Beta_corr));
        TanTrack[1]=(RBETA->Eval(RminTrack+passo)-RBETA->Eval(RminTrack))/(pow(Beta_corr,2)*beta->Eval(Beta_corr));
        TanTRD[1]=(RBETA->Eval(RminTRD+passo)-RBETA->Eval(RminTRD))/(pow(Beta_corr,2)*beta->Eval(Beta_corr));
        TanTOF[2]=passo/(pow(RG,2)*Rig->Eval(RG));
        TanTrack[2]=passo/(pow(RG,2)*Rig->Eval(RG));
        TanTRD[2]=passo/(pow(RG,2)*Rig->Eval(RG));

        for(int i=0;i<3;i++) {TanTOF[i]=3*TanTOF[i];TanTrack[i]=3*TanTrack[i];TanTRD[i]=3*TanTRD[i];}
        PSCALTOF=CooTOF[0]*TanTOF[0]+CooTOF[1]*TanTOF[1]+CooTOF[2]*TanTOF[2];
        PSCALTrack=CooTrack[0]*TanTrack[0]+CooTrack[1]*TanTrack[1]+CooTrack[2]*TanTrack[2];
        PSCALTRD=CooTRD[0]*TanTRD[0]+CooTRD[1]*TanTRD[1]+CooTRD[2]*TanTRD[2];
        float normaCooTOF=0;
        float normaCooTrack=0;
        float normaCooTRD=0;
        float normaTanTOF=0;
        float normaTanTrack=0;
        float normaTanTRD=0;
        for(int i=0;i<3;i++) {
                normaCooTOF=normaCooTOF+CooTOF[i]*CooTOF[i];
                normaCooTrack=normaCooTrack+CooTrack[i]*CooTrack[i];
                normaCooTRD=normaCooTRD+CooTRD[i]*CooTRD[i];
                normaTanTOF=normaTanTOF+TanTOF[i]*TanTOF[i];
                normaTanTrack=normaTanTrack+TanTrack[i]*TanTrack[i];
                normaTanTRD=normaTanTRD+TanTRD[i]*TanTRD[i];
                        }

                normaCooTOF=pow(normaCooTOF,0.5);
                normaCooTrack=pow(normaCooTrack,0.5);
                normaCooTRD=pow(normaCooTRD,0.5);
                normaTanTOF=pow(normaTanTOF,0.5);
                normaTanTrack=pow(normaTanTrack,0.5);
                normaTanTRD=pow(normaTanTRD,0.5);
                PSCALTOF=acos(PSCALTOF/(DistTOF*normaTanTOF));
                PSCALTrack=acos(PSCALTrack/(DistTrack*normaTanTrack));
                PSCALTRD=acos(PSCALTRD/(DistTRD*normaTanTRD));
		
	 //////////////////////////////////////////////////////////////////////////
	 //
	 //
	 ////////////////////////////// PROIEZIONE P. PERP. (TRot.)////////////////
	    float AsseBetaTOF[3]={0,1,0};
                float AsseBetaTrack[3]={0,1,0};
                float AsseBetaTRD[3]={0,1,0};
                float PVettTOF[3]={0,0,0};
                float PVettTrack[3]={0,0,0};
                float PVettTRD[3]={0,0,0};
                PVettTOF[0]=AsseBetaTOF[1]*TanTOF[2]-AsseBetaTOF[2]*TanTOF[1];
                PVettTOF[1]=AsseBetaTOF[0]*TanTOF[2]-AsseBetaTOF[2]*TanTOF[0];
                PVettTOF[2]=AsseBetaTOF[0]*TanTOF[1]-AsseBetaTOF[1]*TanTOF[0];
                PVettTrack[0]=AsseBetaTrack[1]*TanTrack[2]-AsseBetaTrack[2]*TanTrack[1];
                PVettTrack[1]=AsseBetaTrack[0]*TanTrack[2]-AsseBetaTrack[2]*TanTrack[0];
                PVettTrack[2]=AsseBetaTrack[0]*TanTrack[1]-AsseBetaTrack[1]*TanTrack[0];
                PVettTRD[0]=AsseBetaTRD[1]*TanTRD[2]-AsseBetaTRD[2]*TanTRD[1];
                PVettTRD[1]=AsseBetaTRD[0]*TanTRD[2]-AsseBetaTRD[2]*TanTRD[0];
                PVettTRD[2]=AsseBetaTRD[0]*TanTRD[1]-AsseBetaTRD[1]*TanTRD[0];
                PSCALTOF2=TanTOF[0]*AsseBetaTOF[0]+TanTOF[1]*AsseBetaTOF[1]+TanTOF[2]*AsseBetaTOF[2];
                PSCALTrack2=TanTrack[0]*AsseBetaTrack[0]+TanTrack[1]*AsseBetaTrack[1]+TanTrack[2]*AsseBetaTrack[2];
                PSCALTRD2=TanTRD[0]*AsseBetaTRD[0]+TanTRD[1]*AsseBetaTRD[1]+TanTRD[2]*AsseBetaTRD[2];
                TVector3 R_TOF(PVettTOF[0],PVettTOF[1],PVettTOF[2]);
                TVector3 R_Track(PVettTrack[0],PVettTrack[1],PVettTrack[2]);
                TVector3 R_TRD(PVettTRD[0],PVettTRD[1],PVettTRD[2]);
                TVector3 X_TOF(0,0,1);
                TVector3 X_Track(0,0,1);
                TVector3 X_TRD(0,0,1);
                X_TOF.Rotate((acos(PSCALTOF2/normaTanTOF)),R_TOF);
                X_Track.Rotate((acos(PSCALTrack2/normaTanTrack)),R_Track);
                X_TRD.Rotate((acos(PSCALTRD2/normaTanTRD)),R_TRD);
                TVector3 Y_TOF(1,0,0);
                TVector3 Y_Track(1,0,0);
                TVector3 Y_TRD(1,0,0);
                Y_TOF.Rotate((acos(PSCALTOF2/normaTanTOF)),R_TOF);
                Y_Track.Rotate((acos(PSCALTrack2/normaTanTrack)),R_Track);
                Y_TRD.Rotate((acos(PSCALTRD2/normaTanTRD)),R_TRD);
                PSCALTOF2=CooTOF[0]*X_TOF(0)+CooTOF[1]*X_TOF(1)+CooTOF[2]*X_TOF(2);
                PSCALTrack2=CooTrack[0]*X_Track(0)+CooTrack[1]*X_Track(1)+CooTrack[2]*X_Track(2);
                PSCALTRD2=CooTOF[0]*X_TRD(0)+CooTRD[1]*X_TRD(1)+CooTRD[2]*X_TRD(2);
                PSCALTOF3=CooTOF[0]*Y_TOF(0)+CooTOF[1]*Y_TOF(1)+CooTOF[2]*Y_TOF(2);
                PSCALTrack3=CooTrack[0]*Y_Track(0)+CooTrack[1]*Y_Track(1)+CooTrack[2]*Y_Track(2);
                PSCALTRD3=CooTOF[0]*Y_TRD(0)+CooTRD[1]*Y_TRD(1)+CooTRD[2]*Y_TRD(2);

                PhiProjTOF=acos(PSCALTOF2/(DistTOF*X_TOF.Mag()));
                if(PSCALTOF3<0) PhiProjTOF=2*pi-PhiProjTOF;
                PhiProjTrack=acos(PSCALTrack2/(DistTrack*X_Track.Mag()));
                if(PSCALTrack3<0) PhiProjTrack=2*pi-PhiProjTrack;
                PhiProjTRD=acos(PSCALTRD2/(DistTRD*X_TRD.Mag()));
                if(PSCALTRD3<0) PhiProjTRD=2*pi-PhiProjTRD;

		
		
		
		////////////////////////////////////////////////////////////////		
		DistanzaTOT=pow(pow(DistTOF,2)+pow(DistTrack,2)+pow(DistTRD,2),0.5);
		if(M<1) {DistTOF_P=DistTOF;DistTrack_P=DistTrack;DistTRD_P=DistTRD;PhiProjTOF_P=PhiProjTOF;PhiProjTrack_P=PhiProjTrack;PhiProjTRD_P=PhiProjTRD;RminTOF_P=RminTOF;RminTrack_P=RminTrack;RminTRD_P=RminTRD;};
		return;
}
long double CalcoloLikelihood(){
float X=0;
float Y=0;
long double P_TOF=2;
long double P_Track=0;
long double P_TRD=0;
long double D_TOF=0;
long double D_Track=0;
long double D_TRD=0;

float Rmin=0.5;
float Rmax=0.9;
for(int Z=0;Z<9;Z++){
X=DistTOF*cos(PhiProjTOF);
Y=DistTOF*sin(PhiProjTOF);
if(RminTOF>Rmin&&RminTOF<=Rmax){
	for(int i=0;i<25;i++)
		if(Y>=(-5+(10/(float)25)*i)&&Y<(-5+(10/(float)25)*(i+1)))
			for(int j=0;j<25;j++)
				if(X>=(-5+(10/(float)25)*j)&&X<(-5+(10/(float)25)*(j+1))){
					if(Z==0) {P_TOF=SelezioneTOF_P_0[i][j];D_TOF=SelezioneTOF_D_0[i][j]; }
                                        if(Z==1) {P_TOF=SelezioneTOF_P_1[i][j];D_TOF=SelezioneTOF_D_1[i][j]; }
                                        if(Z==2) {P_TOF=SelezioneTOF_P_2[i][j];D_TOF=SelezioneTOF_D_2[i][j]; }
                                        if(Z==3) {P_TOF=SelezioneTOF_P_3[i][j];D_TOF=SelezioneTOF_D_3[i][j]; }
                                        if(Z==4) {P_TOF=SelezioneTOF_P_4[i][j];D_TOF=SelezioneTOF_D_4[i][j]; }
                                        if(Z==5) {P_TOF=SelezioneTOF_P_5[i][j];D_TOF=SelezioneTOF_D_5[i][j]; }
                                        if(Z==6) {P_TOF=SelezioneTOF_P_6[i][j];D_TOF=SelezioneTOF_D_6[i][j]; }
                                        if(Z==7) {P_TOF=SelezioneTOF_P_7[i][j];D_TOF=SelezioneTOF_D_7[i][j]; }
                                        if(Z==8) {P_TOF=SelezioneTOF_P_8[i][j];D_TOF=SelezioneTOF_D_8[i][j]; }
					}
				}
Rmin=Rmin+0.4;
Rmax=Rmax+0.4;

}


Rmin=0.5;
Rmax=0.9;
for(int Z=0;Z<9;Z++){
X=DistTrack*cos(PhiProjTrack);
Y=DistTrack*sin(PhiProjTrack);
if(RminTrack>Rmin&&RminTrack<=Rmax){
        for(int i=0;i<25;i++)
                if(Y>=(-5+(10/(float)25)*i)&&Y<(-5+(10/(float)25)*(i+1)))
                        for(int j=0;j<25;j++)
                                if(X>=(-5+(10/(float)25)*j)&&X<(-5+(10/(float)25)*(j+1))){
                                        if(Z==0) {P_Track=SelezioneTrack_P_0[i][j];D_Track=SelezioneTrack_D_0[i][j]; }
                                        if(Z==1) {P_Track=SelezioneTrack_P_1[i][j];D_Track=SelezioneTrack_D_1[i][j]; }
                                        if(Z==2) {P_Track=SelezioneTrack_P_2[i][j];D_Track=SelezioneTrack_D_2[i][j]; }
                                        if(Z==3) {P_Track=SelezioneTrack_P_3[i][j];D_Track=SelezioneTrack_D_3[i][j]; }
                                        if(Z==4) {P_Track=SelezioneTrack_P_4[i][j];D_Track=SelezioneTrack_D_4[i][j]; }
                                        if(Z==5) {P_Track=SelezioneTrack_P_5[i][j];D_Track=SelezioneTrack_D_5[i][j]; }
                                        if(Z==6) {P_Track=SelezioneTrack_P_6[i][j];D_Track=SelezioneTrack_D_6[i][j]; }
                                        if(Z==7) {P_Track=SelezioneTrack_P_7[i][j];D_Track=SelezioneTrack_D_7[i][j]; }
                                        if(Z==8) {P_Track=SelezioneTrack_P_8[i][j];D_Track=SelezioneTrack_D_8[i][j]; }
                                        }
                                }
Rmin=Rmin+0.4;
Rmax=Rmax+0.4;

}

Rmin=0.5;
Rmax=0.9;
for(int Z=0;Z<9;Z++){
X=DistTRD*cos(PhiProjTRD);
Y=DistTRD*sin(PhiProjTRD);
if(RminTRD>Rmin&&RminTRD<=Rmax){
        for(int i=0;i<25;i++)
                if(Y>=(-5+(10/(float)25)*i)&&Y<(-5+(10/(float)25)*(i+1)))
                        for(int j=0;j<25;j++)
                                if(X>=(-5+(10/(float)25)*j)&&X<(-5+(10/(float)25)*(j+1))){
                                        if(Z==0) {P_TRD=SelezioneTRD_P_0[i][j];D_TRD=SelezioneTRD_D_0[i][j]; }
                                        if(Z==1) {P_TRD=SelezioneTRD_P_1[i][j];D_TRD=SelezioneTRD_D_1[i][j]; }
                                        if(Z==2) {P_TRD=SelezioneTRD_P_2[i][j];D_TRD=SelezioneTRD_D_2[i][j]; }
                                        if(Z==3) {P_TRD=SelezioneTRD_P_3[i][j];D_TRD=SelezioneTRD_D_3[i][j]; }
                                        if(Z==4) {P_TRD=SelezioneTRD_P_4[i][j];D_TRD=SelezioneTRD_D_4[i][j]; }
                                        if(Z==5) {P_TRD=SelezioneTRD_P_5[i][j];D_TRD=SelezioneTRD_D_5[i][j]; }
                                        if(Z==6) {P_TRD=SelezioneTRD_P_6[i][j];D_TRD=SelezioneTRD_D_6[i][j]; }
                                        if(Z==7) {P_TRD=SelezioneTRD_P_7[i][j];D_TRD=SelezioneTRD_D_7[i][j]; }
                                        if(Z==8) {P_TRD=SelezioneTRD_P_8[i][j];D_TRD=SelezioneTRD_D_8[i][j]; }
                                        }
                                }

Rmin=Rmin+0.4;
Rmax=Rmax+0.4;

}

trueD=2;
fakeD=2;
if(DistTOF>3||DistTrack>3||DistTRD>3||RminTOF>=4.1||RminTRD>=4.1||RminTrack>=4.1) return 2;
else if(!(PhiProjTOF>=0&&PhiProjTOF<6.39)) return 2;
else if(!(PhiProjTrack>=0&&PhiProjTrack<6.39)) return 2;
else if(!(PhiProjTRD>=0&&PhiProjTRD<6.39)) return 2;
else{

fakeD=P_TOF*P_Track*P_TRD;
trueD=D_TOF*D_Track*D_TRD;

return trueD/(long double)(fakeD+trueD);
}

}

bool Protoni (TTree *albero,int i)
{
	
        bool isprot=true;
        clusterTOFfuori=0;
        clusterTrackfuori=0;
	clusterTRDfuori=0;
	int k = albero->GetEvent(i);
	float n_sigmaTOF=3;
	float n_sigmaTrack=3;
	float n_sigmaTRD=3;
	float n_sigmabeta=2;
	float n_sigmaR=2;	
	EndepTOF=EdepTOF;
	Nuovasel(R,0.938,protons); 
	//TOF
       for (int j=0;j<4;j++)
        	if ((*Endep)[j]>EdepTOFbeta->Eval(Beta_corr)+n_sigmaTOF*pow(EdepTOFbeta->Eval(Beta_corr),2)*etof->Eval(Beta_corr)||(*Endep)[j]<EdepTOFbeta->Eval(Beta_corr)-n_sigmaTOF*pow(EdepTOFbeta->Eval(Beta_corr),2)*etof->Eval(Beta_corr)) clusterTOFfuori++;
        
        if(clusterTOFfuori>1) isprot=false;
        else b++;
        //TRACKER
        for (int j=0;j<NTrackHits;j++)
        	if((*clusterTrack)[j]>EdepTrackbeta->Eval(Beta_corr)+n_sigmaTrack*pow(EdepTrackbeta->Eval(Beta_corr),2)*etrack->Eval(Beta_corr)||(*clusterTrack)[j]<EdepTrackbeta->Eval(Beta_corr)-n_sigmaTrack*pow(EdepTrackbeta->Eval(Beta_corr),2)*etrack->Eval(Beta_corr)) clusterTrackfuori++;
	if (clusterTrackfuori>2) isprot=false;
	else d++;
        //TRD
	for(int j=0;j<NTRDclusters;j++)	
		if((*TRDclusters)[j]>EdepTRDbeta->Eval(Beta_corr)+n_sigmaTRD*pow(EdepTRDbeta->Eval(Beta_corr),2)*etrd->Eval(Beta_corr)||(*TRDclusters)[j]<EdepTRDbeta->Eval(Beta_corr)-n_sigmaTRD*pow(EdepTRDbeta->Eval(Beta_corr),2)*etrd->Eval(Beta_corr))  clusterTRDfuori++;
	if(clusterTRDfuori>8) isprot=false;
	else e++;
	//=true: Disattiva selezione/////
	isprot=true;
	////////////////////////////////
        return isprot;
}

bool Deutoni (TTree *albero,int i)
{
        bool isprot=true;
        clusterTOFfuori=0;
        clusterTrackfuori=0;
	clusterTRDfuori=0;        
	int k = albero->GetEvent(i);
	float n_sigmaTOF=3;
	float n_sigmaTrack=3;
	float n_sigmaTRD=3;
	float n_sigmabeta=2;
	float n_sigmaR=2;
	EndepTOF=EdepTOF;	
	Nuovasel(R,1.875,deutons);		
	// if(Beta_corr<0.825&&DistTOF<3&&DistTrack<3&&DistTRD<3) LDiscriminant=CalcoloLIKELIHOOD();
	//else LDiscriminant=0;
	LDiscriminant=CalcoloLikelihood();	
	//TOF
        for (int j=0;j<4;j++)
        	if ((*Endep)[j]>EdepTOFbeta->Eval(Beta_corr)+n_sigmaTOF*pow(EdepTOFbeta->Eval(Beta_corr),2)*etof->Eval(Beta_corr)||(*Endep)[j]<EdepTOFbeta->Eval(Beta_corr)-n_sigmaTOF*pow(EdepTOFbeta->Eval(Beta_corr),2)*etof->Eval(Beta_corr)) clusterTOFfuori++;
        
        if(clusterTOFfuori>1) isprot=false;
        else b1++;
	
        //TRACKER
	for (int j=0;j<NTrackHits;j++)
        	if((*clusterTrack)[j]>EdepTrackbeta->Eval(Beta_corr)+n_sigmaTrack*pow(EdepTrackbeta->Eval(Beta_corr),2)*etrack->Eval(Beta_corr)||(*clusterTrack)[j]<EdepTrackbeta->Eval(Beta_corr)-n_sigmaTrack*pow(EdepTrackbeta->Eval(Beta_corr),2)*etrack->Eval(Beta_corr)) clusterTrackfuori++;
	if (clusterTrackfuori>2) isprot=false;
	else d1++;
	
	//TRD
	for(int j=0;j<NTRDclusters;j++)	
		if((*TRDclusters)[j]>EdepTRDbeta->Eval(Beta_corr)+n_sigmaTRD*pow(EdepTRDbeta->Eval(Beta_corr),2)*etrd->Eval(Beta_corr)||(*TRDclusters)[j]<EdepTRDbeta->Eval(Beta_corr)-n_sigmaTRD*pow(EdepTRDbeta->Eval(Beta_corr),2)*etrd->Eval(Beta_corr))  clusterTRDfuori++;

	if(clusterTRDfuori>8) isprot=false;
	else e1++;		
	/////////////// SEL. VECCHIE //////////////////////////
	/*if(EdepTOF>EdepTOFbeta->Eval(Beta)+n_sigmaTOF*pow(EdepTOFbeta->Eval(Beta),2)*etof->Eval(Beta)||EndepTOF<EdepTOFbeta->Eval(Beta)-n_sigmaTOF*pow(EdepTOFbeta->Eval(Beta),2)*etof->Eval(Beta)) isprot=false;
	if(endepostatrack/NTrackHits>EdepTrackbeta->Eval(Beta)+n_sigmaTrack*pow(EdepTrackbeta->Eval(Beta),2)*etrack->Eval(Beta)||endepostatrack/NTrackHits<EdepTrackbeta->Eval(Beta)-n_sigmaTrack*pow(EdepTrackbeta->Eval(Beta),2)*etrack->Eval(Beta)) isprot=false;
	if(EdepTRD/NTRDclusters>EdepTRDbeta->Eval(Beta)+n_sigmaTRD*pow(EdepTRDbeta->Eval(Beta),2)*etrd->Eval(Beta)||EdepTRD/NTRDclusters<EdepTRDbeta->Eval(Beta)-n_sigmaTRD*pow(EdepTRDbeta->Eval(Beta),2)*etrd->Eval(Beta)) isprot=false;
	
	if(EdepTOF>EdepTOFbeta->Eval(deutons->Eval(R))+n_sigmaTOF*pow(EdepTOFbeta->Eval(deutons->Eval(R)),2)*etof->Eval(Beta)||EndepTOF<EdepTOFbeta->Eval(deutons->Eval(R))-n_sigmaTOF*pow(EdepTOFbeta->Eval(deutons->Eval(R)),2)*etof->Eval(Beta)) isprot=false;
	if(endepostatrack/NTrackHits>EdepTrackbeta->Eval(deutons->Eval(R))+n_sigmaTrack*pow(EdepTrackbeta->Eval(deutons->Eval(R)),2)*etrack->Eval(Beta)||endepostatrack/NTrackHits<EdepTrackbeta->Eval(deutons->Eval(R))-n_sigmaTrack*pow(EdepTrackbeta->Eval(deutons->Eval(R)),2)*etrack->Eval(Beta)) isprot=false;
	if(EdepTRD/NTRDclusters>EdepTRDbeta->Eval(deutons->Eval(R))+n_sigmaTRD*pow(EdepTRDbeta->Eval(deutons->Eval(R)),2)*etrd->Eval(Beta)||EdepTRD/NTRDclusters<EdepTRDbeta->Eval(deutons->Eval(R))-n_sigmaTRD*pow(EdepTRDbeta->Eval(deutons->Eval(R)),2)*etrd->Eval(Beta)) isprot=false;*/
	/////////////////////////////////////////////////////////
	//=true: Disattiva selezione/////
	isprot=true;
	////////////////////////////////
        return isprot;
}


int deutonsID (TTree *albero,int i) {
	int P_ID=0;
	int k = albero->GetEvent(i);
	bool isprot=true;
	
	////////// MASS WINDOW BASED SELECTION //////////////////	
	/*Massa=pow(fabs(pow(fabs(R_corr)*pow((1-pow(Beta_corr,2)),0.5)/Beta_corr,2)),0.5);
        if((Beta_corr>protons->Eval(R_corr-3*pow(R_corr,2)*Rig->Eval(R))-3*pow(Beta_corr,2)*beta->Eval(Beta_corr)||Beta_corr<deutons->Eval(R_corr-2*pow(R_corr,2)*Rig->Eval(R))-2*pow(Beta_corr,2)*beta->Eval(Beta_corr))&&BetaRICH<0) isprot=false;
	if(Beta_corr>0.825&&BetaRICH<0) isprot=false;
        if (Beta_corr<0.4&&1/Massa>0.5) isprot= false;
        if((Beta_corr>=0.4&&Beta_corr<0.5)&&1/Massa>0.5) isprot= false;
        if((Beta_corr>=0.5&&Beta_corr<0.55)&&1/Massa>0.52) isprot= false;
	if((Beta_corr>=0.55&&Beta_corr<0.6)&&1/Massa>0.543) isprot= false;
	if((Beta_corr>=0.6&&Beta_corr<0.65)&&1/Massa>0.543) isprot= false;	
	if((Beta_corr>=0.65&&Beta_corr<0.7)&&1/Massa>0.543) isprot= false;	
	if((Beta_corr>=0.7&&Beta_corr<0.8)&&1/Massa>0.543) isprot= false;	
	if((Beta_corr>=0.8&&Beta_corr<0.85)&&1/Massa>0.48) isprot= false;
	if(BetaRICH>f1RICH->Eval(R_corr)) isprot=false;
	if(Massa>=2.5||Massa<1.67) isprot=false;*/
	/////////////////////////////////////////////////////////
	
	///////// MATTER SELECTION ////////////////////////////////
	/*if (Beta_corr<1) {
		if(BetaRICH<0){
		if(Beta_corr>protons->Eval(R_corr-3*pow(R_corr,2)*Rig->Eval(R_corr))-3*pow(Beta_corr,2)*beta->Eval(Beta_corr)||Beta_corr<deutons->Eval(R_corr-2*pow(R_corr,2)*Rig->Eval(R_corr))-2*pow(Beta_corr,2)*beta->Eval(Beta_corr))
			isprot=false;
		}	
		else {
		if(BetaRICH>f1RICH->Eval(R_corr)) isprot=false;
		if(Massa>=2.5||Massa<1.67) isprot=false;
		}
	}*/	
	///////////////////////////////////////////////////////////
	
	////////////////////////NUOVA SEL /////////////////////////
	/*if (DistTOF>1.8||DistTrack>3||DistTRD>2) isprot=false;	
	if(Beta_corr<0.825){	
		if(Beta_corr<=0.5) if(PhiTrack<3.52||PhiTrack>4.56||PhiTOF<1.58||PhiTOF>3.12||PhiTRD<2.07||PhiTRD>3.98) isprot=false;
		
		if(Beta_corr<=0.6&&Beta_corr>0.5) if(PhiTrack<1.58||PhiTrack>4||PhiTOF<1.5||PhiTOF>4||PhiTRD<1.88||PhiTRD>4.13) isprot=false;

		if(Beta_corr<=0.7&&Beta_corr>0.6) if(PhiTrack<2.6||PhiTrack>4.76||PhiTOF<2.45||PhiTOF>4.41||PhiTRD<2.25||PhiTRD>4.7) isprot=false;
|
		if(Beta_corr<=0.75&&Beta_corr>0.7) if(PhiTrack<1.3||PhiTrack>5||PhiTOF<1.45||PhiTOF>5.03||PhiTRD<1.17||PhiTRD>5) isprot=false;

		if(Beta_corr<=0.815&&Beta_corr>0.75) if(PhiTrack<1.7||PhiTrack>4.9||PhiTOF<1.8||PhiTOF>4.27||PhiTRD<1.77||PhiTRD>4.76)  isprot=false;

		if(Beta_corr>0.815) if(PhiTrack<3.12||PhiTrack>4.8||PhiTOF<2||PhiTOF>4.8||PhiTRD<2.35||PhiTRD>4.67) isprot=false;
		}
	else{
		if(BetaRICH<0||BetaRICH>f1RICH->Eval(R)) isprot=false;
		if(Massa>=2.5||Massa<1.67) isprot=false;
	    }*/
	//////////////////////////////////////////////////////////	
	
	/////////////////////////// NUOVA SEL PROIEZ: ////////////////
	/*float X;
	float Y;
	float Dist;	
	if (DistTOF>1.8||DistTrack>3||DistTRD>2) isprot=false;	
	if(Beta_corr<0.825){
		X=DistTOF*cos(PhiProjTOF);
		Y=DistTOF*sin(PhiProjTOF);
		Dist=pow((pow((X-5),2)+pow(Y,2)),0.5);
		if((8-Dist)>Taglio_TOF->Eval(RminTOF)) isprot=false;
		
		X=DistTrack*cos(PhiProjTrack);
		Y=DistTrack*sin(PhiProjTrack);
		Dist=pow((pow((X-5),2)+pow(Y,2)),0.5);
		if((8-Dist)>Taglio_Track->Eval(RminTrack)) isprot=false;
		
		X=DistTRD*cos(PhiProjTRD);
		Y=DistTRD*sin(PhiProjTRD);
		Dist=pow((pow((X-5),2)+pow(Y,2)),0.5);
		if((8-Dist)>Taglio_TRD->Eval(RminTRD)) isprot=false;
			
	}
	else{
		if(BetaRICH<0||BetaRICH>f1RICH->Eval(R)) isprot=false;
		if(Massa>=2.5||Massa<1.67) isprot=false;
	    }*/
	//////////////////////////////////////////////////////////////
	/////////////////////////// NUOVA SEL PROIEZ: (2)/////////////
	/*float XTRD=DistTRD*cos(PhiProjTRD);
	float YTRD=DistTRD*sin(PhiProjTRD);
	float D_TRD=pow((pow((XTRD-5),2)+pow(YTRD,2)),0.5);
	float XTOF=DistTOF*cos(PhiProjTOF);
	float YTOF=DistTOF*sin(PhiProjTOF);
	float D_TOF=pow((pow((XTOF-5),2)+pow(YTOF,2)),0.5);
	float XTrack=DistTrack*cos(PhiProjTrack);
	float YTrack=DistTrack*sin(PhiProjTrack);
	float D_Track=pow((pow((XTrack-5),2)+pow(YTrack,2)),0.5);
	float Dist_SEL=pow(pow(D_TOF,2)+pow(D_TRD,2)+pow(D_Track,2),0.5);
	if(DistTOF>3||DistTrack>3||DistTRD>3) isprot=false;
	if(Beta_corr<0.825){	
		if(Beta_corr<=0.5) if(Dist_SEL<10.57) isprot=false;
		
		if(Beta_corr<=0.6&&Beta_corr>0.5) if(Dist_SEL<9.57) isprot=false;

		if(Beta_corr<=0.7&&Beta_corr>0.6) if(Dist_SEL<9.13) isprot=false;

		if(Beta_corr<=0.75&&Beta_corr>0.7) if(Dist_SEL<7.95) isprot=false;

		if(Beta_corr<=0.815&&Beta_corr>0.75) if(Dist_SEL<9.57)  isprot=false;

		if(Beta_corr>0.815) if(Dist_SEL<9.05) isprot=false;
		}
	else{
		if(BetaRICH<0||BetaRICH>f1RICH->Eval(R)) isprot=false;
		if(Massa>=2.5||Massa<1.67) isprot=false;
	    }
	*/
        //////////////////////////////////////////////////////////////
	////////////////////////// NUOVA SEL LIKELIHOOD/////////////
	
	long double logLklhd=log(1-trueD/(fakeD+trueD)); 	
	if(DistTOF>3||DistTrack>3||DistTRD>3) isprot=false;
	if(!(PhiProjTOF>=0&&PhiProjTOF<=6.3)) isprot=false;
	if(!(PhiProjTrack>=0&&PhiProjTrack<=6.3)) isprot=false;
	if(!(PhiProjTRD>=0&&PhiProjTRD<=6.3)) isprot=false;
	if(Beta_corr<=0.825){
		if(RminTOF>=0.5&&RminTOF<1.2) if(logLklhd>-21.73) isprot=false;
		if(RminTOF>=1.2&&RminTOF<1.7) if(logLklhd>-21.05) isprot=false;
		if(RminTOF>=1.7&&RminTOF<2.2) if(logLklhd>-22.80) isprot=false;
		if(RminTOF>=2.2&&RminTOF<2.7) if(logLklhd>-23.96) isprot=false;
		if(RminTOF>=2.7&&RminTOF<3.0) if(logLklhd>-21.24) isprot=false;
		if(RminTOF>=3.0&&RminTOF<3.5) if(logLklhd>-19.00) isprot=false;
	}	
	else{
                if(BetaRICH<0||BetaRICH>f1RICH->Eval(R)) isprot=false;
                if(Massa>=2.5||Massa<1.67) isprot=false;
            }
	
	/////////////////////////////////////////////////////////////
	/////////////// =true : ANNULLARE SELEZIONE //////////////////	
	//isprot=true;
	/////////////////////////////////////////////////////	
	if(isprot) P_ID=2;
	return P_ID;


}


int protonsID (TTree *albero,int i) {
        int P_ID=0;
        int k = albero->GetEvent(i);
        bool isprot=true;
	///////////// PROBABILITY BASED SELECTION ////////////	
	/*rig=(int)(R_corr*10);
        bet=(int)(Beta_corr*100);	
	 if(rig>=0&&rig<100&&bet>0&&bet<100) {
                probP=matricervsbeta[bet][rig];
                probD=matricervsbetad[bet][rig];
		if(probP<1e-6) isprot=false;		
		}*/
	/////////////////////////////////////////////////////
	
	///////// MATTER SELECTION ////////////////////////////////
	/*if (Beta_corr<1) if(Beta_corr<protons->Eval(R_corr-2*pow(R_corr,2)*Rig->Eval(R_corr))-2*pow(Beta_corr,2)*beta->Eval(Beta_corr)||Beta_corr>protons->Eval(R_corr+2*pow(R_corr,2)*Rig->Eval(R_corr))+2*pow(Beta_corr,2)*beta->Eval(Beta_corr))
	isprot=false;*/
	///////////////////////////////////////////////////////////
	
	////////////////////////NUOVA SEL /////////////////////////
	if(DistTOF>3) isprot=false;
	if(DistTrack>3) isprot=false;
	if(DistTRD>3) isprot=false;
	//////////////////////////////////////////////////////////
	
	///////////////  =true : ANNULLARE SELEZIONE //////////////////	
	//isprot=true;
	/////////////////////////////////////////////////////	
	if(isprot) P_ID=1;
        return P_ID;

}
