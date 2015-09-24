#include "gui.hpp"


void readFlux(std::string filename, std::vector<float> & fluxP, std::vector<float> & fluxD){
    std::ifstream f("flux.txt");
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

MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h)
    : windowWidth(w),
      windowHeight(h),
      nGenBins(39),
      TGMainFrame(p,windowWidth, windowHeight, kHorizontalFrame),
      model(PDModel::FromCSVSBiDim( "beta_vs_rgdt_GenBin0.pd", nGenBins, "../datasets/mask.csv" )),
      rightMargin(0.2) {
    // Creates widgets of the example

    initPoint();

    TGTab *fTab = new TGTab(this, 300, 300);
    fTab->Connect("Selected(Int_t)", "TestDialog", this, "DoTab(Int_t)");

    TGCompositeFrame *tf1 = fTab->AddTab("Tab 1");
    addMain(tf1);

    TGCompositeFrame *tf2 = fTab->AddTab("Tab 2");
    addDiff(tf2);

    AddFrame(fTab);

    
    // Sets window name and shows the main frame
    SetWindowName("Simple Example");
    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();

    DoDraw();
}

TGVerticalFrame * MyMainFrame::predictedMatrixFrame(TGHorizontalFrame* fr){
    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 40,200);
    {
        canvas["predicted"] = new TRootEmbeddedCanvas ("Ecanvas",vframe,500,500);
        canvas["predicted"] -> GetCanvas() -> SetRightMargin(rightMargin);
 
        vframe->AddFrame(canvas["predicted"], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
                                                     10,10,10,1));
        TGHorizontalFrame *hframe=new TGHorizontalFrame(vframe, 200,40);
        TGTextButton *draw = new TGTextButton(hframe,"&Draw");
        draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
        hframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
        TGTextButton *exit = new TGTextButton(hframe,"&Exit ",
                                              "gApplication->Terminate()");
        TGCheckButton *logButton = new TGCheckButton(hframe,"&LogZ");
        logButton->Connect("Clicked()","MyMainFrame",this,"DoLog()");

        hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
        vframe->AddFrame(hframe,new TGLayoutHints(kLHintsCenterX,2,2,2,2));
        hframe->AddFrame(logButton, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
        
        fr -> AddFrame(vframe,new TGLayoutHints(kLHintsCenterX,2,2,2,2));

        MatrixF prediction = model.GetPredictionFast(point);
        getHisto(prediction,h["predicted"]);
    }
}

TGVerticalFrame * MyMainFrame::observedMatrixFrame(TGHorizontalFrame* fr){
    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 40,200);
    {
        canvas["observed"] = new TRootEmbeddedCanvas ("observedCan",vframe,500,500);
        vframe->AddFrame(canvas["observed"], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
                                                     10,10,10,1));

        h["observed"] = new TH2F("hObserved","hObserved", h["predicted"]->GetNbinsX(),0,100,h["predicted"]->GetNbinsY(),0,100);
        MatrixF observedMatrix = model.getObservedDataFromFile("../datasets/observed_data.txt");
        getHisto(observedMatrix, h["observed"]);
        canvas["observed"] -> GetCanvas() -> SetRightMargin(rightMargin);
 
        zAxisMin = h["observed"] -> GetMinimum();
        zAxisMax = h["observed"] -> GetMaximum();
                
        fr -> AddFrame(vframe,new TGLayoutHints(kLHintsCenterX,2,2,2,2));
    }
}

void MyMainFrame::addDiff(TGCompositeFrame* fr){
    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 40,200);
    {
        canvas["diff"] = new TRootEmbeddedCanvas ("observedCan",vframe,500,500);
        vframe->AddFrame(canvas["diff"], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
                                                           10,10,10,1));

        canvas["diff"] -> GetCanvas() -> SetRightMargin(rightMargin);
 

        h["diff"] = new TH2F("hDiff","hDiff", h["predicted"]->GetNbinsX(),0,100,h["predicted"]->GetNbinsY(),0,100);
        h["diff"] -> Add(h["predicted"],h["observed"],1,-1);
        h["diff"] -> Divide(h["observed"]);

        TGTextButton *draw = new TGTextButton(vframe,"&Draw");
        draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
        vframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

                
        fr -> AddFrame(vframe,new TGLayoutHints(kLHintsCenterX,2,2,2,2));
    }
}

void MyMainFrame::addMain(TGCompositeFrame* frParent){
    TGHorizontalFrame *fr = new TGHorizontalFrame(frParent, 40,200);
    observedMatrixFrame(fr);
    predictedMatrixFrame(fr);
    
    fluxFrame=new TGHorizontalFrame(fr,200);
    {
        std::map<std::string, TGVerticalFrame*> flux;
        std::map<std::string, std::vector<float>> value;

        flux["proton"] = new TGVerticalFrame(fluxFrame);
        flux["deuton"] = new TGVerticalFrame(fluxFrame);
        value["proton"] = point.fluxP;
        value["deuton"] = point.fluxD;
        bin["proton"] = std::vector<TGNumberEntry*>(point.fluxP.size());
        bin["deuton"] = std::vector<TGNumberEntry*>(point.fluxD.size());


        
        for(auto it=flux.begin();it!=flux.end();it++){
            for(int i = 0;i<nGenBins;i++){
                TGHorizontalFrame *binFrame=new TGHorizontalFrame(it->second);
                
                TGLabel* binNumber = new TGLabel(binFrame, ("#"+generalUtils::toString(i)).c_str() );
                binFrame -> AddFrame(binNumber);
                
                bin[it->first][i] = new TGNumberEntry(binFrame, value[it->first][i], 10, -1, TGNumberFormat::kNESInteger);
                binFrame -> AddFrame(bin[it->first][i]);
                
                it->second -> AddFrame(binFrame, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
            }
            fluxFrame -> AddFrame(it->second, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
        }

        TGTextButton *clear = new TGTextButton(fluxFrame,"&Clear");
        clear->Connect("Clicked()","MyMainFrame",this,"DoClear()");
        fluxFrame->AddFrame(clear);

        TGTextButton *clearDeuton = new TGTextButton(fluxFrame,"&Clear deutons");
        clearDeuton->Connect("Clicked()","MyMainFrame",this,"DoClearDeutons()");
        fluxFrame->AddFrame(clearDeuton);

        TGTextButton *clearProton = new TGTextButton(fluxFrame,"&Clear protons");
        clearProton->Connect("Clicked()","MyMainFrame",this,"DoClearProtons()");
        fluxFrame->AddFrame(clearProton);

        fr -> AddFrame(fluxFrame,new TGLayoutHints(kLHintsRight,2,2,2,2));
    }
    frParent -> AddFrame(fr);
}



void MyMainFrame::initPoint(){
    readFlux("flux.txt",point.fluxP, point.fluxD);
    
    MatrixF prediction = model.GetPredictionFast(point);
    h["predicted"] = new TH2F("hPredicted","hPredicted", prediction.getNcolums(),0,100,prediction.getNrows(),0,100);

    gStyle -> SetOptStat(0);

}

void getHisto(const MatrixF & matrix, TH2F* h){
    for(int i = 1;i<=matrix.getNcolums();i++){
        for(int j = 1;j<=matrix.getNrows();j++){
            h -> SetBinContent(j,i,matrix.get(i-1,j-1));
        }
    }
}

int main(int argc, char **argv) {
    TApplication theApp("App",&argc,argv);
    new MyMainFrame(gClient->GetRoot(),600,600);
    theApp.Run();
    return 0;
} 
