#include "EQm.h"



//-- AMS ECAL Q Class.

class MIPQ{
  public:
	MIPQ(){};
	~MIPQ(){};
	void    Clear(){ NPnt = 0; RMS = 1000; Mean = 0;}
	int 	NPnt;	//-- No. of point used in MIP Q calculation.
	float   RMS;	//-- Combined Q rms.
	float   Mean;   //-- Q Mean value.
};


class AmsEcalQ{
  public:
	AmsEcalQ(){};
	//-- Mode- nlayer 0 Calibration(0 New, 1 Old). bit 1 Birk(0 Birk, 1 No Birk.)
    AmsEcalQ(TrTrackR* ptr, EcalShowerR* show, float beta=1, float ri=99999);	

    ~AmsEcalQ(){};
	float  Dir[3];
	float  Pnt[3];
	float  PL[2];
	int    ID[18];
	float  IP[18];
	float  Ri;
	float  Beta;
	float  Ric[18];
	float  S35R[18];
	float  S13R[18];
	float  Q2[18];
	float  SA[18];
	int    SelectMIP();//-- 0: MIP Q. 1: nlayer to Express which layer is used.
	int    GetEdMAP(EcalShowerR* show);
	int    GetMAP(float Ed[18][15], EcalShowerR* show);



	float  GetQL(int layer=0);
	//--   In[1]. layer: Ecal layer(0~17).
	//--   Out  . Ecal layer charge.
	MIPQ   GetMIPQ(const int kPar=kTruncM, const float Thres=1.5);
	//--   In[1]. Mean Q type. 1: Plain Mean Q. 2: Truncate Mean Q. 2*2: Gauss Mean Q. 
	//--   In[2]. RMS Threshold to Calculate Truncated and Gauss Mean. 
	static float GetQErr(const int ktype, const int nlayer, const int Z, float &QM);
	//--   Get Mean Q Error which can be a refference for doing cuts, return the Q sigma fitting in center range.
	//--   ktype : Mean Tyep. 
	//--   nlayer: MIP Layer No. 1<=nlayer<=18.
	//--   Z     : Ion Charge Z.
	//--   QM    : Q Mean Center Value.

	float GetPlainM(const vector<float> Qlayer, int nlayer, int &nhit, float &rms);
	float GetTruncM(const vector<float> Qlayer, int nlayer, int &nhit, float &rms, const float Thres=1.5, float trA=0.075, float trZ=0.075);
	float GetGaussM(const vector<float> Qlayer, int nlayer, int &nhit, float &rms, const float Thres=1.5, float sA =3.00,  float sZ =3.00);


	static int    kPlainM;
	static int    kTruncM;
	static int    kGaussM;
	
	
  private:
	//float  vQ[18];	//-- Virtual Q Used to do Correction. 
	int    vZ[18][2];
	float  vP[18][2];
	float  Ek[18];	//-- kinetic E Before Every Ecal Layer.

	float  CorrPMTA(int lay = 0);//
  void   CalvQ(int Mode=0);	//--0: With PMT pre-correction.
	void   CalEk();
	int	   CalIP(); 			//--Get PMT Incident Position At Cell.
	int    CalPL(); 			//--Calculate Path Length.
  bool   CorrPMT(int layer = 0);  //-- PMT Incident Position Correction. For All Layers.
  bool   CorrPL(int layer = 0);	//-- Path Lenght Correction.
	bool   CorrRi(int layer = 0);  //-- Use Corrected Ri to do Correction.
	bool   CorrBirk(int layer = 0);//-- 1: No Birk Correction. 0: Birk Correction. 


	//-- Parameterazation Function
	static float  dEdXPDF(float X, const float* p);
	static float  PmtPDF (float X, const float* p);
	static double BirkHPDF(double *x, double* p);
	static float  Linear (float X, const int layer, const float C);
	//static double  HesPDF(double *x, double* p);
	static float  HesPDF(float X, const float* p);


};
 


int   AmsEcalQ:: kPlainM  =1;
int   AmsEcalQ:: kTruncM  =2;
int   AmsEcalQ:: kGaussM  =2*2;

