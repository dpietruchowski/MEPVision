#include "morphogene.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

MEPObjectPtr MorphoGene::create(unsigned int geneNumber)
{
    MEPId id = {MEPGENE, geneNumber, 0};
    MorphoParameters param = MorphoParameters::getRandom();
    return MEPObjectPtr(new MorphoGene(MorphoGene::morphologyOperation,
                                       param,
                                       id));
}

int MorphoGene::morphologyOperation(const std::vector<cv::Mat> &src, cv::Mat &dst,
                                    const MorphoParameters& param)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }

    if((param.morphShape > 2) || (param.morphShape < 0))
        throw std::string("MorphoGene::morphologyOperation: Bad shape");
    if((param.morphType > 6) || (param.morphType < 0))
        throw std::string("MorphoGene::morphologyOperation: Bad morpho type");

    const cv::Mat& src1 = src[0];
    cv::Mat element = cv::getStructuringElement(param.morphShape,
                                                cv::Size(param.morphWidth,
                                                     param.morphHeight),
                                                cv::Point(-1,
                                                      -1));
    cv::morphologyEx(src1, dst, param.morphType, element,
                     cv::Point(-1,-1), param.iterations);
    return 1;
}

MorphoGene::MorphoGene(MorphoGene::MorphoPtr morphoOperation,
                       MorphoParameters &param, MEPId id):
    Gene(id, 1), morphoOperation_(morphoOperation), parameters_(param)
{

}

MorphoGene::MorphoGene(const MorphoGene &rhs):
    Gene(rhs), morphoOperation_(rhs.morphoOperation_),
    parameters_(rhs.parameters_)
{

}

MEPObjectPtr MorphoGene::cloneGene() const
{
    return MEPObjectPtr( new MorphoGene(*this) );
}

void MorphoGene::writeGene(std::string & gene) const
{
    gene += parameters_.toString();
}

int MorphoGene::getGeneNArguments() const
{
    return 1;
}

void MorphoGene::runGene(const std::vector<cv::Mat> &src, cv::Mat &dst) const
{
    morphoOperation_(src, dst, parameters_);
}

MorphoParameters MorphoParameters::getRandom()
{
    return MorphoParameters({std::rand() % 7,
                            std::rand() % 3,
                            1 + std::rand() % MAX_WIDTH,
                            1 + std::rand() % MAX_HEIGHT,
                            1 + std::rand() % MAX_ITER,
                            1 + std::rand() % MAX_WIDTH,
                            1 + std::rand() % MAX_HEIGHT});
}

std::string MorphoParameters::typeToString() const
{
    switch(morphType)
    {
    case cv::MORPH_ERODE: return "Erode";
    case cv::MORPH_DILATE: return "Dilate";
    case cv::MORPH_OPEN: return "Open";
    case cv::MORPH_CLOSE: return "Close";
    case cv::MORPH_GRADIENT: return "Gradient";
    case cv::MORPH_TOPHAT: return "Tophat";
    case cv::MORPH_BLACKHAT: return "Blackhat";
    default:
        return "Undefined";
    }
}

std::string MorphoParameters::shapeToString() const
{
    switch(morphShape)
    {
    case cv::MORPH_RECT: return "Rect";
    case cv::MORPH_ELLIPSE: return "Ellipse";
    case cv::MORPH_CROSS: return "Cross";
    default:
        return "Undefined";
    }
}

std::string MorphoParameters::toString() const
{
    std::string param;
    param += typeToString();
    param += " ";
    param += shapeToString();
    param += " Size(";
    param += std::to_string(morphWidth);
    param += ",";
    param += std::to_string(morphHeight);
    param += ") ";
    param += std::to_string(iterations);

    return param;
}
