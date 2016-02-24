#include <vector>
#include <iostream>
#include <Eigen/CXX11/Tensor>

int main(void)
{

    typedef Eigen::Tensor<double, 1>::DimensionPair DimPair;

    int NRm = 5;
    int NBm = 5;
    int NRt = 3;

    // Declare and fill the two tensors
    Eigen::Tensor<double, 3> protonP(NRm, NBm, NRt);
    std::vector<double> td {
        0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0,  
        0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 1.0, 0.0, /**/ 0.0, 0.0, 0.0,   5,  10,  
        0.0, 0.0, 1.0, 0.0, 0.0, /**/ 0.0, 0.0, 1.0, 6.0, 1.0, /**/ 0.0, 0.0, 0.0,  10,  50,  
        0.0, 1.0, 6.0, 1.0, 0.0, /**/ 0.0, 0.0, 0.0, 1.0, 0.0, /**/ 0.0, 0.0,  10,   5,  10,  
        0.0, 0.0, 1.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0,  
    };
    for(int i = 0; i < td.size(); i++) protonP( i/(NBm*NRt) , (i%(NBm*NRt))%NBm , (i%(NBm*NRt))/NBm) = td[i];
 
    // Print the  tensor
    std::cout << std::fixed;
    std::cout.precision(2);

    std::cout << "\nTensor before normalization\n";
    std::cout << protonP << "\n";

    // Normalize the tensor
    for(int i = 0; i < protonP.dimension(2); i++ )
    {
        Eigen::Tensor<double,0> d = protonP.chip(i, 2).sum();
        protonP.chip(i,2) = protonP.chip(i, 2) * protonP.chip(i, 2).constant(1/d());
    }
    std::cout << "\nTensor after the normalization\n";
    std::cout << protonP << "\n";

    
    return 0;
}



