#include "mepgene.h"

#include <utility>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void dynamicCast(MEPObjects &objects, MEPGenes &genes)
{
    for(const auto &obj: objects)
    {
        genes.push_back(dynamic_cast<MEPGene&> (obj.get()));
    }
}


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
    if(isValid() == false)
        children_.push_back(child);
    else
        throw std::string("MEPGene::addChild: Object is valid, cannot add children");
}

void MEPGene::writeObject(std::string& object) const
{
    if(isValid() == false)
        throw std::string("MEPGene::writeObject: Object is invalid");

    int nSpaces = 40 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }

    writeGene(object);
    object += "\n";
    string spaces = "";
    for(int i = 0; i < 6; i++)
    {
        spaces += " ";
    }
}

void MEPGene::writeObjectTree(std::string &object) const
{
    if(isValid() == false)
        throw std::string("MEPGene::writeObject: Object is invalid");

    int nSpaces = 40 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }

    writeGene(object);
    object += "\n";
    string spaces = "";
    for(int i = 0; i < 6; i++)
    {
        spaces += " ";
    }

    for(const auto& child: children_)
    {
        object += spaces;
        object += child.get().write();
    }
}

void MEPGene::showObject(const string& id) const
{
    if(isValid() == false)
        throw std::string("MEPGene::showObject: Object is invalid");

    if(!isValidResults())
        throw std::string("MEPGene::showObject: TU BEDZIE ENUM");
    showGene(id);
}

void MEPGene::showObjectTree(const string& id) const
{
    if(isValid() == false)
        throw std::string("MEPGene::showObjectTree: Object is invalid");

    showObject(id);

    for(const auto& child: children_)
    {
        child.get().showTree();
    }
    cv::waitKey();
}

void MEPGene::runObject()
{
    if(isValid() == false)
        throw std::string("MEPGene::runObject: Object is invalid");

    runGene(children_);
}

void MEPGene::clearObjectResult()
{
    if(isValid() == false)
        throw std::string("MEPGene::clearObjectResult: Object is invalid");

    clearGeneResult();
}

int MEPGene::assessObject(MEPFitness& fitness)
{
    if(isValid() == false)
        throw std::string("MEPGene::assessObject: Object is invalid");

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
    if(isValid() == false)
        throw std::string("MEPGene::cloneObject: Object is invalid");

    return cloneGene();
}

const MEPId& MEPGene::getChildId(int childNumber) const
{
    return children_[childNumber].get().getId();
}
