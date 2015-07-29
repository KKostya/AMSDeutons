#ifndef TRACKER_H
#define TRACKER_H
// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include "TrCharge.h"

#include <amschain.h>

int NTrackHits(AMSEventR * ev);

double Rup  (AMSEventR * ev);
double Rdown(AMSEventR * ev);
double R    (AMSEventR * ev);
double Rfull(AMSEventR * ev);

double ChiQup  (AMSEventR * ev);
double ChiQdown(AMSEventR * ev);
double ChiQ    (AMSEventR * ev);
double ChiQfull(AMSEventR * ev);

std::vector<double> EDepLayerX(AMSEventR * ev);
std::vector<double> EDepLayerY(AMSEventR * ev);
std::vector<double> EDepTrackX(AMSEventR * ev);
std::vector<double> EDepTrackY(AMSEventR * ev);

std::vector<double> ResidualX    (AMSEventR * ev);
std::vector<double> ResidualY    (AMSEventR * ev);
std::vector<double> ResidualUpX  (AMSEventR * ev);
std::vector<double> ResidualUpY  (AMSEventR * ev);
std::vector<double> ResidualDownX(AMSEventR * ev);
std::vector<double> ResidualDownY(AMSEventR * ev);
std::vector<double> ResidualFullX(AMSEventR * ev);
std::vector<double> ResidualFullY(AMSEventR * ev);

int unusedLayers(AMSEventR * ev);

int LayerBits    (AMSEventR * ev);
int LayerBitsUp  (AMSEventR * ev);
int LayerBitsDown(AMSEventR * ev);
int LayerBitsFull(AMSEventR * ev);


#endif //TRACKER_H
