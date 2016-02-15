#ifndef RTREE_HEADER
#define RTREE_HEADER

#include "TObject.h"
#include "TH2.h"
#include "TH3.h"

class TIsotopesImpl;

class TIsotopesMCMC : public TObject 
{
    TIsotopesImpl * pImpl;
public:
    TIsotopesMCMC();
    TIsotopesMCMC(TH3D * protonP, TH3D * deutonP, TH2D * data);
    ~TIsotopesMCMC();
    TH1D * GetProtonFlux();
    TH1D * GetDeutonFlux();
    double GetLogLikelihood(TH1D * p, TH1D * d);
    ClassDef(TIsotopesMCMC,1)  
};
#endif
