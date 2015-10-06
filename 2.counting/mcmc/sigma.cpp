#include "sigma.hpp"

std::map<std::string, TH2F*>  loadPredictedAndObservedMatrix(){
    std::map<std::string, TH2F*> h;
    RealDataModel model(19);

    SearchSpace point;
    MyMainFrame::readFlux("initialConditionsGui.txt", point.fluxP, point.fluxD);
    MatrixF predictedMatrix = model.GetPredictionFast(point);
    MatrixF observedMatrix = model.getObservedDataFromFile("../datasets/observed_data.txt");

    h["predicted"] = new TH2F("hPredicted","hPredicted", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());
    h["observed"] = new TH2F("hObserved","hObserved", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());

    MyMainFrame::getHisto(observedMatrix, h["observed"]);
    MyMainFrame::getHisto(predictedMatrix,h["predicted"]);

    return h;
}

int main(int argc, char **argv) {
    TApplication theApp("App",&argc,argv);

    std::map<std::string, TH2F*> h = loadPredictedAndObservedMatrix();

    Stack stMean("mean beta");
    Stack stSigma("sigma beta");

    stMean.setFrame( 0,10, 0.8, 1.05);
    stSigma.setFrame( 0,10, 0,0.045);

    for( auto it = h.begin(); it!=h.end();it++){
        GraphFromHistos g( it -> second, "gaus(0)", 1);
        g.setFittingRange(0.8, 1.1);
        // g.drawFit(true);
        g.improveFittingRange(true);
        std::vector<TGraphAsymmErrors*> res = g.build();

        stMean.push_back(res[1], it -> first);
        stSigma.push_back(res[2], it -> first);
    }

    stMean.draw();
    stSigma.draw();

    stMean.write("betaTOFMeanVsRig");
    stSigma.write("betaTOFSigmaVsRig");
    
    theApp.Run();
    return 0;
} 


