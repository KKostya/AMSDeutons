# Root utils for statistics stuff 

## Getting the code
Currently the code lives in the `eigen-tools` branch of the common repository     

    git clone https://github.com/KKostya/AMSDeutons.git
    cd AMSDeutons
    git checkout eigen-tools

## Compilation
To compile we first need do download the Eigen C++ library. There is a cript for that:

    source setup_eigen.sh

Now just type: 

    source enable
    make

## Using from ROOT
If everything went well, you sould have a `TIsotopesMCMC.so` file ready. We can try using it
durectly from ROOT. 

There is a small `mkroot.C` script that prepares several 5X5  matices for 
templates and data. Launch root and execute it first
    
    root [0] .X mkroot.C 

Now you have two 3D histograms `TH3D * p` and  `TH3D * d` containing proton and
deuteron templates and also the `TH2D * t` histogram containing the data to
fit.  Lets load the library and create the object passing those histograms to it:

    root [1] .L TIsotopesMCMC.so 
    root [2] mcmc = new TIsotopesMCMC(p,d,t)

The fitting will start as soon as you request the result

    root [3] pf = mcmc->GetProtonFlux()
    Gradient optimizer with:
    epsilon = 0.001
    iterations = 100000
    Running...finished.
    (class TH1D *) 0x3637570
    root [4] pf->Draw()
    Info in <TCanvas::MakeDefCanvas>:  created default TCanvas with name c1

