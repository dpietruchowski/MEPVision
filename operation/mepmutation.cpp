#include "mepmutation.h"

MEPMutation::MEPMutation(OperationPointsType* pointsType):
    MEPOperation(pointsType, 1)
{

}

void MEPMutation::reproduce(const MEPChromosomes &parents,
                            MEPGenerator &generator,
                            const Points &points,
                            MEPChromosome &child) const
{
    const MEPChromosome& parent = parents[0].get();
    child.clonePart(parent, 0, points[0] - 1);
    addMutated(parent, generator, child);

    int nPoints = static_cast<int> (points.size());
    int parentSize = parent.getSize();
    for(int i = 0; i < (nPoints - 1); ++i)
    {
        child.clonePart(parent, points[i] + 1, points[i+1] - 1);
        addMutated(parent, generator, child);
    }
    child.clonePart(parent, points[nPoints - 1] + 1, parentSize - 1);
}

