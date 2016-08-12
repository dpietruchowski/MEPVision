#ifndef GENERATIONALALGORITHM_H
#define GENERATIONALALGORITHM_H

#include "mepalgorithm.h"

class GenerationalAlgorithm : public MEPAlgorithm
{
public:
    GenerationalAlgorithm();
public:
    double registerOperation(double probability, OperationType type);

private:
    virtual void runAlgorithm(int i, MEPFitness* fitness,
                              MEPGenerator& generator, Stats& stats);
    virtual void setNMutatedGene(int size);

private:
    MEPOperationGenerator operationGenerator_;
    double sumProOperation_;
};

#endif // GENERATIONALALGORITHM_H
