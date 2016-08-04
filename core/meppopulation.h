#ifndef MEPPOPULATION_H
#define MEPPOPULATION_H

#include "mepcomposite.h"
#include "../operation/mepoperation.h"

//TODO Implement function
class MEPSHARED_EXPORT MEPPopulation : public MEPComposite
{
public:
    MEPPopulation(const MEPId&, int initSize);
    MEPPopulation(const MEPPopulation&);
    MEPPopulation& operator =(const MEPPopulation&);
    void swap(MEPPopulation&);
    MEPObjectPtr reproduce(MEPSelectionType, MEPGenerator&, MEPOperation&) const;

private:
    void initComposite(MEPGenerator&, int size);
    MEPObjectPtr cloneObject() const;
    void cloneCompositeObject(const MEPComposite& rhs,
                              int objectNumber);
    MEPObjectPtr reproduce(MEPSelectionType, MEPGenerator&) const;

};

#endif // MEPPOPULATION_H
