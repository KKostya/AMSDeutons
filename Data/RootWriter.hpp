#ifndef ROOTWRITER_H
#define ROOTWRITER_H

#include <vector>
#include <TTree.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

#include "Provenance.h"
#include "Geo.h"
#include "Tracker.h"
#include "Ecal.h"
#include "TOF.h"
#include "TRD.h"
#include "RICH.h"
#include "MC.h"
#include "SelectionStatus.h"

class AMSEventR;
typedef std::vector<void (*)(AMSEventR *)> ROOTDataList;

void AddProvenanceVariables(ROOTDataList & data, TTree * tree);
void AddGeoVariables(ROOTDataList & data, TTree * tree);
void AddTrackerVariables(ROOTDataList & data, TTree * tree);
void AddECALVariable(ROOTDataList & data, TTree * tree);
void AddTRDVariables(ROOTDataList & data, TTree * tree);
void AddTOFVariables(ROOTDataList & data, TTree * tree);

void AddMCVariables(ROOTDataList & data, TTree * tree);

void AddSelectionVariables(ROOTDataList & data, TTree * tree);

#endif //ROOTWRITER_H
