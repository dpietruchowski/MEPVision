#ifndef GENE_H
#define GENE_H

#include "core/mepgene.h"

class Gene : public MEPGene
{
protected:
    Gene(const MEPId&, int size);
    Gene(const Gene&);

private:
    bool isValidResult() const;
    void clearGeneResult();
    void showGene(const std::string& windowName) const;

    void runGene(const Children&);
    int assessGene(MEPFitness&) const;
private:
    virtual MEPObjectPtr cloneGene() const = 0;
    virtual void writeGene(std::string&) const = 0;
    virtual void runGene(const std::vector<cv::Mat>&, cv::Mat&) = 0;

    virtual MEPObjectPtr mutate() const = 0;
    
private:
	cv::Mat result_;
};

#endif // GENE_H
