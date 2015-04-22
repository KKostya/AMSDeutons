#ifndef _TREEREADER__HPP_
#define _TREEREADER__HPP_

#include "TreeReaderVirt.hpp"

class TreeReader: public TreeReaderVirt {
public:
    TreeReader( std::vector< std::string > _data ): TreeReaderVirt(_data){

    }

    bool process(){
	std::cout << "hello world" << std::endl;
	return 1;
    }

    int cutEvent(){
	return 0;
    }
};

#endif


    
