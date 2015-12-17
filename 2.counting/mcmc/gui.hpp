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
    TGTab *fTab;
    std::map<std::string,TRootEmbeddedCanvas *> canvas;
    std::map<std::string, TH2F*> h;
    std::map<std::string, std::vector<TGNumberEntry*>> bin;
    std::map<std::string, TH1*> h1d;

    std::string fileFlux;
    int nGenBins;
    RealDataModel model;
    SearchSpace point;
    TGHorizontalFrame *fluxFrame;
    TGTab* tabFrame;
    TGFrame* buttonFrame;
    float rightMargin;
    std::map<std::string, MatrixF> matrix;
    std::map<std::string, TGraphErrors*> gr;
    std::map<std::string, TGNumberEntry*> buttonEntries;
    TGNumberEntry *binToCompare, *valueToCompare, *slicedBinNumberButton;
    Stack *stProj1d, *stProj1dRatio, *stCounts, *stRatio;
    
    
    void initPoint();

    float zAxisMin, zAxisMax;

    bool snapZScale;



    void setFrameDiff(){
        if(buttonEntries["xMin"] -> GetNumber() == -1) buttonEntries["xMin"] ->  SetNumber( h["diff"] -> GetXaxis() -> GetXmin() );
        if(buttonEntries["xMax"] -> GetNumber() == -1) buttonEntries["xMax"] ->  SetNumber( h["diff"] -> GetXaxis() -> GetXmax() );
        if(buttonEntries["yMin"] -> GetNumber() == -1) buttonEntries["yMin"] ->  SetNumber( h["diff"] -> GetYaxis() -> GetXmin() );
        if(buttonEntries["yMax"] -> GetNumber() == -1) buttonEntries["yMax"] ->  SetNumber( h["diff"] -> GetYaxis() -> GetXmax() );
        if(buttonEntries["zMin"] -> GetNumber() == -1) buttonEntries["zMin"] ->  SetNumber( h["diff"] -> GetZaxis() -> GetXmin() );
        if(buttonEntries["zMax"] -> GetNumber() == -1) buttonEntries["zMax"] ->  SetNumber( h["diff"] -> GetZaxis() -> GetXmax() );
        h["diff"] -> GetXaxis() -> SetRangeUser( buttonEntries["xMin"] -> GetNumber(), buttonEntries["xMax"] -> GetNumber() );
        h["diff"] -> GetYaxis() -> SetRangeUser( buttonEntries["yMin"] -> GetNumber(), buttonEntries["yMax"] -> GetNumber() );
        h["diff"] -> GetZaxis() -> SetRangeUser( buttonEntries["zMin"] -> GetNumber(), buttonEntries["zMax"] -> GetNumber() );

        canvas["diff"] -> GetCanvas() -> Update();
    }

