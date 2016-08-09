#ifndef FUNCTIONGENE_H
#define FUNCTIONGENE_H

#include <string>
#include "gene.h"
#include "functionset.h"

class MEPSHARED_EXPORT FunctionGene: public Gene
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
    MEPObjectPtr cloneGene() const;
    void saveGene(std::string&) const;
    void writeGene(std::string&) const;
    int getGeneNArguments() const;
    void runGene(const std::vector<cv::Mat>&, cv::Mat&) const;
public:
    FunctionGene(std::pair<FunctionId, FunctionPtr> p, MEPId id);
private:
    FunctionGene(std::pair<FunctionId, FunctionPtr> p);
    FunctionGene(const FunctionGene& functionGene);
private:
    FunctionPtr function_;
    FunctionId functionId_;

    static FunctionSet functions_;
};

#endif // FUNCTIONGENE_H
