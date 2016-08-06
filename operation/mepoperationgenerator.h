#ifndef MEPOPERATIONGENERATOR_H
#define MEPOPERATIONGENERATOR_H

#include "mepoperation.h"
#include "../generator/generator.h"

class MEPOperationGenerator
{
public:
    typedef MEPOperation* (*CreateObjectFunction)();
public:
    MEPOperationGenerator();
public:
    MEPOperation* createRandomPtr();
    void registerObject(double probability, CreateObjectFunction function);
private:
    Generator<CreateObjectFunction> generator_;
};

#endif // MEPOPERATIONGENERATOR_H
