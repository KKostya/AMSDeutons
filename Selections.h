#include <string>
#include <vector>
#include "Data.h"

typedef bool (*CutFunction)(Data & data);
class SubSelection
{
    int nSelected;
    std::string name;
    CutFunction eval;
public:
    SubSelection(CutFunction f, std::string n):nSelected(0),name(n),eval(f){} 
    int GetNSelected(){return nSelected;}
    std::string GetName(){return name;}
    bool Test(Data & data);
};

std::vector<SubSelection *> GetListOfSelections();
bool Quality(Data &data);


std::vector<SubSelection *> GetListOfBandCuts();
bool Belt(Data &data);



//   float CalcolaRmin(float Min,float Max, TSpline *E, float X, float Y, float Z, TF1 *RBETA)
//   {
//   
//       if((Max-Min)<0.01) return (Max-Min)/2;
//       float Max_m=Max;			
//       Max=(Max-Min)/2;
//       float bt_min=RBETA->Eval(Min);
//       float bt_max=RBETA->Eval(Max);				
//       float G_min=2*(Min-X)+2*(E->Eval(bt_min)-Y)*((E->Eval(bt_min+RBETA->Eval(Min+0.01))-E->Eval(bt_min))/0.01)+2*(bt_min-Z)*((RBETA->Eval(Min+0.01)-bt_min)/0.01);
//       float G_max=2*(Max-X)+2*(E->Eval(bt_max)-Y)*((E->Eval(bt_max+RBETA->Eval(Max+0.01))-E->Eval(bt_max))/0.01)+2*(bt_max-Z)*((RBETA->Eval(Max+0.01)-bt_max)/0.01);
//       if(G_min*G_max<0) return CalcolaRmin(Min,Max,E,X,Y,Z,RBETA);
//       else return CalcolaRmin(Max,Max_m,E,X,Y,Z,RBETA);
//   }

//void Nuovasel(float RG,float M, TF1 *RBETA)
//{
//    BT=0;
//    distR=0;
//    distB=0;
//    distETOF=0;
//    distETrack=0;
//    distETRD=0;
//    DistTOF=0;
//    DistTrack=0;
//    DistTRD=0;
//    DR1=0; DR2=0; DR3=0;
//
//    float RGDT = RG/2;
//    float CooTOF[]   = {0,0,0};
//    float CooTrack[] = {0,0,0};
//    float CooTRD[]   = {0,0,0};
//
//    //////////////////// CALCOLO DISTANZA /////////////////////////                        
//    Dist1=1000000;
//    Dist2=1000000;
//    Dist3=1000000;
//
    for(int z=0;z<1e6;z++)
    {
       float edepTheo =  EdepTOFbeta->Eval(BT);


       passo=0.01;
       BT = RBETA->Eval(RGDT);
       distR=(RGDT-RG)/(pow(RG,2)*Rig->Eval(RG)); 
       distB=(RBETA->Eval(RGDT)-Beta_corr)/(pow(Beta_corr,2)*beta->Eval(Beta_corr));
       distETOF=(edepTheo-EdepTOF)/(pow(edepTheo,2)*etof->Eval(BT));
       distETrack=(EdepTrackbeta->Eval(BT)-EdepTrack)/(pow(EdepTrackbeta->Eval(BT),2)*etrack->Eval(BT));     
       distETRD=(EdepTRDbeta->Eval(BT)-E_depTRD)/(pow(EdepTRDbeta->Eval(BT),2)*etrd->Eval(BT));

       DistTOF=pow(pow(distR,2)+pow(distB,2)+pow(distETOF,2),0.5);
       DistTrack=pow(pow(distR,2)+pow(distB,2)+pow(distETrack,2),0.5);
       DistTRD=pow(pow(distR,2)+pow(distB,2)+pow(distETRD,2),0.5);
       if(DistTOF<Dist1) { Dist1=DistTOF; CooTOF[0]=distETOF; CooTOF[1]=distB; CooTOF[2]=distR; RminTOF=RGDT;}       
       else DR1++;
       if(DistTrack<Dist2) { Dist2=DistTrack; CooTrack[0]=distETrack; CooTrack[1]=distB; CooTrack[2]=distR; RminTrack=RGDT;}   
       else DR2++;
       if(DistTRD<Dist3) {  Dist3=DistTRD; CooTRD[0]=distETRD; CooTRD[1]=distB; CooTRD[2]=distR; RminTRD=RGDT;}       
       else DR3++;
       if(DR1>10&&DR2>10&&DR3>10) break;       
       RGDT=RGDT+passo;

   }
   DistTRD = sqrt(DistTRD);
