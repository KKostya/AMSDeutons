#include <string>
#include "SubSelection.hpp"

class AMSEventR;

std::vector<SubSelection<AMSEventR *> *> GetGeoSelectionsList();
bool GeoSelection(AMSEventR *data);

std::vector<SubSelection<AMSEventR *> *> GetPreSelectionsList();
bool PreSelection(AMSEventR *data);


