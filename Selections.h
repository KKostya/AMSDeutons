#include <string>
#include <vector>
#include "SubSelection.hpp"
#include "Data.h"


std::vector< SubSelection<Data &> *> GetListOfSelections();
bool Quality(Data &data);

std::vector<SubSelection<Data &> *> GetListOfBandCuts();
bool Belt(Data &data);
