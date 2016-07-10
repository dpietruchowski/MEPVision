#ifndef MEPFITNESS_H
#define MEPFITNESS_H

#include <memory>
#include <vector>
#include <opencv2/core/core.hpp>

class MEPFitness
{
public:
    MEPFitness(std::string referenceImageName);
    virtual ~MEPFitness() {}
public:
    int measure(const cv::Mat& image) const;

    void setReferenceImage(std::string referenceImage);

private:
    virtual int fitness(cv::Mat &A, cv::Mat &B) const = 0;
    MEPFitness();

private:
    cv::Mat referenceImage_;
};

#endif // MEPFITNESS_H
