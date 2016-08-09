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
    MEPObject(rhs), size_(rhs.size_)
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

    int nSpaces = 52 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }

    writeGene(object);
}

void MEPGene::writeObjectTree(std::string &object) const
{
    if(isValid() == false)
        throw std::string("MEPGene::writeObject: Object is invalid");

    int nSpaces = 50 - object.size();
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
        object += "\n";
    }
}

void MEPGene::showObject(const string& id)
{
    if(isValid() == false)
        throw std::string("MEPGene::showObject: Object is invalid");

    runGeneTree();

    if(!isValidResults())
        throw std::string("MEPGene::showObject: TU BEDZIE ENUM");
    showGene(id);

    clearObjectResult();
}

//void MEPGene::showObjectTree(const string& id) const
//{
//    if(isValid() == false)
//        throw std::string("MEPGene::showObjectTree: Object is invalid");

//    showObject(id);

//    for(const auto& child: children_)
//    {
//        child.get().showTree();
//    }
//    cv::waitKey();
//}

void MEPGene::runObjectTree()
{
    if(isValid() == false)
        throw std::string("MEPGene::runObject: Object is invalid");

    for(const auto& child: children_)
    {
        child.get().runObjectTree();
    }

    runGene(children_);
}

void MEPGene::saveObject(string &object) const
{
    object += "#";
    object += std::to_string(size_);
    saveGene(object);
    for(const auto& child: children_)
    {
        object += "!";
        object += child.get().getId().toString();
    }
    object += "!";
}

void MEPGene::runGeneTree()
{
    runObjectTree();
    for(const auto& child: children_)
    {
        child.get().clearObjectResultTree();
    }
}

void MEPGene::clearObjectResult()
{
    if(isValid() == false)
        throw std::string("MEPGene::clearObjectResult: Object is invalid");

    clearGeneResult();
}

void MEPGene::clearObjectResultTree()
{
    clearObjectResult();
    for(auto& child: children_)
    {
        child.get().clearObjectResultTree();
    }
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

int MEPGene::runObject(MEPFitness& fitness)
{
    if(isValid() == false)
        throw std::string("MEPGene::runObject: Object is invalid");

    if(isValidResults() == false)
    {
        runObjectTree();
    }

    return assessGene(fitness);
}

const MEPId& MEPGene::getChildId(int childNumber) const
{
    return children_[childNumber].get().getId();
}
