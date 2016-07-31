#ifndef HAUSDORFFSMALL_H
#define HAUSDORFFSMALL_H

#include "hausdorff.h"

class MEPSHARED_EXPORT HausdorffSmall: public Hausdorff
{
public:
    HausdorffSmall(std::string referenceImageName);
    HausdorffSmall(std::string referenceImageName,
                  int width, int height);
private:
    virtual void transformImages(cv::Mat& A, cv::Mat& B);
private:
    int width_;
    int height_;
};

#endif // HAUSDORFFSMALL_H
