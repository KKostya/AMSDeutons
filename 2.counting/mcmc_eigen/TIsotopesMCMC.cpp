#include <Eigen/CXX11/Tensor>
#include "TIsotopesMCMC.hpp"
#include <Model.hpp>
#include <GradOptimizer.hpp>
#include "RootUtils.hpp"

class TIsotopesImpl
{
    double min, max;
    Model  * model; 
    TH1D * protonF, * deutonF;

    bool performed_fit;
    void run(){
        performed_fit = true;
        
        Eigen::Tensor<double, 1> fluxP(model->getNRt());
        Eigen::Tensor<double, 1> fluxD(model->getNRt());

        GradOptimizer opt(*model, fluxP.setConstant(1), fluxD.setConstant(1));
        opt.run();

        protonF = new TH1D("fluxP", "Unfolded proton flux",   fluxP.dimension(0), min, max);
        deutonF = new TH1D("fluxD", "Unfolded deuteron flux", fluxD.dimension(0), min, max);

        tensor_to_root(opt.GetProtonFlux(), protonF);
        tensor_to_root(opt.GetDeuteronFlux(), deutonF);
    }
public:
    TIsotopesImpl(TH3D * protonP, TH3D * deutonP, TH2D * data):
        performed_fit(false)
    {
        Eigen::Tensor<double, 3> pP = root_to_tensor(protonP);
        Eigen::Tensor<double, 3> dP = root_to_tensor(deutonP);
        Eigen::Tensor<double, 2> dt = root_to_tensor(data);

        min = protonP->GetZaxis()->GetXmin();
        max = protonP->GetZaxis()->GetXmax();
        model = new Model(pP, dP, dt);
    }

    double GetLogLikelihood(TH1D * p, TH1D * d)
    {
        return model->logL(root_to_tensor(p), root_to_tensor(d));
    }

    TH1D * GetProtonFlux(){
        if(!performed_fit) run();
        return protonF;
    } 

    TH1D * GetDeutonFlux(){
        if(!performed_fit) run();
        return deutonF;
    } 
};


TIsotopesMCMC::TIsotopesMCMC(TH3D * protonP, TH3D * deutonP, TH2D * data)
{
    pImpl = new TIsotopesImpl(protonP, deutonP, data);
}
TIsotopesMCMC::~TIsotopesMCMC(){ delete pImpl; }

double TIsotopesMCMC::GetLogLikelihood(TH1D * p, TH1D * d){ return pImpl->GetLogLikelihood(p,d); }
TH1D * TIsotopesMCMC::GetProtonFlux()   { return pImpl->GetProtonFlux(); }
TH1D * TIsotopesMCMC::GetDeutonFlux()   { return pImpl->GetDeutonFlux(); }

ClassImp(TIsotopesMCMC)
