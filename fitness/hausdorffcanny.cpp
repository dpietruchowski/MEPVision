#include "hausdorffcanny.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

HausdorffCanny::HausdorffCanny(string referenceImageName):
    Hausdorff(referenceImageName)
{
}


void HausdorffCanny::transformImages(Mat &A, Mat &B)
{
    Canny(A, A, 20, 20*30);
    Canny(B, B, 20, 20*30);
}