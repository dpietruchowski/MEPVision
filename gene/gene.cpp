#include "gene.h"
#include "opencv2/highgui/highgui.hpp"

Gene::Gene(const MEPId& id):
    MEPGene(id)
{

}

Gene::Gene(const Gene& rhs):
    MEPGene(rhs)
{

}

bool Gene::isValidResult(const cv::Mat& result) const
{
    return !result.empty();
}

void Gene::clearGeneResult(cv::Mat& result) const
{
    result.release();
}

void Gene::showGene(const std::string& windowName, const cv::Mat& result) const
{
    cv::imshow(windowName, result);
}
