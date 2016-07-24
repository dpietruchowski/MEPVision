#ifndef MEPGENE_H
#define MEPGENE_H

#include "mepobject.h"

#include <memory>
#include <string>
#include <vector>

//TODO For doing library for different types of result you can do
//     class which implement for example function show, isvalid, clear
//TODO Move result do Gene
class MEPSHARED_EXPORT MEPGene;
using MEPGenePtr = std::shared_ptr<MEPGene>;
class MEPSHARED_EXPORT MEPGene : public MEPObject
{
public:
    typedef std::vector<MEPGenePtr>  Children;
    MEPGene(const MEPId& id, int size);
    int getNArguments() const;
    bool isValid() const;

protected:
    MEPGene(const MEPGene&);
    void swap(MEPGene&);

private:
    void writeObject(std::string&) const;
    void showObject(const std::string& id) const;
    void showObjectTree(const std::string& id) const;
    void clearObjectResult();
    MEPObjectPtr cloneObject() const;

    void runObject();
    int assessObject(MEPFitness&);

private:
    //TerminalGene and FunctionGene must implement this functions
    virtual void writeGene(std::string&) const = 0;
    virtual void showGene(const std::string& windowName) const = 0;
    virtual void clearGeneResult() = 0;
    virtual MEPObjectPtr cloneGene() const = 0;

    virtual int assessGene(MEPFitness&) const = 0;

    virtual void runGene(const Children&) = 0;
    virtual bool isValidResult() const = 0;
    virtual MEPObjectPtr mutate() const = 0;
    
private:
    Children children_;
    int size_;
};

#endif // MEPGENE_H
