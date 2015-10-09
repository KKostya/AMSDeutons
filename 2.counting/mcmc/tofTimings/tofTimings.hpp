#ifndef _TOFTIMINGS__HPP_
#define _TOFTIMINGS__HPP_

#include <string>
#include <vector>
#include <iostream>

#include "Loop.hpp"
#include "rootUtils.hpp"
#include "Stack.hpp"
#include "generalUtils.hpp"

class TofTimings : public Loop{
public:
    TofTimings( std::vector< std::string > _data ) : Loop(_data){
        std::cout << "init with #" << data.size() << std::endl;
    }
  
    TofTimings( std::string _data ) : Loop(_data){
        std::cout << "init with #" << data.size() << std::endl;
    }
  
    std::map<std::string, Stack *> st;

    void SetName(std::string _prefixe);

private:
    std::string prefixe;
    float p;
    float R;
    bool isMC;
    int nChi2Cut;
    BetaHR* betaH;
    BetaR* beta;
  
protected:
    virtual bool process();
    virtual void draw();
    virtual int cutEvent();
    virtual void init();
};

#endif


