#include "argumentmutation.h"

ArgumentMutation::ArgumentMutation(OperationPointsType *pointsType):
    MEPMutation(pointsType)
{

}

void ArgumentMutation::addMutated(const MEPChromosome &parent,
                                  MEPGenerator &,
                                  MEPChromosome &child) const
{
    MEPObjectPtr mutated = parent.getObject(child.getSize()).clone();

    std::vector<int> args;
    for(int i = 0; i < dynamic_cast<MEPGene&> (*mutated).getNArguments(); ++i)
    {
        args.push_back(std::rand() % child.getSize());
    }

    child.MEPComposite::addObject(mutated, args);
}

MEPOperation *RandArgumentMutation::create()
{
    return new RandArgumentMutation(1 + rand() % 10);
}
