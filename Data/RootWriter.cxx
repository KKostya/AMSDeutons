#include "RootWriter.hpp"

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

/////////////////////////////////////////////////////////////
///////////////////// Variables for TTree selections /////////
/////////////////////////////////////////////////////////////
void AddProvenanceVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<unsigned int, Run  >("Run",   tree));
    data.push_back(Wrap<unsigned int, Event>("Event", tree));
    data.push_back(Wrap<unsigned int, UTime>("UTime", tree));
    data.push_back(Wrap<double      , JMDCTime>("JMDCTime", tree));
}

void AddGeoVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<double, ThetaS    >("ThetaS"  ,  tree));
    data.push_back(Wrap<double, PhiS      >("PhiS"    ,  tree));
    data.push_back(Wrap<double, Livetime  >("Livetime",  tree));
    data.push_back(Wrap<double, Latitude  >("Latitude",  tree));
    data.push_back(Wrap<double, Rcutoff   >("Rcutoff" ,  tree));
    data.push_back(Wrap<int   , PhysBPatt >("PhysBPatt", tree));
    data.push_back(Wrap<int   , JMembPatt >("JMembPatt", tree));
    data.push_back(Wrap<unsigned int, UTime>("UTime", tree));

    data.push_back(Wrap<unsigned long long, fStatus>("fStatus", tree));
}

void AddSelectionVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<unsigned long long , selStatus >("selStatus" , tree));
    //data.push_back(Wrap< mySelStatus , selStatus2 >("selStatus" , tree));
    //data.push_back(Wrap<TBits , selStatus2 >("selStatus2" , tree));

    data.push_back(Wrap<double             , BetaTOF                     >("BetaTOF"   , tree));
    data.push_back(Wrap<double             , BetaRICH                    >("betaRICH"  , tree));

    // Rich variables
    data.push_back(Wrap<double             , DistanceTileBorder          >("rich_distanceTileBorder", tree));
    data.push_back(Wrap<double             , RingWidth                   >("rich_ringWidth", tree));
    data.push_back(Wrap<float              , getBeta                     >("rich_getBeta", tree));
    data.push_back(Wrap<int                , PmtCorrectionsFailed        >("rich_pmtCorrectionsFailed", tree));
    data.push_back(Wrap<int                , getUsedHits                 >("rich_getUsedHits", tree));
    data.push_back(Wrap<float              , getPhotoElectrons           >("rich_getPhotoElectrons", tree));
    data.push_back(Wrap<float              , getExpectedPhotoElectrons   >("rich_getExpectedPhotoElectrons", tree));
    data.push_back(Wrap<float              , getCharge2Estimate          >("rich_getCharge2Estimate", tree));
    data.push_back(Wrap<float              , getBetaError                >("rich_getBetaError", tree));
    data.push_back(Wrap<float              , getProb                     >("rich_getProb", tree));
    data.push_back(Wrap<float              , getWidth                    >("rich_getWidth", tree));
    data.push_back(Wrap<float              , getRawIndexUsed             >("rich_getRawIndexUsed", tree));
    data.push_back(Wrap<float              , getIndexUsed                >("rich_getIndexUsed", tree));
    data.push_back(Wrap<std::vector<float> , getTrackEmissionPoint       >("rich_getTrackEmissionPoint", tree));
    data.push_back(Wrap<float              , getBetaConsistency          >("rich_getBetaConsistency", tree));
    data.push_back(Wrap<int                , getHits                     >("rich_getHits", tree));
    data.push_back(Wrap<int                , getPMTs                     >("rich_getPMTs", tree));
    data.push_back(Wrap<int                , getReflectedHits            >("rich_getReflectedHits", tree));
    data.push_back(Wrap<float              , getPMTChargeConsistency     >("rich_getPMTChargeConsistency", tree));
    data.push_back(Wrap<float              , getBetaExpectedResolution   >("rich_getBetaExpectedResolution", tree));
    data.push_back(Wrap<float              , getBetaExpectedRms          >("rich_getBetaExpectedRms", tree));
    data.push_back(Wrap<float              , getChargeExpectedRms        >("rich_getChargeExpectedRms", tree));
    
}

