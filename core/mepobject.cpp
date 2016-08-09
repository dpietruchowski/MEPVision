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
    id_.swap(rhs.id_);
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

string MEPObject::save() const
{
    string object = "#";
    object += id_.toString();
    saveObject(object);

    return object;
}

void MEPObject::show()
{
    showObject(id_.toString());
}

//void MEPObject::showTree()
//{
//    showObjectTree(id_.toString());
//}

void MEPObject::clearResult()
{
    clearObjectResult();
}

std::string MEPObject::writeObject() const
{
    std::string object;

    object += id_.toString();
    object += " ";
    object += enumToString(getState());
    int nSpaces = 35 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }

    object += to_string(rank_);
    nSpaces = 41 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }
    object += to_string(score_);

    return object;
}

std::string MEPObject::write() const
{
    string object = writeObject();
    writeObject(object);

    return object;
}

string MEPObject::writeTree() const
{
    string object = writeObject();
    writeObjectTree(object);

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

void MEPObject::run(MEPFitness& fitness)
{
    score_ = runObject(fitness);
    clearResult();
}

MEPObjectPtr MEPObject::clone() const
{
    MEPObjectPtr objectClone = cloneObject();

    return objectClone;
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
