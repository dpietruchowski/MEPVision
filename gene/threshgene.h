#ifndef THRESHGENE_H
#define THRESHGENE_H

#include "gene.h"

struct ThreshParameters
{
    static ThreshParameters getRandom();
    int threshValue;
    int threshType; //max 4

    ThreshParameters(int value, int type):
        threshValue(value), threshType(type) {}
    ThreshParameters(const std::string& param)
    { fromString(param); }
    std::string typeToString() const;
    int typeFromString(const std::string&) const;
    std::string toString() const;
    void fromString(const std::string&);
};

class ThreshGene : public Gene
{
public:
    typedef int(*ThreshPtr) (const std::vector<cv::Mat>&, cv::Mat&,
                             const ThreshParameters&);
    static MEPObjectPtr create(unsigned int geneNumber);
    static int thresholdOperation(const std::vector<cv::Mat>&, cv::Mat&,
                                   const ThreshParameters&);
public:
    ThreshGene(ThreshPtr, ThreshParameters&, MEPId id);
private:
    ThreshGene(const ThreshGene& rhs);

private:
    MEPObjectPtr cloneGene() const;
    void saveGene(std::string&) const;
    void writeGene(std::string&) const;
    int getGeneNArguments() const;
    void runGene(const std::vector<cv::Mat>&, cv::Mat&) const;

private:
    ThreshPtr threshOperation_;
    ThreshParameters parameters_;
};

#endif // THRESHGENE_H
