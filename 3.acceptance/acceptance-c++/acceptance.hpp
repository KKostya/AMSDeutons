#ifndef _ACCEPTANCE__HPP_
#define _ACCEPTANCE__HPP_

#include <string>
#include <vector>
#include <iostream>

#include "TParameter.h"
#include "TObjString.h"

#include "Loop.hpp"
#include "rootUtils.hpp"
#include "Stack.hpp"

#include <climits>

class Acceptance : public Loop{
public:
    Acceptance( std::vector< std::string > _data ) : Loop(_data){
        std::cout << "init with #" << data.size() << std::endl;
    }
  
    Acceptance( std::string _data ) : Loop(_data){
        std::cout << "init with #" << data.size() << std::endl;
    }
  
private:
    float p;
    float R;
    bool isMC;
    int nChi2Cut;

    int biggest = 0;
    int smallest = INT_MAX;

    float pMin;
    float pMax;
  
protected:
    virtual bool process();
    virtual void write();
    virtual void draw();
    virtual int cutEvent();
    virtual void init();
};

#endif


