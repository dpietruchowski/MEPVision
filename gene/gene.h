#ifndef GENE_H
#define GENE_H

#include "core/mepgene.h"

class Gene : public MEPGene
{
protected:
    Gene(const MEPId&);
    Gene(const Gene&);

private:
    bool isValidResult(const cv::Mat&) const;
    void clearGeneResult(cv::Mat&) const;
    void showGene(const std::string& windowName, const cv::Mat&) const;
private:
    virtual MEPObjectPtr cloneObject() const = 0;
    virtual void writeGene(std::string&) const = 0;
    virtual int getGeneNArguments() const = 0;
    virtual void runGene(const std::vector<cv::Mat>&, cv::Mat&) const = 0;
};

#endif // GENE_H
