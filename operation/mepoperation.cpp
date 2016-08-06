#include "mepoperation.h"

MEPOperation::MEPOperation(OperationPointsType* pointsType, int nParents):
pointsType_(pointsType), nParents_(nParents)
{
}

MEPOperation::~MEPOperation()
{
    delete pointsType_;
}

int MEPOperation::getNParents() const
{
   return nParents_;
}

MEPObjectPtr MEPOperation::reproduce(const MEPChromosomes parents,
                                     MEPGenerator& generator)
{
    int nParents = static_cast<int> (parents.size());
    if(nParents != nParents_)
        throw std::string("Zla liczba rodzicow");

    MEPObjectPtr child = generator.createChromosome();

    pointsType_->calcPoints(parents);

    reproduce(parents, generator, pointsType_->getOperationPoints(),
              dynamic_cast<MEPChromosome&> (*child));

    return child;
}
