#include "mepobject.h"

#include <utility>
#include <limits>

using namespace std;

MEPObject::MEPObject(const MEPId& id):
    id_(id), score_(std::numeric_limits<int>::max()), rank_(-1),
    nClones_(new int(0))
{
}

MEPObject::MEPObject(const MEPObject& rhs):
    score_(std::numeric_limits<int>::max()), rank_(-1)
{
    nClones_ = rhs.nClones_;
    (*nClones_)++;

    id_ = rhs.id_;

    id_.cloneNumber = *nClones_;
}

void MEPObject::swap(MEPObject& rhs)
{
    std::swap(id_, rhs.id_);
    std::swap(score_, rhs.score_);
    std::swap(rank_, rhs.rank_);
}

bool MEPObject::operator ==(const MEPObject& rhs) const
{
    return id_ == rhs.id_;
}

bool MEPObject::isClone(const MEPObject& rhs) const
{
    return (id_.type == rhs.id_.type) && (id_.number == rhs.id_.number);
}

bool MEPObject::operator <(const MEPObject& rhs) const
{
    return score_ < rhs.score_;
}

bool MEPObject::operator ==(const int& rank) const
{
    return rank_ == rank;
}

bool MEPObject::operator ==(const MEPId& id) const
{
    return id_ == id;
}

void MEPObject::show() const
{
    showObject(id_.toString());
}

void MEPObject::showTree() const
{
    showObjectTree(id_.toString());
}

void MEPObject::write(std::string& object) const
{
    object += id_.toString();
    int nSpaces = 20 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }

    object += to_string(rank_);
    nSpaces = 26 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }
    object += to_string(score_);
   }

std::string MEPObject::write() const
{
    string object;

    write(object);
    writeObject(object);

    return object;
}

void MEPObject::clearResults()
{
    clearObjectResult();
}

void MEPObject::setAsFirst()
{
    rank_ = 0;
}

void MEPObject::setAsNext(const MEPObject& rhs)
{
    rank_ = rhs.rank_ + 1;
}

void MEPObject::run()
{
    runObject();
}

MEPObjectPtr MEPObject::clone() const
{
    MEPObjectPtr objectClone = cloneObject();

    return objectClone;
}

void MEPObject::assess(MEPFitness& fitness)
{
    score_ = assessObject(fitness);
}

int MEPObject::getScore() const
{
    return score_;
}

const MEPId& MEPObject::getId() const
{
    return id_;
}

void MEPObject::addToSelection(MEPSelection& selection) const
{
    selection.add(rank_, score_);
}

MEPState MEPObject::getState() const
{
    bool result = isValidResults();
    bool score = score_ < std::numeric_limits<int>::max();
    bool sorted = rank_ >= 0;

    int state = result | (score << 1) | (sorted << 2);
    if(state == 0)
        return MEPCREATED;
    if(state == 1)
        return MEPDONE;
    if(state == 2)
        return MEPCLEARED;
    if(state == 3)
        return MEPASSESSED;
    if(state == 6)
        return MEPCLEAREDSORTED;
    if(state == 7)
        return MEPCOMPLITED;

    return MEPUNDEFINED;
}
