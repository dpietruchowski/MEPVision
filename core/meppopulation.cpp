#include "meppopulation.h"

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

void MEPPopulation::initComposite(MEPGenerator& generator, int size)
{
    for(int i = 0; i < size; i++)
    {
        MEPObjectPtr chromosome = generator.create(*this);
        chromosome->init(generator);
        addObject(chromosome);
    }
}

MEPObjectPtr MEPPopulation::cloneObject() const
{
    return MEPObjectPtr( new MEPPopulation(*this) );
}

void MEPPopulation::cloneCompositeObject(const MEPComposite& rhs,
                                         const MEPObject& object,
                                         const Objects&)
{
    addObject(object.clone());
}
