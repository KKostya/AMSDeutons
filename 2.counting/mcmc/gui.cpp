#include "gui.hpp"

std::string files[] = {
    "beta_vs_rgdt_GenBin0.pd", 
    "beta_vs_rgdt_GenBin1.pd", 
    "beta_vs_rgdt_GenBin2.pd", 
    "beta_vs_rgdt_GenBin3.pd", 
    "beta_vs_rgdt_GenBin4.pd", 
    "beta_vs_rgdt_GenBin5.pd", 
    "beta_vs_rgdt_GenBin7.pd", 
    "beta_vs_rgdt_GenBin6.pd", 
    "beta_vs_rgdt_GenBin8.pd", 
    "beta_vs_rgdt_GenBin9.pd", 
    "beta_vs_rgdt_GenBin10.pd",
    "beta_vs_rgdt_GenBin11.pd",
    "beta_vs_rgdt_GenBin12.pd",
    "beta_vs_rgdt_GenBin13.pd",
    "beta_vs_rgdt_GenBin14.pd",
    "beta_vs_rgdt_GenBin16.pd",
    "beta_vs_rgdt_GenBin15.pd",
    "beta_vs_rgdt_GenBin17.pd",
    "beta_vs_rgdt_GenBin18.pd",
    "beta_vs_rgdt_GenBin19.pd", 
    "beta_vs_rgdt_GenBin20.pd", 
    "beta_vs_rgdt_GenBin21.pd", 
    "beta_vs_rgdt_GenBin22.pd", 
    "beta_vs_rgdt_GenBin23.pd", 
    "beta_vs_rgdt_GenBin24.pd", 
    "beta_vs_rgdt_GenBin26.pd", 
    "beta_vs_rgdt_GenBin25.pd", 
    "beta_vs_rgdt_GenBin27.pd", 
    "beta_vs_rgdt_GenBin28.pd", 
    "beta_vs_rgdt_GenBin29.pd",
    "beta_vs_rgdt_GenBin30.pd",
    "beta_vs_rgdt_GenBin31.pd",
    "beta_vs_rgdt_GenBin32.pd",
    "beta_vs_rgdt_GenBin33.pd",
    "beta_vs_rgdt_GenBin35.pd",
    "beta_vs_rgdt_GenBin34.pd",
    "beta_vs_rgdt_GenBin36.pd",
    "beta_vs_rgdt_GenBin37.pd"
};

void readFlux(std::string filename, std::vector<float> & fluxP, std::vector<float> & fluxD){
    std::ifstream f("flux.txt");
    if( ! f.good() ){
        std::cout << "The file : " << filename << " does not exist or is corrupted" << std::endl;
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
    : TGMainFrame(p,w,h, kHorizontalFrame), model(PDModel::FromCSVSBiDim( std::vector<std::string>(begin(files),end(files)), "../datasets/mask.csv" )) {
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
}

TGVerticalFrame * MyMainFrame::predictedMatrixFrame(TGHorizontalFrame* fr){
    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 40,200);
    {
        fEcanvas = new TRootEmbeddedCanvas ("Ecanvas",vframe,500,500);
        vframe->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
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
    }
}

TGVerticalFrame * MyMainFrame::observedMatrixFrame(TGHorizontalFrame* fr){
    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 40,200);
    {
        observedCanvas = new TRootEmbeddedCanvas ("observedCan",vframe,500,500);
        vframe->AddFrame(observedCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
                                                     10,10,10,1));

        TH2F* hObserved = new TH2F("hObserved","hObserved", h->GetNbinsX(),0,100,h->GetNbinsY(),0,100);
        MatrixF observedMatrix = model.getObservedDataFromFile("../datasets/observed_data.txt");

        getHisto(observedMatrix, hObserved);
        hObserved -> Draw("colz");
        
        
        fr -> AddFrame(vframe,new TGLayoutHints(kLHintsCenterX,2,2,2,2));
    }
}


void MyMainFrame::addDiff(TGCompositeFrame* frParent){
    TGHorizontalFrame *fr = new TGHorizontalFrame(frParent, 40,200);
    observedMatrixFrame(fr);
    predictedMatrixFrame(fr);
    
    std::vector<std::string> theFiles(begin(files),end(files));
    fluxFrame=new TGHorizontalFrame(fr);
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
            for(int i = 0;i<theFiles.size()/2;i++){
                TGHorizontalFrame *binFrame=new TGHorizontalFrame(it->second);
                
                TGLabel* binNumber = new TGLabel(binFrame, ("#"+generalUtils::toString(i)).c_str() );
                binFrame -> AddFrame(binNumber);
                
                bin[it->first][i] = new TGNumberEntry(binFrame, value[it->first][i], 6, -1, TGNumberFormat::kNESInteger);
                binFrame -> AddFrame(bin[it->first][i]);
                
                it->second -> AddFrame(binFrame, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
            }
            fluxFrame -> AddFrame(it->second, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
        }

        TGTextButton *clear = new TGTextButton(fluxFrame,"&Clear");
        clear->Connect("Clicked()","MyMainFrame",fr,"DoClear()");
        fluxFrame->AddFrame(clear);
        
        fr -> AddFrame(fluxFrame,new TGLayoutHints(kLHintsRight,2,2,2,2));
    }
    frParent -> AddFrame(fr);
}

void MyMainFrame::addMain(TGCompositeFrame* frParent){
    TGHorizontalFrame *fr = new TGHorizontalFrame(frParent, 40,200);
    predictedMatrixFrame(fr);
    
    std::vector<std::string> theFiles(begin(files),end(files));
    fluxFrame=new TGHorizontalFrame(fr);
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
            for(int i = 0;i<theFiles.size()/2;i++){
                TGHorizontalFrame *binFrame=new TGHorizontalFrame(it->second);
                
                TGLabel* binNumber = new TGLabel(binFrame, ("#"+generalUtils::toString(i)).c_str() );
                binFrame -> AddFrame(binNumber);
                
                bin[it->first][i] = new TGNumberEntry(binFrame, value[it->first][i], 6, -1, TGNumberFormat::kNESInteger);
                binFrame -> AddFrame(bin[it->first][i]);
                
                it->second -> AddFrame(binFrame, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
            }
            fluxFrame -> AddFrame(it->second, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
        }

        TGTextButton *clear = new TGTextButton(fluxFrame,"&Clear");
        clear->Connect("Clicked()","MyMainFrame",fr,"DoClear()");
        fluxFrame->AddFrame(clear);
        
        fr -> AddFrame(fluxFrame,new TGLayoutHints(kLHintsRight,2,2,2,2));
    }
    frParent -> AddFrame(fr);
}

void MyMainFrame::initPoint(){
    readFlux("flux.txt",point.fluxP, point.fluxD);
    
    MatrixF prediction = model.GetPredictionFast(point);
    h = new TH2F("h","h", prediction.getNcolums(),0,100,prediction.getNrows(),0,100);

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
