#ifndef SELECTIONSTATUS_H
#define SELECTIONSTATUS_H
#include <stdint.h>
#include <sstream> 
#include <bitset>

// AMS includes #ifndef _PGTRACK_
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

#include "../Selections/SelectionLists.hpp"

//typedef std::bitset<64> bitField_t;

unsigned long long selStatus(AMSEventR * ev);
TBits selStatus2(AMSEventR * ev);
std::string GetSelectionNames();

#endif //SELECTIONSTATUS_H
