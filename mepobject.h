#ifndef MEPOBJECT_H
#define MEPOBJECT_H

#include <string>
#include <memory>

#include "mep_global.h"
#include "meptypes.h"

//TODO Think if swap is necessary. It is only use for operator =
//     So maybe it is better to delete swapObject function and leave swap function
//     Swap function of derived class will invoke swap function from higher class
//     in class hierarchy
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
    void run();
    MEPObjectPtr clone() const;

protected:
    MEPObject(const MEPObject& rhs);
    void swap(MEPObject&);
    void write(std::string&) const;
private:
    virtual void writeObject(std::string&) const = 0;
    virtual void showObject() const = 0;
    virtual void showObjectTree() const = 0;
    virtual void runObject() = 0;
    virtual void clearObjectResult() = 0;
    virtual MEPObjectPtr cloneObject() const = 0;
private:
    MEPId id_;
    //For debbuging
    //MEPId ownerId_;
    MEPScore fitness_;
    MEPScore rank_;

    std::shared_ptr<int> nClones_;
};

#endif // MEPOBJECT_H
