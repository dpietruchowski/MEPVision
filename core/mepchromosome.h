#ifndef MEPCHROMOSOME_H
#define MEPCHROMOSOME_H

#include "mepcomposite.h"

#include <vector>

//TODO Implement initialize function
class MEPSHARED_EXPORT MEPChromosome : public MEPComposite
{
public:
    MEPChromosome(const MEPId&, int initSize);
    MEPChromosome(const MEPChromosome&);
    MEPChromosome& operator =(const MEPChromosome&);
    void swap(MEPComposite&);

private:
    void initComposite(MEPGenerator&, int size);
    MEPObjectPtr cloneObject() const;
    void cloneCompositeObject(const MEPComposite& rhs,
                              const MEPObject&,
                              const Objects&);
};

#endif // MEPCHROMOSOME_H
