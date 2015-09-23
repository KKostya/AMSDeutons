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

MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h)
    : TGMainFrame(p,w,h), model(PDModel::FromCSVSBiDim( std::vector<std::string>(begin(files),end(files)), "../datasets/mask.csv" )) {
    // Creates widgets of the example
    fEcanvas = new TRootEmbeddedCanvas ("Ecanvas",this,200,200);
    AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
                                         10,10,10,1));
    TGHorizontalFrame *hframe=new TGHorizontalFrame(this, 200,40);
    TGTextButton *draw = new TGTextButton(hframe,"&Draw");
    draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");
    hframe->AddFrame(draw, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    TGTextButton *exit = new TGTextButton(hframe,"&Exit ",
                                          "gApplication->Terminate()");
    hframe->AddFrame(exit, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    AddFrame(hframe,new TGLayoutHints(kLHintsCenterX,2,2,2,2));

    // Sets window name and shows the main frame
    SetWindowName("Simple Example");
    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();

    SearchSpace point;
    point.fluxP.push_back(3165.72);     
    point.fluxP.push_back(14165.8); 
    point.fluxP.push_back(61011.1); 
    point.fluxP.push_back(134436);  
    point.fluxP.push_back(162383);  
    point.fluxP.push_back(182538);  
    point.fluxP.push_back(139180);  
    point.fluxP.push_back(389212);  
    point.fluxP.push_back(432333);  
    point.fluxP.push_back(146634);  
    point.fluxP.push_back(276084);  
    point.fluxP.push_back(216946);  
    point.fluxP.push_back(10.6869); 
    point.fluxP.push_back(7.42032); 
    point.fluxP.push_back(256613);  
    point.fluxP.push_back(25.3764); 
    point.fluxP.push_back(48988.1); 
    point.fluxP.push_back(205.929); 
    point.fluxP.push_back(9630.93);

    point.fluxD.push_back(342.942);
    point.fluxD.push_back(12344.2);
    point.fluxD.push_back(1711.07);
    point.fluxD.push_back(21542.6);
    point.fluxD.push_back(14753.3);
    point.fluxD.push_back(2926.6); 
    point.fluxD.push_back(7882.65);
    point.fluxD.push_back(2841.71);
    point.fluxD.push_back(16468.8);
    point.fluxD.push_back(2186.63);
    point.fluxD.push_back(8619.49);
    point.fluxD.push_back(2978.43);
    point.fluxD.push_back(85.0417);
    point.fluxD.push_back(92.2313);
    point.fluxD.push_back(29210.1);
    point.fluxD.push_back(170.11); 
    point.fluxD.push_back(217.125);
    point.fluxD.push_back(160.243);
    point.fluxD.push_back(1157.51);

        
    MatrixF prediction = model.GetPredictionFast(point);
    getHisto(prediction);
} 

void MyMainFrame::getHisto(const MatrixF & matrix){
    h = new TH2F("h","h", matrix.getNrows(),0,100,matrix.getNcolums(),0,100);
    for(int i = 1;i<=matrix.getNrows();i++){
        for(int j = 1;j<=matrix.getNcolums();j++){
            h -> SetBinContent(i,j,matrix.get(i-1,j-1));
        }
    }
}

int main(int argc, char **argv) {
    TApplication theApp("App",&argc,argv);
    new MyMainFrame(gClient->GetRoot(),200,200);
    theApp.Run();
    return 0;
} 
