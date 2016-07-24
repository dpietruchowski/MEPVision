#include "mepgene.h"

#include <utility>

using namespace std;

MEPGene::MEPGene(const MEPId& id, int size):
    MEPObject(id), size_(size)
{

}

MEPGene::MEPGene(const MEPGene& rhs):
    MEPObject(rhs)
{
    for(int i = 0; i < static_cast<int> (rhs.children_.size()); i++)
    {
        //Trzeba pomyslec czy dynamic pointer cast nie skasuje nam pozniej obiektu
        children_.push_back(std::dynamic_pointer_cast<MEPGene>
                                (rhs.children_[i]->clone()) );
    }
}

void MEPGene::swap(MEPGene& rhs)
{
    MEPObject::swap(rhs);
    children_.swap(rhs.children_);
}

void MEPGene::writeObject(std::string& object) const
{
	if(!isValid())
		throw "Object is invalid";
		
    writeGene(object);
    object += "\n";
    string spaces = "";
    for(int i = 0; i < 15; i++)
    {
        spaces += " ";
    }
    for(const auto& child: children_)
    {
        object += spaces;
        child->write(object);
        object += "\n";
    }
}

void MEPGene::showObject(const string& id) const
{
	if(!isValid())
		throw "Object is invalid";
		
    if(!isValidResult())
        throw "TU BEDZIE ENUM";
    showGene(id);
}

void MEPGene::showObjectTree(const string& id) const
{
	if(!isValid())
		throw "Object is invalid";
		
    showObject(id);
    for(const auto& child: children_)
    {
        child->showTree();
    }
}

void MEPGene::runObject()
{
	if(!isValid())
		throw "Object is invalid";
		
    runGene(children_);
}

void MEPGene::clearObjectResult()
{
	if(!isValid())
		throw "Object is invalid";
		
    clearGeneResult();
}

int MEPGene::assessObject(MEPFitness& fitness)
{
	if(!isValid())
		throw "Object is invalid";
		
    return assessGene(fitness);
}

bool MEPGene::isValid() const
{
    return size_ == static_cast<int> (children_.size());
}


int MEPGene::getNArguments() const
{
    return size_;
}

MEPObjectPtr MEPGene::cloneObject() const
{
    return cloneGene();
}
