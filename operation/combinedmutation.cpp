#include "combinedmutation.h"

CombinedMutation::CombinedMutation(OperationPointsType *pointsType):
    MEPMutation(pointsType)
{

}

void CombinedMutation::addMutated(const MEPChromosome &,
                                  MEPGenerator & generator,
                                  MEPChromosome &child) const
{
    MEPObjectPtr mutated = generator.createGene();
    std::vector<int> args;
    for(int i = 0; dynamic_cast<MEPGene&> (*mutated).getNArguments(); ++i)
    {
        args.push_back(std::rand() % child.getSize());
    }

    child.MEPComposite::addObject(mutated, args);
}
