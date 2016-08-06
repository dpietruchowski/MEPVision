#ifndef HAUSDORFFCANNY_H
#define HAUSDORFFCANNY_H

#include "hausdorff.h"

class MEPSHARED_EXPORT HausdorffCanny: public Hausdorff
{
public:
    static MEPFitness* create();
    HausdorffCanny(std::string referenceImageName);

private:
    virtual void transformImages(cv::Mat& A, cv::Mat& B);
};

#endif // HAUSDORFFCANNY_H
