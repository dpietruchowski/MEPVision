#ifndef MEPFITNESSGENERATOR_H
#define MEPFITNESSGENERATOR_H

#include "../generator/generator.h"
#include "mepfitness.h"

class MEPFitnessGenerator
{
public:
    typedef MEPFitness* (*CreateObjectFunction)(const cv::Mat& image);
public:
    MEPFitnessGenerator();
    void setReferenceImage(const cv::Mat& img);
public:
    MEPFitness* createRandomPtr();
    void registerObject(double probability, CreateObjectFunction function);

private:
    Generator<CreateObjectFunction> generator_;
    cv::Mat referenceImage_;
};

#endif // MEPFITNESSGENERATOR_H
