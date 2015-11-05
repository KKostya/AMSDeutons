#include "TApplication.h"

#include "Stack.hpp"
#include "generalUtils.hpp"
#include "rootUtils.hpp"


int main(int argc, char** argv){
    TApplication app("app",&argc,argv);
    Stack st("BetaH");
    std::map<std::string, std::string> file;
    file["no smearing"] = "output/nosmearing.root";
    file["smearing40"]    = "output/smearing40.root";
    file["smearing200"]    = "output/smearing200.root";
    std::string range = "(100,0.7,1.2)";

    for(auto it = file.begin(); it != file.end(); it++){
        TH1* h = st.push_back(it -> second,"AMSRoot",("ev.fBetaH[0] -> GetBeta()>>" + range ).c_str());
        st.editLegendEntry(h, it -> first);
    }
    
    st.draw();
    app.Run();
}


