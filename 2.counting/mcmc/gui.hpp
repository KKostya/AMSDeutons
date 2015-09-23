#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>
#include <TGFrame.h>

#include "TH2F.h"

#include "pd_model.hpp"

class MyMainFrame : public TGMainFrame {
private:
    TRootEmbeddedCanvas *fEcanvas;
    PDModel model;
    TH2F* h;
    
public:
    MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
    void DoDraw() {
        // Draws function graphics in randomly choosen interval
        // TF1 *f1 = new TF1("f1","sin(x)/x",0,gRandom->Rndm()*10);
        // f1->SetFillColor(19);
        // f1->SetFillStyle(1);
        // f1->SetLineWidth(3);
        // f1->Draw();
        h -> Draw("colz");
        TCanvas *fCanvas = fEcanvas->GetCanvas();
        fCanvas->cd();
        fCanvas->Update();
    }

    void getHisto(const MatrixF & matrix);
}; 
