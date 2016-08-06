#include "hamming.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

MEPFitness *Hamming::create()
{
    return new Hamming("kangur_ref.png");
}

Hamming::Hamming(string referenceImageName):
    MEPFitness(referenceImageName)
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

    return measure;
}
