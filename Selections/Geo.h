#include <string>
#include "SubSelection.hpp"

bool notFirstTwo(AMSEventR * ev);
bool notInSaaCut(AMSEventR * ev);
bool   zenithCut(AMSEventR * ev);
bool  runtypeCut(AMSEventR * ev);

std::vector<SubSelection<AMSEventR *> *> GetGeoSelectionsList();
bool GeoSelection(AMSEventR *data);
