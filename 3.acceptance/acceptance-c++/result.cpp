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

#include "rootUtils.hpp"
#include "generalUtils.hpp"
#include "Stack.hpp"

int main(int argc, char** argv){
    TApplication app("app",&argc,argv);

    std::vector <std::string > files =  generalUtils::getFilesInDirWithPattern("/afs/cern.ch/work/b/bcoste/acceptance-c++/d.pl1.0_520_GG_Blic/","ana");

    std::cout << "files.size() : " << files.size() << std::endl;

    

    TH1F* h = (TH1F*)((TH1F*)rootUtils::get(files[0],"hacc"))->Clone("h");
    h -> SetBit(TH1::kIsAverage);

    for(int i = 1;i<files.size();i++){
        //    for(int i = 1;i<=1674;i++){
        std::cout << "i : " << i << std::endl;
        TH1F* htmp = (TH1F*)rootUtils::get(files[i],"hacc");
        if(htmp -> GetEntries() < 1 || htmp->GetMaximum() < 0 ){
            std::cout << "problem" << std::endl;
            continue;
        }
        
        htmp -> SetBit(TH1::kIsAverage);

        h -> Add(htmp);
        gFile->Close();
    }
    
    
    h -> Draw();

    // new TCanvas();
    // TH1F* htmp = (TH1F*)rootUtils::get(files[1674],"hacc");
    // htmp->Draw();
    // std::cout << "htmp->GetMaximum() : " << htmp->GetMaximum() << std::endl;
    // std::cout << "htmp->GetMinimum() : " << htmp->GetMinimum() << std::endl;
    // std::cout << "files[1674] : " << files[1674] << std::endl;
    // std::cout << "htmp -> GetEntries() : " << htmp -> GetEntries() << std::endl;
    app.Run();
}