AmsEcalQ:: AmsEcalQ(TrTrackR* ptr, EcalShowerR* show, float beta, float ri){
  //-- Get Pos and Dir on Ecal Surface.

  const float Ecz = -143.;
  AMSPoint Amspnt; AMSDir Amsdir;
  ptr->Interpolate(Ecz, Amspnt, Amsdir);

  //-- Get Pos and Dir on Ecal Surface.
  for (int i=0; i<3; i++){
    Dir[i] = -1*Amsdir[i];
    Pnt[i] = Amspnt[i];
  }   
  //-- Get Rigidity.
  if (ri>=99998)    ri = ptr->GetRigidity();
  Ri   = fabs(ri);
  Beta = fabs(beta); 


  CalPL();
  CalIP();
  GetEdMAP(show);   //-- Get EdMAP[18][7]+Q2[18]+S35R[18].
  CalvQ();					//-- Get Virtue Q. vQ[18]+vZ[18][2]+vP[18][2].
  CalEk(); 					//-- Get Corrected Ri and Ek Before Every Ecal Layer. Ric[18]+Ek[18].

  //-- Use All the Infor Above to Do Q Calibration. PMT+PL+Ri+QCalibration.
  for (int ilayer=0; ilayer<18; ilayer++){
		if ( Q2[ilayer]<=0.1 )		continue;
		CorrPMT ( ilayer );  
		CorrBirk( ilayer ); 
		CorrPL  ( ilayer ); 	 
		//CorrRi(layer);	 
	}

};



int AmsEcalQ:: GetMAP(float Ed[18][15], EcalShowerR* show){
  if (!show)	return -1;


  //-- Get All Cell Ed Map.
  float ADCmap[18][72] = {{0}};
  for (int i2D=0; i2D<show->NEcal2DCluster(); i2D++){
    Ecal2DClusterR* p2DCl = show->pEcal2DCluster(i2D);      //-- 2D Cluster.
    for (int i1D=0; i1D<p2DCl->NEcalCluster(); i1D++){
			EcalClusterR* p1DCl = p2DCl->pEcalCluster(i1D);   //-- 1D Cluster.
			for (int ihit=0; ihit<p1DCl->NEcalHit(); ihit++){
				EcalHitR* phit = p1DCl->pEcalHit(ihit);     //-- EcalHit.
				int layer = phit->Plane;
				int cell  = phit->Cell;
				ADCmap[layer][cell] = phit->Edep;
			}
    }  
  }  
  
  for (int layer = 0; layer<18; layer++){
    int Hit = ID[layer];
    if (Hit<0||Hit>71)	continue;
    for (int i = 0; i<15; i++ ){
			int id = Hit - 7 + i;
			Ed[layer][i] = (id<0||id>71)?0:ADCmap[layer][id];
    }
  }//-- Now Got 15 Calibrated Ed along TRK Extropolated Track in Ecal. 
  return 0;
}


int AmsEcalQ:: GetEdMAP(EcalShowerR* show){
  float EdMAP[18][15] = {{0}};
  GetMAP(EdMAP, show);

  
  //-- Find TRK Extropolated Cell in each layer.
  for (int im=0; im<18; im++){
		SA[im] = 0;
		for (int i=0; i<15; i++)	SA[im] += EdMAP[im][i];
		
		Q2[im] = 0;
		S35R[im] = -1;
		S13R[im] = -1;
		float EdMax=0, S3=0, S5=0;
		int NMax = -1;
		
		for (int iHit=5; iHit<10; iHit++) // ????????????????????????????????
			if (EdMAP[im][iHit]>EdMax){
				EdMax = EdMAP[im][iHit];
				NMax  = iHit;
			}
		if (NMax<0)	continue;

		int dir   = (EdMAP[im][NMax-1]>EdMAP[im][NMax+1])?(-1):1;
		float S2  = EdMAP[im][NMax + dir] + EdMax;
		if (S2<0.1)	continue;
		S3 = EdMAP[im][NMax-1] + EdMax + EdMAP[im][NMax+1];
		S5 = EdMAP[im][NMax-2] + S3 + EdMAP[im][NMax+2];
		S13R[im] = EdMax/S3;
		S35R[im] = S3/S5;
		Q2[im] = S3;
  }  

  return  1;  
}







