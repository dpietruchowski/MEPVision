#ifndef ATTRIBUTEMUTATION_H
#define ATTRIBUTEMUTATION_H

#include "mepmutation.h"

class AttributeMutation : public MEPMutation
{
public:
    AttributeMutation(OperationPointsType*);
private:
    void addMutated(const MEPChromosome&, MEPGenerator&, MEPChromosome&) const;
};

class RandAttributeMutation: public AttributeMutation
{
public:
    static MEPOperation* create();
    RandAttributeMutation(int nMutatedPoints):
        AttributeMutation(new RandomPoints(nMutatedPoints)) {}
};

class WorstAttributeMutation: public AttributeMutation
{
public:
    WorstAttributeMutation(int nMutatedPoints):
        AttributeMutation(new WorstPoints(nMutatedPoints)) {}
};

class UniformAttributeMutation: public AttributeMutation
{
public:
    UniformAttributeMutation():
        AttributeMutation(new UniformPoints()) {}
};

#endif // ATTRIBUTEMUTATION_H
