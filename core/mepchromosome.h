#ifndef MEPCHROMOSOME_H
#define MEPCHROMOSOME_H

#include "mepcomposite.h"

#include <vector>

//TODO Implement initialize function
class MEPChromosome : public MEPComposite
{
public:
    MEPChromosome(const MEPId&, int initSize);
    MEPChromosome(const MEPChromosome&);
    MEPChromosome& operator =(const MEPChromosome&);
    void swap(MEPComposite&);

private:
//    void initComposite(MEPGenerator&, int size);
    MEPObjectPtr cloneObject() const;
private:
    typedef std::vector<int> Arguments;
    std::vector<Arguments> objectArguments;
};

#endif // MEPCHROMOSOME_H
