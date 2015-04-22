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

#include "rootUtils.hpp"
#include "Stack.hpp"



int main(){
    std::vector<std::string> files = rootUtils::getFilesInDirWithPattern("/afs/cern.ch/user/b/bcoste/eos/ams/Data/AMS02/2014/ISS.B950/pass6/", "root");
    std::cout << "files.size() : " << files.size() << std::endl;

    
    TFile* file = new TFile("RTI.root","recreate");
    int N = 10;
    TTree* tree = new TTree("rti","rti");

    AMSSetupR* run = 0;
    tree->Branch("run.","AMSSetupR",&run);

    mapClass t;
    
    for(int i = 0;i<N;i++){
	std::cout << "i : " << i << std::endl;
	AMSSetupR *runToCopy = 0;

	TTree* treeLocal = (TTree*)rootUtils::root::get( files[i], "AMSRootSetup");
	run = 0;
	treeLocal->SetBranchAddress("run.",&runToCopy);
	treeLocal -> GetEntry(0);
	run = runToCopy;
	tree -> Fill();

	t.mapNameEntryNo[ rootUtils::getFileName(files[i]) ] = i;
    }

    t.Write();
    file -> Write();
    file -> Close();
    
}
