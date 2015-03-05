nt RichQC(RichRingR *prich){
  
  RichRingR &rich=*prich;


  int cutmask=0;
  float cut_prob=0.01;                        //  Kolmogorov test probability
  float cut_pmt=3;                            //  number of pmts
  float cut_collovertotal=0.4;                //  ring photoelctrons / total photoelectrons in the event 
  float cut_chargeconsistency=10;              //  hit/PMT charge consistency test
  float cut_betaconsistency[2]={0.01,0.005};  //  beta_lip vs beta_ciemat consistency ([0]=NaF, [1]=aerogel) 
  float cut_expphe[2]={1,2};                  //  expected number of photoelectrons   ([0]=NaF, [1]=aerogel)
  float cut_aerogelexternalborder=3500.;      //  aerogel external border (r**2)
  float cut_aerogel_nafborder[2]={17.,19.};   //  aerogel/NaF border                  ([0]=NaF, [1]=aerogel)

  int nbadtiles=5;                            
  int kbadtile[nbadtiles];
  kbadtile[0]=3;
  kbadtile[1]=7;
  kbadtile[2]=87;
  kbadtile[3]=100;
  kbadtile[4]=108;   //  tiles with bad beta recosntruction 

  if(!rich.IsGood() || !rich.IsClean()) cutmask= cutmask | (1<<0);

  if(rich.getProb()<cut_prob) cutmask= cutmask | (1<<1);          
            
  if(rich.getPMTs()<cut_pmt) cutmask= cutmask | (1<<2);

  if(rich.getPhotoElectrons()/RichHitR::getCollectedPhotoElectrons() < cut_collovertotal) cutmask | (1<<3);

  if(rich.getPMTChargeConsistency()>cut_chargeconsistency)  cutmask= cutmask | (1<<4);

  //  const float* TrackEmission=ring.getTrackEmissionPoint();
  float x=rich.getTrackEmissionPoint()[0];
  float y=rich.getTrackEmissionPoint()[1];

  if(rich.IsNaF()) {
    if(rich.getExpectedPhotoelectrons()<cut_expphe[0]) cutmask= cutmask | (1<<5);
    if(rich.getBetaConsistency()>cut_betaconsistency[0]) cutmask= cutmask | (1<<6);
    if(max(abs(x),abs(y)) > cut_aerogel_nafborder[0])cutmask= cutmask | (1<<7); 
  }
  else {
    if(rich.getExpectedPhotoelectrons()<cut_expphe[1]) cutmask= cutmask | (1<<5);
    if(rich.getBetaConsistency()>cut_betaconsistency[1]) cutmask= cutmask | (1<<6); 
    if(x*x+y*y            > cut_aerogelexternalborder) cutmask= cutmask | (1<<7);
    if(max(abs(x),abs(y)) < cut_aerogel_nafborder[1]) cutmask= cutmask | (1<<7);
    for(int kbad=0;kbad<nbadtiles;kbad++) {
      if(rich.getTileIndex()==kbadtile[kbad])  cutmask= cutmask | (1<<8);
    }
  }
 
  return cutmask;
}