public:
    MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);

    void updatePredictedHistoAndDrawAll(){
        updatePredictedHisto();
        drawAll();
    }

    void updatePredictedHisto(){
        for(int i = 0;i<point.fluxP.size();i++) point.fluxP[i] = bin["proton"][i] -> GetNumberEntry()->GetIntNumber();
        for(int i = 0;i<point.fluxD.size();i++) point.fluxD[i] = bin["deuton"][i] -> GetNumberEntry()->GetIntNumber();
        matrix["predicted"] = model.GetPredictionFast(point);
        getHisto(matrix["predicted"],h["predicted"]);

        if(snapZScale){
            h["predicted"] -> SetMinimum(zAxisMin);
            h["predicted"] -> SetMaximum(zAxisMax);
        }else{
            h["predicted"] -> SetMinimum(h["predicted"]->GetBinContent(h["predicted"]->GetMinimumBin()));
            h["predicted"] -> SetMaximum(h["predicted"]->GetBinContent(h["predicted"]->GetMaximumBin()));
        }

        h["predicted"] -> SetTitle( ("#splitline{hPredicted}{LogLike: "+ generalUtils::toString(model.GetLogLikelihood(point))+"}").c_str() );

    }

    void drawCanvas(std::string name, std::string goption = "colz"){
        canvas[name] -> GetCanvas() -> cd();
        h[name] -> Draw(goption.c_str());
        gPad -> SetLogx(1);
        gPad -> Update();
    }

    void drawTabMainPredictedPanel(){
        drawCanvas("predicted");
    }

    void drawTabMainObservedPanel(){
        drawCanvas("observed");
    }

    void drawTabMain(){
        drawTabMainPredictedPanel();
        drawTabMainObservedPanel();
    }

    void drawTabDiff(){
        h["diff"] -> Add(h["predicted"],h["observed"],1,-1);
        h["diff"] -> Divide(h["observed"]);
        drawCanvas("diff");
        h["observed"] -> Draw("cont1same");
        setFrameDiff();
    }

    void drawTabSlice(){
        //stProj1d.clear();
        //stProj1dRatio.clear();
        int bin = slicedBinNumberButton -> GetNumberEntry() -> GetIntNumber();
        stProj1d = new Stack(Form("rig : [%f, %f]", h["observed"] -> GetXaxis() -> GetBinLowEdge(bin), h["observed"] -> GetXaxis() -> GetBinLowEdge(bin+1)));

        for(auto &name: {"observed", "predicted"}){
            h1d[name] = h[name] -> ProjectionY(Form("%s_proj_bin%i",name,bin), bin,bin+1);
            stProj1d -> push_back(h1d[name], name);
        }
        
        stProj1d -> draw(canvas["slicePerRigBin"] -> GetCanvas());
        gPad -> SetLeftMargin(0.3);
        canvas["slicePerRigBin"] -> GetCanvas() -> Update();
        
        canvas["slicePerRigBinRatio"] -> GetCanvas() -> cd();
        h["diff"] -> ProjectionY(Form("%s_proj_bin%i","diff",bin), bin,bin+1) -> Draw();
        canvas["slicePerRigBinRatio"] -> GetCanvas() -> Update();
    }

    void drawCounts(){
        stCounts = new Stack("counts");
        stRatio = new Stack("ratio d/p");
        for(int i = 0;i<point.fluxP.size();i++){
            std::cout << "flux : " << i << ", P: " << point.fluxP[i] << ", D: " << point.fluxD[i] << std::endl;
            gr["proton"] -> SetPoint(i, model.getRgdtBinsT()[i], point.fluxP[i]);
            gr["deuton"] -> SetPoint(i, model.getRgdtBinsT()[i], point.fluxD[i]);
            gr["d/p"] -> SetPoint(i, model.getRgdtBinsT()[i], point.fluxD[i]/point.fluxP[i]);
        }
        
        for(auto &name: {"proton","deuton"}) stCounts -> push_back(gr[name], name);
        
        stCounts -> draw(canvas["counts"] -> GetCanvas());
        gPad -> SetLeftMargin(0.25);
        canvas["counts"] -> GetCanvas() -> Update();
        
        stRatio -> push_back(gr["d/p"],"ratio d/p");
        stRatio -> draw(canvas["countsRatio"] -> GetCanvas());
        gPad -> SetLeftMargin(0.2);
        canvas["countsRatio"] -> GetCanvas() -> Update();
        
    }

    void drawAll() {
        // updateContribHisto();
        // updateContribCustomHisto();
        // h["contribDiff"] -> Add(h["contrib"], h["contribCustom"],1,-1);
        
        // std::cout << "connar2" << std::endl;
        
        drawTabMain();
        drawTabDiff();
        //drawTabContrib();
        drawTabSlice();
        drawCounts();
    }

    

    void DoSnapZScale(){
        snapZScale= !snapZScale;
        updatePredictedHisto();
        drawTabMainPredictedPanel();
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

    void DoLogYSlice() {
        static bool logy = false;
        canvas["slicePerRigBin"] -> GetCanvas() -> SetLogy(!logy);
        canvas["slicePerRigBin"] -> GetCanvas() -> Update();

        logy = !logy;
    }
    
    TGVerticalFrame * observedMatrixFrame(TGHorizontalFrame* fr);
    void addMain();
    void addDiff();
    void addContrib();
    void addSlicePerRigBin();
    void addCounts();
    void addHistoFrame(std::string name, TGCompositeFrame* fr);
    TGHorizontalFrame* AddTabFrame(std::string name);
    TGTab* createTabFrame(TGHorizontalFrame* frParent);
    TGHorizontalFrame* createFluxFrame(TGHorizontalFrame* frParent);

    TGVerticalFrame* createButtonFrame(TGFrame* frParent);

    void DoClear() {
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(0);
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(0);
        updatePredictedHistoAndDrawAll();
    }

    void DoClearDeutons() {
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(0);
        updatePredictedHistoAndDrawAll();
    }

    void DoClearProtons() {
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(0);
        updatePredictedHistoAndDrawAll();
    }

    void DoDefaultValue() {
        readFlux(fileFlux,point.fluxP, point.fluxD);
        for(int i = 0;i<point.fluxP.size();i++) bin["proton"][i] -> SetIntNumber(point.fluxP[i]);
        for(int i = 0;i<point.fluxD.size();i++) bin["deuton"][i] -> SetIntNumber(point.fluxD[i]);
        updatePredictedHistoAndDrawAll();
    }

    void DoSave() {
        std::ofstream f("save.txt");
        for(int i = 0;i<bin["proton"].size();i++){
            f << bin["proton"][i] -> GetNumberEntry()->GetIntNumber() << "\t" << bin["deuton"][i] -> GetNumberEntry()->GetIntNumber() << std::endl;
        }
        f.close();
    }

    void updateContribHisto(){
        MatrixF likelihoodMatrix = matrix["predicted"];
        likelihoodMatrix.map(
                             [this](float expected , int n, int m){
                                 // if(expected > 100000){
                                 //     std::cout << expected << "\t" << observed.get(n,m) << std::endl;
                                 // }
                                 return model.GetCellLogLikelihood(expected,n,m);
                             });

        getHisto(likelihoodMatrix,h["contrib"]);
    }

    void updateContribCustomHisto(){
        std::cout << "updateContribHisto" << std::endl;
    
        SearchSpace modifiedPoint = point;
        int bin = binToCompare -> GetNumberEntry() ->GetIntNumber();
        int value = valueToCompare -> GetNumberEntry() -> GetIntNumber();
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

    ClassDef(MyMainFrame,0)

}; 
