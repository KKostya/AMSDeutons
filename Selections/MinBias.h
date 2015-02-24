#include <string>
#include "SubSelection.hpp"

bool minimumbiasTOF     (AMSEventR * );
bool minimumbiasTRIGG   (AMSEventR * );
bool minimumbiasTRD     (AMSEventR * );
bool minimumbiasTRACKER (AMSEventR * );

std::vector<SubSelection<AMSEventR *> *> GetMinBiasList();
bool MinBias(AMSEventR *data);
