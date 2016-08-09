#include "hausdorffcanny.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

MEPFitness *HausdorffCanny::create(const cv::Mat& referenceImage)
{
    return new HausdorffCanny(referenceImage);
}

HausdorffCanny::HausdorffCanny(string referenceImageName):
    Hausdorff(referenceImageName)
{
}

HausdorffCanny::HausdorffCanny(const Mat &referenceImage):
    Hausdorff(referenceImage)
{

}


void HausdorffCanny::transformImages(Mat &A, Mat &B) const
{
    Canny(A, A, 20, 20*30);
    Canny(B, B, 20, 20*30);
}
