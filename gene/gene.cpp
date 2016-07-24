#include "gene.h"
#include "opencv2/highgui/highgui.hpp"

#include <memory>

Gene::Gene(const MEPId& id, int size):
    MEPGene(id, size)
{

}

Gene::Gene(const Gene& rhs):
    MEPGene(rhs)
{

}

bool Gene::isValidResult() const
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
}

int Gene::assessGene(MEPFitness& fitness) const
{
    return fitness.measure(result_);
}

void Gene::runGene(const Children& children)
{
    std::vector<cv::Mat> arg;
    for(const auto& child: children)
    {
        if(!static_cast<const Gene&> (*child).isValidResult())
            throw "TU BEDZIE ENUM ERROR";
        arg.push_back(static_cast<const Gene&> (*child).result_);
    }

    if(!isValidResult())
        throw "TU BEDZIE ENUM ERROR";
    runGene(arg, result_);
}
