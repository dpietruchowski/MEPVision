#include "mepchromosome.h"
#include "mepgene.h"

void dynamicCast(MEPObjects &objects, MEPChromosomes &chromosomes)
{
    for(const auto &obj: objects)
    {
        chromosomes.push_back(dynamic_cast<MEPChromosome&> (obj.get()));
    }
}

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
}

void MEPChromosome::initComposite(MEPGenerator& generator, int size)
{
    for(int i = 0; i < 2; i++)
    {
        MEPObjectPtr gene;
        gene = generator.createGene();
        while(dynamic_cast<MEPGene&>(*gene).getNArguments() != 0)
            gene = generator.createGene();
        MEPComposite::addObject(gene);
    }
    for(int i = 2; i < size; i++)
    {
        MEPObjectPtr gene = generator.createGene();
        std::vector<int> args;
        for(int k = 0; k < dynamic_cast<MEPGene&>(*gene).getNArguments(); k++)
        {
            int childNumber = rand() % i;
            args.push_back(childNumber);
        }
        MEPComposite::addObject(gene, args);
    }
}

MEPObjectPtr MEPChromosome::cloneObject() const
{
    MEPObjectPtr cloned( new MEPChromosome(*this) );
    dynamic_cast<MEPComposite&>(*cloned).clonePart(*this, 0, getSize() - 1);

    return cloned;
}

void MEPChromosome::cloneCompositeObject(const MEPComposite& rhs,
                                         int objectNumber)
{
    const MEPObject& object = rhs.findByOrder(objectNumber);
    MEPObjectPtr clone = object.clone();

    int geneNumber = getSize();
    std::vector<int> args;
    for(int i = 0; i < dynamic_cast<const MEPGene&>(object).getNArguments(); i++)
    {
        int objectArg = rhs.find(rhs.findById(dynamic_cast<const MEPGene&>(object).getChildId(i)));
        int argDiff = rhs.find(object) - objectArg;
    	int arg = 0;
    	if(argDiff < geneNumber)
    		arg = geneNumber - argDiff;
        args.push_back(arg);
    }

    MEPComposite::addObject(clone, args);
}

MEPObjectPtr MEPChromosome::reproduce(MEPSelectionType type,
                                      MEPGenerator &generator,
                                      double probability) const
{
    MEPObjectPtr chromosome = generator.createChromosome();
    MEPComposite& chromosomeComposite = dynamic_cast<MEPComposite&> (*chromosome);
    for(int i = 0; i < 2; i++)
    {
        MEPObjectPtr gene;
        gene = generator.createGene();
        while(dynamic_cast<MEPGene&>(*gene).getNArguments() != 0)
            gene = generator.createGene();
        chromosomeComposite.addObject(gene);
    }
    while(chromosome->isValid() == false)
    {
        double random = (double)std::rand() / (RAND_MAX);
        if(random < probability)
        {
            MEPObjectPtr gene;
            gene = generator.createGene();
            std::vector<int> args;
            for(int i = 0;
                i < dynamic_cast<MEPGene&>(*gene).getNArguments();
                ++i)
                args.push_back(std::rand() % chromosomeComposite.getSize());
            chromosomeComposite.addObject(gene, args);
        } else
        {
            const MEPComposite& selectedChromosome = dynamic_cast<const MEPComposite&>
                                                     (select(type));
            chromosomeComposite.reproduceCompositeObject(selectedChromosome,
                                                         type);
        }
    }

    return chromosome;
}

void MEPChromosome::addObject(Objects& genes,
                              MEPObject& gene,
                              std::vector<int>& args)
{
    for(int i = 0; i < dynamic_cast<const MEPGene&>(gene).getNArguments(); ++i)
    {
        if(args[i] > getSize())
            throw std::string("MEPChromosome::addObject: Cannot add child, argument > size");
        dynamic_cast<MEPGene&>(gene).addChild(dynamic_cast<MEPGene&>(*genes[args[i]]));
    }
}
