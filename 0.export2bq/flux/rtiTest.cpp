#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "TKey.h"
#include "TROOT.h"
#include "TChain.h"
#include "TF1.h"

#include "root_setup.h"
#include "root.h"

#include "rootUtils.hpp"
#include "Stack.hpp"

int main(){
    TTree* tree = (TTree*)rootUtils::root::get("/afs/cern.ch/user/b/bcoste/eos/ams/Data/AMS02/2014/ISS.B950/pass6/1329298183.00000001.root","AMSRootSetup");
    TTree* tree2 = (TTree*)rootUtils::root::get("/afs/cern.ch/user/b/bcoste/eos/ams/Data/AMS02/2014/ISS.B950/pass6/1329298183.00000001.root","AMSRoot");

    AMSSetupR *run = 0;
    AMSEventR *ev = 0;
    tree->SetBranchAddress("run.",&run);
    tree2->SetBranchAddress("ev.",&ev);
    

    tree -> GetEntry(0);
    tree2 -> GetEntry(2);

    // TTree* tree = (TTree*)rootUtils::root::get("RTI.root","rti");
    // AMSSetupR *run = 0;
    // tree->SetBranchAddress("run.",&run);
    // tree -> GetEntry(0);
    
    //    std::cout << "AMSEvent::fRunList.size() : " << ev->fRunList.size() << std::endl;
	

    AMSSetupR::RTI theRTI;

    std::cout << "run->getRTI(theRTI,1413490745 ) : " << run->getRTI(theRTI,1329298198) << std::endl;

    std::cout << "theRTI.evno : " << theRTI.evno << std::endl;
    
    std::cout << "run -> fHeader.Run : " << run -> fHeader.Run << std::endl;
}