//-- 0: A1.
//-- 1: MPV1.
//-- 2: S1L.
//-- 3: S1R.
//-- 4: A2.
//-- 5: MPV1.
//-- 6: S2l.
//-- 7: S2r.
//
float AmsEcalQ:: dEdXPDF(float X, const float* p) 
{
  float A1, A2, MPV1, S1l, S1r, v1, MPV2, S2l, S2r, v2; 
  A1   = p[0];
  MPV1 = p[1];
  S1l  = p[2];
  S1r  = p[3];
  A2   = p[4];
  MPV2 = p[5];
  S2l  = p[6];
  S2r  = p[7];
  v1   = (X - MPV1)/(S1l*S1r);
  v2   = (X - MPV2)/(S2l*S2r);

  float Val = A1*exp(-1*S1r*(v1 + exp(-1*v1)))+A2*exp(-1*S2r*(v2 + exp(-1*v2)));
  return Val;
}


float AmsEcalQ:: PmtPDF(float X, const float* p){
  X = (X<-0.5)?(-0.5):X;
  X = (X>0.5)?0.5:X;
  float val = p[0] + p[1]*X + p[2]*X*X + p[3]*X*X*X + p[4]*X*X*X*X + p[5]*X*X*X*X*X + p[6]*X*X*X*X*X*X + p[7]*X*X*X*X*X*X*X + p[8]*X*X*X*X*X*X*X*X;
  val = val/p[0];
  return val;
}

float AmsEcalQ:: HesPDF(float X, const float* p){
  X = (X<-0.5)?(-0.5):X;
  X = (X>0.5)?0.5:X;
  float s = p[0] + p[1]*X + p[2]*X*X + p[3]*X*X*X + p[4]*X*X*X*X;
  s /= p[0];
  return 1./(s*s);
}

//--Birk C PDF
double AmsEcalQ:: BirkHPDF(double* x, double *p){
  double val = 0, X = x[0], A = p[0], B = p[1], C = p[2], A2 = p[3], A3=p[4], A1=p[5], C1=p[6];
  double zH = 10*10;
  val = (X<zH)*A*X/(1+B*atan(C/B*X)+A2*X*X+A3*X*X*X)+(X>=zH)*(A1*(X-zH)+C1);
  return val;  
}

//--Birk PDF.
float AmsEcalQ:: Linear(float X, const int layer, const float C){
    float A1=0.08, A2=0.10, A3=0.20, A4=0.00;
	float B1=0.10, B2=1.10, B3=2.20, B4=2.80;
	bool  U1=(X>=B1&&X<B2), U2=(X>=B2&&X<B3), U3=(X>=B3&&X<B4), U4=(X>=B4);
	float C1=C,             C2=C1-A1*(B2-B1), C3=C2-A2*(B3-B2), C4=C3-A3*(B4-B3);
	float val = U1*(C1-A1*(X-B1)) + U2*(C2-A2*(X-B2)) + U3*(C3-A3*(X-B3)) + U4*(C4-A4*(X-B4)) ; 
	val += 0.06/18.*layer; 
	return val;
}



