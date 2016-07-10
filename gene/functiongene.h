#ifndef FUNCTIONGENE_H
#define FUNCTIONGENE_H

#include <string>
#include "gene.h"
#include "functionset.h"

class FunctionGene: public Gene
{
public:
    static FunctionSet& getFunctionSet();
public:
    static MEPObjectPtr create(unsigned int geneNumber);
    static MEPObjectPtr create(unsigned int geneNumber, int nArguments);

private:
    void setFunction(std::pair<FunctionId, FunctionPtr> p);
private:
    //Inherate from MEPGene
    MEPObjectPtr cloneObject() const;
    void writeGene(std::string&) const;
    int getGeneNArguments() const;
    void runGene(const std::vector<cv::Mat>&, cv::Mat&) const;
private:
    FunctionGene(std::pair<FunctionId, FunctionPtr> p, MEPId id);
    FunctionGene(std::pair<FunctionId, FunctionPtr> p);
    FunctionGene(const FunctionGene& functionGene);
private:
    FunctionPtr function_;
    FunctionId functionId_;

    static FunctionSet functions_;
};

#endif // FUNCTIONGENE_H