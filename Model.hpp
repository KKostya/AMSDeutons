#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <cassert>
#include <Eigen/CXX11/Tensor>

class Model
{
    // Optimizators are impletmented as some classes inheriting from the Model
    // In order to have direct access to those tensors -- I make them protected
protected: 
    Eigen::Tensor<double, 3> protonP;
    Eigen::Tensor<double, 3> deutonP;

    Eigen::Tensor<double, 2> data;
public:
    typedef Eigen::Tensor<double, 1> FluxType;

    Model(const Eigen::Tensor<double, 3> & p, 
          const Eigen::Tensor<double, 3> & d,
          const Eigen::Tensor<double, 2> & N):
        protonP(p), deutonP(d), data(N)
    { 
        assert(p.dimension(0) == d.dimension(0));
        assert(p.dimension(1) == d.dimension(1));
        assert(N.dimension(0) == p.dimension(0));
        assert(N.dimension(1) == p.dimension(1));
    }

    int getNRm() const { return protonP.dimension(0); } 
    int getNBm() const { return protonP.dimension(1); } 
    int getNRt() const { return protonP.dimension(2); } 

    Eigen::Tensor<double, 2> lambda(const FluxType & protonF, const FluxType & deutonF) const
    {
        typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;
        Eigen::array<DimPair, 1> indexes{{ DimPair(2, 0) }};
        return protonP.contract(protonF, indexes) +
               deutonP.contract(deutonF, indexes); 
    }

    double logL(const FluxType & protonF, const FluxType & deutonF) const
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

    Eigen::Tensor<double, 1> gradLogL_protons(const FluxType & protonF, const FluxType & deutonF) const
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

    Eigen::Tensor<double, 1> gradLogL_deutons(const FluxType & protonF, const FluxType & deutonF)
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

    void NormalizeTemplates()
    {
        for(int i = 0; i < protonP.dimension(2); i++ )
        {
            Eigen::Tensor<double,0> d = protonP.chip(i, 2).sum();
            //std::cout << "#TP = " << i << " sum= " << d() << "\n";
            if( d() == 0 ) continue;
            protonP.chip(i,2) = protonP.chip(i, 2) * protonP.chip(i, 2).constant(1/d());
        }
        for(int i = 0; i < deutonP.dimension(2); i++ )
        {
            Eigen::Tensor<double,0> d = deutonP.chip(i, 2).sum();
            //std::cout << "#TD = " << i << " sum= " << d() << "\n";
            if( d() == 0 ) continue;
            deutonP.chip(i,2) = deutonP.chip(i, 2) * deutonP.chip(i, 2).constant(1/d());
        }
    }

    Eigen::Tensor<double, 2> getProtonTemplate(int n) { return protonP.chip(n, 2); }
    Eigen::Tensor<double, 2> getDeutonTemplate(int n) { return deutonP.chip(n, 2); }
};

#endif
