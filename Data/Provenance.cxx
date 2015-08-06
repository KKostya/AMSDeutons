#include "Provenance.h"


unsigned int Run  (AMSEventR * ev){ return ev->Run();   }
unsigned int Event(AMSEventR * ev){ return ev->Event(); }
unsigned int UTime(AMSEventR * ev){ return ev->UTime(); }
double JMDCTime(AMSEventR * ev){
    double error=10;
    HeaderR* head = &(ev -> fHeader);
    return double(ev->UTime())+head->Time[1]/1000000.+head->TimeCorr(error,ev->UTime())-ev->gpsdiff(ev->UTime());
}


