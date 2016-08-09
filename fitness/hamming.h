#ifndef HAMMING_H
#define HAMMING_H

#include "mepfitness.h"

class MEPSHARED_EXPORT Hamming: public MEPFitness
{
public:
    static MEPFitness* create(const cv::Mat &referenceImage);
    Hamming(std::string referenceImageName);
    Hamming(const cv::Mat& referenceImage);

private:
    virtual int fitness(cv::Mat &A, cv::Mat &B) const;
};

#endif // HAMMING_H
