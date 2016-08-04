#include "mepobjectgenerator.h"
#include <iostream>
using namespace std;

MEPObjectGenerator::MEPObjectGenerator():
    objectCounter_(0)
{
}

MEPObjectPtr MEPObjectGenerator::createRandomPtr()
{
    CreationCounter<CreateObjectFunction> counter = generator_.createRandom();
    CreateObjectFunction function = counter.callbackFunction;

    MEPObjectPtr object = function(objectCounter_);
    objectCounter_++;
    return object;
}

void MEPObjectGenerator::registerObject(double probability, CreateObjectFunction function)
{
    generator_.registerCallback(probability, function);
}
