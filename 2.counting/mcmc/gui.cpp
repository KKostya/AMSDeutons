#include "gui.hpp"


MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h)
    : nGenBins(19),
      TGMainFrame(p,w,h, kHorizontalFrame),
      model(nGenBins),
      rightMargin(0.2),
      snapZScale(true),
      fileFlux("initialConditionsGui.txt"){
    // Creates widgets of the example

    initPoint();

    TGHorizontalFrame *hFrame=new TGHorizontalFrame(this, 200,40);


    tabFrame = createTabFrame(hFrame);
    hFrame -> AddFrame(tabFrame);

    fluxFrame = createFluxFrame(hFrame);
    hFrame -> AddFrame(fluxFrame);

    buttonFrame = createButtonFrame(hFrame);
    hFrame -> AddFrame(buttonFrame);
    
    AddFrame(hFrame);

    
    // Sets window name and shows the main frame
    SetWindowName("Simple Example");
    MapSubwindows();
    Resize(GetDefaultSize());
    MapWindow();

    DoDraw();
}

TGTab* MyMainFrame::createTabFrame(TGHorizontalFrame* frParent){
    TGTab *fTab = new TGTab(frParent, 300, 300);
    fTab->Connect("Selected(Int_t)", "TestDialog", this, "DoTab(Int_t)");

    TGCompositeFrame *tf1 = fTab->AddTab("Tab 1");
    addMain(tf1);

    TGCompositeFrame *tf2 = fTab->AddTab("Tab 2");
    addDiff(tf2);

    TGCompositeFrame *tf3 = fTab->AddTab("Tab 3");
    addContrib(tf3);

    return fTab;
}

TGVerticalFrame * MyMainFrame::predictedMatrixFrame(TGHorizontalFrame* fr){
    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 40,200);
    {
        canvas["predicted"] = new TRootEmbeddedCanvas ("Ecanvas",vframe,500,500);
        canvas["predicted"] -> GetCanvas() -> SetRightMargin(rightMargin);
 
        vframe->AddFrame(canvas["predicted"], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
                                                     10,10,10,1));


        fr -> AddFrame(vframe,new TGLayoutHints(kLHintsCenterX,2,2,2,2));

        predictedMatrix = model.GetPredictionFast(point);
        getHisto(predictedMatrix,h["predicted"]);
    }
}

TGVerticalFrame* MyMainFrame::createButtonFrame(TGFrame* frParent){
    TGVerticalFrame *outFrame = new TGVerticalFrame(frParent, 20,40);

    TGTextButton *draw = new TGTextButton(outFrame,"&Draw");
    draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");

    TGTextButton *exit = new TGTextButton(outFrame,"&Exit ",
                                          "gApplication->Terminate()");
    TGCheckButton *logButton = new TGCheckButton(outFrame,"&LogZ");
    logButton->Connect("Clicked()","MyMainFrame",this,"DoLog()");

    TGCheckButton *sameZScaleButton = new TGCheckButton(outFrame,"&snap Z scales");
    sameZScaleButton->Connect("Clicked()","MyMainFrame",this,"DoSnapZScale()");
    sameZScaleButton->SetState(kButtonDown);

    TGTextButton *clear = new TGTextButton(outFrame,"&Clear");
    clear->Connect("Clicked()","MyMainFrame",this,"DoClear()");

    TGTextButton *save = new TGTextButton(outFrame,"&Save");
    save->Connect("Clicked()","MyMainFrame",this,"DoSave()");

    TGTextButton *clearDeuton = new TGTextButton(outFrame,"&Clear deutons");
    clearDeuton->Connect("Clicked()","MyMainFrame",this,"DoClearDeutons()");


    TGTextButton *clearProton = new TGTextButton(outFrame,"&Clear protons");
    clearProton->Connect("Clicked()","MyMainFrame",this,"DoClearProtons()");

    TGTextButton *defaultValue = new TGTextButton(outFrame,"&Default");
    defaultValue->Connect("Clicked()","MyMainFrame",this,"DoDefaultValue()");

    binToCompare = new TGNumberEntry(outFrame, 0, 10, -1,  TGNumberFormat::kNESInteger,
                                     TGNumberFormat::kNEANonNegative,
                                     TGNumberFormat::kNELLimitMinMax,
                                     0, nGenBins-1);
    binToCompare->Connect("ValueSet(Long_t)", "MyMainFrame", this, "DoDraw()");
    (binToCompare->GetNumberEntry())->Connect("ReturnPressed()", "MyMainFrame", this,
                                              "DoDraw()");

    valueToCompare = new TGNumberEntry(outFrame, 0, 10, -1, TGNumberFormat::kNESInteger);
    valueToCompare->Connect("ValueSet(Long_t)", "MyMainFrame", this, "DoDraw()");
    (valueToCompare->GetNumberEntry())->Connect("ReturnPressed()", "MyMainFrame", this,
                                              "DoDraw()");


    outFrame->AddFrame(draw);
    outFrame->AddFrame(save);
    outFrame->AddFrame(clear);
    outFrame->AddFrame(clearDeuton);
    outFrame->AddFrame(clearProton);
    outFrame->AddFrame(defaultValue);
    outFrame->AddFrame(exit);
    outFrame->AddFrame(logButton);
    outFrame->AddFrame(sameZScaleButton);
    outFrame->AddFrame(binToCompare);
    outFrame->AddFrame(valueToCompare);

    // outFrame->AddFrame(outFrame,new TGLayoutHints(kLHintsCenterX,2,2,2,2));
    return outFrame;
}

