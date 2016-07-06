#ifndef MEPCOMPOSITE_H
#define MEPCOMPOSITE_H

#include <vector>
#include <string>

#include "mepobject.h"

class MEPSHARED_EXPORT MEPComposite : public MEPObject
{
public:
    MEPComposite(const MEPId& id);
    MEPComposite(const MEPComposite&);
    void create(int size);
    //void initialize(const MEPGenerator&);

    int getSize() const;

    void sort();
    const MEPObject& find(const int rank) const;
    const MEPObject& find(const MEPId&) const;

    int find(const MEPObject&) const;
    void clonePart(const MEPComposite& rhs, int startGeneNumber,
                   int endGeneNumber);

protected:
    void swap(MEPComposite&);
private:
    void addObject(MEPObjectPtr);
private:
    //Dziedziczace po MEPObject
    void writeObject(std::string&) const;
    void showObject() const;
    void showObjectTree() const;
    void runObject();
    void clearObjectResult();
    MEPObjectPtr cloneObject() const = 0;
    //Meotdy MEPComposite
    virtual void createComposite(int size) = 0;
private:
    std::vector<MEPObjectPtr> objects_;
};

#endif // MEPCOMPOSITE_H
