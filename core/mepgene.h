#ifndef MEPGENE_H
#define MEPGENE_H

#include "mepobject.h"

#include <memory>
#include <string>
#include <vector>

//TODO For doing library for different types of result you can do
//     class which implement for example function show, isvalid, clear
class MEPSHARED_EXPORT MEPGene;
using MEPGenePtr = std::shared_ptr<MEPGene>;
class MEPSHARED_EXPORT MEPGene : public MEPObject
{
public:
    MEPGene(const MEPId& id);
    int getNArguments() const;

protected:
    MEPGene(const MEPGene&);
    void swap(MEPGene&);

private:
    void writeObject(std::string&) const;
    void showObject(const std::string& id) const;
    void showObjectTree(const std::string& id) const;
    void clearObjectResult();

    void runObject();
    int assessObject(MEPFitness&);


private:
    //TerminalGene and FunctionGene must implement this functions
    virtual MEPObjectPtr cloneObject() const = 0;
    virtual void writeGene(std::string&) const = 0;
    virtual int getGeneNArguments() const = 0;
    virtual void runGene(const std::vector<cv::Mat>&, cv::Mat&) const = 0;

    virtual bool isValidResult(const cv::Mat&) const = 0;
    virtual void clearGeneResult(cv::Mat&) const = 0;
    virtual void showGene(const std::string& windowName, const cv::Mat&) const = 0;
private:
    std::vector<MEPGenePtr> children_;
    cv::Mat result_;
};

#endif // MEPGENE_H
