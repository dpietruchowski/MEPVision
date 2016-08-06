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
    if(points.size() == 0)
    {
        child.clonePart(parents[1].get(), 0, parents[1].get().getSize() - 1);
        return;
    }

    child.clonePart(parents[1].get(), 0, points[0] - 1);
    int nPoints = static_cast<int> (points.size());
    for(int i = 0; i < nPoints - 1; ++i)
    {
        child.clonePart(parents[i%2].get(), points[i], points[i+1] - 1);
    }
    child.clonePart(parents[abs(nPoints-1)%2].get(), points[(nPoints-1)],
                    parents[abs(nPoints-1)%2].get().getSize() - 1);
}


MEPOperation *TwoPointCrossover::create()
{
    return new TwoPointCrossover();
}

MEPOperation *OnePointCrossover::create()
{
    return new OnePointCrossover();
}

MEPOperation *UniformCrossover::create()
{
    return new UniformCrossover();
}
