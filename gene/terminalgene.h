#ifndef TERMINALGENE_H
#define TERMINALGENE_H

#include "gene.h"
#include "terminalset.h"
#include <string>


//TODO In constructor: Gene() instead of Gene(MEPId())
class MEPSHARED_EXPORT TerminalGene: public Gene
{
public:
    static TerminalSet& getTerminalSet();
public:
    static MEPObjectPtr create(unsigned int geneNumber);

private:
    void setTerminal(MatPtr newTerminal);
private:
    //Inherate from MEPGene
    MEPObjectPtr cloneGene() const;
    void saveGene(std::string&) const;
    void writeGene(std::string&) const;
    int getGeneNArguments() const;
    void runGene(const std::vector<cv::Mat>&, cv::Mat&) const;
public:
    TerminalGene(MatPtr image, MEPId id);
private:
    TerminalGene(MatPtr image);
    TerminalGene(const TerminalGene& terminalGene);
private:
    MatPtr terminal_;
    std::string terminalName_;

    static TerminalSet terminals_;
};

#endif // TERMINALGENE_H
