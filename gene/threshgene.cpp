#include "threshgene.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace std;

MEPObjectPtr ThreshGene::create(unsigned int geneNumber)
{
    MEPId id = {MEPTHRESHGENE, geneNumber, 0};
    ThreshParameters param = ThreshParameters::getRandom();
    return MEPObjectPtr(new ThreshGene(ThreshGene::thresholdOperation, param,
                                       id));
}

int ThreshGene::thresholdOperation(const std::vector<cv::Mat> &src, cv::Mat &dst,
                                   const ThreshParameters &param)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }

    if((param.threshType > 4) || (param.threshType < 0))
        throw std::string("ThreshGene::thresholdOperation Bad morpho type");

    const cv::Mat& src1 = src[0];
    cv::threshold(src1, dst, param.threshValue, 255, param.threshType);
    return 1;
}

ThreshGene::ThreshGene(ThreshGene::ThreshPtr operation,
                       ThreshParameters & param, MEPId id):
    Gene(id, 1), threshOperation_(operation), parameters_(param)
{

}

ThreshGene::ThreshGene(const ThreshGene &rhs):
    Gene(rhs), threshOperation_(rhs.threshOperation_), parameters_(rhs.parameters_)
{

}

MEPObjectPtr ThreshGene::cloneGene() const
{
    return MEPObjectPtr( new ThreshGene(*this) );
}

void ThreshGene::saveGene(std::string &gene) const
{
    gene += "#";
    gene += parameters_.toString();
    gene += "#";
}

void ThreshGene::writeGene(std::string & gene) const
{
    gene += parameters_.toString();
}

int ThreshGene::getGeneNArguments() const
{
    return 1;
}

void ThreshGene::runGene(const std::vector<cv::Mat> &src, cv::Mat &dst) const
{
    thresholdOperation(src, dst, parameters_);
}

ThreshParameters ThreshParameters::getRandom()
{
    return ThreshParameters(1 + std::rand() % 254,
                            std::rand() % 5);
}

std::string ThreshParameters::typeToString() const
{
    switch(threshType)
    {
    case cv::THRESH_BINARY: return "ThreshBinary";
    case cv::THRESH_BINARY_INV: return "ThreshBinaryInv";
    case cv::THRESH_TOZERO: return "ThreshToZero";
    case cv::THRESH_TOZERO_INV: return "ThreshToZeroInv";
    case cv::THRESH_TRUNC: return "ThreshTrunc";
    default:
        return "Undefined";
    }
}

int ThreshParameters::typeFromString(const std::string &type) const
{
    if(type == "ThreshBinary") return cv::THRESH_BINARY;
    if(type == "ThreshBinaryInv") return cv::THRESH_BINARY_INV;
    if(type == "ThreshToZero") return cv::THRESH_TOZERO;
    if(type == "ThreshToZeroInv") return cv::THRESH_TOZERO_INV;
    if(type == "ThreshTrunc") return cv::THRESH_TRUNC;

    throw string("ThreshParameters::typeFromString: zly typ");
}

std::string ThreshParameters::toString() const
{
    std::string param;
    param += typeToString();
    param += " ";
    param += std::to_string(threshValue);

    return param;
}

//Format: "ThreshTrunc 32"
void ThreshParameters::fromString(const std::string &param)
{
    size_t space = param.find_first_of(" ");
    string type = param.substr(0, space);
    threshType = typeFromString(type);
    string value = param.substr(space+1);
    threshValue = stoi(value);
}
