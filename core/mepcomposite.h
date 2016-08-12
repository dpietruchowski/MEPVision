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
    int getSumScore() const;
    bool isValid() const;
    bool isValidResults() const;
    void show();
    std::vector<bool> isObjectsClone(const MEPComposite&);
    std::vector<bool> compare(const MEPComposite &rhs, int size) const;

    const MEPObject& findByOrder(int number) const;
    const MEPObject& findByRank(const int rank) const;
    const MEPObject& findById(const MEPId&) const;

    int findNumber(const MEPId&) const;
    int find(const MEPObject&) const;
    void clonePart(const MEPComposite& rhs, int startGeneNumber,
                   int endGeneNumber);
    void addObject(MEPObjectPtr object,
                   std::vector<int> args = std::vector<int>());
    bool setObject(MEPObjectPtr object,
                   std::vector<int> args = std::vector<int>());

    const MEPObject& select(MEPSelectionType) const;

protected:
    void swap(MEPComposite&);
private:
    //Dziedziczace po MEPObject
    void saveObject(std::string&) const;
    void writeObject(std::string&) const;
    void writeObjectTree(std::string&) const;
    void showObject(const std::string& id);
//    void showObjectTree(const std::string& id) const;
    void clearObjectResults();

    int sortObject();
    int runObject(MEPFitness& fitness);

    virtual void addObject(Objects&, MEPObject&, std::vector<int>&) {}
    virtual MEPObjectPtr cloneObject() const = 0;
    //Meotdy MEPComposite
    virtual void initComposite(MEPGenerator&, int size) = 0;
    virtual void cloneCompositeObject(const MEPComposite& rhs,
                                      int objectNumber) = 0;
private:
    Objects objects_;
    int size_;
    double normalized_;
};

#endif // MEPCOMPOSITE_H
