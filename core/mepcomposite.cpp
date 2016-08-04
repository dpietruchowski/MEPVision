#include "mepcomposite.h"

#include <string>
#include "../selection/rouletteselection.h"
#include "../selection/tournamentselection.h"
#include "../generator/mepgenerator.h"

using namespace std;

MEPComposite::MEPComposite(const MEPId& id, int size):
    MEPObject(id), size_(size)
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

const MEPObject &MEPComposite::select(MEPSelectionType type) const
{
    MEPSelection *selection;
    switch(type)
    {
    case FITNESS_ROULETTESELECTION:
        selection = new FitnessRouletteSelection();
        break;
    case RANK_ROULETTESELECTION:
        selection = new RankRouletteSelection();
        break;
    case TOURNAMENTSELECTION:
        selection = new TournamentSelection(getSize()/2);
        break;
    default:
        throw std::string("MEPComposite::select: Should never get here");
    }

    if(!isValid())
        throw std::string("MEPComposite::reproduce: Object is invalid");

    for(int i = 0; i < getSize(); ++i)
    {
        objects_[i]->addToSelection(*selection);
    }

    selection->calcScores();
    const MEPObject& selected = find(selection->getSelectedRank());

    delete selection;
    return selected;
}

void MEPComposite::reproduceCompositeObject(const MEPComposite &rhs,
                                            MEPSelectionType type)
{
   cloneCompositeObject(rhs, rhs.find(rhs.select(type)));
}

void MEPComposite::init(MEPGenerator& generator)
{
    initComposite(generator, size_);
}

void MEPComposite::sort()
{
    if(!isValid())
        throw std::string("MEPComposite::sort: Object is invalid");
    
    vector<MEPObject*> sorted;
    for(auto& obj : objects_)
    {
        sorted.push_back(obj.get());
    }

    std::sort(sorted.begin(),sorted.end(),
              [](const MEPObject* lhs, const MEPObject* rhs) -> bool
              { return *lhs < *rhs; });

    sorted[0]->setAsFirst();
    for(int i = 1; i < static_cast<int>(sorted.size()); i++)
    {
        sorted[i]->setAsNext(*sorted[i-1]);
    }
}

const MEPObject& MEPComposite::find(const int rank) const
{
    if(!isValid())
        throw std::string("MEPComposite::find: Object is invalid");
    
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
    if(!isValid())
        throw std::string("MEPComposite::find: Object is invalid");
    
    vector<MEPObjectPtr>::const_iterator it;
    it = std::find_if(objects_.begin(), objects_.end(),
                      [&](const MEPObjectPtr& obj)
                         { return *obj == id; });
    if(it == objects_.end())
        --it;

    return **it;
}

int MEPComposite::findNumber(const MEPId& id) const
{
    return find(find(id));
}

const MEPObject& MEPComposite::getObject(int number) const
{
    return *objects_[number];
}

int MEPComposite::find(const MEPObject& object) const
{
    if(!isValid())
        throw std::string("MEPComposite::find: Object is invalid");
    
    for(int i = 0; i < getSize(); i++)
    {
        if(*objects_[i] == object)
            return i;
    }
    throw std::string("MEPComposite::find: nie ma takiego genu");
}

void MEPComposite::clonePart(const MEPComposite& rhs,
                             int startObjectNumber,
                             int endObjectNumber)
{
    if(!isValid())
        throw std::string("MEPComposite::clonePart: Object is invalid");
    
    if ( (startObjectNumber > endObjectNumber) ||
             (startObjectNumber >= rhs.getSize()))
    {
        throw std::string("MEPComposite::clonePart: Zly punkt poczatkowy kopiowania chromosomu");
    }

    if ( endObjectNumber >= rhs.getSize() )
    {
        throw std::string("MEPComposite::clonePart: Zly punkt koncowy kopiowania chromosomu");
    }

    for (int i = startObjectNumber; i <= endObjectNumber; i++)
    {
        cloneCompositeObject(rhs, i);
    }
}

