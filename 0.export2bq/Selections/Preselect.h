bool aParticle   (AMSEventR * ); 
bool aTrack      (AMSEventR * ); 
bool aTRDTrack   (AMSEventR * ); 
bool oneParticle (AMSEventR * ); 
bool oneTrack    (AMSEventR * );
bool oneTRDTrack    (AMSEventR * ); 
bool chargeOne   (AMSEventR * ); 
bool downGoing   (AMSEventR * ); 
bool betaNotCrazy(AMSEventR * );
bool physicsTrigger(AMSEventR *);
bool basicBetaH(AMSEventR *);
bool isolatedBetaH(AMSEventR *);

template <int N>
bool fitExists(AMSEventR * ); 
