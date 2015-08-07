#ifndef ECAL_H
#define ECAL_H


#include <amschain.h>



   double EnergyE  (AMSEventR * ev);

   /**
   * dedx in the ECAL for the event at stake
   * @param ev the event (duh)
   * @return the global sum(dE)/sum(dX) for the layers at MIP.
   */
   double dedxECAL (AMSEventR * ev);


   /**
   * Number of layers at MIP
   * @param ev the event (duh)
   * @return the number of layers at MIP (S3/S5<0.99 mainly, plus basic cuts)
   */
   int nlayMip (AMSEventR * ev);

#endif //ECAL_H
