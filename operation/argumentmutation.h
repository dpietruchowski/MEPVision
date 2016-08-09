#ifndef ARGUMENTMUTATION_H
#define ARGUMENTMUTATION_H

#include "mepmutation.h"

class ArgumentMutation : public MEPMutation
{
public:
    ArgumentMutation(OperationPointsType*);
private:
    void addMutated(const MEPChromosome&, MEPGenerator&, MEPChromosome&) const;
};

class RandArgumentMutation: public ArgumentMutation
{
public:
    static MEPOperation* create(int nMutatedPoints);
    RandArgumentMutation(int nMutatedPoints):
        ArgumentMutation(new RandomPoints(nMutatedPoints)) {}
};

class WorstArgumentMutation: public ArgumentMutation
{
public:
    static MEPOperation* create(int nMutatedPoints);
    WorstArgumentMutation(int nMutatedPoints):
        ArgumentMutation(new WorstPoints(nMutatedPoints)) {}
};

class UniformArgumentMutation: public ArgumentMutation
{
public:
    static MEPOperation* create(int);
    UniformArgumentMutation():
        ArgumentMutation(new UniformPoints()) {}
};

#endif // ARGUMENTMUTATION_H
