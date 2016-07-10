#include "hamming.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

Hamming::Hamming(string referenceImageName):
    MEPFitness(referenceImageName)
{
}

int Hamming::fitness(cv::Mat &A, cv::Mat &B) const
{
    cv::Mat C;

    cv::bitwise_xor(A, B, C);
    int measure = cv::countNonZero(C);

    return measure;
}
