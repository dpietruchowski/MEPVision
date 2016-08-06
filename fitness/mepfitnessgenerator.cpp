#include "mepfitnessgenerator.h"

MEPFitnessGenerator::MEPFitnessGenerator()
{

}

MEPFitness *MEPFitnessGenerator::createRandomPtr()
{
    CreationCounter<CreateObjectFunction> counter = generator_.createRandom();
    CreateObjectFunction function = counter.callbackFunction;

    return function();
}

void MEPFitnessGenerator::registerObject(double probability, MEPFitnessGenerator::CreateObjectFunction function)
{
    generator_.registerCallback(probability, function);
}

