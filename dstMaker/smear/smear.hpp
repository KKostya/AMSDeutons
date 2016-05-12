#ifndef _SMEAR__HPP_
#define _SMEAR__HPP_

#include <string>
#include <vector>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Loop.hpp"
#include "rootUtils.hpp"
#include "Stack.hpp"

class Smear : public Loop{
private:
    BetaHR *betah;
    float p;
    float R;
    bool isMC;
    int nChi2Cut;
    bool smearing;

public:
    Smear( std::vector< std::string > _data, int _maxEntries, bool _smearing ) : Loop(_data), smearing(_smearing) {
    std::cout << "init with #" << data.size() << std::endl;
    maxEntries = _maxEntries;
  }
  
  Smear( std::string _data ) : Loop(_data){
    std::cout << "init with #" << data.size() << std::endl;
  }
  

  
protected:
  virtual bool process();
  virtual int cutEvent();
  virtual void init();
};

#endif


