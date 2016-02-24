#ifndef TSMEARSVD_HEADER
#define TSMEARSVD_HEADER

#include "TObject.h"
#include "TH2.h"

class TSmearImpl;

class TSmearSVD : public TObject 
{
    TSmearImpl * pImpl;
public:
    TSmearSVD();
    TSmearSVD(TH2D * data, TH2D * mc. int refBin);
    bool SetReferenceBin(int refBin);
    bool SetXaxis();
    bool SetYaxis();
    TH2D * GetSmeared();
    TH1D * GetKernel();
    ~TSmearSVD();
    ClassDef(TSmearSVD,1)  
};
#endif
