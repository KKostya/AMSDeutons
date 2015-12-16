#include <fstream>
#include "generalUtils.hpp"

using namespace generalUtils;

int main(int argc, char** argv){
    float threshold = 1000;
    if(argc > 1) threshold = stringTo<float>(argv[1]);
    std::ofstream f("../datasets/mask.csv");

    std::vector<std::string> rows = splitIntoLines( exec("cat ../datasets/observed_data.txt | head -n -1") );
    for( auto &row: rows ){
        auto r = split(row, " ");
        r.pop_back();
        for(auto &val: r){
            f << (stringTo<float>(val) > threshold ? 1 : 0) << ",";
        }
        f << "\n";
    }
    f.close();
}
