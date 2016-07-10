#include "mepgene.h"

#include <utility>

using namespace std;

MEPGene::MEPGene(const MEPId& id):
    MEPObject(id)
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
    if(!isValidResult(result_))
        throw "TU BEDZIE ENUM";
    showGene(id, result_);
}

void MEPGene::showObjectTree(const string& id) const
{
    showObject(id);
    for(const auto& child: children_)
    {
        child->showTree();
    }
}

void MEPGene::runObject()
{
    std::vector<cv::Mat> arg;
    for(const auto& child: children_)
    {
        if(!isValidResult(child->result_))
            throw "TU BEDZIE ENUM";
        arg.push_back(child->result_);
    }

    if(!isValidResult(result_))
        throw "TU BEDZIE ENUM";
    runGene(arg, result_);
}

void MEPGene::clearObjectResult()
{
    clearGeneResult(result_);
}

int MEPGene::assessObject(MEPFitness& fitness)
{
    return fitness.measure(result_);
}

int MEPGene::getNArguments() const
{
    return getGeneNArguments();
}
