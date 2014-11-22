#include <string>
#include "SubSelection.hpp"

// N.B. If you've got linking errors -- check the ending
// of the Golden.cxx file and add an appropriate template 
// instantiation

template <int SIGMA, int FIT>
std::vector<SubSelection<AMSEventR *> *> GetGoldenList();

template <int SIGMA, int FIT>
bool Golden(AMSEventR *data);


