#ifndef STEADYSTATEALGORITHM_H
#define STEADYSTATEALGORITHM_H

#include "mepalgorithm.h"

class SteadyStateAlgorithm : public MEPAlgorithm
{
public:
    SteadyStateAlgorithm();
public:
    double registerCrossover(double probability, OperationType type);
    double registerMutation(double probability, OperationType type);
    void setFitnessType(FitnessType type);

private:
    virtual void runAlgorithm(int i, MEPFitness* fitness,
                              MEPGenerator& generator, Stats& stats);
    virtual void setNMutatedGene(int size);


private:
    FitnessType fitnessType_;
    MEPOperationGenerator crossoverGenerator_;
    MEPOperationGenerator mutationGenerator_;
    double sumProCrossover_;
    double sumProMutation_;
};

#endif // STEADYSTATEALGORITHM_H
