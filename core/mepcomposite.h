#ifndef MEPCOMPOSITE_H
#define MEPCOMPOSITE_H

#include "mepobject.h"

#include <vector>
#include <string>


//TODO Think if in method assess should calculate standardized and fitness score
//     and set rank;
class MEPSHARED_EXPORT MEPComposite : public MEPObject
{
public:
    MEPComposite(const MEPId& id, int initSize);
    MEPComposite(const MEPComposite&);
//    void init(MEPGenerator&);

    int getSize() const;

    void sort();
    const MEPObject& find(const int rank) const;
    const MEPObject& find(const MEPId&) const;

    int find(const MEPObject&) const;
    void clonePart(const MEPComposite& rhs, int startGeneNumber,
                   int endGeneNumber);

protected:
    void swap(MEPComposite&);
    void addObject(MEPObjectPtr);
private:
    //Dziedziczace po MEPObject
    void writeObject(std::string&) const;
    void showObject() const;
    void showObjectTree() const;
    void clearObjectResult();

    void runObject();
//    void assessObject(MEPFitness&);

    virtual MEPObjectPtr cloneObject() const = 0;
    //Meotdy MEPComposite
//    virtual void initComposite(MEPGenerator&, int size) = 0;
private:
    std::vector<MEPObjectPtr> objects_;
    int initSize_;
};

#endif // MEPCOMPOSITE_H
