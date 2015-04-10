#include "Ecal.h"

double EnergyE  (AMSEventR * ev){
    EcalShowerR* shower = ev -> pEcalShower(0);
    if( shower == NULL ){
        return 0;
    }
    return shower -> EnergyE;
}
