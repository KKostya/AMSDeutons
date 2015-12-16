#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <getopt.h>

#include <TFile.h>
#include <TTree.h>
#include <TLeafD.h>




void MakeFile(const std::string & fname)
{
    // Open ROOT and create a tree
    TFile * tfile = new TFile(fname.c_str(), "RECREATE");
    TTree * ttree = new TTree("data", "data");
    ttree->Write();
    tfile->Close();
    delete tfile;
}

void BinFileToBranch(
    const std::string & rootFile, 
    const std::string &  binFile, 
    const std::string &  varName, 
    const std::string &  varType,
    int vsize )
{
    std::ifstream file( binFile, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (file.read(buffer.data(), size))
    {
        TFile * tfile = new TFile(rootFile.c_str(), "UPDATE");
        TTree * ttree = (TTree*)tfile->Get("data");

        TBranch * branch = ttree->Branch(varName.c_str(), 0, varType.c_str());
        for(int i = 0; i < size/vsize; i++)
        {
            branch->SetAddress((void *)&buffer[vsize*i]);
            ttree->Fill();
        }
        ttree->Write(0, TObject::kOverwrite);
        tfile->Close();
        delete tfile;
    }

}


std::map<std::string, std::string> rootTypeKeys = {
    {      "char", "B"},
    {     "short", "S"},
    {       "int", "I"}, {       "unsigned int", "i"},
    {     "float", "F"},
    {    "double", "D"}, 
    { "long long", "L"}, { "unsigned long long", "l"}
};


int main(int argc, char **argv)
{
    int c;
    std::string outFname, indirName;
    while((c = getopt(argc, argv, "o:i:")) != -1) {
        if(c == 'o') outFname  = std::string(optarg);
        if(c == 'i') indirName = std::string(optarg);
    }

    std::cout << outFname <<  "  " << indirName << "\n";
    
    if(  outFname == "")  outFname = "test.root";
    if( indirName == "") indirName = "test";

    MakeFile(outFname);

    std::string str;
    std::fstream metadata(indirName + "/metadata.txt");
    while(std::getline(metadata, str))
    {
        std::stringstream ss(str); 

        // Get first word and check it doesnt end with a colon
        std::string vname; 
        ss >> vname;
        if(vname.back() == ':') continue;

        // Get the size in bytes
        int size = 0;
        ss >> size;

        // Read the type of a variable
        std::string type;
        char skip;
        ss.get(skip);
        std::getline(ss, type);
   
        // Add the branch to root 
        std::cout << "Adding variable \"" << vname << "\" (" 
                  << rootTypeKeys[type]  << ":" 
                  << size << ") ... ";
        BinFileToBranch( outFname, 
            indirName  + "/" + vname + "_chunk0.bin", 
            vname, vname + "/" + rootTypeKeys[type], size
        );
        std::cout << " done.\n";
    }
}
