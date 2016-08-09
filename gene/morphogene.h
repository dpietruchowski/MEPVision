#ifndef MORPHOGENE_H
#define MORPHOGENE_H

#include "gene.h"

struct MorphoParameters
{
    const static int MAX_WIDTH = 10;
    const static int MAX_HEIGHT = 10;
    const static int MAX_ITER = 10;
    static MorphoParameters getRandom();
    int morphType; // max 6
//    int morphShape; // max 2
//    int morphWidth;
//    int morphHeight;
    int iterations;
    MorphoParameters(int type, int iter):
        morphType(type), iterations(iter) {}
    MorphoParameters(const std::string& param)
    { fromString(param); }
    std::string typeToString() const;
    int typeFromString(std::string&) const;
//    std::string shapeToString() const;
    std::string toString() const;
    void fromString(const std::string&);
};

struct MorphoElement
{
    cv::Mat element;
    MorphoElement() {}
    MorphoElement(const std::string& elem, int nRows, int nCols)
    { fromString(elem, nRows, nCols); }
    std::string toString() const;
    void fromString(const std::string&, int nRows, int nCols);
};

class MorphoGene : public Gene
{
public:
    typedef int(*MorphoPtr) (const std::vector<cv::Mat>&, cv::Mat&,
                             const MorphoParameters&,
                             const cv::Mat& element);
    static MEPObjectPtr create(unsigned int geneNumber);
    static int morphologyOperation(const std::vector<cv::Mat>&, cv::Mat&,
                                   const MorphoParameters&,
                                   const cv::Mat& element);
public:
    MorphoGene(MorphoPtr, const MorphoParameters&,
               const MorphoElement& element, const MEPId& id);
private:
    MorphoGene(const MorphoGene& rhs);
private:
    //Inherate from MEPGene
    MEPObjectPtr cloneGene() const;
    void saveGene(std::string&) const;
    void writeGene(std::string&) const;
    int getGeneNArguments() const;
    void runGene(const std::vector<cv::Mat>&, cv::Mat&) const;
private:
    MorphoPtr morphoOperation_;
    MorphoParameters parameters_;
    MorphoElement structElement_;
};

#endif // MORPHOGENE_H
