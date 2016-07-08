#ifndef MEPPOPULATION_H
#define MEPPOPULATION_H

#include "mepcomposite.h"

//TODO Implement function
class MEPPopulation : public MEPComposite
{
public:
    MEPPopulation(const MEPId&, int initSize);
    MEPPopulation(const MEPPopulation&);
    MEPPopulation& operator =(const MEPPopulation&);
    void swap(MEPPopulation&);

private:
    void initComposite(MEPGenerator&, int size);
    MEPObjectPtr cloneObject() const;
};

#endif // MEPPOPULATION_H
