#ifndef MEPOPERATION_H
#define MEPOPERATION_H

#include "mepoperationtypes.h"

class MEPOperation
{
public:
    MEPOperation(OperationPointsType*, int nParents);
    ~MEPOperation();

    MEPObjectPtr reproduce(const MEPChromosomes, MEPGenerator&);
    int getNParents() const;

private:
    virtual void reproduce(const MEPChromosomes&,
                           MEPGenerator&,
                           const Points&,
                           MEPChromosome&) const = 0;
private:
    OperationPointsType* pointsType_;
    int nParents_;
};

#endif
