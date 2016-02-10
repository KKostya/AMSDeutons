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

    Model(const Eigen::Tensor<double, 3> & p, 
          const Eigen::Tensor<double, 3> & d,
          const Eigen::Tensor<double, 2> & N):
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
        typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;
        Eigen::array<DimPair, 1> indexes{{ DimPair(2, 0) }};
        auto l = protonP.contract(protonF, indexes) + deutonP.contract(deutonF, indexes); 
        auto z    = l.constant(0);                       // This is needed to cut away the log of zeros
        auto llog = ( l > z ).select(l.log(), z);        // "select" is the t_if.select(t_then,t_else)
        Eigen::Tensor<double, 2> ll  = data*llog - l;    // Here evaluation is forced
        Eigen::Tensor<double, 0> res = ll.sum();         // The sum returns 0-rank tensor. 
        return res();                                    // 0-tensor call to operator() without aruments to get the value
    }

    Eigen::Tensor<double, 1> gradLogL_protons()
    {
        typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;
        Eigen::array<DimPair, 1> indexesL {{ DimPair(2, 0) }};
        auto l = protonP.contract(protonF, indexesL) + deutonP.contract(deutonF, indexesL); 
        auto one = l.constant(1);                         // 
        auto z   = l.constant(0);                         // This is to avoid division by zero 
        auto ds  = ( l > z ).select(data/l - one, z);     // "select" is the t_if.select(t_then,t_else)
 
        Eigen::array<DimPair, 2> indexesG {{ DimPair(0, 0), DimPair(1, 1) }};
        return ds.contract(protonP, indexesG);
    }

    Eigen::Tensor<double, 1> gradLogL_deutons()
    {
        typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;
        Eigen::array<DimPair, 1> indexesL {{ DimPair(2, 0) }};
        auto l = protonP.contract(protonF, indexesL) + deutonP.contract(deutonF, indexesL); 
        auto one = l.constant(1);                         // 
        auto z   = l.constant(0);                         // This is to avoid division by zero 
        auto ds  = ( l > z ).select(data/l - one, z);     // "select" is the t_if.select(t_then,t_else)
 
        Eigen::array<DimPair, 2> indexesG {{ DimPair(0, 0), DimPair(1, 1) }};
        return ds.contract(deutonP, indexesG);
    }
};
