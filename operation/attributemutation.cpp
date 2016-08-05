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

    int mutatedNArguments = dynamic_cast<MEPGene&> (*mutated).getNArguments();
    int clonedNArguments = cloned.getNArguments();
    int higherNArguments = mutatedNArguments > clonedNArguments ?
                            mutatedNArguments : clonedNArguments;
    int lowerNArguments = mutatedNArguments < clonedNArguments ?
                            mutatedNArguments : clonedNArguments;

    for(int i = 0; i < lowerNArguments; ++i)
    {
        const MEPObject& clonedChild = parent.find(cloned.getChildId(i));
        int clonedChildNumber = parent.find(clonedChild);
        args.push_back(clonedChildNumber);
    }

    for(int i = lowerNArguments; i < higherNArguments; ++i)
    {
        int clonedChildNumber = std::rand() % child.getSize();
        args.push_back(clonedChildNumber);
    }

    child.MEPComposite::addObject(mutated, args);
}