/////////////////////////////////////////////////////////////
///////////////////// Variables for TTree data /////////////
/////////////////////////////////////////////////////////////
void AddTrackerVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<int                , NTrackHits    >("NTrackHits"   , tree));

    data.push_back(Wrap<double             , Rfull         >("Rfull"        , tree));
    data.push_back(Wrap<double             , Rup           >("Rup"          , tree));
    data.push_back(Wrap<double             , Rdown         >("Rdown"        , tree));
    data.push_back(Wrap<double             , R             >("R"            , tree));

    data.push_back(Wrap<double             , ChiQfull      >("ChiQfull"     , tree));
    data.push_back(Wrap<double             , ChiQup        >("ChiQup"       , tree));
    data.push_back(Wrap<double             , ChiQdown      >("ChiQdown"     , tree));
    data.push_back(Wrap<double             , ChiQ          >("ChiQ"         , tree));

    data.push_back(Wrap<std::vector<double>, EDepLayerX    >("EDepLayerX"   , tree));
    data.push_back(Wrap<std::vector<double>, EDepLayerY    >("EDepLayerY"   , tree));
    data.push_back(Wrap<std::vector<double>, EDepTrackX    >("EDepTrackX"   , tree));
    data.push_back(Wrap<std::vector<double>, EDepTrackY    >("EDepTrackY"   , tree));

    data.push_back(Wrap<std::vector<double>, ResidualX     >("ResidualX"    , tree));
    data.push_back(Wrap<std::vector<double>, ResidualY     >("ResidualY"    , tree));
    data.push_back(Wrap<std::vector<double>, ResidualUpX   >("ResidualUpX"  , tree));
    data.push_back(Wrap<std::vector<double>, ResidualUpY   >("ResidualUpY"  , tree));
    data.push_back(Wrap<std::vector<double>, ResidualDownX >("ResidualDownX", tree));
    data.push_back(Wrap<std::vector<double>, ResidualDownY >("ResidualDownY", tree));
    data.push_back(Wrap<std::vector<double>, ResidualFullX >("ResidualFullX", tree));
    data.push_back(Wrap<std::vector<double>, ResidualFullY >("ResidualFullY", tree));

    data.push_back(Wrap<int                , unusedLayers  >("unusedLayers" , tree));

    data.push_back(Wrap<int                , LayerBits     >("LayerBits"    , tree));
    data.push_back(Wrap<int                , LayerBitsUp   >("LayerBitsUp"  , tree));
    data.push_back(Wrap<int                , LayerBitsDown >("LayerBitsDown", tree));
    data.push_back(Wrap<int                , LayerBitsFull >("LayerBitsFull", tree));
}

void AddTRDVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<int    , NTRDclusters>("NTRDclusters", tree));
    data.push_back(Wrap<double , EdepTRD     >("EdepTRD"     , tree));
    data.push_back(Wrap<double , ChargeTRD   >("ChargeTRD"     , tree));
}

void AddTOFVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<int                , NTofClusters    >("NTofClusters"    , tree));    
    data.push_back(Wrap<int                , NTofClustersUsed>("NTofClustersUsed", tree));
    data.push_back(Wrap<std::vector<double>, EdepTOF         >("EdepTOF"         , tree));
    data.push_back(Wrap<double             , BetaTOF         >("BetaTOF"         , tree));
    data.push_back(Wrap<double             , ChargeTOF       >("ChargeTOF"         , tree));
}

void AddECALVariable(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap<double             , EnergyE         >("EnergyE"         , tree));
}

void AddMCVariables(ROOTDataList & data, TTree * tree)
{
    data.push_back(Wrap< double            , GenMomentum >("GenMomentum", tree ));
    data.push_back(Wrap< int               , GenParID    >("GenParID",    tree ));
    data.push_back(Wrap< std::vector<float>, GenCoo      >("GenCoo",      tree ));
    data.push_back(Wrap< std::vector<float>, GenDir      >("GenDir",      tree ));
}


