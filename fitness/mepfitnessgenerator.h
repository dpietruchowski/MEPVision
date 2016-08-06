#ifndef MEPFITNESSGENERATOR_H
#define MEPFITNESSGENERATOR_H

#include "../generator/generator.h"
#include "mepfitness.h"

class MEPFitnessGenerator
{
public:
    typedef MEPFitness* (*CreateObjectFunction)();
public:
    MEPFitnessGenerator();
public:
    MEPFitness* createRandomPtr();
    void registerObject(double probability, CreateObjectFunction function);

private:
    Generator<CreateObjectFunction> generator_;
};

#endif // MEPFITNESSGENERATOR_H
