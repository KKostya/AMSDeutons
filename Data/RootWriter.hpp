#include <vector>
#include <TTree.h>
class AMSEventR;
typedef std::vector<void (*)(AMSEventR *)> ROOTDataList;

void AddProvenanceVariables(ROOTDataList & data, TTree * tree);
void AddGeoVariables(ROOTDataList & data, TTree * tree);
//void AddTrackerVariables(ROOTDataList & data, TTree * tree);
