#ifndef MEPOPERATIONGENERATOR_H
#define MEPOPERATIONGENERATOR_H

#include "mepoperation.h"
#include "../generator/generator.h"

class MEPOperationGenerator
{
public:
    typedef MEPOperation* (*CreateObjectFunction)(int nMutatedGene);
public:
    MEPOperationGenerator();
    void setMaxNMutatedGene(int maxNMutatedGene);
public:
    MEPOperation* createRandomPtr();
    void registerObject(double probability, CreateObjectFunction function);
private:
    Generator<CreateObjectFunction> generator_;
    int maxNMutatedGene_;
};

#endif // MEPOPERATIONGENERATOR_H
