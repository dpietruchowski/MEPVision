#include "mepfitnessgenerator.h"

MEPFitnessGenerator::MEPFitnessGenerator()
{

}

void MEPFitnessGenerator::setReferenceImage(const cv::Mat &img)
{
    referenceImage_ = img;
}

MEPFitness *MEPFitnessGenerator::createRandomPtr()
{
    CreationCounter<CreateObjectFunction> counter = generator_.createRandom();
    CreateObjectFunction function = counter.callbackFunction;

    return function(referenceImage_);
}

void MEPFitnessGenerator::registerObject(double probability, MEPFitnessGenerator::CreateObjectFunction function)
{
    generator_.registerCallback(probability, function);
}

