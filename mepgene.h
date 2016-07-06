#ifndef MEPGENE_H
#define MEPGENE_H

#include <memory>
#include <string>
#include <vector>

#include "mepobject.h"

typedef int OpenCv;
class MEPSHARED_EXPORT MEPGene;
using MEPGenePtr = std::shared_ptr<MEPGene>;
class MEPSHARED_EXPORT MEPGene : public MEPObject
{
public:
    MEPGene(const MEPId& id);

protected:
    MEPGene(const MEPGene&);
    void swap(MEPGene&);

private:
    void writeObject(std::string&) const;
    void showObject() const;
    void showObjectTree() const;
    void runObject();
    void clearObjectResult();

private:
    //TerminalGene and FunctionGene must implement this functions
    virtual MEPObjectPtr cloneObject() const = 0;
    virtual void writeGene(std::string&) const = 0;
    virtual void showGene(const OpenCv&) const = 0;
    virtual int getGeneNArguments() const = 0;
    virtual void runGene(const std::vector<OpenCv>&, OpenCv&) const = 0;
    virtual void clearGeneResult(OpenCv&) = 0;
    virtual bool isValidResult(const OpenCv&) const = 0;
private:
    std::vector<MEPGenePtr> children_;
    OpenCv result_;
};

#endif // MEPGENE_H
