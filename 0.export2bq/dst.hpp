#ifndef _DST__HPP_
#define _DST__HPP_

#include <string>
#include <vector>
#include <iostream>
#include <tuple>

#include "DstAmsBinary.hpp"
#include "rootUtils.hpp"
#include "Stack.hpp"

#include "TofRecon.h"
#include "TrCharge.h"

#include "Geo.h"
#include "Preselect.h"
#include "Golden.h"
#include "MinBias.h"
#include "RICH.h"


#define MAXRAM 1e9

std::vector<float> EdepTOF(AMSEventR * ev);
int NTRDclusters(AMSEventR * ev);
double EdepTRD(AMSEventR * ev);

class DistanceMinimizer;


class Dst : public DstAmsBinary{
public:
    Dst( std::string _data ) : DstAmsBinary( _data, MAXRAM){
        std::cout << "init with #" << data.size() << std::endl;
        smearing = 0;
        timingOffset = 0;
    }
    
    void setSmearing(int _smearing){
        this -> smearing = _smearing;
    }

    void setTimingOffset(int _timingOffset){
        this -> timingOffset = _timingOffset;
    }

public:
    virtual void init();

    void registerVariables() override; 

    BetaHR* betaH;
    BetaR* beta;
    TofClusterHR *clusterHL[4];
    int trackFitId_111,trackFitId_121,trackFitId_131,trackFitId_151;
    MCEventgR* mc;
    Level1R *level;
    RichRingR *rich;
    TofTrack* tofTrack;

    int smearing;
    int timingOffset;
    DistanceMinimizer *distanceMinimizer;
    int nlay; float qrms;// stupidity for ChargeTof

    std::vector<TrClusterR*> trackRawClusters;
    std::map<TrRecHitR*,std::pair<TrClusterR*, TrClusterR*> > trackHitToClusterMap;

    std::vector<std::pair<std::string, std::function<bool(AMSEventR*)> > > selections;

    template <int SIDE> std::vector<float> edepLayer();
    template <int SIDE> std::vector<float> edepTrack();
    template <typename T> void add(std::string name, std::function<T()> lambda);
    template <typename T, int SIZE> void add(std::string name, std::function<T()> lambda);

    // std::vector<double> EdepTOF(AMSEventR * ev);

    std::vector<float> LayerJQ();

    virtual void initPointers();
private:
    void registerSelStatus();
};

#include "3DVariables.hpp"

#endif


