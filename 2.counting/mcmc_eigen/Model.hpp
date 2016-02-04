#include <Eigen/CXX11/Tensor>

class Model
{
    Eigen::Tensor<double, 3> protonP;
    Eigen::Tensor<double, 3> deutonP;

    Eigen::Tensor<double, 1> protonF;
    Eigen::Tensor<double, 1> deutonF;
 
public:
    Model(int NRm, int NBm, int NRt):
        protonP(NRm, NBm, NRt), protonF(NRt),
        deutonP(NRm, NBm, NRt), deutonF(NRt)
    { }

    int getNRm() const { return protonP.dimension(0); } 
    int getNBm() const { return protonP.dimension(1); } 
    int getNRt() const { return protonP.dimension(2); } 

    double & Ip(int iRt) { return protonF(iRt); }
    double & Id(int iRt) { return deutonF(iRt); }
    double & Pp(int iRm, int iBm, int iRt) { return protonP(iRm, iBm, iRt); }
    double & Pd(int iRm, int iBm, int iRt) { return deutonP(iRm, iBm, iRt); }

    Eigen::Tensor<double, 2> get_lambda()
    {
        typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;
        Eigen::array<DimPair, 1> indexes{{ DimPair(2, 0) }};
        return protonP.contract(protonF, indexes) +
               deutonP.contract(deutonF, indexes); 
    }
};

class Likelihood
{
    Model m;
    Eigen::Tensor<double, 2> data;
public: 
    Likelihood(int NRm, int NBm, int NRt):
        m( NRm, NBm, NRt), data(NRm, NBm){} 

    double & N(int iRm, int iBm) { return protonP(iRm, iBm, iRt); }

    Model & model() { return m; }
    double logL()
    {
        m.get_lambda()
    }
};
