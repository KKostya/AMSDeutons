#ifndef ECAL_H
#define ECAL_H


//#include <amschain.h>
#include "root_RVSP.h"
#include "AmsEcalQ_mod.h"



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


   /**
   * Q. Li's MIPQ Structure for nuclei charge estimator, with methods:
   * MIPQ::Mean : float, best value of the estimator
   * MIPQ::RMS  : float, associated RMS
   * MIPQ::NPnt : int, number of layers used in the computation
   * @param ev the event
   * @return the MIPQ object derived by his AmsEcalQ class 
   */
    MIPQ MIPQLi (AMSEventR * ev);
   
#endif //ECAL_H