//int AmsEcalQ:: SelectMIP(long& QIndex){
int AmsEcalQ:: SelectMIP(){
  //QIndex = 0;
  float kR = log10(Ri);
  if (kR>3.0)  kR = 3.0; 
  if (kR<0.2)  kR = 0.1; 

  float sum  = 0, var=0, rmsn0 = 1; 
  int   nQ  = 0; 
  //float C = 3.0 ;//+ 0.05*kR; 
  for (int k=0; k!=18; k++){
    if (Q2[k]<1e-1)    continue;

    float R = Q2[k]/CorrPMTA(k);
    sum += R;
    float m = sum/(nQ+1);
    var += R*R; 
    float rms   = sqrt(fabs(var/(nQ+1) - m*m));
    float rmsn  = rms/m;
    float rmsnr = (rmsn0>0)?(rmsn/rmsn0):1;

    if      (nQ<3&&(S35R[k]<Linear(kR, k, 0.90)||S13R[k]<Linear(kR, k, 0.60)))  break;
		else if (nQ>2&&(S35R[k]<Linear(kR, k, 0.85)||S13R[k]<Linear(kR, k, 0.55)))  break;
    

    //-- Here Use Norm RMS and its Deviation to Select MIP. 
    if ( nQ>=3 && rmsnr>sqrt((nQ+9)/(nQ+1)) ){
      k = k + 1;
      if (k==18)    					break;  //-- 18th L. 
      //else if (S35R[k]<Linear(kR, k, 0.85)||S13R[k]<Linear(kR, k, 0.55))    break;
      float R2 = Q2[k]/CorrPMTA(k);
      sum  = sum - R + R2;
      m    = sum/(nQ+1);
      var  = var - R*R + R2*R2;
      rms  = sqrt(fabs(var/(nQ+1) - m*m));
      rmsn = rms/m;
      rmsnr = (rmsn0>0)?(rmsn/rmsn0):1;
      if (rmsnr>sqrt((nQ+9)/(nQ+1)))    break;
      k=k-1;
    }
    rmsn0 = rmsn;

		//QIndex |= (1<<k);
    nQ++;
    //cout << "nlayer " << nQ << " " << pow(2, nQ) -1 << ", bit version " << QIndex << "    " <<std::nlayerset<32>(QIndex) << endl;
    //printf("L=%2d, kRi=%6.2f, SA=%8.4f, SAC=%8.4f, M=%8.4f, Nhit=%2d, Thres=%4.4f, RMSN=%8.4f, rmsR=%4.3f, S35R=%4.3f\n", SAIndeR.at
  }

  return nQ;
}


int  AmsEcalQ:: CalIP(){
  const float CellX = 0.9;
  float tanx, tany, ecz, ecx, ecy;

  if (Dir[2]>=0)	return -1;
  tanx = Dir[0]/Dir[2];
  tany = Dir[1]/Dir[2];

  for (int layer=0; layer<18; layer++){
	int sl = layer/2;
	ecz = EQ::LzEcal[layer];  //-- Cell Center Z Position.
	float  dz = (ecz - Pnt[2]);
	ecx = Pnt[0] + dz*tanx;           //--Trk Intepolated Position in Ecal.
	ecy = Pnt[1] + dz*tany;

	float sll = EQ::LxEcal[layer];
	float  it  = (sl%2==0)?(ecy+sll):(ecx+sll);
	int   cell = int(it/CellX);
	float ip   = (it/CellX-int(it/CellX)) - 0.5;
	IP[layer] = ip;
	ID[layer] = cell;
  }
  return 0;
}


int AmsEcalQ:: CalPL(){
  if (Dir[2]>=0)	return -1;
  float dx=fabs(Dir[0]), dy=fabs(Dir[1]), dz=fabs(Dir[2]);
  PL[0] = sqrt(1+pow(dx/dz,2));
  PL[1] = sqrt(1+pow(dy/dz,2));
  return 0;
}

void AmsEcalQ:: CalEk(){
  for (int im=0; im<18; im++){
	Ek[im]  =  0;
	Ric[im] =  0;
  }
  const float mass = 0.9315;
  Ek[0]  = sqrt(Ri*Ri + 4*mass*mass) - 2*mass;
  Ric[0] = Ri;
  for (int im=1; im<18; im++){
	float Edsum = 0, Q = (vZ[im-1][0]*vP[im-1][0] + vZ[im-1][1]*vP[im-1][1])/(vP[im-1][0] + vP[im-1][1]);
	//-- No Edep on this Layer.
	if (Q<1e-3){
	  Ric[im] = Ric[im-1];
	  Ek[im]  = Ek[im-1];
	  continue;
	}
	Edsum = SA[im]; 
	Edsum = Edsum/Q/1000;	//-- Ek for A Pair of Nucleons in GeV.
	Ek[im]  = Ek[im-1] - Edsum; 
	float r = Ric[im-1];
	float R_2 = r*r+Edsum*Edsum-2*Edsum*sqrt(r*r+4*mass*mass);
	Ric[im] = (R_2>0)?sqrt(R_2):0;
	//-- DeBuG
	//printf("L%d, Ri=%f, vQ=%f, Ric=%f, Ek=%f, Ed=%f\n", im,Ri,Q,Ric[im],Ek[im],Q2[im]);
  }
}





