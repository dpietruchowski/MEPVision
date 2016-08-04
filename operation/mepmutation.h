#ifndef MEPMUTATION_H
#define MEPMUTATION_H

#include "mepoperation.h"

class MEPMutation : public MEPOperation
{
public:
    MEPMutation(OperationPointsType*);
private:
    void reproduce(const MEPChromosomes&, MEPGenerator&,
                   const Points&, MEPChromosome&) const;
    virtual void addMutated(const MEPChromosome&, MEPGenerator&,
                            MEPChromosome&) const = 0;
};

#endif // MEPMUTATION_H
