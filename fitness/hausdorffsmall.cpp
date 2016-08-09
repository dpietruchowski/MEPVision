#include "hausdorffsmall.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

MEPFitness *HausdorffSmall::create(const cv::Mat& referenceImage)
{
    return new HausdorffSmall(referenceImage);
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

HausdorffSmall::HausdorffSmall(const Mat &referenceImage):
    Hausdorff(referenceImage),
    width_(220), height_(100)
{

}

void HausdorffSmall::transformImages(Mat &A, Mat &B) const
{
    resize(A, A, Size(width_,height_));
    resize(B, B, Size(width_,height_));
}