float AmsEcalQ:: CorrPMTA(int layer){
  float X = IP[layer];
  if ((layer<0||layer>17||X<-0.5||X>0.5)){
	return 1;
  }

  float  Cor = PmtPDF(X, EQ::PmtPar[layer][0]);
  return Cor;
}


void AmsEcalQ:: CalvQ(int Mode){
  if (Mode!=0)	Mode=0;
  //-- Get Original Z^2.
  float Edep[18]={0};
  for (int im=0; im<18; im++){
	for (int in=0; in<2; in++)	vP[im][in] = vZ[im][in] = 0;
	//vQ[im]   = 0;
	Edep[im] = Q2[im];
	Edep[im] = Edep[im]/CorrPMTA(im);
  }

  //-- Begin Loop in Ecal Layers.
  for (int im=0; im<18; im++){
	float Ed = Edep[im];
	if (Ed<=1e-3)	  continue;

	//-- Get Prob MAP.
	float Prob[26]={0}, sum=0;
	for (int iz=1; iz<=26; iz++){
	  int id = iz -2;
	  if (iz<2)			id = 0;
	  if (iz>10)		id = 10 - 2;
	  float dE = Ed/(iz*iz);
	  Prob[iz-1] = dEdXPDF(dE, EQ::PDFPar[im/6][id]);
	  //--
	  //printf("dE=%f, ", dE[0]);
	  sum += Prob[iz-1]; 
	}

	//-- Find Max and 2nd Max Prob. and Q.
	float PMax[3]={0, 0, 0};
	int    ZMax[3]={-1, -1, -1};
	for (int id=0; id<26; id++){
	  int iz = id + 1;
	  if (Prob[id]>PMax[0]){
		ZMax[2] = ZMax[1];
		PMax[2] = PMax[1];
		ZMax[1] = ZMax[0];
		PMax[1] = PMax[0];
		ZMax[0] = iz;
		PMax[0] = Prob[id];
	  }
	  else if (Prob[id]>PMax[1]){
		ZMax[2] = ZMax[1];
		PMax[2] = PMax[1];
		ZMax[1] = iz;
		PMax[1] = Prob[id];
	  }
	  else if(Prob[id]>PMax[2]){
		ZMax[2] = iz;
		PMax[2] = Prob[id];
	  }
	}
	//-- Normalized to 1.
	float Norm = PMax[0] + PMax[1];
	for (int i=0; i<2; i++){
	  vZ[im][i] = ZMax[i];
	  vP[im][i] = PMax[i]/Norm;
	}
	//-- Calculate virtue Q.
	//vQ[im] = (PMax[0]*ZMax[0] + PMax[1]*ZMax[1])/(PMax[0] + PMax[1]); 
	//-- DeBuG
	//printf("L=%2d, vQ=%4.2f, Q1=%2d, P1=%3.3f, Q2=%2d, P2=%3.3f, Ed=%5.1f, Ed_PMTC=%5.1f\n",im, vQ[im], vZ[im][0], vP[im][0], vZ[im][1], vP[im][1], Q2[im], Edep[im]);
  }
}


