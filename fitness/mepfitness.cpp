#include "mepfitness.h"
#include "hamming.h"
#include "hausdorff.h"
#include "hausdorffcanny.h"
#include "hausdorffsmall.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;

MEPFitness::MEPFitness()
{

}

MEPFitness::MEPFitness(string referenceImageName)
{
    referenceImage_ = cv::imread(referenceImageName);
}

MEPFitness::MEPFitness(const cv::Mat &referenceImage):
    referenceImage_(referenceImage)
{

}

int MEPFitness::measure(const cv::Mat &image) const
{
    int measure = 100000;//?
    cv::Mat C, D;
    cv::threshold(image, C, 125, 255, 0);
    threshold(referenceImage_, D, 125, 255, 0);
    cv::extractChannel(C, C, 0);
    cv::extractChannel(D, D, 0);

    measure = this->fitness(C, D);

    return measure;
}

void MEPFitness::setReferenceImage(std::string referenceImage)
{

    referenceImage_ = cv::imread(referenceImage);
    if(referenceImage_.empty())
        throw "Terminal pusty";
}
