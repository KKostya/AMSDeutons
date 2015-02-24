#include <string>
#include "SubSelection.hpp"

bool aRing(AMSEventR * );
bool oneRing(AMSEventR * );
bool noNaF(AMSEventR * );
bool photFracG04(AMSEventR * );
bool photFracL2(AMSEventR * );
bool atleastFiveHits(AMSEventR * );
bool betaDisp(AMSEventR * );
bool counts5(AMSEventR * );
 
std::vector<SubSelection<AMSEventR *> *> GetRICHSelectionsList();
bool RICHSelection(AMSEventR *data);
