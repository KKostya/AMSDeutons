#ifndef SELECTIONLISTS_H
#define SELECTIONLISTS_H
#include<vector>

#include <amschain.h>

#include "Geo.h"
#include "Preselect.h"
#include "Golden.h"
#include "MinBias.h"
#include "RICH.h"



struct SelectionItem{
    SelectionItem(std::string _name, bool (*_cutFunction)(AMSEventR* ev)) : name(_name), cutFunction(_cutFunction){}
    std::string name;
    bool (*cutFunction)(AMSEventR * ev);
};

typedef bool (*CutFunction)(AMSEventR *);
typedef std::vector< SelectionItem > SelectionList;


void AddGeoSelections(SelectionList & selections);
void AddGoldenSelections(SelectionList & selections);
void AddMinBiasSelections(SelectionList & selections);
void AddPreSelections(SelectionList & selections);

void AddOldRICHSelections(SelectionList & selections);
void AddRICHSelections(SelectionList & selections);

#endif //SELECTIONLISTS_H
