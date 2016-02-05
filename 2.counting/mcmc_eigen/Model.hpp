#include <cassert>
#include <Eigen/CXX11/Tensor>

class Model
{
    Eigen::Tensor<double, 3> protonP;
    Eigen::Tensor<double, 3> deutonP;

    Eigen::Tensor<double, 1> protonF;
    Eigen::Tensor<double, 1> deutonF;
 
    Eigen::Tensor<double, 2> data;
public:
    Model(int NRm, int NBm, int NRt):
        protonP(NRm, NBm, NRt), protonF(NRt),
        deutonP(NRm, NBm, NRt), deutonF(NRt)
    { }

    Model(const Eigen::Tensor<double, 3> & p, 
          const Eigen::Tensor<double, 3> & d,
          const Eigen::Tensor<double, 3> & N):
        protonP(p), protonF(p.dimension(2)),
        deutonP(d), deutonF(d.dimension(2)),
        data(N)
    { 
        assert(p.dimension(0) == d.dimension(0));
        assert(p.dimension(1) == d.dimension(1));
        assert(N.dimension(0) == p.dimension(0));
        assert(N.dimension(1) == p.dimension(1));
    }

    int getNRm() const { return protonP.dimension(0); } 
    int getNBm() const { return protonP.dimension(1); } 
    int getNRt() const { return protonP.dimension(2); } 

    double & fluxP(int iRt) { return protonF(iRt); }
    double & fluxD(int iRt) { return deutonF(iRt); }

    Eigen::Tensor<double, 2> lambda()
    {
        typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;
        Eigen::array<DimPair, 1> indexes{{ DimPair(2, 0) }};
        return protonP.contract(protonF, indexes) +
               deutonP.contract(deutonF, indexes); 
    }

    double logL()
    {
        auto l = lambda();
        return (l*data.log() - l).sum();
    }

    double gradLogL_protons()
    {
        typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;
        Eigen::array<DimPair, 2> indexes{{ DimPair(0, 0), DimPair(1, 1) }};
        return (data/lambda() - 1).contract(protonP, indexes);
    }

    double gradLogL_deutons()
    {
        typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;
        Eigen::array<DimPair, 2> indexes{{ DimPair(0, 0), DimPair(1, 1) }};
        return (data/lambda() - 1).contract(deutonP, indexes);
    }

};
