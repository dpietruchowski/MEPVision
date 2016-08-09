#ifndef MEPGENE_H
#define MEPGENE_H

#include "mepobject.h"

#include <string>
#include <vector>
#include <functional>

class MEPGene;
typedef std::vector<std::reference_wrapper<MEPGene>> MEPGenes;
//TODO For doing library for different types of result you can do
//     class which implement for example function show, isvalid, clear
//TODO Move result do Gene
class MEPSHARED_EXPORT MEPGene : public MEPObject
{
public:
    MEPGene(const MEPId& id, int size);
    int getNArguments() const;
    bool isValid() const;
    const MEPId& getChildId(int childNumber) const;
    void addChild(MEPGene&);
    void runGeneTree();

protected:
    MEPGene(const MEPGene&);
    void swap(MEPGene&);

private:
    void runObjectTree();
    //TODO Wymyslec lepsza nazwe

    void saveObject(std::string&) const;
    void writeObject(std::string&) const;
    void writeObjectTree(std::string&) const;
    void showObject(const std::string& id);
//    void showObjectTree(const std::string& id) const;
    void clearObjectResult();
    void clearObjectResultTree();
    MEPObjectPtr cloneObject() const;
    virtual bool isValidResults() const = 0;

    int runObject(MEPFitness&);

private:
    //TerminalGene and FunctionGene must implement this functions
    virtual void saveGene(std::string&) const = 0;
    virtual void writeGene(std::string&) const = 0;
    virtual void showGene(const std::string& windowName) const = 0;
    virtual void clearGeneResult() = 0;
    virtual MEPObjectPtr cloneGene() const = 0;

    virtual int assessGene(MEPFitness&) const = 0;
    virtual void runGene(const MEPGenes&) = 0;

private:
    MEPGenes children_;
    int size_;
};

void dynamicCast(MEPObjects &objects, MEPGenes &genes);

#endif // MEPGENE_H
