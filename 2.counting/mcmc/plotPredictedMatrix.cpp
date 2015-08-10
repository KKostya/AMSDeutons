// macro
#include <iostream>
#include "rootUtils.hpp"


void plot(std::string filename){
    std::vector<std::string> vec = generalUtils::splitIntoLines(generalUtils::exec("cat " + filename ));
    TH2F* h;
    new TCanvas( filename.c_str(), filename.c_str());
    for(int i = 0;i<vec.size();i++){
        std::vector<std::string> s = generalUtils::split( vec[i], ",");
        std::cout << "s.size() : " << s.size() << std::endl;
        for(int j = 0;j<s.size();j++){
            if(i == 0 && j == 0){
                h = new TH2F( filename.c_str(),filename.c_str(),s.size(),0,s.size(),vec.size(),0,vec.size());
            }
            h -> SetBinContent(j+1,i+1,generalUtils::stringTo<float>(s[j]));
        }
    }
    h -> Draw("colz");
}


void plotPredictedMatrixF(){
    for(int i = 0;i<27;i++){
        plot( ("fatter/predictedMatrixF_"+generalUtils::toString(i)).c_str());
    }
}
