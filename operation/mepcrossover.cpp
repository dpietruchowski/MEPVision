#include "mepcrossover.h"

MEPCrossover::MEPCrossover(OperationPointsType* pointsType):
    MEPOperation(pointsType, 2)
{

}

void MEPCrossover::reproduce(const MEPChromosomes &parents,
                             MEPGenerator &,
                             const Points &points,
                             MEPChromosome &child) const
{
    child.clonePart(parents[1].get(), 0, points[0] - 1);
    int nPoints = static_cast<int> (points.size());
    for(int i = 0; i < nPoints - 1; ++i)
    {
        child.clonePart(parents[i%2].get(), points[i], points[i+1] - 1);
    }
    child.clonePart(parents[(nPoints-1)%2].get(), points[(nPoints-1)],
                    parents[(nPoints-1)%2].get().getSize());
}

