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

float RUp  (AMSEventR * ev);
float RDown(AMSEventR * ev);
float R    (AMSEventR * ev);
float RL1  (AMSEventR * ev);

float ChiQUp  (AMSEventR * ev);
float ChiQDown(AMSEventR * ev);
float ChiQ    (AMSEventR * ev);
float ChiQL1  (AMSEventR * ev);

std::vector<float> EDepLayerX(AMSEventR * ev);
std::vector<float> EDepLayerY(AMSEventR * ev);
std::vector<float> EDepTrackX(AMSEventR * ev);
std::vector<float> EDepTrackY(AMSEventR * ev);


float L1_Hit_X(AMSEventR * ev);
float L1_Hit_Y(AMSEventR * ev);
float L1_Hit_Z(AMSEventR * ev);
float L2_Hit_X(AMSEventR * ev);
float L2_Hit_Y(AMSEventR * ev);
float L2_Hit_Z(AMSEventR * ev);


std::vector<float> LayerJQ(AMSEventR * ev);
float Q_all(AMSEventR * ev);
float InnerQ_all(AMSEventR * ev);

std::vector<float> ResidualX    (AMSEventR * ev);
std::vector<float> ResidualY    (AMSEventR * ev);
std::vector<float> ResidualUpX  (AMSEventR * ev);
std::vector<float> ResidualUpY  (AMSEventR * ev);
std::vector<float> ResidualDownX(AMSEventR * ev);
std::vector<float> ResidualDownY(AMSEventR * ev);
std::vector<float> ResidualL1X  (AMSEventR * ev);
std::vector<float> ResidualL1Y  (AMSEventR * ev);

int unusedLayers(AMSEventR * ev);

int LayerBits    (AMSEventR * ev);
int LayerBitsUp  (AMSEventR * ev);
int LayerBitsDown(AMSEventR * ev);
int LayerBitsL1  (AMSEventR * ev);


#endif //TRACKER_H
