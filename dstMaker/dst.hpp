#ifndef _DST__HPP_
#define _DST__HPP_

#include <string>
#include <vector>
#include <iostream>
#include <tuple>

#include "DstAmsBinary.hpp"
#include "rootUtils.hpp"
#include "gitversion.hpp"

#include "TofRecon.h"
#include "TrCharge.h"

#include "Geo.h"
#include "Preselect.h"
#include "Golden.h"
#include "MinBias.h"
#include "RICH.h"


#define MAXRAM 3000000000LL

std::vector<float> EdepTOF(AMSEventR * ev);
int NTRDclusters(AMSEventR * ev);
double EdepTRD(AMSEventR * ev);

class DistanceMinimizer;


class Dst : public DstAmsBinary{
public:
    Dst( std::vector<std::string> _data ) : DstAmsBinary( _data, MAXRAM){
        std::cout << "init with #" << data.size() << std::endl;
        smearing = 0;
        timingOffset = 0;
        for( auto &it: codeTrackId ) trackFitId[it.second] = 0;
    }
    
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
    std::map<int,int> trackFitId;
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

    typedef std::vector<std::pair<std::string, bool(*)(AMSEventR*)>> Selections;
    static Selections selections;

    typedef std::map<std::string, int> CodeTrackId;
    static CodeTrackId codeTrackId;

    template <int SIDE> std::vector<float> edepLayer();
    template <int SIDE> std::vector<float> edepTrack();

    template <typename T> void add(std::string name, std::function<T()> lambda){
        variables.push_back(new Container<T>(name, lambda));
    }

    template <typename T, int SIZE> void add(std::string name, std::function<T()> lambda){
        variables.push_back(new Container<T,SIZE>(name, lambda));
    }

    // template <typename T> void add(std::string name, std::function<T()> lambda);
    // template <typename T, int SIZE> void add(std::string name, std::function<T()> lambda);

    // std::vector<double> EdepTOF(AMSEventR * ev);

    std::vector<float> LayerJQ();

    virtual void initPointers();

    void saveMetaData(std::string filename){
        DstAmsBinary::saveMetaData(filename);
        std::ofstream myfile( filename, std::ios::out|std::ios::app);
        myfile << "gitversion: " << gitversion << "\n";
        myfile << "selStatus: ";
        for(auto const &it : selections) myfile << it.first << ",";
        myfile.close();
    }

};

#include "3DVariables.hpp"

#endif


