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
    RandArgumentMutation(int nMutatedPoints):
        ArgumentMutation(new RandomPoints(nMutatedPoints)) {}
};

class WorstArgumentMutation: public ArgumentMutation
{
public:
    WorstArgumentMutation(int nMutatedPoints):
        ArgumentMutation(new WorstPoints(nMutatedPoints)) {}
};

class UniformArgumentMutation: public ArgumentMutation
{
public:
    UniformArgumentMutation():
        ArgumentMutation(new UniformPoints()) {}
};

#endif // ARGUMENTMUTATION_H
