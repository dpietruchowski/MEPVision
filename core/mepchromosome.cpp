#include "mepchromosome.h"
#include "mepgene.h"

MEPChromosome::MEPChromosome(const MEPId& id, int initSize):
    MEPComposite(id, initSize)
{

}

MEPChromosome::MEPChromosome(const MEPChromosome& rhs):
    MEPComposite(rhs)
{

}

MEPChromosome& MEPChromosome::operator =(const MEPChromosome& rhs)
{
    MEPChromosome copy(rhs);
    swap(copy);
    return *this;
}

void MEPChromosome::swap(MEPComposite& rhs)
{
    MEPComposite::swap(rhs);
    swap(rhs);
}

void MEPChromosome::initComposite(MEPGenerator& generator, int size)
{
    for(int i = 0; i < 2; i++)
    {
        MEPObjectPtr gene;
        while(dynamic_cast<MEPGene&>(*gene).getNArguments() == 0)
            gene = generator.create(*this);
        addObject(gene);
    }
    for(int i = 0; i < size; i++)
    {
        MEPObjectPtr gene = generator.create(*this);
        addObject(gene);
        for(int k = 0; k < dynamic_cast<MEPGene&>(*gene).getNArguments(); k++)
        {
    	int childNumber = rand() % i;
            addChild(dynamic_cast<MEPGene&>(*gene), childNumber);
        }
    }
}

MEPObjectPtr MEPChromosome::cloneObject() const
{
    return MEPObjectPtr( new MEPChromosome(*this) );
}

void MEPChromosome::cloneCompositeObject(const MEPComposite& rhs,
    									 const MEPObject& object,
                                         const Objects& objects)
{
    MEPObjectPtr clone = object.clone();

    int geneNumber = getSize();
    for(int i = 0; i < dynamic_cast<const MEPGene&>(object).getNArguments(); i++)
    {
        int objectArg = rhs.find(rhs.find(dynamic_cast<const MEPGene&>(object).getChildId(i)));
        int argDiff = rhs.find(object) - objectArg;
    	int arg = 0;
    	if(argDiff < geneNumber)
    		arg = geneNumber - argDiff;

        dynamic_cast<MEPGene&> (*clone).addChild(dynamic_cast<MEPGene&>(*objects[arg]));
    }

    addObject(clone);
}