TGVerticalFrame * MyMainFrame::observedMatrixFrame(TGHorizontalFrame* fr){
    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 40,200);
    {
        canvas["observed"] = new TRootEmbeddedCanvas ("observedCan",vframe,500,500);
        vframe->AddFrame(canvas["observed"], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY,
                                                     10,10,10,1));

        h["observed"] = new TH2F("hObserved","hObserved", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());
        observedMatrix = model.getObservedDataFromFile("../datasets/observed_data.txt");
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
 

        h["diff"] = new TH2F("hDiff","hDiff", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());
        h["diff"] -> Add(h["predicted"],h["observed"],1,-1);
        h["diff"] -> Divide(h["observed"]);
                
        fr -> AddFrame(vframe,new TGLayoutHints(kLHintsLeft,2,2,2,2));
    }
}

void MyMainFrame::addContrib(TGCompositeFrame* frParent){
    h["contrib"] = new TH2F("hContrib","hContrib", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());
    h["contribCustom"] = new TH2F("hContribCustom","hContribCustom", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());
    h["contribDiff"] = new TH2F("hContribDiff","hContribDiff", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());
    
    if(0){
        TGHorizontalFrame *hframe=new TGHorizontalFrame(frParent, 40,200);
        {
            canvas["contrib"] = new TRootEmbeddedCanvas ("contrib",hframe,500,500);
            canvas["contrib"] -> GetCanvas() -> SetRightMargin(rightMargin);
            hframe->AddFrame(canvas["contrib"], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10,10,10,1));
        }

        {
            canvas["contribCustom"] = new TRootEmbeddedCanvas ("contribCustom",hframe,500,500);

            canvas["contribCustom"] -> GetCanvas() -> SetRightMargin(rightMargin);
            
            hframe->AddFrame(canvas["contribCustom"], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10,10,10,1));
        }
        frParent -> AddFrame(hframe,new TGLayoutHints(kLHintsRight,2,2,2,2));
    }else{
        TGHorizontalFrame *hframe=new TGHorizontalFrame(frParent, 40,200);
        {
            canvas["contribDiff"] = new TRootEmbeddedCanvas ("contribDiff",hframe,500,500);
            canvas["contribDiff"] -> GetCanvas() -> SetRightMargin(rightMargin);

            hframe->AddFrame(canvas["contribDiff"], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10,10,10,1));
        }
        frParent -> AddFrame(hframe,new TGLayoutHints(kLHintsRight,2,2,2,2));
    }


    
}

