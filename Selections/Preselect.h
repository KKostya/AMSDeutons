#include <string>
#include "SubSelection.hpp"

bool aParticle   (AMSEventR * ); 
bool aTrack      (AMSEventR * ); 
bool aTRDTrack   (AMSEventR * ); 
bool oneParticle (AMSEventR * ); 
bool oneTrack    (AMSEventR * ); 
bool chargeOne   (AMSEventR * ); 
bool downGoing   (AMSEventR * ); 
bool betaNotCrazy(AMSEventR * ); 

template <int N>
bool fitExists(AMSEventR * ); 

std::vector<SubSelection<AMSEventR *> *> GetListOfPreselections();
bool Preselection(AMSEventR *data);
