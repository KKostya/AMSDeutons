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

#include "root_setup.h"
#include "root.h"

#include "../utils/rootUtils.hpp"
#include "../utils/Binning.hpp"

// For the current data, creates an array exposureTime[iBin][iAngle][iChargeSign]
// of the exposure time
// iAngle corresponds to max cutoff for 25,30,35,40 degrees (gv) for neg+pos
int computeExposureTime(const Binning &binning, TTree* geodata, float cutoffSafetyFactor){
    
    long int nEntries = geodata -> GetEntries();

    unsigned int U_time;

    
    int nBins = binning.size();
    
    std::map< int, std::map< int, std::map< int, float> > > exposureTime;
    
    AMSSetupR::RTI theRTI;
    float cutOff;

    std::map< unsigned int, bool > timeMap;
    geodata -> SetBranchAddress("UTime",  &U_time );
    for(int i = 0;i<nEntries;i++){
	U_time  = 0;
	geodata -> GetEntry(i);

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

    for(int iBin = 0;iBin<nBins;iBin++){
	for(int iAngle = 0; iAngle<4; iAngle++){
	    for( int iChargeSign = 0; iChargeSign<2; iChargeSign++){
		if( binning[iBin]->inf > theRTI.cf[iAngle][iChargeSign] * cutoffSafetyFactor ){
		    std::cout << "exposureTime["<< iBin << "]["<< iAngle << "][" << iChargeSign << "] = " << exposureTime[iBin][iAngle][iChargeSign] << std::endl;
		}
	    }
	}
    }

    return 1;
}

int main(){
    TTree* geodata = (TTree*)rootUtils::root::get("../ntuple.root","data");

    std::vector< float > bins;
    bins.push_back(8);
    bins.push_back(10);
    bins.push_back(12);
    bins.push_back(14);

    Binning binning(bins);
    float cutoffSafetyFactor = 1.3;

    computeExposureTime(binning, geodata, cutoffSafetyFactor);
    return 1;
}

