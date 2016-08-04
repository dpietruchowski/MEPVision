#include "meppopulation.h"
#include "mepchromosome.h"

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
    for(int i = 0; i < childComposite.getSize(); ++i)
    {
        MEPChromosomes parents;
        for(int k = 0; k < operation.getNParents(); ++k)
        {
            parents.push_back(dynamic_cast<const MEPChromosome&> (select(type)));
        }

        MEPObjectPtr reproduced = operation.reproduce(parents, generator);
        childComposite.addObject(reproduced);
    }
}

void MEPPopulation::initComposite(MEPGenerator& generator, int size)
{
    for(int i = 0; i < size; i++)
    {
        std::vector<int> args;
        MEPObjectPtr chromosome = generator.createChromosome();
        chromosome->init(generator);
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

    for(int i = 0; i < childComposite.getSize(); ++i)
    {
        MEPObjectPtr chromosome = generator.createChromosome();
        MEPComposite& chromosomeComposite = dynamic_cast<MEPComposite&> (*chromosome);
        for(int k = 0; k < chromosomeComposite.getSize(); ++k)
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
