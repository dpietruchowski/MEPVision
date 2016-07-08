#include "mepchromosome.h"

MEPChromosome::MEPChromosome(const MEPId& id, int initSize):
    MEPComposite(id, initSize)
{

}

MEPChromosome::MEPChromosome(const MEPChromosome& rhs):
    MEPComposite(rhs)
{

}

MEPChromosome& MEPChromosome::operator =(const MEPChromosome& rhs)
{
    MEPChromosome copy(rhs);
    swap(copy);
    return *this;
}

void MEPChromosome::swap(MEPComposite& rhs)
{
    MEPComposite::swap(rhs);
    swap(rhs);
}

//void MEPChromosome::initComposite(MEPGenerator& generator, int size)
//{
//}

MEPObjectPtr MEPChromosome::cloneObject() const
{
    return MEPObjectPtr( new MEPChromosome(*this) );
}
