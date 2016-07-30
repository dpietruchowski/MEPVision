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
}

void MEPGene::swap(MEPGene& rhs)
{
    MEPObject::swap(rhs);
    children_.swap(rhs.children_);
}

void MEPGene::addChild(MEPGene& child)
{
    if(!isValid())
        children_.push_back(child);
    else
        throw "Object is valid, cannot add children";
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
        child.get().write(object);
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
        child.get().showTree();
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
    if(!isValid())
        throw "Object is invalid";

    return cloneGene();
}

const MEPId& MEPGene::getChildId(int childNumber) const
{
    return children_[childNumber].get().getId();
}
