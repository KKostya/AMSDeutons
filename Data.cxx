#include <math.h>
#include <TSpline.h>
#include <TF2.h>
#include "Data.h"

DataGeo::DataGeo(TTree * tree)
{
    tree->Branch("U_time"            , &U_time            );
    tree->Branch("Latitude"          , &Latitude          );
    tree->Branch("zonageo"           , &zonageo           );
    tree->Branch("Rcutoff"           , &Rcutoff           );
    tree->Branch("Livetime"          , &Livetime          );
    tree->Branch("ThetaS"            , &ThetaS            );
    tree->Branch("PhiS"              , &PhiS              );
    tree->Branch("Unbias"            , &Unbias            );
}

DataMC::DataMC(TTree * tree)
{
    tree->Branch("Momento_gen"       , &Momento_gen       );
    tree->Branch("Beta_gen"          , &Beta_gen          );
    tree->Branch("Massa_gen"         , &Massa_gen         );
}

DataPresel::DataPresel(TTree * tree):
    Endep(4), chiq(6), R_(6), ResiduiX(6), ResiduiY(6),
    DataMC(tree) // superconstructor calls
{
    tree->Branch("Ev_Num"            , &EventNumber       );
    tree->Branch("Trig_Num"          , &Trig_Num          );
    tree->Branch("CaricaTOF"         , &CaricaTOF         );
    tree->Branch("CaricaTRD"         , &CaricaTRD         );
    tree->Branch("CaricaTrack"       , &CaricaTrack       );
    tree->Branch("ProbQ"             , &ProbQ             );
    tree->Branch("Qbest"             , &Qbest             );
    tree->Branch("NAnticluster"      , &NAnticluster      );
    tree->Branch("NTofClusters"      , &NTofClusters      );
    tree->Branch("NTofClustersusati" , &NTofClustersusati );
    tree->Branch("Endep"             , &Endep             );
    tree->Branch("Chisquare"         , &Chisquare         );
    tree->Branch("ResiduiX"          , &ResiduiX          );
    tree->Branch("ResiduiY"          , &ResiduiY          );
    tree->Branch("NTrackHits"        , &NTrackHits        );
    tree->Branch("Rup"               , &Rup               );
    tree->Branch("Rdown"             , &Rdown             );
    tree->Branch("R"                 , &R                 );
    tree->Branch("R_"                , &R_                );
    tree->Branch("chiq"              , &chiq              );
    tree->Branch("layernonusati"     , &layernonusati     );
    tree->Branch("endepostatrack"    , &endepostatrack    );
    tree->Branch("ResiduiX"          , &ResiduiX          );
    tree->Branch("ResiduiY"          , &ResiduiY          );
    tree->Branch("clusterTrack"      , &clusterTrack      );
    tree->Branch("Beta"              , &Beta              );
    tree->Branch("Betacorr"          , &Betacorr          );
    tree->Branch("BetaRICH"          , &BetaRICH          );
    tree->Branch("EdepTRD"           , &EdepTRD           );
    tree->Branch("TRDclusters"       , &TRDclusters       );
    tree->Branch("NTRDSegments"      , &NTRDSegments      );
    tree->Branch("NTRDclusters"      , &NTRDclusters      );
    tree->Branch("Massa"             , &Massa             );
}
