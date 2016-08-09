#include "argumentmutation.h"

ArgumentMutation::ArgumentMutation(OperationPointsType *pointsType):
    MEPMutation(pointsType)
{

}

void ArgumentMutation::addMutated(const MEPChromosome &parent,
                                  MEPGenerator &,
                                  MEPChromosome &child) const
{
    MEPObjectPtr mutated = parent.findByOrder(child.getSize()).clone();

    std::vector<int> args;
    for(int i = 0; i < dynamic_cast<MEPGene&> (*mutated).getNArguments(); ++i)
    {
        args.push_back(std::rand() % child.getSize());
    }

    child.MEPComposite::addObject(mutated, args);
}

MEPOperation *RandArgumentMutation::create(int nMutatedPoints)
{
    return new RandArgumentMutation(nMutatedPoints);
}

MEPOperation *UniformArgumentMutation::create(int)
{
    return new UniformArgumentMutation();
}

MEPOperation *WorstArgumentMutation::create(int nMutatedPoints)
{
    return new WorstArgumentMutation(nMutatedPoints);
}
