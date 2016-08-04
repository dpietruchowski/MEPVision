#ifndef MEPGENERATOR_H
#define MEPGENERATOR_H

#include "mepobjectgenerator.h"

class MEPSHARED_EXPORT MEPChromosome;
class MEPSHARED_EXPORT MEPPopulation;
//TODO Register callback to create Chromosome,
//     Function Gene, Terminal Gene, Population.
class MEPSHARED_EXPORT MEPGenerator
{
public:
    MEPGenerator();

    MEPObjectPtr createGene();
    MEPObjectPtr createChromosome();
    MEPObjectPtr createPopulation();

    void registerGene(double probability, MEPObjectGenerator::CreateObjectFunction);
    void registerChromosome(MEPObjectGenerator::CreateObjectFunction);
    void registerPopulation(MEPObjectGenerator::CreateObjectFunction);
private:
    MEPObjectGenerator geneGenerator_;
    MEPObjectGenerator chromosomeGenerator_;
    MEPObjectGenerator populationGenerator_;
};

#endif // MEPGENERATOR_H
