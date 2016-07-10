#include "hausdorff.h"
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Hausdorff::Hausdorff(string referenceImageName):
    MEPFitness(referenceImageName)
{
}

int Hausdorff::fitness(Mat &A, Mat &B) const
{
    vector<Point> a, b;

    this->transformImages(A, B);
    cv::Canny(A, A, 20, 20*30);
    findNonZero(A, a);
    Canny(B, B, 20, 20*30);
    findNonZero(B, b);
    return this->distance(a, b);
}

void Hausdorff::transformImages(Mat &A, Mat &B) const
{
    //do nothing;
}

int Hausdorff::distance(const vector<Point> &a,
                               const vector<Point> &b) const
{
    int maxDistAB = 0;
    for (size_t i = 0; i < a.size(); i++)
    {
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
