#ifndef MEPCOMPOSITE_H
#define MEPCOMPOSITE_H

#include "mepobject.h"
#include "mepgene.h"

#include <vector>
#include <string>


//TODO addchild - shouldnt be here
class MEPSHARED_EXPORT MEPComposite : public MEPObject
{
public:
    typedef std::vector<MEPObjectPtr> Objects;
    MEPComposite(const MEPId& id, int size);
    MEPComposite(const MEPComposite&);
    void init(MEPGenerator&);

    int getSize() const;
    bool isValid() const;
    bool isValidResults() const;
    std::vector<bool> isObjectsClone(const MEPComposite&);
    std::vector<bool> compare(const MEPComposite &rhs, int size) const;

    const MEPObject& getObject(int number) const;
    const MEPObject& find(const int rank) const;
    const MEPObject& find(const MEPId&) const;

    int findNumber(const MEPId&) const;
    int find(const MEPObject&) const;
    void clonePart(const MEPComposite& rhs, int startGeneNumber,
                   int endGeneNumber);
    void addObject(MEPObjectPtr object,
                   std::vector<int> args = std::vector<int>());

    virtual MEPObjectPtr reproduce(MEPSelectionType, MEPGenerator&) const = 0;
    void reproduceCompositeObject(const MEPComposite& rhs, MEPSelectionType);

protected:
    void swap(MEPComposite&);
    const MEPObject& select(MEPSelectionType) const;
private:
    void sort();
    //Dziedziczace po MEPObject
    void writeObject(std::string&) const;
    void showObject(const std::string& id) const;
    void showObjectTree(const std::string& id) const;
    void clearObjectResult();

    void runObject();
    int assessObject(MEPFitness&);

    virtual void addObject(Objects&, MEPObject&, std::vector<int>&) {}
    virtual MEPObjectPtr cloneObject() const = 0;
    //Meotdy MEPComposite
    virtual void initComposite(MEPGenerator&, int size) = 0;
    virtual void cloneCompositeObject(const MEPComposite& rhs,
                                      int objectNumber) = 0;
private:
    Objects objects_;
    int size_;
};

#endif // MEPCOMPOSITE_H
