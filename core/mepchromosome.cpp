#include "mepchromosome.h"

#include "mepgene.h"

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

void MEPChromosome::initComposite(MEPGenerator& generator, int size)
{
    for(int i = 0; i < 2; i++)
    {
        MEPObjectPtr gene;
        while(dynamic_cast<MEPGene&>(*gene).getNArguments() == 0)
            gene = generator.create(*this);
        addObject(gene);
    }
    for(int i = 0; i < size; i++)
    {
        MEPObjectPtr gene = generator.create(*this);
        addObject(gene);
        Arguments args;
        for(int k = 0; k < dynamic_cast<MEPGene&>(*gene).getNArguments(); k++)
        {
            int childNumber = rand() % i;
            args.push_back(childNumber);
        }
    }
}

MEPObjectPtr MEPChromosome::cloneObject() const
{
    return MEPObjectPtr( new MEPChromosome(*this) );
}