void MEPComposite::addObject(MEPObjectPtr object, std::vector<int> args)
{
    if(isValid() == false)
    {
        addObject(objects_, *object, args);
        objects_.push_back(object);
    }
    else
        throw std::string("MEPComposite::addObject: Can not add object, composite is full");
}

int MEPComposite::getSize() const
{
    return objects_.size();
}

void MEPComposite::writeObject(std::string& object) const
{
    if(!isValid())
        throw std::string("MEPComposite::writeObject: Object is invalid");
    
    object += "\n";
    for(const auto& obj: objects_)
    {
        object += "   ";
        string sobj = obj->write();
        object += obj->write();
    }
}

void MEPComposite::writeObjectTree(std::string& object) const
{
    if(!isValid())
        throw std::string("MEPComposite::writeObject: Object is invalid");

    object += "\n";
    for(const auto& obj: objects_)
    {
        object += "   ";
        string sobj = obj->writeTree();
        object += obj->writeTree();
    }
}

void MEPComposite::showObject(const string&) const
{
    if(!isValid())
        throw std::string("MEPComposite::showObject: Object is invalid");
    
    for(const auto& obj: objects_)
    {
        obj->show();
    }
}

void MEPComposite::showObjectTree(const string&) const
{
    if(!isValid())
        throw std::string("MEPComposite::showObjectTree: Object is invalid");
    
    for(const auto& obj: objects_)
    {
        obj->showTree();
    }
}

void MEPComposite::runObject()
{
    if(!isValid())
        throw std::string("MEPComposite::runObject: Object is invalid");
    
    for(const auto& obj: objects_)
    {
        obj->run();
    }
}

void MEPComposite::clearObjectResult()
{
    if(!isValid())
        throw std::string("MEPComposite::clearObjectResult: Object is invalid");
    
    for(const auto& obj: objects_)
    {
        obj->clearResults();
    }
}


int MEPComposite::assessObject(MEPFitness& fitness)
{
    if(!isValid())
        throw std::string("MEPComposite::assessObject: Object is invalid");
    
    for(const auto& object: objects_)
    {
        object->assess(fitness);
    }
    sort();
    return find(0).getScore();
}

bool MEPComposite::isValid() const
{
    if(size_ != static_cast<int> (objects_.size()))
        return false;

    for(const auto& obj: objects_)
    {
        // Jesli conajmniej jeden nie jest valid to chromosome nie jest poprawny
        if(obj->isValid() == false)
            return false;
    }

    return true;
}

std::vector<bool> MEPComposite::isObjectsClone(const MEPComposite& rhs)
{
    vector<bool> comparison;
    int lowerSize = size_ < rhs.size_ ? size_ : rhs.size_;
    int higherSize = size_ > rhs.size_ ? size_ : rhs.size_;

    for(int i = 0; i < lowerSize; ++i)
    {
        comparison.push_back(objects_[i]->isClone(*rhs.objects_[i]));
    }
    for(int i = lowerSize; i < higherSize; ++i)
    {
        comparison.push_back(false);
    }

    return comparison;
}

bool MEPComposite::isValidResults() const
{
    bool valid = true;
    for(const auto& obj: objects_)
    {
        valid &= obj->isValidResults();
    }

    return valid;
}

std::vector<bool> MEPComposite::compare(const MEPComposite &rhs,
                                        int size) const
{
    if((size > getSize()) || (size > rhs.getSize()))
        throw "Za duza liczba genow do porownania";

    vector<bool> comparison;
    for(int i = 0; i < size; i++)
    {
        MEPObject& obj1 = *objects_[i];
        MEPObject& obj2 = *rhs.objects_[i];

        if(*objects_[i] < *rhs.objects_[i])
            comparison.push_back(true);
        else
            comparison.push_back(false);
    }

    return comparison;
}
