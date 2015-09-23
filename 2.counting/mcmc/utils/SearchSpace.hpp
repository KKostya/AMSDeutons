#ifndef _SEARCHSPACE__HPP_
#define _SEARCHSPACE__HPP_

struct SearchSpace
{
    SearchSpace(): fluxP(), fluxD(){}
    ~SearchSpace(){}

    std::vector<float> fluxP;
    std::vector<float> fluxD;
    inline long unsigned int size(){return fluxP.size() + fluxD.size();}
    inline float getRaw(int i){ return i >= fluxP.size()? fluxD[i-fluxP.size()]:fluxP[i]; }
    void dump() const {
        for(int i = 0;i<fluxP.size();i++){
            std::cout << "fluxP["<<i<<"] : " << fluxP[i] << std::endl;
	}

        for(int i = 0;i<fluxD.size();i++){
            std::cout << "fluxD["<<i<<"] : " << fluxD[i] << std::endl;
	}        
    }
};

#endif

