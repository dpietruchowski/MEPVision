#include "gene.h"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <memory>

Gene::Gene(const MEPId& id, int size):
    MEPGene(id, size)
{

}

Gene::Gene(const Gene& rhs):
    MEPGene(rhs)
{

}

bool Gene::isValidResults() const
{
    return !result_.empty();
}

void Gene::clearGeneResult()
{
    result_.release();
}

void Gene::showGene(const std::string& windowName) const
{
    cv::imshow(windowName, result_);
    cv::waitKey();
}

int Gene::assessGene(MEPFitness& fitness) const
{
    return fitness.measure(result_);
}

cv::Mat Gene::getResult() const
{
    cv::Mat copy;
    result_.copyTo(copy);

    return copy;
}

void Gene::runGene(const MEPGenes& children)
{
    std::vector<cv::Mat> arg;
    for(const auto& child: children)
    {
        if(!dynamic_cast<const Gene&> (child.get()).isValidResults())
            throw "Gene::runGene: TU BEDZIE ENUM ERROR";
        arg.push_back(static_cast<const Gene&> (child.get()).result_);
    }

    runGene(arg, result_);
}
