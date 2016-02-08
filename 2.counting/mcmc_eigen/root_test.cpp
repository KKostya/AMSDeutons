#include <vector>
#include <iostream>
#include <TH2F.h>
#include <TF2.h>
#include <Eigen/CXX11/Tensor>

#include "RootUtils.hpp"

int main(void)
{

    TH2F * h   = new TH2F("h","h",10,0.,10.,10,0.,10.);
    TF2  * xyg = new TF2("xyg","xygaus",-2,12,-2,12);
    xyg->SetParameters(1,5,2,5,2);  //amplitude, meanx,sigmax,meany,sigmay
    h->FillRandom("xyg");


    std::cout << "Without overfow:\n";
    Eigen::Tensor<float,2> t = root_to_tensor(h);
    std::cout << t << "\n";

    std::cout << "\nWith overfow:\n";
    Eigen::Tensor<float,2> q = root_to_tensor(h, true);
    std::cout << q << "\n";

    std::cout << "\nSum = " << q.sum() << "\n";
    
    return 0;
}



