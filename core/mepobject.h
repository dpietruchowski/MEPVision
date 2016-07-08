#ifndef MEPOBJECT_H
#define MEPOBJECT_H

#include "mep_global.h"
#include "meptypes.h"
#include "generator/mepgenerator.h"
#include "fitness/mepfitness.h"
//#include "selection/selection.h"
//#include "reproduction/mutation.h"
//#include "reproduction/crossover.h"

#include <string>
#include <memory>

//TODO Think if swap is necessary. It is only use for operator =
//     So maybe it is better to delete swapObject function and leave swap function
//     Swap function of derived class will invoke swap function from higher class
//     in class hierarchy
//TODO Add virtual destructor
class MEPGenerator;
class MEPFitness;

class MEPSHARED_EXPORT MEPObject;
typedef std::shared_ptr<MEPObject> MEPObjectPtr;
class MEPSHARED_EXPORT MEPObject
{
public:
    MEPObject(const MEPId&);
    //Check if the same id;
    bool operator ==(const MEPObject&) const;
    bool operator <(const MEPObject&) const;
    bool operator ==(const int& rank) const;
    bool operator ==(const MEPId& id) const;
    void show() const;
    void showTree() const;
    std::string write() const;
    void clearResults();
    void setAsNext(const MEPObject&);
    MEPObjectPtr clone() const;

//    virtual void init(MEPGenerator&) = 0;
    void run();
//    void assess(MEPFitness&);

protected:
    MEPObject(const MEPObject& rhs);
    void swap(MEPObject&);
    void write(std::string&) const;
private:
    virtual void writeObject(std::string&) const = 0;
    virtual void showObject() const = 0;
    virtual void showObjectTree() const = 0;
    virtual void clearObjectResult() = 0;
    virtual MEPObjectPtr cloneObject() const = 0;

    virtual void runObject() = 0;
//    virtual void assessObject(MEPFitness&) = 0;
private:
    MEPId id_;
    //For debbuging
    //MEPId ownerId_;
    MEPScore score_;
    MEPScore rank_;

    std::shared_ptr<int> nClones_;
};

#endif // MEPOBJECT_H
