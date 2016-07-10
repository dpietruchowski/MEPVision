#include "mepgenerator.h"

MEPGenerator::MEPGenerator()
{

}

MEPObjectPtr MEPGenerator::create(const MEPChromosome&) //Creates Gene
{
    return geneGenerator_.createRandomPtr();
}

MEPObjectPtr MEPGenerator::create(const MEPPopulation&) //Creates Chromosome
{
    return chromosomeGenerator_.createRandomPtr();
}

MEPObjectPtr MEPGenerator::create() //Creates Population
{
    return populationGenerator_.createRandomPtr();
}

void MEPGenerator::registerGene(double probability,
                                MEPObjectGenerator::CreateObjectFunction func)
{
    geneGenerator_.registerObject(probability, func);
}

void MEPGenerator::registerChromosome(MEPObjectGenerator::CreateObjectFunction func)
{
    chromosomeGenerator_.registerObject(1, func);
}

void MEPGenerator::registerPopulation(MEPObjectGenerator::CreateObjectFunction func)
{
    populationGenerator_.registerObject(1, func);
}
