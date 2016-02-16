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
    Eigen::Tensor<double, 3> deutonP(NRm, NBm, NRt);
    std::vector<double> tp {
        0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.1, 0.0, 0.0,  
        0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.1, 0.0, 0.0, 0.0, /**/ 0.0, 0.1, 0.5, 0.1, 0.0,  
        0.1, 0.0, 0.0, 0.0, 0.0, /**/ 0.1, 0.6, 0.1, 0.0, 0.0, /**/ 0.0, 0.1, 0.1, 0.0, 0.0,  
        0.7, 0.1, 0.0, 0.0, 0.0, /**/ 0.0, 0.1, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0,  
        0.1, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0,  
    };
    for(int i = 0; i < tp.size(); i++) protonP( i/(NBm*NRt) , (i%(NBm*NRt))%NBm , (i%(NBm*NRt))/NBm) = tp[i];

    std::vector<double> td {
        0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0,  
        0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.1, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.1,  
        0.0, 0.0, 0.1, 0.0, 0.0, /**/ 0.0, 0.0, 0.1, 0.6, 0.1, /**/ 0.0, 0.0, 0.0, 0.1, 0.5,  
        0.0, 0.1, 0.6, 0.1, 0.0, /**/ 0.0, 0.0, 0.0, 0.1, 0.0, /**/ 0.0, 0.0, 0.1, 0.0, 0.1,  
        0.0, 0.0, 0.1, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0, /**/ 0.0, 0.0, 0.0, 0.0, 0.0,  
    };
    for(int i = 0; i < td.size(); i++) deutonP( i/(NBm*NRt) , (i%(NBm*NRt))%NBm , (i%(NBm*NRt))/NBm) = td[i];
 
    // Print the two tensors
    std::cout << std::fixed;
    std::cout.precision(1);

    std::cout << "\nProton resolution matrices \n";
    std::cout << protonP << "\n";
    std::cout << "\nDeuton resolution matrices \n";
    std::cout << deutonP << "\n";

    // Compute and print template normalizations
    // Reduction indices   
    Eigen::array<ptrdiff_t, 2> reduction_axes = {{0,1}};
    std::cout << " sum(protonP) = {" << protonP.sum(reduction_axes) << "}\n";
    std::cout << " sum(deutonP) = {" << deutonP.sum(reduction_axes) << "}\n";

    // Declaring and filling the two flux vectors
    Eigen::Tensor<double, 1> protonF(NRt); protonF(0) = 10; protonF(1) = 5;  protonF(2) = 1;
    Eigen::Tensor<double, 1> deutonF(NRt); deutonF(0) =  5; deutonF(1) = 2 ; deutonF(2) = 1;

    // Printing the vectors 
    std::cout << "\n";
    std::cout << "Proton  flux = { " << protonF << "}\n";
    std::cout << "Deueron flux = { " << deutonF << "}\n";
    std::cout << "\n";
    
    // Making two contractions 
    Eigen::array<DimPair, 1> indexes{{ DimPair(2, 0) }};
    Eigen::Tensor<double, 2> protonL = protonP.contract(protonF, indexes);
    Eigen::Tensor<double, 2> deutonL = deutonP.contract(deutonF, indexes);
        
    //Adding 
    Eigen::Tensor<double, 2> lambda = protonL + deutonL;

    //Printing the prediction matrix
    std::cout << "Predicted counts: \n";
    std::cout << lambda;

    return 0;
}



