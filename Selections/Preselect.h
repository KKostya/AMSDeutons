#include <string>
#include "SubSelection.hpp"

std::vector<SubSelection<AMSEventR *> *> GetListOfPreselections();
bool Preselection(AMSEventR *data);
