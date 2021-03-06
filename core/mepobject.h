#ifndef MEPOBJECT_H
#define MEPOBJECT_H

#include "../mep_global.h"
#include "meptypes.h"
#include "../generator/mepgenerator.h"
#include "../fitness/mepfitness.h"
#include "../selection/mepselection.h"

#include <string>
#include <memory>

//TODO Think if swap is necessary. It is only use for operator =
//     So maybe it is better to delete swapObject function and leave swap function
//     Swap function of derived class will invoke swap function from higher class
//     in class hierarchy
//TODO Add virtual destructor
//TODO Think about better name for MEPState enum
//TODO MEPSORTED is whether composite is sorted or object is sorted
class MEPObject;
typedef std::vector<std::reference_wrapper<MEPObject>> MEPObjects;

class MEPGenerator;
class MEPFitness;

class MEPSHARED_EXPORT MEPObject;
typedef std::shared_ptr<MEPObject> MEPObjectPtr;
class MEPSHARED_EXPORT MEPObject
{
public:
    MEPObject(const MEPId&);
    virtual ~MEPObject() {}
        /// Operators
    //Check if the same id;
    bool operator ==(const MEPObject&) const;
    bool operator <(const MEPObject&) const;
    bool operator ==(const int& rank) const;
    bool operator ==(const MEPId& id) const;
        /// Interface
    std::string save() const;
    std::string write() const;
    std::string writeTree() const;
    std::string writeObject() const;
    void setAsNext(const MEPObject&);
    void setAsFirst();
    MEPObjectPtr clone() const;
        /// Getters and isers
    int getScore() const;
    int getRank() const;
    const MEPId& getId() const;
    MEPState getState() const;
    bool isClone(const MEPObject&) const;
    virtual bool isValidResults() const = 0;
    virtual bool isValid() const = 0;
    virtual void show();
    void show(const std::string& windowName);
//    void showTree() const;
    void clearResult();
    void clearResults();
        /// For algorithm
    virtual void init(MEPGenerator&) {}
    void run(MEPFitness&);
    void sort();
    void addToSelection(MEPSelection&) const;

protected:
    MEPObject(const MEPObject& rhs);
    void swap(MEPObject&);
private:
    virtual void saveObject(std::string&) const = 0;
    virtual void writeObject(std::string&) const = 0;
    virtual void writeObjectTree(std::string&) const = 0;
    virtual void showObject(const std::string& id) = 0;
//    virtual void showObjectTree(const std::string& id) const = 0;
    virtual void clearObjectResult() {}
    virtual void clearObjectResults() {}
    virtual MEPObjectPtr cloneObject() const = 0;

    virtual int runObject(MEPFitness&) = 0;
    virtual int sortObject() { return 0; }
private:
    MEPId id_;
    int score_;
    int rank_;

    std::shared_ptr<int> nClones_;
};

#endif // MEPOBJECT_H
