#ifndef TOF_H
#define TOF_H

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

#include "TofRecon.h"

int NTofClusters(AMSEventR * ev);    
int NTofClustersUsed(AMSEventR * ev);
std::vector<double> EdepTOF(AMSEventR * ev);
double BetaTOF(AMSEventR * ev);
double ChargeTOF(AMSEventR * ev);
int TrackTof(AMSEventR * ev);

std::vector<double> TOFCoordsX(AMSEventR * ev);
std::vector<double> TOFCoordsY(AMSEventR * ev);
std::vector<double> TOFCoordsZ(AMSEventR * ev);


#endif //TOF_H
