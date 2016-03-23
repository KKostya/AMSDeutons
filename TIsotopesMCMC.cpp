#include <Eigen/CXX11/Tensor>
#include "TIsotopesMCMC.hpp"
#include <Model.hpp>
#include <GradOptimizer.hpp>
#include "RootUtils.hpp"

class TIsotopesImpl
{
    double maxX, maxY, maxZ;
    double minX, minY, minZ;
    Model  * model; 
    TH1D * protonF, * deutonF;

    int nsteps;
    double eps;

    bool performed_fit;
public:
    TIsotopesImpl(TH3D * protonP, TH3D * deutonP, TH2D * data):
        performed_fit(false), nsteps(10), eps(0.0001)
    {
        Eigen::Tensor<double, 3> pP = root_to_tensor(protonP);
        Eigen::Tensor<double, 3> dP = root_to_tensor(deutonP);
        Eigen::Tensor<double, 2> dt = root_to_tensor(data);

        minX = protonP->GetXaxis()->GetXmin();
        minY = protonP->GetYaxis()->GetXmin();
        minZ = protonP->GetZaxis()->GetXmin();
        maxX = protonP->GetXaxis()->GetXmax();
        maxY = protonP->GetYaxis()->GetXmax();
        maxZ = protonP->GetZaxis()->GetXmax();

        model = new Model(pP, dP, dt);
        protonF = new TH1D("fluxP", "Unfolded proton flux",   model->getNRt(), minZ, maxZ);
        deutonF = new TH1D("fluxD", "Unfolded deuteron flux", model->getNRt(), minZ, maxZ);
        for(int i=0; i < model->getNRt() + 2; i++) protonF->SetBinContent( i, 1.0);
        for(int i=0; i < model->getNRt() + 2; i++) deutonF->SetBinContent( i, 1.0);
    }

    double GetLogLikelihood(TH1D * p, TH1D * d)
    {
        return model->logL(root_to_tensor(p), root_to_tensor(d));
    }

    TH1D * GetProtonFlux(){ if(!performed_fit) Run(nsteps, eps); return protonF; } 
    TH1D * GetDeutonFlux(){ if(!performed_fit) Run(nsteps, eps); return deutonF; } 

    void NormalizeTemplates() { model->NormalizeTemplates(); }

    void Run(int n, double epsilon) {
        performed_fit = true;
        nsteps = n;
        eps = epsilon;
        
        Eigen::Tensor<double, 1> fluxP = root_to_tensor(protonF);
        Eigen::Tensor<double, 1> fluxD = root_to_tensor(deutonF);

        GradOptimizer opt(*model, fluxP, fluxD);
        opt.run(eps, nsteps);

        tensor_to_root(opt.GetProtonFlux(),   protonF);
        tensor_to_root(opt.GetDeuteronFlux(), deutonF);
    }

    TH2D * GetProtonTemplate(int n) {
        TH2D * ret = new TH2D("","",model->getNRm(), minX, maxX, model->getNBm(), minY, maxY);
        tensor_to_root(model->getProtonTemplate(n), ret);
        return ret;
    }

    TH2D * GetDeutonTemplate(int n) {
        TH2D * ret = new TH2D("","",model->getNRm(), minX, maxX, model->getNBm(), minY, maxY);
        tensor_to_root(model->getDeutonTemplate(n), ret);
        return ret;
    }

    TH2D * GetPredicted() {
        if(!performed_fit) Run(nsteps, eps);
        TH2D * ret = new TH2D("","",model->getNRm(), minX, maxX, model->getNBm(), minY, maxY);

        Eigen::Tensor<double, 1> fluxP = root_to_tensor(protonF);
        Eigen::Tensor<double, 1> fluxD = root_to_tensor(deutonF);

        tensor_to_root(model->lambda(fluxP, fluxD), ret);

        return ret;

    }
};


TIsotopesMCMC::TIsotopesMCMC(TH3D * protonP, TH3D * deutonP, TH2D * data)
{
    pImpl = new TIsotopesImpl(protonP, deutonP, data);
}
TIsotopesMCMC::~TIsotopesMCMC(){ delete pImpl; }

double TIsotopesMCMC::GetLogLikelihood(TH1D * p, TH1D * d){ return pImpl->GetLogLikelihood(p,d); }


TH1D * TIsotopesMCMC::GetProtonFlux()     { return pImpl->GetProtonFlux(); }
TH1D * TIsotopesMCMC::GetDeutonFlux()     { return pImpl->GetDeutonFlux(); }
void   TIsotopesMCMC::NormalizeTemplates(){ pImpl->NormalizeTemplates();   }
void   TIsotopesMCMC::Run(int n, double epsilon){ pImpl->Run(n, epsilon);   }
TH2D * TIsotopesMCMC::GetProtonTemplate(int n){ return pImpl->GetProtonTemplate(n); }
TH2D * TIsotopesMCMC::GetDeutonTemplate(int n){ return pImpl->GetDeutonTemplate(n); }
TH2D * TIsotopesMCMC::GetPredicted(){ return pImpl->GetPredicted();}

ClassImp(TIsotopesMCMC)
