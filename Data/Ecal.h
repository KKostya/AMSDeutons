#ifndef ECAL_H
#define ECAL_H


#include <amschain.h>



   double EnergyE  (AMSEventR * ev);

   /**
   * dedx in the ECAL for the event at stake
   * @param ev the event (duh)
   * @param nlayers the number of layers of the shower at MIP (the more, the better; function will return 0 below 3 anyway)
   * @return the global sum(dE)/sum(dX) for the layers at MIP.
   */
   float dedxECAL (AMSEventR * ev, int& nlayers);


   /**
   * Number of layers at MIP
   * @param ev the event (duh)
   * @return the number of layers at MIP (S3/S5<0.99 mainly, plus basic cuts)
   */
   int nlayMip (AMSEventR * ev);

#endif //ECAL_H
