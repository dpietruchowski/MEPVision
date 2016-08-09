#ifndef COMBINEDMUTATION_H
#define COMBINEDMUTATION_H

#include "mepmutation.h"

class CombinedMutation : public MEPMutation
{
public:
    CombinedMutation(OperationPointsType*);
private:
    void addMutated(const MEPChromosome&, MEPGenerator&, MEPChromosome&) const;
};

class RandCombinedMutation: public CombinedMutation
{
public:
    static MEPOperation* create(int nMutatedPoints);
    RandCombinedMutation(int nMutatedPoints):
        CombinedMutation(new RandomPoints(nMutatedPoints)) {}
};

class WorstCombinedMutation: public CombinedMutation
{
public:
    static MEPOperation* create(int nMutatedPoints);
    WorstCombinedMutation(int nMutatedPoints):
        CombinedMutation(new WorstPoints(nMutatedPoints)) {}
};

class UniformCombinedMutation: public CombinedMutation
{
public:
    static MEPOperation* create(int);
    UniformCombinedMutation():
        CombinedMutation(new UniformPoints()) {}
};

#endif // COMBINEDMUTATION_H
