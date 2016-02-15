#include <vector>
#include <iostream>
#include <Model.hpp>


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

    // Declaring and filling the two flux vectors
    Eigen::Tensor<double, 1> protonF(NRt); protonF(0) = 10; protonF(1) = 5;  protonF(2) = 1;
    Eigen::Tensor<double, 1> deutonF(NRt); deutonF(0) =  5; deutonF(1) = 2 ; deutonF(2) = 1;

    // Finally, some data 
    Eigen::Tensor<double, 2> data(NRm, NBm);

    std::vector<double> tt {
        0.0, 0.0, 0.1, 0.0, 0.0, 
        0.0, 0.6, 0.5, 0.3, 0.1, 
        1.5, 3.1, 1.3, 1.3, 0.7, 
        7.0, 2.0, 3.1, 0.7, 0.1, 
        1.0, 0.0, 0.5, 0.0, 0.0, 
    };
    for(int i = 0; i < tt.size(); i++) data(i/NBm,i%NBm) = tt[i];

    data = data + 0.1;

    std::cout << data << "\n";

    Model model(protonP, deutonP, data);

    Model::FluxType fluxP(3), fluxD(3);
    fluxP(0) = 10; fluxD(0) = 5;
    fluxP(1) =  5; fluxD(1) = 2;
    fluxP(2) =  2; fluxD(2) = 1;

    std::cout << model.logL(fluxP, fluxD) << "\n\n";
    std::cout << model.gradLogL_protons(fluxP, fluxD) << "\n\n";
    std::cout << model.gradLogL_deutons(fluxP, fluxD) << "\n\n";
}


