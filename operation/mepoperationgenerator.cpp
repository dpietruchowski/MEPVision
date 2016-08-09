#include "mepoperationgenerator.h"

MEPOperationGenerator::MEPOperationGenerator()
{

}

void MEPOperationGenerator::setMaxNMutatedGene(int maxNMutatedGene)
{
    maxNMutatedGene_ = maxNMutatedGene;
}

MEPOperation *MEPOperationGenerator::createRandomPtr()
{
    CreationCounter<CreateObjectFunction> counter = generator_.createRandom();
    CreateObjectFunction function = counter.callbackFunction;

    return function(1 + std::rand() % (maxNMutatedGene_ - 1));
}

void MEPOperationGenerator::registerObject(double probability, MEPOperationGenerator::CreateObjectFunction function)
{
    generator_.registerCallback(probability, function);
}

