#include "mepobjectgenerator.h"
#include <iostream>
using namespace std;

MEPObjectGenerator::MEPObjectGenerator()
{
}

MEPObjectPtr MEPObjectGenerator::createRandomPtr()
{
    CreationCounter<CreateObjectFunction> counter = generator_.createRandom();
    CreateObjectFunction function = counter.callbackFunction;

    MEPObjectPtr object = function(counter.nCreation);
    return object;
}

void MEPObjectGenerator::registerObject(double probability, CreateObjectFunction function)
{
    generator_.registerCallback(probability, function);
}
