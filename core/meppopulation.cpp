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
                                MEPOperationGenerator &operationGenerator) const
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
        for(int k = 0; k < operation->getNParents(); ++k)
        {
            const MEPObject& selected = select(type);
            parents.push_back(dynamic_cast<const MEPChromosome&> (selected));
        }

        MEPObjectPtr reproduced = operation->reproduce(parents, generator);
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

MEPObjectPtr MEPPopulation::reproduce(MEPSelectionType type,
                                      MEPGenerator &generator,
                                      double probability) const
{
    MEPObjectPtr child = generator.createPopulation();
    MEPComposite& childComposite = dynamic_cast<MEPComposite&> (*child);

    while(child->isValid() == false)
    {
        MEPObjectPtr chromosome = generator.createChromosome();
        MEPComposite& chromosomeComposite = dynamic_cast<MEPComposite&> (*chromosome);
        for(int i = 0; i < 2; i++)
        {
            MEPObjectPtr gene;
            gene = generator.createGene();
            while(dynamic_cast<MEPGene&>(*gene).getNArguments() != 0)
                gene = generator.createGene();
            chromosomeComposite.addObject(gene);
        }
        while(chromosome->isValid() == false)
        {
            double random = (double)std::rand() / (RAND_MAX);
            if(random < probability)
            {
                MEPObjectPtr gene;
                gene = generator.createGene();
                std::vector<int> args;
                for(int i = 0;
                    i < dynamic_cast<MEPGene&>(*gene).getNArguments();
                    ++i)
                    args.push_back(std::rand() % chromosomeComposite.getSize());
                chromosomeComposite.addObject(gene, args);
            } else
            {
                const MEPComposite& selectedChromosome = dynamic_cast<const MEPComposite&>
                                                         (select(type));
                chromosomeComposite.reproduceCompositeObject(selectedChromosome,
                                                             type);
            }
        }
        childComposite.addObject(chromosome);
    }

    return child;
}
