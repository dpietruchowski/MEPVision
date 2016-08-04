#ifndef MEPCHROMOSOME_H
#define MEPCHROMOSOME_H

#include "mepcomposite.h"

#include <vector>

class MEPChromosome;
typedef std::vector<std::reference_wrapper<const MEPChromosome>> MEPChromosomes;
//TODO Implement initialize function
class MEPSHARED_EXPORT MEPChromosome : public MEPComposite
{
public:
    MEPChromosome(const MEPId&, int initSize);
    MEPChromosome(const MEPChromosome&);
    MEPChromosome& operator =(const MEPChromosome&);
    void swap(MEPComposite&);

private:
    virtual void addObject(Objects&, MEPObject&, std::vector<int>&);
    void initComposite(MEPGenerator&, int size);
    MEPObjectPtr cloneObject() const;
    void cloneCompositeObject(const MEPComposite& rhs,
                              int objectNumber);
    MEPObjectPtr reproduce(MEPSelectionType, MEPGenerator&) const;
};

void dynamicCast(MEPObjects &objects, MEPChromosomes &chromosomes);

#endif // MEPCHROMOSOME_H
