.L TIsotopesMCMC.so

f = new TFile("2012_01_tot_P1.root")
p = (TH3D *)f->Get("MCMCPTemplatesAgl")
d = (TH3D *)f->Get("MCMCDTemplatesAgl")
t = (TH2D *)f->Get("MCMCDataAgl")

mcmc = new TIsotopesMCMC(p,d,t)
mcmc->NormalizeTemplates()
pf = mcmc->GetProtonFlux()
