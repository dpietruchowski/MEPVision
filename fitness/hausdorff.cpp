#include "hausdorff.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

MEPFitness *Hausdorff::create(const cv::Mat& referenceImage)
{
    return new Hausdorff(referenceImage);
}

Hausdorff::Hausdorff(string referenceImageName):
    MEPFitness(referenceImageName)
{
}

Hausdorff::Hausdorff(const Mat &referenceImage):
    MEPFitness(referenceImage)
{

}

int Hausdorff::fitness(Mat &A, Mat &B) const
{
    vector<Point> a, b;

    this->transformImages(A, B);
    if(countNonZero(A) == 0)
        return 100000;
    findNonZero(A, a);
    findNonZero(B, b);

    return this->maxDistance(a, b);
}

void Hausdorff::transformImages(Mat &, Mat &) const
{
    //do nothing;
}

int Hausdorff::distance(const vector<Point> &a,
                               const vector<Point> &b) const
{
    int maxDistAB = 0;
//    int k = 0;
    for (size_t i = 0; i < a.size(); i++)
    {
//        if (i == k*1000)
//        {
//            std::cout << "." << std::flush;
//            k++;
//        }
        int minB = 1000000;
        for (size_t j = 0; j < b.size(); j++)
        {
           int dx = abs(a[i].x - b[j].x);
           int dy = abs(a[i].y - b[j].y);
           int tmpDst = dx*dx + dy*dy;

           if (tmpDst < minB)
           {
               minB = tmpDst;
           }
           if (tmpDst == 0)
           {
               break;
           }
        }
        maxDistAB += minB;
    }

    if (a.size() != 0)
       maxDistAB/=a.size();
    return maxDistAB;
}

int Hausdorff::maxDistance(const vector<Point> &a,
                           const vector<Point> &b) const
{
    int maxDistAB = distance(a, b);
    int maxDistBA = distance(b, a);
    int maxDist = max(maxDistAB, maxDistBA);

    return maxDist;
}