void MyMainFrame::updateContribHisto(){
    MatrixF likelihoodMatrix = predictedMatrix;
    likelihoodMatrix.map(
                         [this](float expected , int n, int m){
                             // if(expected > 100000){
                             //     std::cout << expected << "\t" << observed.get(n,m) << std::endl;
                             // }
                             return model.GetCellLogLikelihood(expected,n,m);
                         });

    getHisto(likelihoodMatrix,h["contrib"]);
}
void MyMainFrame::updateContribCustomHisto(){
    std::cout << "updateContribHisto" << std::endl;
    
    SearchSpace modifiedPoint = point;
    int bin = binToCompare -> GetNumberEntry()->GetIntNumber();
    int value = valueToCompare -> GetNumberEntry()->GetIntNumber();
    modifiedPoint.fluxP[bin] = value;
    
    MatrixF modifiedPredictedMatrix = model.GetPredictionFast(modifiedPoint);

    modifiedPredictedMatrix.map(
                         [this](float expected , int n, int m){
                             // if(expected > 100000){
                             //     std::cout << expected << "\t" << observed.get(n,m) << std::endl;
                             // }
                             return model.GetCellLogLikelihood(expected,n,m);
                         });

    getHisto(modifiedPredictedMatrix,h["contribCustom"]);
}

TGHorizontalFrame* MyMainFrame::createFluxFrame(TGHorizontalFrame* frParent){
    TGHorizontalFrame* outFrame=new TGHorizontalFrame(frParent,200);
    {
        std::map<std::string, TGVerticalFrame*> flux;
        std::map<std::string, std::vector<float>> value;

        flux["proton"] = new TGVerticalFrame(outFrame);
        flux["deuton"] = new TGVerticalFrame(outFrame);
        value["proton"] = point.fluxP;
        value["deuton"] = point.fluxD;
        bin["proton"] = std::vector<TGNumberEntry*>(point.fluxP.size());
        bin["deuton"] = std::vector<TGNumberEntry*>(point.fluxD.size());

        
        for(auto it=flux.begin();it!=flux.end();it++){
            for(int i = 0;i<nGenBins;i++){
                TGHorizontalFrame *binFrame=new TGHorizontalFrame(it->second);
                
                TGLabel* binNumber = new TGLabel(binFrame, Form("%1.2f GeV",model.getRgdtBinsT()[i] ));
                binFrame -> AddFrame(binNumber);
                
                bin[it->first][i] = new TGNumberEntry(binFrame, value[it->first][i], 10, -1, TGNumberFormat::kNESInteger);
                bin[it->first][i]->Connect("ValueSet(Long_t)", "MyMainFrame", this, "DoDraw()");
                (bin[it->first][i]->GetNumberEntry())->Connect("ReturnPressed()", "MyMainFrame", this,
                                                               "DoDraw()");

                
                binFrame -> AddFrame(bin[it->first][i]);
                
                it->second -> AddFrame(binFrame, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
            }
            outFrame -> AddFrame(it->second, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
        }


        frParent -> AddFrame(outFrame,new TGLayoutHints(kLHintsRight,2,2,2,2));
    }

    return outFrame;
}

void MyMainFrame::addMain(TGCompositeFrame* frParent){
    TGHorizontalFrame *fr = new TGHorizontalFrame(frParent, 40,200);
    observedMatrixFrame(fr);
    predictedMatrixFrame(fr);
    
    frParent -> AddFrame(fr);
}


void MyMainFrame::initPoint(){
    readFlux(fileFlux,point.fluxP, point.fluxD);
    
    predictedMatrix = model.GetPredictionFast(point);
    h["predicted"] = new TH2F("hPredicted","hPredicted", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());

    gStyle -> SetOptStat(0);

}




int main(int argc, char **argv) {
    TApplication theApp("App",&argc,argv);
    gStyle -> SetPalette(1);
    new MyMainFrame(gClient->GetRoot(),1400,800);
    theApp.Run();
    return 0;
} 
