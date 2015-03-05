typedef bool (*CutFunction)(AMSEventR *);
typedef bool std::vector<std::pair<std::string, CutFunction> > SelectionList;

void AddGeoSelections(SelectionList & selections);
void AddGoldenSelections(SelectionList & selections);
void AddMinBiasSelections(SelectionList & selections);
void AddPreSelections(SelectionList & selections);

void AddOldRICHSelections(SelectionList & selections);
void AddRICHSelections(SelectionList & selections);
