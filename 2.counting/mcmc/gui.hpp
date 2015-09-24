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

#include "pd_model.hpp"
#include "generalUtils.hpp"

void getHisto(const MatrixF & matrix, TH2F* h);

class MyMainFrame : public TGMainFrame {
private:
    TRootEmbeddedCanvas *fEcanvas;
    TRootEmbeddedCanvas *observedCanvas;
    PDModel model;
    TH2F* h;
    SearchSpace point;
    std::map<std::string, std::vector<TGNumberEntry*>> bin;
    TGHorizontalFrame *fluxFrame;
    
    void initPoint();
public:
    MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
    void DoDraw() {
        for(int i = 0;i<point.fluxP.size();i++) point.fluxP[i] = bin["proton"][i] -> GetNumberEntry()->GetIntNumber();
        for(int i = 0;i<point.fluxD.size();i++) point.fluxD[i] = bin["deuton"][i] -> GetNumberEntry()->GetIntNumber();
        MatrixF prediction = model.GetPredictionFast(point);
        getHisto(prediction,h);

        h -> Draw("colz");
        TCanvas *fCanvas = fEcanvas->GetCanvas();
        fCanvas->cd();
        fCanvas->Update();
    }

    void DoLog() {
        static bool logz = false;
        TCanvas *fCanvas = fEcanvas->GetCanvas();
        fCanvas->SetLogz(!logz);
        observedCanvas->GetCanvas()->SetLogz(!logz);
        logz = !logz;
        fCanvas->Update();
        observedCanvas->GetCanvas();
    }
    
    TGVerticalFrame * observedMatrixFrame(TGHorizontalFrame* fr);
    void addDiff(TGCompositeFrame* frParent);
    void addMain(TGCompositeFrame* fr);
    TGVerticalFrame * predictedMatrixFrame(TGHorizontalFrame* fr);

    void DoClear() {
        for(int i = 0;i<point.fluxP.size();i++) point.fluxP[i] = 0;
        for(int i = 0;i<point.fluxD.size();i++) point.fluxD[i] = 0;
        MatrixF prediction = model.GetPredictionFast(point);
        getHisto(prediction,h);
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(0);
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(0);
        fluxFrame -> Layout();
    }
}; 
