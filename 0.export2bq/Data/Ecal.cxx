#include "Ecal.h"

double EnergyE  (AMSEventR * ev){
    EcalShowerR* shower = ev -> pEcalShower(0);
    if( shower == NULL ){
        return 0;
    }
    return shower -> EnergyE;
}


double dedxECAL (AMSEventR * ev){

   // nlayMip returns the number of layers at MIP (and takes care of "bad" events in the process)

   int nlayers= nlayMip(ev);
   if (nlayers==0) return 0;

	// Computing dX
	// Geometrical distance between entry and exit point through Pythagoras * "fraction" of layers hit * fraction of fibers (only place where ionization can occur), 39.23%
  // That's the short, simple function. Has to be "recalibrated" to give the charge.
  // There exists a "far more complicated" dX computing (and a "even far more uselessly complicated" one), that I can implement if we want precision here.
  // Mainly, the most complicated one takes into account the events leaking outside the ECAL ; but abs(xe)>66.285/2 || abs(ye)>66.285/2 should take care of this.
   ParticleR* part=ev->pParticle(0);
   double xe = part->EcalCoo[0][0]; // in cm
   double ye = part->EcalCoo[0][1];
   double ze = part->EcalCoo[0][2];
   double xf = part->EcalCoo[2][0];
   double yf = part->EcalCoo[2][1];
   double zf = part->EcalCoo[2][2];
   if (abs(xe)>66.285/2 || abs(ye)>66.285/2) return 0;
   double dX=sqrt( (xf-xe)*(xf-xe) + (yf-ye)*(yf-ye) +(zf-ze)*(zf-ze) )*0.3923*nlayers/18;
   
   //Computing dE
   double dE = 0;
   for (int ihit=0 ; ihit<ev->nEcalHit(); ihit++)
      if (ev->EcalHit(ihit).Plane< nlayers)
         dE += ev->EcalHit(ihit).Edep;
		dE*=0.03; // The infamous sampling fraction;

   return dE/dX;
}


int nlayMip (AMSEventR * ev) {

   // Event sweeping
   // Adaptation of recommandations from the Twiki nuclei page
   // https://twiki.cern.ch/twiki/bin/view/AMS/Nuclei
   
   if (  ev==NULL
      || ev->nParticle()!=1
      || ev->IsInSAA()
      //|| ev->GetRTIStat()!=0
      )
      return 0;


   //AMSSetupR::RTI rti;
   //ev->GetRTI(rti);
   //if ((rti.good&0x3F)!=0 || rti.lf < 0.5 || rti.zenith >40)
      //return 0;

   AMSPoint pn1, pn9, pd1, pd9;
   ev->GetRTIdL1L9(0, pn1, pd1, ev->UTime(), 60);
   ev->GetRTIdL1L9(1, pn9, pd9, ev->UTime(), 60);
   if (pd1.y() > 35 || pd9.y() > 45)
      return 0;   

   // Variables init.
	
	int nhits=ev->nEcalHit();

	float hPlane[18][72]={{0}};
	float max;
	const float thres=1;
	int cellmax;
	bool isAdj=false; // Not 3 adjacent cells
	bool isAdjPrev=false ; // Were there two adjacent cells the row before?
	bool isEmpty=false; // Not too empty lines
	

	for (int ihit=0;ihit<nhits; ihit++)
		hPlane[ev->EcalHit(ihit).Plane][ev->EcalHit(ihit).Cell]=ev->EcalHit(ihit).ADC[0];

	hPlane[6][50]=0;


	for (char plane=0; plane<18; plane++) {
		max =	thres;
		cellmax = -1;
		isAdjPrev=isAdj;
		isAdj=false; 
		
		for (int cell=0;cell<72;cell++) {
			if (hPlane[int(plane)][cell]>max) {
				max=hPlane[int(plane)][cell];
				cellmax=cell;
			}
		}

		if (cellmax==-1 && plane !=6) {
			if (isEmpty) return plane;
			else {
				isEmpty=true;
				continue;
			}
		}
	
		float S3=hPlane[int(plane)][cellmax];

		if (cellmax>0) { // pas tout à gauche
			S3+=hPlane[int(plane)][cellmax-1];
			for (int cell=0;cell<cellmax-1;cell++ ) if (hPlane[plane][cell]>thres) return plane-(int)isAdjPrev;
			if (hPlane[int(plane)][cellmax-1]) isAdj=true;
		}

		if (cellmax<71) { // pas tout à droite
			S3+=hPlane[int(plane)][cellmax+1];
			for (int cell=cellmax+2;cell<72;cell++ )  if (hPlane[plane][cell]>thres) return plane-(int)isAdjPrev;
			if (hPlane[int(plane)][cellmax+1]) {
				if (isAdj) return plane -1;
				isAdj=true;
			}
		}

		float S5=S3;
		if (cellmax>1)  S5+=hPlane[int(plane)][cellmax-2];
		if (cellmax<70) S5+=hPlane[int(plane)][cellmax+2];
		if (S3/S5<0.99) return plane;
		
	} // Tous les plans ok

	return 18; // Si tous les critères sont remplis, on renvoie vrai
}




MIPQ MIPQLi (AMSEventR * ev) {

	MIPQ MQ;
	MQ.Clear();

	// Basic cuts
	if (ev==NULL) 						return MQ;
	if (ev->nParticle()  !=1) return MQ;
	if (ev->nEcalShower()!=1) return MQ; 
	if (ev->IsInSAA())        return MQ;
	if (ev->GetRTIStat()!=0) 	return MQ;

	// Tracker and shower raw selection
	ParticleR* part=ev->pParticle(0);
	TrTrackR* p_trk=part->pTrTrack();
	if (!p_trk) return MQ;
	EcalShowerR* p_show= part->pEcalShower();
	if (!p_show) return MQ;

	// Computing the object
	AmsEcalQ AEQ(p_trk, p_show);
	MQ=AEQ.GetMIPQ();
	return MQ;
	
}

