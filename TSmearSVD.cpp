#include "TSmearSVD.hpp"

#include <Eigen/CXX11/Tensor>
#include <Eigen/SVD> 

class TSmearImpl
{
    double min, max;
public:
    TSmearImpl(TH2D * data, TH2D * mc. int refBin);
    bool SetReferenceBin(int refBin);
    bool SetXaxis();
    bool SetYaxis();
    ~TSmearSVD();
    ClassDef(TSmearSVD,1)  
};

TSmearImpl::TSmearImpl(TH2D * d, TH2D * m. int refBin)
{
    Eigen::Tensor<double, 2> data = root_to_tensor(d);
    Eigen::Tensor<double, 2> mc   = root_to_tensor(m);

    min = protonP->GetZaxis()->GetXmin();
    max = protonP->GetZaxis()->GetXmax();
    model = new Model(pP, dP, dt);
}

TSmearSVD::TSmearSVD(){}
TSmearSVD::TSmearSVD(TH2D * data, TH2D * mc. int refBin):
   pImpl(new TSmearImpl(data,mc,refBin)) 
 

