#ifndef FUNCTIONSET_H
#define FUNCTIONSET_H

#include "../mep_global.h"

#include <vector>
#include <map>
#include <opencv2/imgproc/imgproc.hpp>

struct MEPSHARED_EXPORT FunctionId
{
    std::string name;
    int nArguments;
};

typedef int(*FunctionPtr) (const std::vector<cv::Mat>&, cv::Mat&);

class MEPSHARED_EXPORT FunctionSet
{
public:
    static const int MAX_N_ARGUMENTS = 2;
public:
    FunctionSet();
    std::pair<FunctionId,FunctionPtr> getRandomFunction() const;
    std::pair<FunctionId,FunctionPtr> getRandomFunction(int nArguments) const;
    std::pair<FunctionId,FunctionPtr> getFunction(std::string name) const;
    std::pair<FunctionId,FunctionPtr> getFunction(int number) const;
    void clear();
    void addFunction(std::string name);
    void deleteFunction(std::string name);
    void addAllFunctions();
    void deleteAllFunctions();
    void setStructuringElement(int size1, int size2, int type);
    int getSize() const;
public:
    static int absDiff(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int addF(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int bitwiseAnd(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int bitwiseXor(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int bitwiseOr(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int minF(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int maxF(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int bitwiseNot(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int thresHold(const std::vector<cv::Mat>& src, cv::Mat& dst);

    static int dilaTe(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int eroDe(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int open(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int close(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int morphGradient(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int topHat(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int blackHat(const std::vector<cv::Mat>& src, cv::Mat& dst);
    static int hitMiss(const std::vector<cv::Mat>& src, cv::Mat& dst);

private:
    typedef std::map<std::string, std::pair<int,FunctionPtr>> Functions;
private:
    std::pair<FunctionId,FunctionPtr> conversion(Functions::const_iterator it) const;
private:
    Functions functionsNotAdded_;
    Functions functions_;
    static cv::Mat element_;
};

#endif // FUNCTIONSET_H
