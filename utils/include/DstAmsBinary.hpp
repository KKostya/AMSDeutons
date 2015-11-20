#ifndef _DSTAMSBINARY__HPP_
#define _DSTAMSBINARY__HPP_

#include <string>
#include <vector>
#include <iostream>
#include <functional>

#include "Loop.hpp"
#include "rootUtils.hpp"
#include "Stack.hpp"

enum OutFileType{
    kBinaryFile,
    kTextFile
};

template <typename T> std::string getType();
template <> std::string getType<float>();
template <> std::string getType<unsigned long long>();
template <> std::string getType<double>();
template <> std::string getType<unsigned int>();
template <> std::string getType<int>();

struct ContainerBase{
    ContainerBase(std::string _name) : name(_name) {}
    std::string name;
    virtual void allocArray(int i) = 0;
    virtual void save(const std::string & outputFileName, int chunkNumber, int chunkStepNumber, const OutFileType & outFileType) = 0;
    virtual void assign(int i) = 0;
    virtual size_t getSize() = 0;
    virtual void writeMetaData(std::ostream & os) = 0;
};



template <typename T, int SIZE = 0 > struct Container : public ContainerBase{
    Container<T,SIZE>(std::string _name, std::function<T()> _f): ContainerBase(_name), f(_f){

    }

    size_t getSize() override {
        return sizeof(T);
    }

    void writeMetaData(std::ostream & os) override {
        os << name << " " << sizeof(T) << " " << getType<T>() << std::endl;
    }


    void allocArray(int size) override {
        var = new T[size];
    }

    std::function<T()> f;
    T *var;

    void assign(int i) override {
        var[i] = f();
    }
    
    void save(const std::string & outputFileName, int chunkNumber, int chunkStepNumber, const OutFileType & outFileType) override {
        std::string extension = ".txt";
        std::ios_base::openmode mode = std::ios::out;

        if(outFileType == kBinaryFile){
            extension = ".bin";
            mode |= std::ios::binary;
        }

        std::string fname( outputFileName +"/" + name + Form("_chunk%i", chunkNumber) + extension);
        std::ofstream myfile( fname, mode);
        std::cout << "fname : " << fname << std::endl;

        if(outFileType == kBinaryFile){
            myfile.write((char*)var, sizeof(T)*chunkStepNumber);
        }else{
            for(int j = 0;j<chunkStepNumber;j++){
                myfile << var[j] << "\n";
            }
        }
        myfile.close();        
    }
};

// Partial specialization for vector<float>
template <int SIZE> struct Container<std::vector<float>, SIZE> : public ContainerBase{
    Container<std::vector<float>,SIZE>(std::string _name, std::function<std::vector<float>() > _f): ContainerBase(_name ), f(_f){
        
    }

    size_t getSize() override {
        return sizeof(float)*SIZE;
    }

    void writeMetaData(std::ostream & os) override {
        for(int i = 0; i < SIZE; i++){
            os << Form("%s_%i",name.c_str(),i) << " " << sizeof(float) << " " << getType<float>() << std::endl;
        }
    }


    void allocArray(int size) override {
        for(int i = 0; i < SIZE; i++){
            var[i] = new float[size];
        }
    }

    std::function<std::vector<float> ()> f;
    float *var[SIZE];

    void assign(int stepNum) override {
        std::vector<float> res = f();
        for(int i = 0; i < SIZE; i++){
            var[i][stepNum] = res[i];
        }
    }
    
    void save(const std::string & outputFileName, int chunkNumber, int chunkStepNumber, const OutFileType & outFileType) override {
        std::string extension = ".txt";
        std::ios_base::openmode mode = std::ios::out;
        if(outFileType == kBinaryFile){
            extension = ".bin";
            mode |= std::ios::binary;
        }

        for(int i = 0; i < SIZE; i++){
            std::string fname( outputFileName +"/" + name + Form("_%i_chunk%i", i, chunkNumber) + extension);
            std::ofstream myfile( fname, mode);
            std::cout << "fname : " << fname << std::endl;

            if(outFileType == kBinaryFile){
                myfile.write((char*)var[i], sizeof(float)*chunkStepNumber);
            }else{
                for(int j = 0;j<chunkStepNumber;j++){
                    myfile << var[i][j] << "\n";
                }
            }
            myfile.close();
        }
    }
};


class DstAmsBinary : public Loop{
public:
    DstAmsBinary( std::vector<std::string> _data, long long _maxRAM ) : Loop(_data),
                                                                  chunkStepNumber(0),
                                                                  maxRAM(_maxRAM),
                                                                  outFileType(kTextFile)
    {}

    DstAmsBinary( std::string _data, long long _maxRAM ) : Loop(_data),
                                                     chunkStepNumber(0),
                                                     maxRAM(_maxRAM),
                                                     outFileType(kTextFile)
    {}

    virtual ~DstAmsBinary(){}
    virtual void registerVariables() = 0;
    virtual void initPointers() = 0;

    void saveChunk();
    void end();
    bool process();
    void init();
    virtual void saveMetaData(std::string filename);
    int cutEvent();
    void setOutFileType(OutFileType outFileType){
        this -> outFileType = outFileType;
    }

protected:
    float p;
    float R;
    bool isMC;
    int nChi2Cut;
    unsigned long long chunkStepNumber;
    unsigned long long chunkSize;
    int nVar;
    long long maxRAM;

    OutFileType outFileType;

    std::vector<ContainerBase*> variables;
};

#endif


