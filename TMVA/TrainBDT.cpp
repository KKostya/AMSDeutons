//
// Compile it with:
//
//  g++ -o likelihood  QualityLikelihoodTrain.cpp `root-config --cflags --libs` -lTMVA
//
//


#include <TFile.h>
#include <TMVA/Factory.h>

int main(void)
{
    // Open  input files, get the trees
    TFile * mcFile = new TFile("/home/AMS/fdimicco/fdimicco/MAIN/sommaMC/sommaMC_old.root");
    TTree * mc = (TTree*)mcFile->Get("grandezze_tagli");

    // Preparing options for the TMVA::Factory
    std::string options( 
        "!V:" 
        "!Silent:"
        "Color:"
        "DrawProgressBar:"
        "Transformations=I;D;P;G,D:"
        "AnalysisType=Classification"
    );

    //Creating the factory
    TFile *   ldFile = new TFile("QualityBDT.root","RECREATE");
    TMVA::Factory * factory = new TMVA::Factory("QualityBDT", ldFile, options.c_str());

    //Preparing variables 
    factory->AddVariable("NAnticluster", 'I');
    factory->AddVariable("Chisquare", 'F');
    factory->AddVariable("layernonusati", 'F');
    factory->AddVariable("NTofUsed := NTofClusters - NTofClustersusati", 'I');
    factory->AddVariable("diffR := TMath::Abs(Rup-Rdown)/R", 'F');
    factory->AddVariable("TOF_Up_Down := TMath::Abs(Endep[2]+Endep[3]-Endep[0]-Endep[1])", 'F');

    //Preselection cuts
    std::string signalCut = "Betacorr<0.75&&Betacorr>0.5&&Massa_gen<2&&Massa_gen>1.5&&(1/Massa)<0.6";
    std::string backgnCut = "Betacorr<0.75&&Betacorr>0.5&&Massa_gen<1&&Massa_gen>0.5&&(1/Massa)<0.6";
	
    factory->AddTree(mc,"Signal"    ,1,signalCut.c_str());
    factory->AddTree(mc,"Background",1,backgnCut.c_str());

    // Preparing
    std::string preselection = "";
    std::string inputparams(
        "SplitMode=Random:"
        "NormMode=NumEvents:"
        "!V"
    );
    factory->PrepareTrainingAndTestTree(preselection.c_str(),inputparams.c_str());

    // Training
    std::string trainparams ="!H:!V:MaxDepth=8";
    factory->BookMethod(TMVA::Types::kBDT, "BDT", trainparams.c_str());

    trainparams ="!H:!V";
    factory->BookMethod(TMVA::Types::kLikelihood, "Likelihood", trainparams.c_str());


    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
}
