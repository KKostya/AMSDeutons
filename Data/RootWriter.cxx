// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

#include "RootWriter.hpp"
#include "Provenance.h"
#include "Geo.h"
#include "Tracker.h"
#include "TOF.h"
#include "TRD.h"


/////////////////////// Lol I'm crazzy!!! ////////////////////
// ROOTWrapper is a metafunction that takes a return type T
// and a function pointer F. It creates another function "wrapped"
// that returns void and a variable of type T that gets the return 
// value of F. 
template <typename T, T (*F)(AMSEventR *)> 
struct ROOTWrapper
{
    static T var;
    static void wrapped(AMSEventR * ev){ var = F(ev); }
};
template <typename T, T (*F)(AMSEventR *)> 
T ROOTWrapper<T,F>::var; // <-- here is your memory for ROOT
//
// 
//
template <typename T, T (*F)(AMSEventR *)> 
void (*Wrap(const std::string & name,TTree * tree)) (AMSEventR *){
    tree->Branch(name.c_str(), &ROOTWrapper<T, F>::var);
    return ROOTWrapper<T, F>::wrapped;
}
///////////////////// end of craziness here //////////////////

void AddProvenanceVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<unsigned int, Run  >("Run",   tree));
    data.push_back(Wrap<unsigned int, Event>("Event", tree));
    data.push_back(Wrap<unsigned int, UTime>("UTime", tree));
}

void AddGeoVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<double, ThetaS  >("ThetaS"  , tree));
    data.push_back(Wrap<double, PhiS    >("PhiS"    , tree));
    data.push_back(Wrap<double, U_time  >("U_time"  , tree));
    data.push_back(Wrap<double, Livetime>("Livetime", tree));
    data.push_back(Wrap<double, Latitude>("Latitude", tree));
    data.push_back(Wrap<double, Rcutoff >("Rcutoff" , tree));
    data.push_back(Wrap<int   , Unbias  >("Unbias"  , tree));

    data.push_back(Wrap<unsigned long long, fStatus>("fStatus", tree));
}

void AddTrackerVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<int                , NTrackHits  >("NTrackHits"  , tree));
    data.push_back(Wrap<double             , Rup         >("Rup"         , tree));
    data.push_back(Wrap<double             , Rdown       >("Rdown"       , tree));
    data.push_back(Wrap<double             , R           >("R"           , tree));
    data.push_back(Wrap<double             , Chisquare   >("Chisquare"   , tree));
    data.push_back(Wrap<std::vector<double>, R_          >("R_"          , tree));
    data.push_back(Wrap<std::vector<double>, chiq        >("chiq"        , tree));
    data.push_back(Wrap<std::vector<double>, ResiduiX    >("ResiduiX"    , tree));
    data.push_back(Wrap<std::vector<double>, ResiduiY    >("ResiduiY"    , tree));
    data.push_back(Wrap<int                , unusedLayers>("unusedLayers", tree));
    data.push_back(Wrap<double             , EdepTrack   >("EdepTrack"   , tree));
}

void AddTRDVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<int    , NTRDclusters>("NTRDclusters", tree));
    data.push_back(Wrap<double , EdepTRD     >("EdepTRD"     , tree));
}

void AddTOFVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<int                , NTofClusters    >("NTofClusters"    , tree));    
    data.push_back(Wrap<int                , NTofClustersUsed>("NTofClustersUsed", tree));
    data.push_back(Wrap<std::vector<double>, EdepTOF         >("EdepTOF"         , tree));
    data.push_back(Wrap<double             , BetaTOF         >("BetaTOF"         , tree));
}




