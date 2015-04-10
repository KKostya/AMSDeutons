#ifndef TRACKER_H
#define TRACKER_H
// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

int NTrackHits(AMSEventR * ev);

double Rup  (AMSEventR * ev);
double Rdown(AMSEventR * ev);
double R    (AMSEventR * ev);
double Rfull(AMSEventR * ev);
double Chisquare(AMSEventR * ev);

std::vector<double> R_(AMSEventR * ev);
std::vector<double> chiq(AMSEventR * ev);

std::vector<double> ResiduiX(AMSEventR * ev);
std::vector<double> ResiduiY(AMSEventR * ev);
int unusedLayers(AMSEventR * ev);

double EdepTrack(AMSEventR * ev);

#endif //TRACKER_H
