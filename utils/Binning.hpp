#ifndef _BINNING__HPP_
#define _BINNING__HPP_

#include <vector>
#include <iostream>


class Binning{
public:
    class Bin{
    public:
	Bin( float binLowEdge, float binHighEdge ): inf(binLowEdge), sup(binHighEdge){}
	
	float inf;
	float sup;
    };

    std::vector< Bin* > bin;

    Binning( std::vector< float > _bins){
	int N = _bins.size();
	for(int i = 0;i<N-1;i++){
	    Bin* aBin = new Bin( _bins[i], _bins[i+1] );
	    bin.push_back( aBin );
	    std::cout << "Bin #" << i << " : " << aBin->inf << " - " << aBin->sup << std::endl;
	}
    }

    int size(){
	return bin.size();
    }

    Bin* operator[](int index){
	return bin[index];
    }

};


#endif
