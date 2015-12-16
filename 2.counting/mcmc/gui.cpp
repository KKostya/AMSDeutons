#include "gui.hpp"


MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h)
    : nGenBins(19),
      TGMainFrame(p,w,h, kHorizontalFrame),
      model(nGenBins,"tofh"),
      rightMargin(0.2),
      snapZScale(true),
      fileFlux("initialConditionsGui.txt"){
    // Creates widgets of the example

    for(auto &name: {"proton","deuton", "d/p"}) gr[name] = new TGraphErrors();
    
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

    updatePredictedHistoAndDrawAll();
}

TGTab* MyMainFrame::createTabFrame(TGHorizontalFrame* frParent){
    fTab = new TGTab(frParent, 300, 300);
    fTab->Connect("Selected(Int_t)", "TestDialog", this, "DoTab(Int_t)");

    addMain();
    addDiff();
    addContrib();
    addSlicePerRigBin();
    addCounts();

    return fTab;
}

TGVerticalFrame* MyMainFrame::createButtonFrame(TGFrame* frParent){
    TGVerticalFrame *outFrame = new TGVerticalFrame(frParent, 20,40);

    // TGTextButton *draw = new TGTextButton(outFrame,"&Draw");
    // draw->Connect("Clicked()","MyMainFrame",this,"DoDraw()");

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

    binToCompare->Connect("ValueSet(Long_t)", "MyMainFrame", this, "drawAll()");
    (binToCompare->GetNumberEntry())->Connect("ReturnPressed()", "MyMainFrame", this,
                                              "drawAll()");

    valueToCompare = new TGNumberEntry(outFrame, 0, 10, -1, TGNumberFormat::kNESInteger);
    valueToCompare->Connect("ValueSet(Long_t)", "MyMainFrame", this, "drawAll()");
    (valueToCompare->GetNumberEntry())->Connect("ReturnPressed()", "MyMainFrame", this,
                                              "drawAll()");


    // outFrame->AddFrame(draw);
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


void MyMainFrame::addHistoFrame(std::string name, TGCompositeFrame* fr){
    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 40,200);
    canvas[name] = new TRootEmbeddedCanvas (name.c_str(),vframe,500,500);
    vframe->AddFrame(canvas[name], new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10,10,10,1));

    canvas[name] -> GetCanvas() -> SetRightMargin(rightMargin);
    fr -> AddFrame(vframe,new TGLayoutHints(kLHintsLeft,2,2,2,2));

}

void MyMainFrame::addDiff(){
    h["diff"] = new TH2F("hDiff","(predicted-observed)/observed", model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());


    TGHorizontalFrame* fr = AddTabFrame("Tab diff");
    addHistoFrame("diff", fr);
}

void MyMainFrame::addSlicePerRigBin(){
    TGHorizontalFrame* fr = AddTabFrame("Tab slice");
    addHistoFrame("slicePerRigBin", fr);
    addHistoFrame("slicePerRigBinRatio", fr);

    TGVerticalFrame *vframe=new TGVerticalFrame(fr, 20,20);
    slicedBinNumberButton = new TGNumberEntry(vframe, 20, 10, -1, TGNumberFormat::kNESInteger);
    slicedBinNumberButton -> Connect("ValueSet(Long_t)", "MyMainFrame", this, "drawTabSlice()");
    (slicedBinNumberButton -> GetNumberEntry())->Connect("ReturnPressed()", "MyMainFrame", this, "drawTabSlice()");    
    vframe -> AddFrame(slicedBinNumberButton);
    fr ->  AddFrame(vframe);
}

void MyMainFrame::addCounts(){
    TGHorizontalFrame* fr = AddTabFrame("Tab slice");
    addHistoFrame("counts", fr);
    addHistoFrame("countsRatio", fr);
}

void MyMainFrame::addContrib(){
    TGHorizontalFrame* frParent = AddTabFrame("Tab contrib");

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
                bin[it->first][i]->Connect("ValueSet(Long_t)", "MyMainFrame", this, "updatePredictedHistoAndDrawAll()");
                (bin[it->first][i]->GetNumberEntry())->Connect("ReturnPressed()", "MyMainFrame", this,
                                                               "updatePredictedHistoAndDrawAll()");
                
                binFrame -> AddFrame(bin[it->first][i]);
                
                it->second -> AddFrame(binFrame, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
            }
            outFrame -> AddFrame(it->second, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
        }


        frParent -> AddFrame(outFrame,new TGLayoutHints(kLHintsRight,2,2,2,2));
    }

    return outFrame;
}

TGHorizontalFrame* MyMainFrame::AddTabFrame(std::string name){
    TGCompositeFrame *frParent = fTab->AddTab(name.c_str());
    TGHorizontalFrame *fr = new TGHorizontalFrame(frParent, 40,200);
    frParent -> AddFrame(fr);
    return fr;
}

void MyMainFrame::addMain(){
    TGHorizontalFrame* fr = AddTabFrame("Tab Main");

    matrix["predicted"] = model.GetPredictionFast(point);
    matrix["observed"] = model.getObservedDataFromFile("../datasets/observed_data.txt");

    for( auto &name: {"predicted","observed"}){
        h[name] = new TH2F(name, name, model.getRgdtBinsM().size()-1,model.getRgdtBinsM().data(), model.getBetaBinsM().size()-1,model.getBetaBinsM().data());
        getHisto(matrix[name], h[name]);
        addHistoFrame(name, fr);
    }

    zAxisMin = h["observed"] -> GetMinimum();
    zAxisMax = h["observed"] -> GetMaximum();

}


void MyMainFrame::initPoint(){
    readFlux(fileFlux,point.fluxP, point.fluxD);
    gStyle -> SetOptStat(0);

}

int main(int argc, char **argv) {
    TApplication theApp("App",&argc,argv);
    gStyle -> SetPalette(1);
    new MyMainFrame(gClient->GetRoot(),1400,800);
    theApp.Run();
    return 0;
} 
