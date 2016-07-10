#include "mepcomposite.h"

#include <string>

using namespace std;

MEPComposite::MEPComposite(const MEPId& id, int initSize):
    MEPObject(id), initSize_(initSize)
{
}

MEPComposite::MEPComposite(const MEPComposite& rhs):
    MEPObject(rhs)
{
    clonePart(rhs, 0, objects_.size() - 1);
}

void MEPComposite::swap(MEPComposite& rhs)
{
    MEPObject::swap(rhs);
    objects_.swap(rhs.objects_);
}

void MEPComposite::init(MEPGenerator& generator)
{
    initComposite(generator, initSize_);
}

void MEPComposite::sort()
{
    vector<MEPObject*> sorted;
    for(auto& obj : objects_)
    {
        sorted.push_back(obj.get());
    }

    std::sort(sorted.begin(),sorted.end(),
              [](const MEPObject* lhs, const MEPObject* rhs) -> bool
              { return *lhs < *rhs; });

    for(int i = 1; i < static_cast<int>(sorted.size()); i++)
    {
        sorted[i]->setAsNext(*sorted[i-1]);
    }
}

const MEPObject& MEPComposite::find(const int rank) const
{
    vector<MEPObjectPtr>::const_iterator it;
    it = std::find_if(objects_.begin(), objects_.end(),
                      [&](const MEPObjectPtr& obj)
                        { return *obj == rank; });
    if(it == objects_.end())
        --it;

    return **it;
}

const MEPObject& MEPComposite::find(const MEPId& id) const
{
    vector<MEPObjectPtr>::const_iterator it;
    it = std::find_if(objects_.begin(), objects_.end(),
                      [&](const MEPObjectPtr& obj)
                         { return *obj == id; });
    if(it == objects_.end())
        --it;

    return **it;
}

int MEPComposite::find(const MEPObject& object) const
{
    for(int i = 0; i < getSize(); i++)
    {
        if(*objects_[i] == object)
            return i;
    }
    throw "nie ma takiego genu";
}

void MEPComposite::clonePart(const MEPComposite& rhs,
                             int startObjectNumber,
                             int endObjectNumber)
{
    if ( (startObjectNumber > endObjectNumber) ||
             (startObjectNumber >= rhs.getSize()))
    {
        throw "Zly punkt poczatkowy kopiowania chromosomu";
    }

    if ( endObjectNumber >= rhs.getSize() )
    {
        throw "Zly punkt koncowy kopiowania chromosomu";
    }

    for (int i = startObjectNumber; i <= endObjectNumber; i++)
    {
        addObject(rhs.objects_[i]->clone());
    }
}

void MEPComposite::addObject(MEPObjectPtr object)
{
    objects_.push_back(object);
}

int MEPComposite::getSize() const
{
    return objects_.size();
}

void MEPComposite::writeObject(std::string& object) const
{
    object = "\n";
    for(const auto& obj: objects_)
    {
        object += " ";
        object += obj->write();
    }
}

void MEPComposite::showObject(const string& id) const
{
    for(const auto& obj: objects_)
    {
        obj->show();
    }
}

void MEPComposite::showObjectTree(const string& id) const
{
    for(const auto& obj: objects_)
    {
        obj->showTree();
    }
}

void MEPComposite::runObject()
{
    for(const auto& obj: objects_)
    {
        obj->run();
    }
}

void MEPComposite::clearObjectResult()
{
    for(const auto& obj: objects_)
    {
        obj->clearResults();
    }
}


int MEPComposite::assessObject(MEPFitness& fitness)
{
    for(const auto& object: objects_)
    {
        object->assess(fitness);
    }
    sort();
    return find(0).getScore();
}
