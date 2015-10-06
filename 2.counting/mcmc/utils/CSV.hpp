#ifndef _CSV__H_
#define _CSV__H_

#include "generalUtils.hpp"
#include "Matrix.hpp"

namespace CSV {
    std::vector<float> getRow(float & first, std::string str)
    {
        std::stringstream ss(str);
        std::vector<float> row;
        std::string entry;
        float value;

        getline(ss, entry, ',');


        {
            std::stringstream se(entry);
            if(!(se >> first)) first = 0;
        }

        while (getline(ss, entry, ','))
            {
                std::stringstream se(entry);
                if(!(se >> value)) value = 0;
                row.push_back(value);
            }

        return row;
    }

    MatrixF getMatrixAndBins( std::fstream & fs, 
                              std::vector<float>& binsT, std::vector<float>& binsM )
    {
        float first;
        std::string line;
        std::vector< std::vector<float> > data;

        getline(fs,line);
        binsM = getRow(first, line);
        binsT.clear();

        while (getline(fs,line))
            {
                data.push_back(getRow(first, line));
                binsT.push_back(first);
            }

        MatrixF M(binsT.size()-1, binsM.size()-1);
        M.Fill(data);

        return M;
    }

    MatrixB getMask(const std::string & fname, int nRows, int nColumns){
        std::vector<std::string> rows = generalUtils::splitIntoLines( generalUtils::exec("cat " + fname) );
        if(rows.size() == 0){
            std::cerr << "WARNING in CSV.hpp:getMask" << std::endl;
            std::cerr << "Unable to read file: " << fname << std::endl;
            std::cerr << "Exit !" << std::endl;
            exit(-1);
        }

        if(rows.size() != nRows){
            std::cerr << "WARNING in CSV.hpp:getMask" << std::endl;
            std::cerr << "Row mismatch: expected (" <<nRows<< ") got (" << rows.size() << ") for mask file: " << fname << std::endl;
            std::cerr << "Exit !" << std::endl;
            exit(-1);
        }

        std::vector< std::vector<bool> > data;
        for(int i = 0;i<rows.size();i++){
            std::vector<bool> vec = generalUtils::stringTo<bool>(generalUtils::split(rows[i],","));
            if(vec.size() != nColumns){
                std::cerr << "WARNING in CSV.hpp:getMask" << std::endl;
                std::cerr << "Column mismatch: expected (" <<nColumns<< ") got (" << vec.size() << ") for mask file: " << fname << std::endl;
                std::cerr << "Exit !" << std::endl;
                exit(-1);
            }
            data.push_back(vec);
        }
    
        MatrixB output(nRows, nColumns);
        output.Fill<std::vector< std::vector<bool> > >(data);
        return output;
    }
}

#endif //CSV_H

