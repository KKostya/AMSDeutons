#include "TObject.h"

class mapClass : public TObject{
public:
    std::map<std::string, unsigned int> mapNameEntryNo;
    int val;
    mapClass();
    ~mapClass();
    ClassDef(mapClass, 1); // the class title
};
