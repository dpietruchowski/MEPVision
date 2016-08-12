#include "meppopulation.h"
#include "mepchromosome.h"
#include "fitness/hamming.h"
#include <iostream>

using namespace std;

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
                                MEPOperationGenerator &operationGenerator,
                                Stats& stats,
                                MEPFitness *fitness) const
{
    MEPObjectPtr child = generator.createPopulation();
    MEPComposite& childComposite = dynamic_cast<MEPComposite&> (*child);
    int i = 0;
    const MEPComposite& best = dynamic_cast<const MEPComposite&>(findByRank(0));
    MEPObjectPtr bestClone = best.clone();
    childComposite.addObject(bestClone);
    while(child->isValid() == false)
    {
        MEPOperation *operation = operationGenerator.createRandomPtr();

        MEPChromosomes parents;
        if(operation->getNParents() == 1)
            stats.nMutation++;
        else
            stats.nCrossover++;

        int parentBestFitness = 10000000;
        for(int k = 0; k < operation->getNParents(); ++k)
        {
            const MEPObject& selected = select(type);
            if(selected.getScore() < parentBestFitness)
                parentBestFitness = selected.getScore();
            stats.selectionRank[selected.getRank()] ++;
            parents.push_back(dynamic_cast<const MEPChromosome&> (selected));
        }

        MEPObjectPtr reproduced = operation->reproduce(parents, generator);

        reproduced->run(*fitness);
        int offspringFitness = reproduced->getScore();

        if(offspringFitness < parentBestFitness)
            if(operation->getNParents() == 1)
                stats.nBetterAfterMutation++;
            else
                stats.nBetterAfterCrossover++;

        childComposite.addObject(reproduced);

        i++;
        delete operation;
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
    MEPObjectPtr cloned( new MEPPopulation(*this) );
    dynamic_cast<MEPComposite&>(*cloned).clonePart(*this, 0, getSize() - 1);

    return cloned;
}

void MEPPopulation::cloneCompositeObject(const MEPComposite& rhs,
                                         int objectNumber)
{
    const MEPObject& object = rhs.findByOrder(objectNumber);
    addObject(object.clone());
}
