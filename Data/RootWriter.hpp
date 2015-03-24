#include <vector>
#include <TTree.h>
class AMSEventR;
typedef std::vector<void (*)(AMSEventR *)> ROOTDataList;

void AddProvenanceVariables(ROOTDataList & data, TTree * tree);
void AddGeoVariables(ROOTDataList & data, TTree * tree);
void AddTrackerVariables(ROOTDataList & data, TTree * tree);
void AddTRDVariables(ROOTDataList & data, TTree * tree);
void AddTOFVariables(ROOTDataList & data, TTree * tree);

void AddMCVariables(ROOTDataList & data, TTree * tree)

void AddSelectionVariables(ROOTDataList & data, TTree * tree);
