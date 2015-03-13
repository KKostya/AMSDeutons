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
    TFile * mcFile = new TFile("326.root");
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
    TFile *   ldFile = new TFile("QualityLikelihood.root","RECREATE");
    TMVA::Factory * factory = new TMVA::Factory("QualityLikelihood", ldFile, options.c_str());

    //Preparing variables 
    factory->AddVariable("NAnticluster", 'I');
    factory->AddVariable("Chisquare", 'F');
    factory->AddVariable("layernonusati", 'F');
    factory->AddVariable("NTofUsed := NTofClusters - NTofClustersusati", 'I');
    factory->AddVariable("diffR := abs(Rup-Rdown)/R", 'F');
    factory->AddVariable("TOF_Up_Down := abs(Endep[2]+Endep[3]-Endep[0]-Endep[1])", 'F');

    //Preselection cuts
    std::string signalCut = "Betacorr<0.75&& (1/Massa>0.6&&1/Massa<1.2)";
    std::string backgnCut = "Betacorr<0.75&&!(1/Massa>0.6&&1/Massa<1.2)";

    factory->AddTree(mc,"Signal"    ,1,signalCut.c_str());
    factory->AddTree(mc,"Background",1,backgnCut.c_str());

    // Preparing
    std::string preselection = "IsPrescaled==0";
    std::string inputparams(
        "nTrain_Signal=2400:"
        "nTrain_Background=700:" 
        "SplitMode=Random:"
        "NormMode=NumEvents:"
        "!V"
    );
    factory->PrepareTrainingAndTestTree(preselection.c_str(),inputparams.c_str());

    // Training
    std::string trainparams ="!H:!V";
    
    factory->BookMethod(TMVA::Types::kLikelihood, "Likelihood", trainparams.c_str());

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
}
