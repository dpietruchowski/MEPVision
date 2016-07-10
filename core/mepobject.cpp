#include "mepobject.h"

#include <utility>

using namespace std;

MEPObject::MEPObject(const MEPId& id):
    id_(id), score_(MEPScore()), rank_(MEPScore()),
    nClones_(new int)
{
    *nClones_ = 0;
}

MEPObject::MEPObject(const MEPObject& rhs):
    score_(MEPScore()), rank_(MEPScore())
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

bool MEPObject::operator <(const MEPObject& rhs) const
{
    return score_.score < rhs.score_.score;
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
    int nSpaces = 15 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }

    object += rank_.toString();
    nSpaces = 38 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }
    object += score_.toString();
    nSpaces = 61 - object.size();
    for(int i = 0; i < nSpaces; i++)
    {
        object += " ";
    }
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

void MEPObject::setAsNext(const MEPObject& rhs)
{
    rank_.score = rhs.rank_.score + 1;
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
    score_.score = assessObject(fitness);
}

int MEPObject::getScore() const
{
    return score_.score;
}
