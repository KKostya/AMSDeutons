bool   aRing (AMSEventR * );
bool oneRing (AMSEventR * );
bool   noNaF (AMSEventR * ev); 

///////////////////////////////////
// New selections
///////////////////////////////////

bool ringGood (AMSEventR * ev);
bool ringClean(AMSEventR * ev);
bool ringProb (AMSEventR * ev);
bool ringPMTs (AMSEventR * ev);

bool ringChargeConsistency (AMSEventR * ev);
bool ringPhotoElectrons    (AMSEventR * ev);
bool ringExpPhe            (AMSEventR * ev);
bool ringBetaCons          (AMSEventR * ev);
bool ringNoNaFBorder       (AMSEventR * ev);

///////////////////////////////////
// Old selections
///////////////////////////////////

bool ringHits   (AMSEventR * ev);
bool photFracG04(AMSEventR * ev);
bool photFracL2 (AMSEventR * ev) ;
bool betaDisp   (AMSEventR * ev) ;
bool counts5    (AMSEventR * ev) ;

