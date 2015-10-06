#include <fstream>

#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TGNumberEntry.h>
#include <TRootEmbeddedCanvas.h>
#include <TGFrame.h>
#include <TGLabel.h>
#include <TGTab.h>

#include "TH2F.h"
#include "TStyle.h"

#include "Stack.hpp"
#include "realisticToyModel.hpp"
#include "generalUtils.hpp"

class MyMainFrame : public TGMainFrame {
private:
    std::map<std::string,TRootEmbeddedCanvas *> canvas;
    std::map<std::string, TH2F*> h;
    std::map<std::string, std::vector<TGNumberEntry*>> bin;

    std::string fileFlux;
    int nGenBins;
    RealDataModel model;
    SearchSpace point;
    TGHorizontalFrame *fluxFrame;
    TGTab* tabFrame;
    TGFrame* buttonFrame;
    float rightMargin;
    MatrixF observedMatrix, predictedMatrix;
    TGNumberEntry *binToCompare, *valueToCompare;
    
    void initPoint();

    float zAxisMin, zAxisMax;

    bool snapZScale;

public:
    MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
    void DoDraw() {
        for(int i = 0;i<point.fluxP.size();i++) point.fluxP[i] = bin["proton"][i] -> GetNumberEntry()->GetIntNumber();
        for(int i = 0;i<point.fluxD.size();i++) point.fluxD[i] = bin["deuton"][i] -> GetNumberEntry()->GetIntNumber();
        predictedMatrix = model.GetPredictionFast(point);
        getHisto(predictedMatrix,h["predicted"]);

        updateContribHisto();
        updateContribCustomHisto();
        h["contribDiff"] -> Add(h["contrib"], h["contribCustom"],1,-1);

        if(snapZScale){
            h["predicted"] -> SetMinimum(zAxisMin);
            h["predicted"] -> SetMaximum(zAxisMax);
        }else{
            h["predicted"] -> SetMinimum(h["predicted"]->GetBinContent(h["predicted"]->GetMinimumBin()));
            h["predicted"] -> SetMaximum(h["predicted"]->GetBinContent(h["predicted"]->GetMaximumBin()));
        }

        h["predicted"] -> SetTitle( ("#splitline{hPredicted}{LogLike: "+ generalUtils::toString(model.GetLogLikelihood(point))+"}").c_str() );

        for(auto it=canvas.begin();it!=canvas.end();it++){
            TCanvas *theCanvas = it -> second ->GetCanvas();
            theCanvas -> cd();
            h[it->first] -> Draw("colz");
            if(it->first == "diff") h["observed"] -> Draw("cont1same");
            gPad -> SetLogx(1);
            theCanvas -> Update();
        }
    }

    void DoSnapZScale(){
        snapZScale= !snapZScale;
        DoDraw();
    }
    
    void DoLog() {
        static bool logz = false;
        TCanvas *fCanvas = canvas["predicted"]->GetCanvas();
        fCanvas->SetLogz(!logz);
        canvas["observed"]->GetCanvas()->SetLogz(!logz);
        logz = !logz;
        fCanvas->Update();
        canvas["observed"]->GetCanvas()->Update();
    }
    
    TGVerticalFrame * observedMatrixFrame(TGHorizontalFrame* fr);
    void addMain(TGCompositeFrame* fr);
    void addDiff(TGCompositeFrame* frParent);
    void addContrib(TGCompositeFrame* frParent);
    TGTab* createTabFrame(TGHorizontalFrame* frParent);
    TGHorizontalFrame* createFluxFrame(TGHorizontalFrame* frParent);
    TGVerticalFrame * predictedMatrixFrame(TGHorizontalFrame* fr);
    TGVerticalFrame* createButtonFrame(TGFrame* frParent);

    void DoClear() {
        for(int i = 0;i<point.fluxP.size();i++) point.fluxP[i] = 0;
        for(int i = 0;i<point.fluxD.size();i++) point.fluxD[i] = 0;
        predictedMatrix = model.GetPredictionFast(point);
        getHisto(predictedMatrix,h["predicted"]);
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(0);
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(0);
        DoDraw();
    }

    void DoClearDeutons() {
        for(int i = 0;i<point.fluxP.size();i++) point.fluxD[i] = 0;
        predictedMatrix = model.GetPredictionFast(point);
        getHisto(predictedMatrix,h["predicted"]);
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(0);
        DoDraw();
    }

    void DoClearProtons() {
        for(int i = 0;i<point.fluxD.size();i++) point.fluxP[i] = 0;
        predictedMatrix = model.GetPredictionFast(point);
        getHisto(predictedMatrix,h["predicted"]);
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(0);
        DoDraw();
    }

    void DoDefaultValue() {
        readFlux(fileFlux,point.fluxP, point.fluxD);
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(point.fluxP[i]);
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(point.fluxD[i]);

        predictedMatrix = model.GetPredictionFast(point);
        getHisto(predictedMatrix,h["predicted"]);
        DoDraw();
    }

    void DoSave() {
        std::ofstream f("save.txt");
        for(int i = 0;i<bin["proton"].size();i++){
            f << bin["proton"][i] -> GetNumberEntry()->GetIntNumber() << "\t" << bin["deuton"][i] -> GetNumberEntry()->GetIntNumber() << std::endl;
        }
        f.close();
    }

    void updateContribHisto();
    void updateContribCustomHisto();

    static void readFlux(std::string filename, std::vector<float> & fluxP, std::vector<float> & fluxD){
        std::ifstream f(filename);
        if( ! f.good() ){
            std::cerr << "ERROR IN gui.cpp:readFlux" << std::endl;
            std::cerr << "The file : " << filename << " does not exist or is corrupted" << std::endl;
            exit(-1);
        }

        fluxP.clear();
        fluxD.clear();
    
        float p,d;
        while(! f.eof() ){
            f >> p >> d;
            fluxP.push_back(p);
            fluxD.push_back(d);
        }

        fluxP.pop_back();
        fluxD.pop_back();
    }

    static void getHisto(const MatrixF & matrix, TH2F* h){
        for(int i = 1;i<=matrix.getNrows();i++){
            for(int j = 1;j<=matrix.getNcolums();j++){
                h -> SetBinContent(j,i,matrix.get(i-1,j-1));
            }
        }
    }



}; 
