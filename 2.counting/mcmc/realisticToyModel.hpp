#ifndef _REALISTICTOYMODEL__HPP_
#define _REALISTICTOYMODEL__HPP_

#include <fstream>
#include "generalUtils.hpp"

#include "pd_model.hpp"


// static std::vector< std::pair<float,float> > getLogDerivative(const std::vector< std::pair<float, float> > & point){
//     long unsigned int nVar = point.size();

//     std::vector< std::pair<float,float> > derivative(nVar-1);
//     for(int i = 0;i<nVar-1;i++){
//         derivative[i].first  = ( point[i+1].first - point[i].first )/ (std::log10(point[i+1].second) - std::log10(point[i].second) );
//         derivative[i].second = std::sqrt(point[i+1].second * point[i].second);
//     }
//     return derivative;
// }

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
    "beta_vs_rgdt_GenBin18.pd"
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

struct RealisticToyModel: public PDModel
{
    static const bool isToyMC = true;

    RealisticToyModel():
        //PDModel(PDModel::FromCSVS("../datasets/B_resolution.csv", "../datasets/R_resolution.csv","../datasets/mask.csv" ))
        PDModel(PDModel::FromCSVSBiDim( std::vector<std::string>(begin(files),end(files)), "../datasets/mask.csv" ))
    {
        // Set true values of the model
        for( int i = 0; i < getBetaBinsT().size() - 1; i++){
            realValues.fluxP.push_back(10000);
            realValues.fluxD.push_back(10000);
        }

        

        exit(-1);
        // Generate fake data

        GenerateToyObservedData(realValues);
    }

    virtual void saveMetaData(std::ofstream & myfile) override {
        myfile << "isToyMC "        << isToyMC << std::endl;
        myfile << "bins " ;
        for(auto v :  getBetaBinsT()) myfile << v << " "; 
        myfile << std::endl;
    }

};

struct RealDataModel: public PDModel
{
    static const bool isToyMC = false;

    RealDataModel():
        PDModel(PDModel::FromCSVSBiDim( std::vector<std::string>(begin(files),end(files)), "../datasets/mask.csv" ))
        //PDModel(PDModel::FromCSVS("../datasets/B_resolution.csv", "../datasets/R_resolution.csv", "../datasets/mask.csv"))
    {
        // Get initial conditions
        std::string fname = "../datasets/initialConditions.txt";
        std::ifstream f(fname);
        if( !f ){
            std::cerr << "No file : " << fname << " found !\nExit !" << std::endl;
            exit(-1);
        }
        while(true){
            float fluxP, fluxD;
            f >> fluxP >> fluxD;
            std::cout << "fluxP : " << fluxP << std::endl;
            std::cout << "fluxD : " << fluxD << std::endl;
            if( f.eof() ) break;
            initialConditions.fluxP.push_back(fluxP);
            initialConditions.fluxD.push_back(fluxD);
        }

        if( initialConditions.fluxP.size() != getBetaBinsT().size()-1 || initialConditions.fluxD.size() != getBetaBinsT().size()-1 ){
            std::cerr << "Wrong initialConditions in initialConditions.txt" << std::endl;
            std::cerr << "Size do not match: model.getBetaBinsT().size()-1" << std::endl;
            exit(-1);
        }

        // for( int i = 0; i < model.getBetaBinsT().size() - 1; i++){
        //     // putting a realistic power law flux
        //     toyFluxP[i] = 100000* pow(sqrt(model.getRgdtBinsT()[i]*model.getRgdtBinsT()[i+1]),-2.7);
        //     toyFluxD[i] = toyFluxP[i] / 10.;
        // }

        // Load real data
        LoadObservedDataFromFile("../datasets/observed_data.txt");
    }

    ~RealDataModel(){}

    virtual void saveMetaData(std::ofstream & myfile) override {
        myfile << "isToyMC "        << isToyMC << std::endl;
        myfile << "bins " ;
        for(auto v :  getBetaBinsT()) myfile << v << " "; 
        myfile << std::endl;
    }
};

#endif
