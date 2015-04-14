#include "SelectionStatus.h"

SelectionList selections;
SelectionList GetSelectionList()
{
    if(selections.size() == 0)
    {
        AddGeoSelections    (selections);
        AddGoldenSelections (selections);
        AddMinBiasSelections(selections);
        AddPreSelections    (selections);
        AddRICHSelections   (selections);
    }
    return selections;
}
unsigned long long selStatus(AMSEventR * ev)
{
    SelectionList selections = GetSelectionList();
    unsigned long long ret = 0;
    for(int nsel=0; nsel<selections.size(); nsel++)
        if(selections[nsel].cutFunction(ev))
            ret += 1LLU << nsel;

    return ret;
}

TBits selStatus2(AMSEventR * ev)
{
    TBits bits;

    SelectionList selections = GetSelectionList();
    unsigned long long ret = 0;
    for(int nsel=0; nsel<selections.size(); nsel++)
        if(selections[nsel].cutFunction(ev)){ 
            bits.SetBitNumber(nsel,true);
        }
    
    return bits;
}

std::string GetSelectionNames()
{
    SelectionList selections = GetSelectionList();
   
    std::stringstream ss;
    ss << selections[0].name;
    for(int nsel=1; nsel<selections.size(); nsel++)
        ss << "," << selections[nsel].name;
    return ss.str();
}
