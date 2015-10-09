#ifndef _DST__HPP_
#define _DST__HPP_

#include <string>
#include <vector>
#include <iostream>

#include "DstAmsBinary.hpp"
#include "rootUtils.hpp"
#include "Stack.hpp"

#define MAXRAM 1e9


class Dst : public DstAmsBinary{
public:
    Dst( std::string _data ) : DstAmsBinary( _data, MAXRAM){
        std::cout << "init with #" << data.size() << std::endl;
    }
  
protected:
    // virtual void init();
    void registerVariables();

    BetaHR* betaH;
    BetaR* beta;

    TofClusterHR *clusterHL0,*clusterHL1,*clusterHL2,*clusterHL3;
    virtual void initPointers();

};

#endif


