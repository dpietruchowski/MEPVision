#include "attributemutation.h"

AttributeMutation::AttributeMutation(OperationPointsType *pointsType):
    MEPMutation(pointsType)
{

}

void AttributeMutation::addMutated(const MEPChromosome &parent,
                                   MEPGenerator &generator,
                                   MEPChromosome &child) const
{
    MEPObjectPtr mutated = generator.createGene();
    const MEPGene& cloned = dynamic_cast<const MEPGene&>
                                    (parent.getObject(child.getSize()));

    std::vector<int> args;
    for(int i = 0; dynamic_cast<MEPGene&> (*mutated).getNArguments(); ++i)
    {
        const MEPObject& clonedChild = parent.find(cloned.getChildId(i));
        int clonedChildNumber = parent.find(clonedChild);
        args.push_back(clonedChildNumber);
    }

    child.MEPComposite::addObject(mutated, args);
}
