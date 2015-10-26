#ifndef _SMEAR__CPP_
#define _SMEAR__CPP_

#include "smear.hpp"

using namespace rootUtils;

void Smear::init(){
  maxRootFiles = 2;
  std::cout << "maxEntries : " << maxEntries << std::endl;
  std::cout << "smearing  : " << smearing  << std::endl;
  Loop::init();

  if( smearing ) TofMCPar::MCtuneDT=-200;// outside or inside the AMS loop both fine 
}

bool Smear::process(){
    if( smearing ) betah->DoMCtune(); //Active smearing
    return true;
}

int Smear::cutEvent(){
  if (ev==NULL) return 1;
  if (ev->nParticle() != 1) return 2;
  part = ev->pParticle(0);

  betah = part -> pBetaH();
  if(betah == NULL) return 2;

  return 0;
}

int main(int argc, char **argv){
    
    bool smearing = false;
    int nStep = 0;
    char c;
    std::string filename = "";
    while((c =  getopt(argc, argv, "f:n:s")) != EOF)
        {
            switch (c)
                {
                case 's':
                    smearing = true;
                    break;
                case 'n':
                    nStep = generalUtils::stringTo<int>(optarg);
                    break;
                case 'f':
                    filename = optarg;
                    break;
                default:
                    break;
                }
        }

  std::vector< std::string > data;
  if(filename == "") data.push_back("/afs/cern.ch/work/b/bcoste/protonB800.root");
  else data.push_back(filename);

  Smear t( data, nStep, smearing );
  t.saveAMSTree( true );

  t.go();

  return 0;
}

#endif

