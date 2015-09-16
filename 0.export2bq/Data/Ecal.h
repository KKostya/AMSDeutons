#ifndef ECAL_H
#define ECAL_H

#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include "TrCharge.h"

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


   /**
   * Q. Li's MIPQ Structure for nuclei charge estimator, with methods:
   * MIPQ::Mean : float, best value of the estimator
   * MIPQ::RMS  : float, associated RMS
   * MIPQ::NPnt : int, number of layers used in the computation
   * @param ev the event
   * @return the MIPQ object derived by his AmsEcalQ class 
   */

    float MIPQLi_Mean (AMSEventR * ev) {return MIPQLi(ev).Mean; }
    float MIPQLi_RMS  (AMSEventR * ev) {return MIPQLi(ev).RMS;  }
      int MIPQLi_NPnt (AMSEventR * ev) {return MIPQLi(ev).NPnt; }
       
#endif //ECAL_H
