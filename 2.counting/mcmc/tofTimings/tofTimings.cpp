#ifndef _TOFTIMINGS__CPP_
#define _TOFTIMINGS__CPP_

#include "tofTimings.hpp"

using namespace rootUtils;

void TofTimings::init(){
  maxRootFiles = 2;
  maxEntries = 1000;

  Loop::init();

  int nBinRgdt = 100;
  int firstRgdt = 1;
  int lastRgdt = 15;

  h2["betaH"] = new TH2F("betaH","betaH",nBinRgdt,firstRgdt,lastRgdt,200,0.5,1.1);
  h2["beta"]  = new TH2F("beta" ,"beta" ,nBinRgdt,firstRgdt,lastRgdt,200,0.5,1.1);
  st["beta"] = new Stack("Beta");

  for(int i = 1;i<=14;i++){
      int inf = i;
      int sup = i+1;
      h[Form("betaH_%i_%i",inf,sup)] = new TH1F(Form("betaH_%i_%i",inf,sup), Form("betaH_%i_%i",inf,sup), 200,0.5,1.1);
      h[Form("beta_%i_%i",inf,sup) ]  = new TH1F(Form("beta_%i_%i",inf,sup),Form("beta_%i_%i",inf,sup), 200,0.5,1.1);
      st["beta"] -> push_back(h[Form("betaH_%i_%i",inf,sup)], Form("betaH_%i_%i",inf,sup));
      st["beta"] -> push_back(h[Form("beta_%i_%i",inf,sup) ], Form("beta_%i_%i",inf,sup));
      st[Form("timings_%i_%i",inf,sup)] = new Stack(Form("timings_%i_%i_GeV",inf,sup));
      st[Form("timings_%i_%i",inf,sup)] -> setFrame(-3,10,0,1.1);
      
      std::vector<std::string> names{"T3-T0","T2-T0","T1-T0","T3-T2"};
      auto init = [&](std::string name) {
          name = name + Form(" [%i - %i] GeV",inf,sup);
          h[name] = new TH1F(name.c_str(),name.c_str(),200,-3,10);
          st[Form("timings_%i_%i",inf,sup)] -> push_back(h[name], name);
      };
      generalUtils::for_each(names,init);
  }

  st["betaH2D"] = new Stack("BetaHR");
  st["betaH2D"] -> push_back(h2["betaH"]);

  st["beta2D"] = new Stack("BetaR");
  st["beta2D"] -> push_back(h2["beta"]);
}

bool TofTimings::process(){
    int nBeta = ev->nBeta();
    if (nBeta > 0){
        beta = ev->pBeta(0);
        if ( beta ){
            float theBeta = beta -> Beta;
            h2["beta"] -> Fill( R, theBeta );
            h[Form("beta_%i_%i",(int)R, (int)R+1)] -> Fill( theBeta );
        }
    }
    
    int nBetaH = ev->nBetaH();
    if (nBetaH > 0){
        betaH = ev->pBetaH(0);
        if ( betaH ){
            float theBetaH = betaH -> GetBeta();
            h2["betaH"] -> Fill( R, theBetaH );
            h[Form("betaH_%i_%i",(int)R, (int)R+1)] -> Fill( theBetaH );
            
            if( betaH -> NTofClusterH() != 4 ){
                std::cout << "what the fuck" << std::endl;
                std::cout << "betaH -> NTofClusterH() : " << betaH -> NTofClusterH() << std::endl;
                return false;
            }
            float T0 = betaH -> GetClusterHL(0) -> Time;

            for(int iLayer = 1;iLayer<4;iLayer++){
                h[Form("T%i-T0 [%i - %i] GeV",iLayer,(int)R,(int)R+1)] -> Fill( betaH -> GetClusterHL(iLayer) -> Time - T0);
            }

            h[Form("T2-T0 [%i - %i] GeV",(int)R,(int)R+1)] -> Fill( betaH -> GetClusterHL(3) -> Time - betaH -> GetClusterHL(2) -> Time);
        }
    }
}

void TofTimings::draw(){
    // st["beta"] -> draw();
    // st["beta2D"] -> draw();
    // st["betaH2D"] -> draw();


    for(auto it = st.begin(); it != st.end(); it++){
        if( it -> first.substr(0,7) != "timings" ) continue;
        std::cout << "it -> first : " << it -> first << std::endl;
        it -> second -> normalizeToBiggest();
        it -> second -> draw();
        it -> second -> write(prefixe + "_" + it -> first);
    }
}

int TofTimings::cutEvent(){
  if (ev==NULL) return 1;
  if (ev->nParticle() != 1) return 2;
  part = ev->pParticle(0);
  tr = (TrTrackR*) part->pTrTrack();
  
  if(!tr) return 3;


  R = tr -> GetRigidity();
  if( R < 1  ) return 4;
  if( R > 15 ) return 5; 
  return 0;
}

void TofTimings::SetName(std::string _prefixe){
    prefixe = _prefixe;
}


int main(int argc, char **argv){
    gROOT -> SetBatch(1);
  TApplication app("app",&argc,argv);

  std::map<std::string, TofTimings*> t;
  std::map<std::string, std::string> url;
  std::map<std::string,Stack* > st;

  // url["data"]         = "/afs/cern.ch/user/b/bcoste/eos/ams/Data/AMS02/2014/ISS.B950/pass6/1364285262.00000001.root";
  url["protons.B800"] = "/afs/cern.ch/work/b/bcoste/protonB800.root";

  for(auto it = url.begin(); it!=url.end(); it++){
      std::vector< std::string > data;
      data.push_back(it -> second);
      t[it -> first] = new TofTimings( data );
      t[it -> first] -> SetName(it->first);
      t[it -> first] -> go();
  }

  app.Run();
  return 0;
}

#endif

