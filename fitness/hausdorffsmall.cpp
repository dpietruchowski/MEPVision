#include "hausdorffsmall.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

MEPFitness *HausdorffSmall::create()
{
    return new HausdorffSmall("kangur_ref.png");
}

HausdorffSmall::HausdorffSmall(string referenceImageName):
    Hausdorff(referenceImageName),
    width_(220), height_(100)
{
}

HausdorffSmall::HausdorffSmall(string referenceImageName,
                             int width, int height):
    Hausdorff(referenceImageName),
    width_(width), height_(height)
{
}

void HausdorffSmall::transformImages(Mat &A, Mat &B)
{
    resize(A, A, Size(width_,height_));
    resize(B, B, Size(width_,height_));
}