bool AmsEcalQ:: CorrPMT(int layer){
  float X = IP[layer];
  if ((layer<0||layer>17)){
	cerr<<"-----------Ecal Q PMT Correction Error!--------";
	printf("IP=%f, L=%d\n", X, layer);
	return 0;
  }

  //--PMT Correction.
  float  Prob[2]={vP[layer][0], vP[layer][1]}, cor[2]={1,1};
  int Z[2]={vZ[layer][0], vZ[layer][1]};
  for (int i=0; i<2; i++){
	if(Z[i]>8) Z[i] = 8;
	if(Z[i]<2) Z[i] = 2;
	int id = Z[i] - 2;
	cor[i]  = PmtPDF(X, EQ::PmtPar[layer][id]); 
  }
  //-- DeBuG
  //printf("Z1=%d, Z2=%d, Q1=%d, Q2=%d, P1=%f, P2=%f\n",Z[0],Z[1],vZ[layer][0],vZ[layer][1],Prob[0],Prob[1]);
  float Cor = (cor[0]*Prob[0]+cor[1]*Prob[1])/(Prob[0]+Prob[1]);	
  //float Cor  = PmtPDF(X, EQ::Pmt2Par[layer][id]); 

  Q2[layer] /= Cor;
  return 1;
}


bool AmsEcalQ:: CorrPL(int layer){
  float X = PL[(layer/2)%2];
  if (X<1){	 cerr<<"--Ecal Q PL Correction Error!--"<<endl;	return 0;}
  //-- 
  float B = EQ::PLPar[1][layer];
  float Cor = B*(X-1)+1;
  Q2[layer] /= Cor;
  return 1;
}


bool AmsEcalQ:: CorrRi(int layer){
  float Edep = Q2[layer];
  float R = (Ri>6)?Ri:Beta;

  float Prob[2]={vP[layer][0], vP[layer][1]}, cor[2]={1,1};
  int Z[2] = {vZ[layer][0], vZ[layer][1]};
  int id = -1;
  for (int i=0; i<2; i++){
    if (Z[i]>8)     Z[i] = 8;
    if (Z[i]<2)     Z[i] = 2;
    id = Z[i] - 2;
		if (Ri>6){
			cout<<"Ri used"<<endl;
			const float* p=EQ::RiPar[layer][id];
			float A1=p[4], A2=p[5], A3=p[6], A4=p[7];
			float B0=p[0], B1=p[1], b=p[2], R0=p[3];
			if (R<p[9])  R=p[9];
			if (R>1200)  R=1200;

			float lR = log(R), lR0 = log(R0);
			float CA = (A1*lR0/R0/R0 + A2*lR0/R0 + A3*lR0 + A4*lR0*R0);
			float CB = B0 + B1*pow(lR0, b); 
			
			cor[i]  = (A1*lR/R/R + A2*lR/R + A3*lR + A4*lR*R - CA + CB)*(R<R0)+ (R>=R0)*(B0 + B1*pow(lR, b));  //-- 
		}
		else {
			cout<<"Beta used"<<endl;
			const float* p=EQ::BetaPar[layer][id];
			if (R<0.5)	R = 0.5;
			if (R>1.0)	R = 1.0;
			cor[i]=p[0] + p[1]*R + p[2]*R*R + p[3]*R*R*R + p[4]*R*R*R*R + p[5]*R*R*R*R*R; 
		}
  }
  float Cor = (cor[0]*Prob[0]+cor[1]*Prob[1])/(Prob[0]+Prob[1]);
  //if (Ri<6)	printf("Q1=%d, Q2=%d, P1=%f, P2=%f, Ri=%f, Beta=%f, cor1=%f, cor2=%f, id2=%d, Cor=%f\n",Z[0],Z[1],Prob[0],Prob[1],Ri,Beta,cor[0],cor[1],id,Cor);

  Q2[layer] = Edep/Cor;
  return 1;
}




bool AmsEcalQ:: CorrBirk(int layer){
  float fQ2 = Q2[layer];

  //-- Birk Correction.
  const int ParN = 7;
  double Par[ParN] = {0};
  for (int i=0; i<ParN; i++)	Par[i] = EQ::BirkPar[i][layer];
  TF1* Birk = new TF1("BirkHPDF", BirkHPDF, 0, 30*30, ParN);
  Birk ->SetParameters(Par);
  float QBirk = Birk->GetX(fQ2); 
  delete Birk;
  //--DeBuG
  //printf("Edep=%f, Q2=%f, Q=%f\n", fQ2, QBirk, sqrt(QBirk));
  Q2[layer] = QBirk;
  return 1;
}



