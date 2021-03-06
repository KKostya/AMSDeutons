#ifndef _DSTAMSBINARY__CPP_
#define _DSTAMSBINARY__CPP_

#include "DstAmsBinary.hpp"

using namespace rootUtils;

void DstAmsBinary::init(){
    maxRootFiles = 0;
    setOutputFile(false);
    Loop::init();

    
    registerVariables();
    nVar = variables.size();
    
    std::size_t memConsumption = 0;
    for(int iVar = 0; iVar < nVar; iVar++) memConsumption += variables[iVar] -> getSize();
    chunkSize = maxRAM / memConsumption;

    std::cout << "chunkSize : " << chunkSize << std::endl;

    if(outputFileName == "")     outputFileName = generalUtils::getFileNameWithoutExtension(data[0]);

    if( mkdir(outputFileName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0){
        int i = 0;
        while( mkdir( (outputFileName+generalUtils::toString(i)).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0 ){
            i++;
        }
        outputFileName = outputFileName+generalUtils::toString(i);
    }
    
    for(int iVar = 0; iVar < nVar; iVar++) variables[iVar] -> allocArray(chunkSize);

}

bool DstAmsBinary::process(){
    initPointers();
    for( int i = 0; i<nVar; i++){
        variables[i] -> assign(chunkStepNumber);
    }

    chunkStepNumber++;
    if( chunkStepNumber >= chunkSize) saveChunk();
}

void DstAmsBinary::end(){
    if( chunkStepNumber > 0 ) saveChunk();
    saveMetaData(outputFileName+"/metadata.txt");
    if( outFileType == kZippedCsvForBigQuery ){
        for(int chunk = 0; chunk < chunkNumber; chunk++) system(Form("gzip %s/%s_chunk%i.csv", outputFileName.c_str(), outputFileName.c_str(), + chunk));
    }
}

void DstAmsBinary::saveChunk(){
    std::cout << "saving chunk" << std::endl;
    std::cout << "var.size() : " << nVar << std::endl;

    if(outFileType == kCsvForBigQuery || outFileType == kZippedCsvForBigQuery ){
        std::ofstream myfile( outputFileName +"/"+ outputFileName + Form("_chunk%i", chunkNumber) + ".csv" );
        for(int step = 0; step < chunkStepNumber; step++){
            std::stringstream line;
            for(int iVar = 0; iVar < nVar; iVar++) variables[iVar] -> append( line, step);
            myfile << line.str().substr(0, line.str().size()-1) << std::endl; // Removing trailing coma
        }
        myfile.close();
    }else{
        for(int iVar = 0; iVar < nVar; iVar++){
            variables[iVar] -> save(outputFileName, chunkNumber, chunkStepNumber, outFileType);
        }
    }

    chunkStepNumber = 0;
    chunkNumber++;
}

void DstAmsBinary::saveMetaData(std::string filename)
{
    std::ofstream myfile( filename, std::ios::out);
    myfile << "nVar: "           << nVar          << std::endl;
    myfile << "chunkSize: "      << chunkSize     << std::endl;
    for(int iVar=0; iVar < nVar; iVar++){
        variables[iVar] -> writeMetaData(myfile);
    }
    myfile.close();
}

int DstAmsBinary::cutEvent(){
    return false;
}


template <typename T> std::string getType(){ std::cout << "Unknown specialization" << std::endl; exit(-1); }
template <> std::string getType<float>(){ return "float"; }
template <> std::string getType<unsigned long long>(){ return "unsigned long long"; }
template <> std::string getType<double>(){ return "double"; }
template <> std::string getType<unsigned int>(){ return "unsigned int"; }
template <> std::string getType<int>(){ return "int"; }

template struct Container<double>;
template struct Container<float>;
template struct Container<int>;
template struct Container<unsigned int>;
template struct Container<unsigned long long>;
#endif


