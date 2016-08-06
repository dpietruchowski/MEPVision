#include "meppopulation.h"
#include "mepchromosome.h"
#include "fitness/hamming.h"

MEPPopulation::MEPPopulation(const MEPId& id, int initSize):
    MEPComposite(id, initSize)
{

}

MEPPopulation::MEPPopulation(const MEPPopulation& rhs):
    MEPComposite(rhs)
{

}

MEPPopulation& MEPPopulation::operator =(const MEPPopulation& rhs)
{
    MEPPopulation copy(rhs);
    swap(copy);
    return *this;
}

void MEPPopulation::swap(MEPPopulation& rhs)
{
    MEPComposite::swap(rhs);
}

MEPObjectPtr MEPPopulation::reproduce(MEPSelectionType type,
                                      MEPGenerator &generator,
                                      MEPOperation &operation) const
{
    MEPObjectPtr child = generator.createPopulation();
    MEPComposite& childComposite = dynamic_cast<MEPComposite&> (*child);
    int i = 0;
    while(child->isValid() == false)
    {
        MEPChromosomes parents;
        for(int k = 0; k < operation.getNParents(); ++k)
        {
            const MEPObject& selected = select(type);
            parents.push_back(dynamic_cast<const MEPChromosome&> (selected));
        }

        MEPObjectPtr reproduced = operation.reproduce(parents, generator);
        childComposite.addObject(reproduced);
        i++;
    }

    return child;
}

void MEPPopulation::initComposite(MEPGenerator& generator, int size)
{
    for(int i = 0; i < size; i++)
    {
        std::vector<int> args;
        MEPObjectPtr chromosome = generator.createChromosome();
        dynamic_cast<MEPComposite&> (*chromosome).init(generator);
        addObject(chromosome, args);
    }
}

MEPObjectPtr MEPPopulation::cloneObject() const
{
    return MEPObjectPtr( new MEPPopulation(*this) );
}

void MEPPopulation::cloneCompositeObject(const MEPComposite& rhs,
                                         int objectNumber)
{
    const MEPObject& object = rhs.getObject(objectNumber);
    addObject(object.clone());
}

MEPObjectPtr MEPPopulation::reproduce(MEPSelectionType type,
                                      MEPGenerator &generator) const
{
    MEPObjectPtr child = generator.createPopulation();
    MEPComposite& childComposite = dynamic_cast<MEPComposite&> (*child);

    while(child->isValid() == false)
    {
        MEPObjectPtr chromosome = generator.createChromosome();
        MEPComposite& chromosomeComposite = dynamic_cast<MEPComposite&> (*chromosome);
        while(chromosome->isValid() == false)
        {
            const MEPComposite& selectedChromosome = dynamic_cast<const MEPComposite&>
                                                     (select(type));
            chromosomeComposite.reproduceCompositeObject(selectedChromosome,
                                                         type);
        }
        childComposite.addObject(chromosome);
    }

    return child;
}
