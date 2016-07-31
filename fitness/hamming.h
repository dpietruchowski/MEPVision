#ifndef HAMMING_H
#define HAMMING_H

#include "mepfitness.h"

class MEPSHARED_EXPORT Hamming: public MEPFitness
{
public:
    Hamming(std::string referenceImageName);

private:
    virtual int fitness(cv::Mat &A, cv::Mat &B) const;
};

#endif // HAMMING_H
