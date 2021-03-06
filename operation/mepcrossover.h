#ifndef MEPCROSSOVER_H
#define MEPCROSSOVER_H

#include "mepoperation.h"

class MEPCrossover : public MEPOperation
{
public:
    MEPCrossover(OperationPointsType*);
private:
    void reproduce(const MEPChromosomes&, MEPGenerator&,
                   const Points&, MEPChromosome&) const;
};

class UniformCrossover : public MEPCrossover
{
public:
    static MEPOperation* create(int);
    UniformCrossover(): MEPCrossover(new UniformPoints()) {}
};

class BetterGeneCrossover : public MEPCrossover
{
public:
    static MEPOperation* create(int);
    BetterGeneCrossover(): MEPCrossover(new BetterGenePoints()) {}
};

class OnePointCrossover : public MEPCrossover
{
public:
    static MEPOperation* create(int);
    OnePointCrossover(): MEPCrossover(new RandomPoints(2)) {}
};

class TwoPointCrossover : public MEPCrossover
{
public:
    static MEPOperation* create(int);
    TwoPointCrossover(): MEPCrossover(new RandomPoints(1)) {}
};

#endif // MEPCROSSOVER_H
