#include <Eigen/CXX11/Tensor>

int main(void)
{
    typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;

    int NRm = 5;
    int NBm = 5;
    int NRt = 5;

    Eigen::Tensor<double, 3> protonP(NRm, NBm, NRt);
    Eigen::Tensor<double, 3> deutonP(NRm, NBm, NRt);

    Eigen::Tensor<double, 1> protonF(NRt);
    Eigen::Tensor<double, 1> deutonF(NRt);
   
    // Making two contractions
    Eigen::array<DimPair, 1> indexes{{ DimPair(2, 0) }};
    Eigen::Tensor<double, 2> protonL = protonP.contract(protonF, indexes);
    Eigen::Tensor<double, 2> deutonL = deutonP.contract(deutonF, indexes);
        
    //Adding 
    Eigen::Tensor<double, 2> lambda = protonL + deutonL;

    return 0;
}



