#ifndef HAUSDORFFCANNY_H
#define HAUSDORFFCANNY_H

#include "hausdorff.h"

class HausdorffCanny: public Hausdorff
{
public:
    HausdorffCanny(std::string referenceImageName);

private:
    virtual void transformImages(cv::Mat& A, cv::Mat& B);
};

#endif // HAUSDORFFCANNY_H
