#include "Provenance.h"

unsigned int Run  (AMSEventR * ev){ return ev->Run();   }
unsigned int Event(AMSEventR * ev){ return ev->Event(); }
time_t       UTime(AMSEventR * ev){ return ev->UTime(); }