float AmsEcalQ:: GetQL(int layer){
  float fQ2 = Q2[layer];
  if (fQ2<=1e-3)	return 0;
  return sqrt(fQ2)/EQ::HePar[layer]*2.008;
  //return sqrt(fQ2);
}



/*float AmsEcalQ:: GetQw(int layer){
  float fX = IP[layer];
  float w = HesPDF(fX, EQ::HesPar[layer]);
  //printf("-- X=%4.3f,  W=%3.2f\n", fX[0], w);
  return w;
}*/



//-- Get EcalQ.
MIPQ AmsEcalQ:: GetMIPQ(const int kPar, const float Thres){
  MIPQ A;
  A.Clear();

  //printf("kPar=%4d, Threshold=%4.2f, tA=%4.2f, tZ=%4.2f.\n", kPar, Thres, tA, tZ);
  vector<float>	QL;
  int nlayer = SelectMIP();
  
  if (nlayer==0)	return A;
  for (int im=0; im<nlayer; im++)	QL.push_back(GetQL(im));

  float rms  = 0, mean = 0;
  int   nhit = 0;
  if 	  ( (kPar&kPlainM)&&!(kPar&kTruncM)&&!(kPar&kGaussM))			mean = GetPlainM(QL, nlayer, nhit, rms);
  else if (!(kPar&kPlainM)&& (kPar&kTruncM)&&!(kPar&kGaussM))		mean = GetTruncM(QL, nlayer, nhit, rms, Thres);
  else if (!(kPar&kPlainM)&&!(kPar&kTruncM)&& (kPar&kGaussM))		mean = GetGaussM(QL, nlayer, nhit, rms, Thres);
  else    cerr<<"AmsEcalQ Mean Q Type Error!"<<endl; 

  A.Mean = mean; 	A.RMS = rms;	A.NPnt = nhit;

  return A;
}





float AmsEcalQ:: GetQErr(const int ktype, const int nlayer, const int Z, float& QM){
  if (Z<2||Z>10)	{
	cerr<<"Z Parameter Error! Out of AmsEcalQ Range! 1=<Z<=10."<<endl;
	return 0;
  }
  if (nlayer<1||nlayer>18)	{
	cerr<<"MIP Layer Number Error! 1=<nlayer<=18."<<endl;
	return 0;
  }

  float Qerr = 0; 
  int id = (Z-2>6)?7:(Z-2), im = nlayer - 1;
  if      ( (ktype==0))                                         {       Qerr = EQ::ZLPar[1][im][id]; QM = EQ::ZLPar[0][im][id];}
  else if ( (ktype&kPlainM)&&!(ktype&kTruncM)&&!(ktype&kGaussM)){		Qerr = EQ::ZMPar[1][im][id]; QM = EQ::ZMPar[0][im][id];}
  else if (!(ktype&kPlainM)&& (ktype&kTruncM)&&!(ktype&kGaussM)){	    Qerr = EQ::ZTPar[1][im][id]; QM = EQ::ZTPar[0][im][id];}
  else if (!(ktype&kPlainM)&&!(ktype&kTruncM)&& (ktype&kGaussM)){		Qerr = EQ::ZGPar[1][im][id]; QM = EQ::ZGPar[0][im][id];}
  else    cerr<<"AmsEcalQ Mean Q Type Error!"<<endl; 
  return Qerr;
}


float AmsEcalQ:: GetPlainM(const vector<float> Qlayer, int nlayer, int &nhit, float &rms){
  float mean = 0;	nhit = 0;	rms  = 0;
  //--
  nhit = Qlayer.size();
  if (nhit<1)	return mean;

  int npnt = 0;
  float sw = 0;
  for (int i=0; i<nlayer; i++){
		float w = HesPDF(IP[i], EQ::HesPar[i]); 
		float qi = Qlayer.at(npnt);
		mean += qi*w; 
		rms  += qi*qi*w;
		sw   += w;
		npnt++;
  }

  mean /= sw;
  rms  /= sw;
  rms   = sqrt(fabs(rms - mean*mean));

  return mean;
}


