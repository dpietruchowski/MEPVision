#include "mepoperationgenerator.h"

MEPOperationGenerator::MEPOperationGenerator()
{

}

MEPOperation *MEPOperationGenerator::createRandomPtr()
{
    CreationCounter<CreateObjectFunction> counter = generator_.createRandom();
    CreateObjectFunction function = counter.callbackFunction;

    return function();
}

void MEPOperationGenerator::registerObject(double probability, MEPOperationGenerator::CreateObjectFunction function)
{
    generator_.registerCallback(probability, function);
}

