#include "morphogene.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <iterator>

using namespace std;

MEPObjectPtr MorphoGene::create(unsigned int geneNumber)
{
    MEPId id = {MEPMORPHOGENE, geneNumber, 0};
    MorphoElement element;
    element.element = cv::Mat(1 + std::rand() % MorphoParameters::MAX_WIDTH,
                    1 + std::rand() % MorphoParameters::MAX_HEIGHT,
                    CV_8U);
    cv::randu(element.element, cv::Scalar(0), cv::Scalar(2));
    MorphoParameters param = MorphoParameters::getRandom();
    return MEPObjectPtr(new MorphoGene(MorphoGene::morphologyOperation, param,
                                       element, id));
}

int MorphoGene::morphologyOperation(const std::vector<cv::Mat> &src, cv::Mat &dst,
                                    const MorphoParameters& param,
                                    const cv::Mat& element)
{
    if (src.size() != 1)
    {
        std::string exception = "Zla liczba argumentow";
        throw exception;
    }

//    if((param.morphShape > 2) || (param.morphShape < 0))
//        throw std::string("MorphoGene::morphologyOperation: Bad shape");
    if((param.morphType > 6) || (param.morphType < 0))
        throw std::string("MorphoGene::morphologyOperation: Bad morpho type");

    const cv::Mat& src1 = src[0];/*
    cv::Point anchor = cv::Point(10,10);
    cv::Mat element = cv::getStructuringElement(param.morphShape,
                                                cv::Size(param.morphWidth,
                                                     param.morphHeight),
                                                cv::Point(-1,-1));*/
    cv::morphologyEx(src1, dst, param.morphType, element,
                     cv::Point(-1,-1), param.iterations);
    return 1;
}

MorphoGene::MorphoGene(MorphoGene::MorphoPtr morphoOperation,
                       const MorphoParameters &param,
                       const MorphoElement& element, const MEPId& id):
    Gene(id, 1), morphoOperation_(morphoOperation), parameters_(param),
    structElement_(element)
{

}

MorphoGene::MorphoGene(const MorphoGene &rhs):
    Gene(rhs), morphoOperation_(rhs.morphoOperation_),
    parameters_(rhs.parameters_), structElement_(rhs.structElement_)
{

}

MEPObjectPtr MorphoGene::cloneGene() const
{
    return MEPObjectPtr( new MorphoGene(*this) );
}

void MorphoGene::saveGene(std::string &gene) const
{
    gene += "#";
    gene += parameters_.toString();

    int nRows = structElement_.element.rows;
    int nCols = structElement_.element.cols;

    gene += "#";
    gene += "%";
    gene += std::to_string(nRows);
    gene += " ";
    gene += std::to_string(nCols);

    gene += "[";
    gene += structElement_.toString();
    gene += "]";
    gene += "%";
}

void MorphoGene::writeGene(std::string & gene) const
{
    gene += parameters_.toString();
    gene += " Size(";
    gene += to_string(structElement_.element.rows);
    gene += ",";
    gene += to_string(structElement_.element.cols);
    gene += ")";
}

int MorphoGene::getGeneNArguments() const
{
    return 1;
}

void MorphoGene::runGene(const std::vector<cv::Mat> &src, cv::Mat &dst) const
{
    morphoOperation_(src, dst, parameters_, structElement_.element);
}

MorphoParameters MorphoParameters::getRandom()
{
    return MorphoParameters(std::rand() % 7,
                            1 + std::rand() % MAX_ITER);
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

int MorphoParameters::typeFromString(std::string &type) const
{
    if(type == "Erode") return cv::MORPH_ERODE;
    if(type == "Dilate") return cv::MORPH_DILATE;
    if(type == "Open") return cv::MORPH_OPEN;
    if(type == "Close") return cv::MORPH_CLOSE;
    if(type == "Gradient") return cv::MORPH_GRADIENT;
    if(type == "Tophat") return cv::MORPH_TOPHAT;
    if(type == "Blackhat") return cv::MORPH_BLACKHAT;

    throw "MorphoParameters::typeFromString: Zly parametr";
}

//std::string MorphoParameters::shapeToString() const
//{
//    switch(morphShape)
//    {
//    case cv::MORPH_RECT: return "Rect";
//    case cv::MORPH_ELLIPSE: return "Ellipse";
//    case cv::MORPH_CROSS: return "Cross";
//    default:
//        return "Undefined";
//    }
//}

std::string MorphoParameters::toString() const
{    
    std::string param;
    param += typeToString();
//    param += " ";
//    param += shapeToString();
    param += " ";
    param += std::to_string(iterations);

    return param;
}

//Format: "Gradient 2"
void MorphoParameters::fromString(const std::string & param)
{
    size_t space = param.find_first_of(" ");
    string type = param.substr(0, space);
    morphType = typeFromString(type);
    string iter = param.substr(space+1);
    iterations = stoi(iter);
}

string MorphoElement::toString() const
{
    vector<int> vec(element.ptr(), element.ptr() + element.total());
    stringstream ss;
    copy(vec.begin(), vec.end(), std::ostream_iterator<int>(ss));
    return ss.str();
}

void MorphoElement::fromString(const string &selement, int nRows, int nCols)
{
    if(selement.size() != nRows * nCols)
        throw std::string("MorphoElement::fromString: Wrong selement");
    element = cv::Mat(nRows, nCols, CV_8U);
    vector<int> vv(selement.begin(), selement.end());
    for_each(vv.begin(),vv.end(),[](int &a){a-=48;});
    int k = 0;
    for(int i=0; i<element.rows; ++i)
         for(int j=0; j<element.cols; ++j)
              element.at<unsigned char>(i, j) = vv[k++];
}
