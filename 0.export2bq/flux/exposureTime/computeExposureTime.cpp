#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "TKey.h"
#include "TROOT.h"
#include "TChain.h"
#include "TF1.h"
#include "TBranch.h"

#include "amschain.h"
#include "root_setup.h"
#include "root.h"

#include "../../utils/rootUtils.hpp"
#include "../../utils/Binning.hpp"

unsigned int U_time;
std::vector< std::string > data;

inline void updateUTime(TTree* tree, unsigned int ientry){
    U_time  = 0;
    tree -> GetEntry(ientry);
}

inline void updateUTime(AMSChain* tree, unsigned int ientry){
    U_time  = 0;
    AMSEventR* ev = tree -> GetEvent(ientry);
    U_time = ev -> UTime();
}

void setBranches(TTree* tree){
    std::cout << "tree" << std::endl;
    
    tree -> SetBranchAddress("UTime",  &U_time );
}    

void setBranches(AMSChain* tree){
    std::cout << "amschain" << std::endl;
}    

// For the current data, creates an array exposureTime[iBin][iAngle][iChargeSign]
// of the exposure time
// iAngle corresponds to max cutoff for 25,30,35,40 degrees (gv) for neg+pos
template< class T> int computeExposureTime(const Binning &binning, T *tree, float cutoffSafetyFactor){
    
    long int nEntries = tree -> GetEntries();
    std::cout << "nEntries : " << nEntries << std::endl;
    
    int nBins = binning.size();
    
    std::map< int, std::map< int, std::map< int, float> > > exposureTime;
    
    AMSSetupR::RTI theRTI;
    float cutOff;

    std::map< unsigned int, bool > timeMap;

    setBranches(tree);

    for(unsigned int i = 0;i<nEntries;i++){
    //    for(unsigned int i = 0;i<10000;i++){
        if( i%100000 == 0 ) std::cout << i * 100. / nEntries << " %" << std::endl;
        updateUTime(tree,i);


	if( timeMap[ U_time ] == 0 ){
	    int ret = AMSEventR::GetRTI(theRTI, U_time);
            
	    // ret == 0 means RTI second is OK
	    if( ret == 0 ){
		for(int iAngle = 0; iAngle<4; iAngle++){
		    for( int iChargeSign = 0; iChargeSign<2; iChargeSign++){
			cutOff = theRTI.cf[iAngle][iChargeSign];
			for(int iBin = 0;iBin<nBins;iBin++){
			    if( binning[iBin]->inf > cutOff * cutoffSafetyFactor ){
				exposureTime[iBin][iAngle][iChargeSign] += theRTI.lf;
			    }
			}
		    }
		}

		timeMap[ U_time ] = 1;

	    }else{
		std::cout << "problem with RTI" << std::endl;
	    }
	}
    }

    
    std::string name2 = "Utime.txt";
    if( data.size() > 0 ) name2 = "U_Time_" + rootUtils::getFileName(data[0]) + ".txt";
    ofstream f2( name2.c_str() );
    for(std::map<unsigned int, bool>::iterator it=timeMap.begin();it!=timeMap.end();it++){
        f2 << it -> first << "\n";
    }
    f2.close();

    std::string name = "exposureTime.txt";
    if( data.size() > 0 ) name = rootUtils::getFileName(data[0]) + ".txt";
    std::cout << "name : " << name << std::endl;
    ofstream f( name.c_str() );

    f << "iBin iAngle iChargeSign exposureTime[iBin][iAngle][iChargeSign]\n";
    for(int iBin = 0;iBin<nBins;iBin++){
	for(int iAngle = 0; iAngle<4; iAngle++){
	    for( int iChargeSign = 0; iChargeSign<2; iChargeSign++){
		  std::cout << "exposureTime["<< iBin << "]["<< iAngle << "][" << iChargeSign << "] = " << exposureTime[iBin][iAngle][iChargeSign] << std::endl;
		  f << iBin << " "<< iAngle << " " << iChargeSign << " " << exposureTime[iBin][iAngle][iChargeSign] << "\n";
	    }
	}
    }

    f.close();
    
    return 1;
}



void addfrancescoFiles(AMSChain* amschain){
    ifstream f("francescoRunAtCern.txt");
    std::string line;
    int i = 0;

    while( !f.eof() && i++ < 1 ){
        std::getline(f, line);
        if( line != "" ) data.push_back(line);
    }


}

int main(int argc, char** argv){
    //    TTree* geodata = (TTree*)rootUtils::root::get("../ntuple.root","data");
    // std::vector< float > bins;
    // bins.push_back(8);
    // bins.push_back(10);
    // bins.push_back(12);
    // bins.push_back(14);
    // Binning binning(bins);

    float cutoffSafetyFactor = 1.3;
    Binning francescoBinning;
    francescoBinning.createLogarithmicBinning(0.1 * pow(10,7/9.5), pow(10,1/9.5), 24);

    AMSChain *amschain = new AMSChain();

    if( argc > 1 ){
        for(int i = 1;i<argc;i++){
            data.push_back( argv[i] );
        }
    }else addfrancescoFiles(amschain);

    for(int i = 0; i<data.size();i++) amschain -> Add( data[i].c_str());
    
    //computeExposureTime<TTree>(binning, geodata, cutoffSafetyFactor);
    computeExposureTime<AMSChain>(francescoBinning, amschain , cutoffSafetyFactor);
    return 0;
}

