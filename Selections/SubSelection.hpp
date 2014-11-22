#ifndef __SUBSELECTION_HPP__
#define __SUBSELECTION_HPP__

#include <string>

template<typename T>
class SubSelection
{
    typedef bool (*CutFunction)(T in);
    int nSelected;
    std::string name;
    CutFunction eval;
public:
    SubSelection(CutFunction f, std::string n):nSelected(0),name(n),eval(f){} 
    int GetNSelected(){return nSelected;}
    std::string GetName(){return name;}
    bool Test(T in)
    { 
        bool result = eval(in);
        if(result) nSelected += 1;
        return result;
    }
};

#endif
