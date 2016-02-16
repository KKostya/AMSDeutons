#include <vector>
#include <iostream>
#include <TH2F.h>
#include <TF2.h>
#include <Eigen/CXX11/Tensor>

#include "RootUtils.hpp"

int main(void)
{

    TH2D * h   = new TH2D("h","h",10,0.,10.,10,0.,10.);
    TF2  * xyg = new TF2("xyg","xygaus",-2,12,-2,12);
    xyg->SetParameters(1,5,2,5,2);  //amplitude, meanx,sigmax,meany,sigmay
    h->FillRandom("xyg");


    std::cout << "Without overfow:\n";
    Eigen::Tensor<double,2> t = root_to_tensor(h);
    std::cout << t << "\n";

    std::cout << "\nWith overfow:\n";
    Eigen::Tensor<double,2> q = root_to_tensor(h, true);
    std::cout << q << "\n";

    std::cout << "\nSum = " << q.sum() << "\n";
    
    Eigen::array<ptrdiff_t, 1> reduction_axes = {{0}};
    std::cout << "Sum over 0th axis: \n";
    std::cout << q.sum(reduction_axes) << "\n";

    std::cout << "Convert to TH1D and print: \n";
    Eigen::Tensor<double,1> s = q.sum(reduction_axes);
    TH1D * hist = new TH1D("h","h", s.dimension(0),0,10);
    tensor_to_root(s, hist, true);

    std::cout << "TH1D: ";
    for(int i=1; i<hist->GetNbinsX()-1; i++) {std::cout << hist->GetBinContent(i) << ", "; }
    std::cout << "\n";

    return 0;
}



