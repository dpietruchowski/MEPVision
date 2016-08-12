#include "hamming.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

MEPFitness *Hamming::create(const cv::Mat &referenceImage)
{
    return new Hamming(referenceImage);
}

Hamming::Hamming(string referenceImageName):
    MEPFitness(referenceImageName)
{
}

Hamming::Hamming(const cv::Mat &referenceImage):
    MEPFitness(referenceImage)
{

}

int Hamming::fitness(cv::Mat &A, cv::Mat &B) const
{
    cv::Mat C;

    cv::bitwise_xor(A, B, C);
    int measure = cv::countNonZero(C); //czarne pixele
    int inpNonZero = A.total() - cv::countNonZero(A); //czarne pixele wejsciowe
    int refNonZero = B.total() - cv::countNonZero(B); //czarne pixele referencyjne
    if(inpNonZero < refNonZero)
    {
        measure += (refNonZero - inpNonZero) * 10;
    }

    inpNonZero = cv::countNonZero(A); //biale pixele wejsciowe
    refNonZero = cv::countNonZero(B); //biale pixele referencyjne
    if(inpNonZero < refNonZero)
    {
        measure += (refNonZero - inpNonZero) * 10;
    }

    return measure;
}