float AmsEcalQ:: GetTruncM(const vector<float> Qlayer, int nlayer, int &nhit, float &rms, const float Thres, float trA, float trZ){
  //printf("Truncte Mean Q are Used.\n");
  float mean = 0; 	nhit = 0; 	rms  = 0;
  //-- Plain Mean Q.
  nhit = Qlayer.size();
  if (nhit<1)		return mean;

  int I = 0;
  float sw = 0, w[nhit];
  for (int i=0; i<nlayer; i++){
		w[I] = HesPDF(IP[i], EQ::HesPar[i]);
		float qi = Qlayer.at(I);
		mean += qi*w[I]; 
		rms  += qi*qi*w[I];
		sw   += w[I];
		I++;
  }

  mean /= sw;
  rms  /= sw;
  rms   = sqrt(fabs(rms - mean*mean));
  if (rms<Thres||nhit<3)	return mean;

  //-- Truncate trA At Low and trZ At High.
  vector<float> Ql = Qlayer;
  std:: sort(Ql.begin(), Ql.end());
  if (trA<=0)	trA =  1e-3;
  if (trZ<=0)	trZ =  1e-3;
  if (trA+trZ>=1)		{cerr<<"Truncated Mean Parameters Error!"<<endl;	return mean; }

  //-- 
  int 	  nh    = Ql.size();
  float   ndA   = trA*nh, ndZ = trZ*nh;		    //-- To Be Truncated Parts.
  int     idA   = ceil(ndA), idZ = ceil(ndZ);   //-- Involved Truncated Parts(integer).
  float   resA  = idA - ndA, resZ = idZ - ndZ;  //-- Residual fraction parts. 
  float   resnh = nh*(1 - trA - trZ);		    //-- All Residual. 
  float   m = 0, r = 0;
  sw = 0;
  for (int i=idA; i<nh-idZ; i++){
	float qi = Ql.at(i); 
	m += qi*w[i]; 	
	r += qi*qi*w[i];
	sw += w[i];
  }
  float qA = Ql.at(idA-1),  qZ = Ql.at(nh-idZ);
  float wA = resA*w[idA-1], wZ = resZ*w[nh-idZ];
  sw += (wA + wZ);
  m  += (wA*qA + wZ*qZ); 
  r  += (wA*qA*qA + wZ*qZ*qZ);

  nhit = resnh;
  mean = m/sw;
  rms  = r/sw;
  rms  = sqrt(fabs(rms - mean*mean));
  //printf("NH=%2d, Nhit=%4.2f, Mean=%4.2f, rms=%4.2f\n", nh, resnh, mean, rms);
  return mean;
}


float AmsEcalQ:: GetGaussM(const vector<float> Qlayer, int nlayer, int &nhit, float &rms, const float Thres, float sA, float sZ){
  float mean = 0; nhit = 0; rms  = 0;
  //-- Plain Mean Q.
  nhit = Qlayer.size();
  if (nhit<1)		return mean;

  int  k = 0;
  float sw = 0, w[nhit];
  for (int i=0; i<nlayer; i++){
		w[k] = HesPDF(IP[i], EQ::HesPar[i]);
		float qi = Qlayer.at(k);
		mean += qi*w[k]; 
		rms  += qi*qi*w[k];
		sw   += w[k];
		k++;
  }

  mean /= sw;
  rms  /= sw;
  rms   = sqrt(fabs(rms - mean*mean));
  if (rms<Thres||nhit<3)	return mean;

  //-- Gauss Mean and RMS.
  int   nh = 0;
  float m  = 0, r = 0;
  sw = 0;
  for (int i=0; i<nhit; i++){
	float qi = Qlayer.at(i); 
	if ((qi-mean)>sZ*rms||(mean-qi)>sA*rms)	continue;
	m += (qi*w[i]);
	r += (qi*qi*w[i]);
	nh++;
	sw += w[i];
  }
  if (nh<1)	return mean;
  nhit = nh;
  mean = m/sw;
  rms  = r/sw;
  rms   = sqrt(fabs(rms - mean*mean));
  return mean;
}
