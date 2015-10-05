#ifndef PD_MODEL_H
#define PD_MODEL_H
#include <vector>
#include <functional>
#include <iostream>
#include <regex>
#include <tuple>
#include <limits>

#include "Matrix.hpp"
#include "SearchSpace.hpp"

std::vector< std::pair<float,float> > getLogDerivative(const std::vector< std::pair<float, float> > & point);
std::ostream& operator<<(std::ostream& os, const SearchSpace& point);

class ModelBase
{
protected:
    std::vector<float*> spectatorVariables;
    SearchSpace realValues;
    SearchSpace initialConditions;
public:
    ModelBase() : spectatorVariables(),realValues(), initialConditions(){}

    // ModelBase(const ModelBase & original):
    //     realValues(original.realValues),
    //     initialConditions(original.initialConditions){}

    virtual ~ModelBase(){}


    virtual float GetLogLikelihood(const SearchSpace & point) = 0;
    virtual void saveMetaData(std::ofstream & ){}
    virtual void endOfAlgoAction(const std::string & filename, const SearchSpace & point){}

    const SearchSpace GetRealValues(){ return realValues; }
    const SearchSpace GetInitialConditions(){ return initialConditions; }
};

class PDModel: public ModelBase
{
    std::vector<MatrixF> matrixBase;
    std::vector<float> betaBinsT, betaBinsM;
    std::vector<float> rgdtBinsT, rgdtBinsM;
    MatrixF rgdtF_transposed,  betaF;
    MatrixF deltaP, deltaD;
    MatrixF observed;

    MatrixB mask;

    float regularizationFactor;
    float regularizationTerm;

    void SetRigidityResolution(const MatrixF & matrix);
    void SetBetaResolution    (const MatrixF & matrix);

    void init();

    // save predicted matrix for SearchSpace 'point' in file 'filename'
    void savePredictedMatrix(const SearchSpace & point, const std::string & filename);

public:
    static const float mp;
    static const float md;

    // Initializations 
    PDModel( const std::vector<float> & bT, const std::vector<float> & bM, 
             const std::vector<float> & rT, const std::vector<float> & rM,
             const MatrixF & betaF, const MatrixF & rgdtF, const MatrixB & mask);

    PDModel( const std::vector<float> & bT, const std::vector<float> & bM, 
             const std::vector<float> & rT, const std::vector<float> & rM,
             const std::vector<MatrixF> & betaVsRig, const MatrixB & mask);

    virtual ~PDModel(){}

    static PDModel FromCSVS(const std::string & betaFile, const std::string & rgdtFile, const std::string & maskFile, int maxTrueBinNumber = 0 );
    static PDModel FromCSVSBiDim(const std::vector<std::string> & matricesFiles, const std::string & maskFile);
    static PDModel FromCSVSBiDim(const std::string & firstFileName, int nFiles, const std::string & maskFile );

    // Getters
    inline std::vector<float> getBetaBinsT(){ return betaBinsT; }
    inline std::vector<float> getBetaBinsM(){ return betaBinsM; }
    inline std::vector<float> getRgdtBinsT(){ return rgdtBinsT; }
    inline std::vector<float> getRgdtBinsM(){ return rgdtBinsM; }
    float regularizationTermAccessor(){ return regularizationTerm; }

    // Predictions
    MatrixF GetPrediction(const SearchSpace & point);
    
    // Perform a linear combination of base matrices
    MatrixF GetPredictionFast(const SearchSpace & point);
    
    // Log likelihood
    virtual float GetLogLikelihood(const SearchSpace & point) override;
    
    // Gradient of Log likelihood
    SearchSpace GetLogLikelihoodGradient(const SearchSpace & point);

    // Regularization term
    void ComputeRegularizationTerm(const SearchSpace & point);
    
    void setRegularizationFactor(float _regularizationFactor){
        this -> regularizationFactor = _regularizationFactor;
    }
    
    // Observed
    void LoadObservedDataFromFile(const std::string & fname);
    MatrixF getObservedDataFromFile(const std::string & fname);
    
    void GenerateToyObservedData(const SearchSpace & point){
        observed = GetPrediction(point);
    }

    void endOfAlgoAction(const std::string & filename, const SearchSpace & point) override {
        savePredictedMatrix(point, filename+"/lastPointPredictedMatrix.txt");
    }

    void SetMask(const std::string & maskFile);
    void SetMask(const MatrixB & _mask);
};

#endif //PD_MODEL_H

