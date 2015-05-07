#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "TKey.h"
#include "TROOT.h"
#include "TChain.h"
#include "TF1.h"
#include "TApplication.h"

#include "/afs/cern.ch/user/b/bcoste/utils/include/Stack.hpp"

#include "../utils/rootUtils.hpp"
#include "../utils/Binning.hpp"


int main(int argc, char** argv){
    TApplication app("app",&argc,argv);
    
    Binning binning;
    binning.createLogarithmicBinning(0.5,1.2,30);

    std::map< std::string, Stack* > st;

    st["tof"] = new Stack("tof");
    st["tof"] -> push_back("data.root","data","BetaTOF:Mass>>h(100,0,5,100,0.8,1.1)");
    st["tof"] -> draw();

    st["rich"] = new Stack("rich");
    st["rich"] -> push_back("data.root","data","BetaRICH:Mass>>h(100,0,5,100,0.8,1.1)");
    st["rich"] -> draw();

    st["corr"] = new Stack("corr");
    st["corr"] -> push_back("data.root","data","BetaCorr:Mass>>h(100,0,5,100,0.5,1.01)");
    st["corr"] -> draw();

    app.Run();
 
}
