#ifndef GRAD_OPTIMIZER_H
#define GRAD_OPTIMIZER_H

#include <vector>
#include <iostream>
#include <Model.hpp>

class GradOptimizer: public Model
{
    int iterations;
    double epsilon;
    bool verbose;
    FluxType protonF;
    FluxType deutonF;

public:
    GradOptimizer(const Model & m, const FluxType & fluxP, const FluxType & fluxD):
        Model(m), protonF(fluxP), deutonF(fluxD), 
        epsilon(0.001), iterations(10), verbose(true) { }

    void run()
    {
        std::cout << "Gradient optimizer with:\n";
        std::cout << "  epsilon = " << epsilon << "\n";
        std::cout << "  iterations = " << iterations << "\n";
        std::cout << "Running...";
        std::cout.flush();

        auto epsilonP = protonF.constant(epsilon);
        auto epsilonD = deutonF.constant(epsilon);
        for(int i=0; i<iterations; i++)
        {

            protonF += epsilonP * gradLogL_protons(protonF,deutonF);
            deutonF += epsilonD * gradLogL_deutons(protonF,deutonF);

            if(verbose) {
                std::cout << "I = " << i << " Current logL = " << logL(protonF, deutonF) << "\n";
                //std::cout << "P = " << protonF << "\n";
                //std::cout << "D = " << deutonF << "\n";
            }
        }
        std::cout << "finished.\n";
    }

    void SetIterations(int i) { iterations = i; }
    void SetEpsilon(double e) { epsilon = e; }

    const FluxType & GetProtonFlux()   const { return protonF; }
    const FluxType & GetDeuteronFlux() const { return deutonF; }
};
#endif
