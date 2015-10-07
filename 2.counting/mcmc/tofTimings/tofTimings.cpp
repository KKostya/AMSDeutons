#ifndef _TOFTIMINGS__CPP_
#define _TOFTIMINGS__CPP_

#include "tofTimings.hpp"

using namespace rootUtils;

void TofTimings::init(){
  maxRootFiles = 2;
  maxEntries = 1000;

  Loop::init();
}

bool TofTimings::process(){

}


void TofTimings::draw(){
}

int TofTimings::cutEvent(){
  if (ev==NULL) return 1;
  if (ev->nParticle() != 1) return 2;
  part = ev->pParticle(0);
  tr = (TrTrackR*) part->pTrTrack();
  
  if(!tr) return 3;
  if(ev -> nEcalShower() != 1) return 4;

  return 0;
}

int main(int argc, char **argv){
  TApplication app("app",&argc,argv);

  std::vector< std::string > data;

  TofTimings t( data );
  //  t.setEventList("list.txt");
  t.go();

  app.Run();
  return 0;
}

#endif

