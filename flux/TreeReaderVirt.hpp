#ifndef _TREEREADERVIRT__HPP_
#define _TREEREADERVIRT__HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "TChain.h"
#include "TMacro.h"

#include "amschain.h"

#include "rootUtils.hpp"

class TreeReaderVirt {
public:
    TreeReaderVirt( std::vector<std::string> _data);
    void setMask( unsigned int mask );

    void go(){
	init();
	loopOnEvents();
    }

protected:
    virtual bool process() = 0;
    virtual void init();
    virtual void setBranchStatuses(){}
    virtual int cutEvent() = 0;
    virtual void write(){}
    virtual void setOutputBranches(){
	isOutputTree = false;
	delete outputTree;
	outputTree = NULL;
    }

    
    TChain* ch;
    Long64_t nentries;
    std::vector< std::string > data;
    int maxEntries;
    int maxRootFiles;
    Long64_t entry;
    std::map<int, int> cut;
    std::string outputFileName;
    TFile* outputFile;
    TTree* outputTree;
    bool isOutputTree;
    
private:
    void loopOnEvents();
    void loadChain();
    void openOutputFiles();
    void registerSrcFilesInRootuple();
    void writePrivate();
    void dumpCuts();
    int nentriesAfterCuts;
};

#endif


    
