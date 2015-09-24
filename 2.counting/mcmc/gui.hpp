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
#include "pd_model.hpp"
#include "generalUtils.hpp"

void getHisto(const MatrixF & matrix, TH2F* h);

class MyMainFrame : public TGMainFrame {
private:
    std::map<std::string,TRootEmbeddedCanvas *> canvas;
    std::map<std::string, TH2F*> h;
    std::map<std::string, std::vector<TGNumberEntry*>> bin;

    int nGenBins;
    PDModel model;
    SearchSpace point;
    TGHorizontalFrame *fluxFrame;
    float rightMargin;
    
    void initPoint();

    float zAxisMin, zAxisMax;

public:
    MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
    void DoDraw() {
        for(int i = 0;i<point.fluxP.size();i++) point.fluxP[i] = bin["proton"][i] -> GetNumberEntry()->GetIntNumber();
        for(int i = 0;i<point.fluxD.size();i++) point.fluxD[i] = bin["deuton"][i] -> GetNumberEntry()->GetIntNumber();
        MatrixF prediction = model.GetPredictionFast(point);
        getHisto(prediction,h["predicted"]);

        h["predicted"] -> SetMinimum(zAxisMin);
        h["predicted"] -> SetMaximum(zAxisMax);

        for(auto it=canvas.begin();it!=canvas.end();it++){
            TCanvas *theCanvas = it -> second ->GetCanvas();
            theCanvas -> cd();
            h[it->first] -> Draw("colz");
            theCanvas -> Update();
        }
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
    void addDiff(TGCompositeFrame* frParent);
    void addMain(TGCompositeFrame* fr);
    TGVerticalFrame * predictedMatrixFrame(TGHorizontalFrame* fr);

    void DoClear() {
        for(int i = 0;i<point.fluxP.size();i++) point.fluxP[i] = 0;
        for(int i = 0;i<point.fluxD.size();i++) point.fluxD[i] = 0;
        MatrixF prediction = model.GetPredictionFast(point);
        getHisto(prediction,h["predicted"]);
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(0);
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(0);
        fluxFrame -> Layout();
    }

    void DoClearDeutons() {
        for(int i = 0;i<point.fluxP.size();i++) point.fluxD[i] = 0;
        MatrixF prediction = model.GetPredictionFast(point);
        getHisto(prediction,h["predicted"]);
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(0);
        fluxFrame -> Layout();
    }

    void DoClearProtons() {
        for(int i = 0;i<point.fluxD.size();i++) point.fluxP[i] = 0;
        MatrixF prediction = model.GetPredictionFast(point);
        getHisto(prediction,h["predicted"]);
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(0);
        fluxFrame -> Layout();
    }
}; 
