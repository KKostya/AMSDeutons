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

   ParticleR* part=ev->pParticle(0);
   double xe = part->EcalCoo[0][0]; // in cm
   double ye = part->EcalCoo[0][1];
   double ze = part->EcalCoo[0][2];
   double xf = part->EcalCoo[2][0];
   double yf = part->EcalCoo[2][1];
   double zf = part->EcalCoo[2][2];
   if (abs(xe)>66.285/2 || abs(ye)>66.285/2) return 0;
   double dX=sqrt( (xf-xe)*(xf-xe) + (yf-ye)*(yf-ye) +(zf-ze)*(zf-ze) )*0.03*0.3923*1.1256*nlayers/18;
   // HAHAHA I know, rite :D 0.39 = mean lead density, 0.03 = fraction, 1.1256 =... not sure. (lulz)

   double dE = 0;
   for (int ihit=0 ; ihit<ev->nEcalHit(); ihit++)
      if (ev->EcalHit(ihit).Plane<int(nlayers))
         dE += ev->EcalHit(ihit).Edep;

   return dE/dX;
}

int nlayMip (AMSEventR * ev) {

   // Event sweeping
   // Adaptation of recommandations from the Twiki nuclei page
   // https://twiki.cern.ch/twiki/bin/view/AMS/Nuclei
   
   if (  ev==NULL
      || ev->nParticle()!=1
      || ev->IsInSAA()
      || ev->GetRTIStat()!=0
      )
      return 0;

   AMSSetupR::RTI rti;
   ev->GetRTI(rti);
   if ((rti.good&0x3F)!=0 || rti.lf < 0.5 || rti.zenith >40)
      return 0;

   AMSPoint pn1, pn9, pd1, pd9;
   ev->GetRTIdL1L9(0, pn1, pd1, ev->UTime(), 60);
   ev->GetRTIdL1L9(1, pn9, pd9, ev->UTime(), 60);
   if (pd1.y() > 35 || pd9.y() > 45)
      return 0;   


   // Variables init.
	
   int nhits=ev->nEcalHit();

   float hPlane[18][72]={{0}};   // Map of hit energies
   for (int ihit=0;ihit<nhits; ihit++)
      hPlane[ev->EcalHit(ihit).Plane][ev->EcalHit(ihit).Cell]=ev->EcalHit(ihit).ADC[0];
   hPlane[6][50]=0;              // Dead cell
   

   int cellmax;                 
   bool isAdj=false;             


   // Basic idea : one condition not filled -> the last layer at MIP was before
   // Index starts at 0; we return plane = number of layers at MIP (= plane + 1 -1)
		
   for (char plane=0; plane<18; plane++) { 

      float elmax =	3;    // max energy seen in the current layer; threshold at 3 ADC
      int cellmax = -1;    // corresponding cell
      bool isAdj=false;    // check we don't have 3 adjacent cells
      
      for (int cell=0;cell<72;cell++) {
	    if (hPlane[int(plane)][cell]>elmax) {
		     elmax=hPlane[int(plane)][cell];
		     cellmax=cell;
	    }
      }		
      if (cellmax==-1) 	return plane; // no hit > 3
      
      float S3=hPlane[int(plane)][cellmax];
      
      if (cellmax>0) { // not totally left
	    S3+=hPlane[int(plane)][cellmax-1];
	    if (hPlane[int(plane)][cellmax-1]) isAdj=true;
      }
      
      if (cellmax<71) { // not totally right
	    S3+=hPlane[int(plane)][cellmax+1];
	    if (hPlane[int(plane)][cellmax+1] && isAdj) return plane;
      }
      
      float S5=S3;
      if (cellmax>1)  S5+=hPlane[int(plane)][cellmax-2];
      if (cellmax<70) S5+=hPlane[int(plane)][cellmax+2];
      if (S3/S5<0.99) return plane;
		

   } // End of loop on layers

   return 18; // All layers have been seen as MIP
}
