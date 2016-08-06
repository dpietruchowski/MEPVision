#ifndef HAUSDORFF_H
#define HAUSDORFF_H

#include "mepfitness.h"

class MEPSHARED_EXPORT Hausdorff: public MEPFitness
{
public:
    static MEPFitness* create();
    Hausdorff(std::string referenceImageName);

private:
    virtual int fitness(cv::Mat &A, cv::Mat &B) const;
    virtual void transformImages(cv::Mat &A,
                            cv::Mat &B) const;
    int distance(const std::vector<cv::Point> &a,
                 const std::vector<cv::Point> &b) const;
    int maxDistance(const std::vector<cv::Point> &a,
                    const std::vector<cv::Point> &b) const;
};

#endif // HAUSDORFF_H
