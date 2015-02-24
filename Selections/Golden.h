#include <string>
#include "SubSelection.hpp"


template<int SEVERITY, int FIT> bool goldenTOF(AMSEventR *);
template<int SEVERITY, int FIT> bool goldenTRD(AMSEventR *);
template<int SEVERITY, int FIT> bool goldenTRACKER(AMSEventR *);


// N.B. If you've got linking errors -- check the ending
// of the Golden.cxx file and add an appropriate template 
// instantiation

template <int SIGMA, int FIT>
std::vector<SubSelection<AMSEventR *> *> GetGoldenList();

template <int SIGMA, int FIT>
bool Golden(AMSEventR *data);


