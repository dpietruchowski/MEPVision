#ifndef MORPHOGENE_H
#define MORPHOGENE_H

#include "gene.h"

struct MorphoParameters
{
    const static int MAX_WIDTH = 15;
    const static int MAX_HEIGHT = 15;
    const static int MAX_ITER = 25;
    static MorphoParameters getRandom();
    int morphType; // max 6
    int morphShape; // max 2
    int morphWidth;
    int morphHeight;
    int anchorX;
    int anchorY;
    int iterations;
    MorphoParameters(int type, int shape, int width, int height,
                     int anchorX, int anchorY, int iter):
        morphType(type), morphShape(shape), morphWidth(width),
        morphHeight(height), anchorX(anchorX), anchorY(anchorY),
        iterations(iter) {}
    std::string typeToString() const;
    std::string shapeToString() const;
    std::string toString() const;
};

class MorphoGene : public Gene
{
public:
    typedef int(*MorphoPtr) (const std::vector<cv::Mat>&, cv::Mat&,
                             const MorphoParameters&);
    static MEPObjectPtr create(unsigned int geneNumber);
    static int morphologyOperation(const std::vector<cv::Mat>&, cv::Mat&,
                                   const MorphoParameters&);
private:
    MorphoGene(MorphoPtr, MorphoParameters&, MEPId id);
    MorphoGene(const MorphoGene& rhs);
private:
    //Inherate from MEPGene
    MEPObjectPtr cloneGene() const;
    void writeGene(std::string&) const;
    int getGeneNArguments() const;
    void runGene(const std::vector<cv::Mat>&, cv::Mat&) const;
    MEPObjectPtr mutate() const {}
private:
    MorphoPtr morphoOperation_;
    MorphoParameters parameters_;
};

#endif // MORPHOGENE_H
