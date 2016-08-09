#ifndef HAUSDORFFSMALL_H
#define HAUSDORFFSMALL_H

#include "hausdorff.h"

class MEPSHARED_EXPORT HausdorffSmall: public Hausdorff
{
public:
    static MEPFitness* create(const cv::Mat& referenceImage);
    HausdorffSmall(std::string referenceImageName);
    HausdorffSmall(std::string referenceImageName,
                  int width, int height);
    HausdorffSmall(const cv::Mat& referenceImage);
private:
    virtual void transformImages(cv::Mat& A, cv::Mat& B) const;
private:
    int width_;
    int height_;
};

#endif // HAUSDORFFSMALL_H
