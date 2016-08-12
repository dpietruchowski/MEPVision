#include "functionset.h"
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat FunctionSet::element_ = getStructuringElement(MORPH_ELLIPSE, Size(5,7));

FunctionSet::FunctionSet()
{
    pair<int,FunctionPtr> f;
    pair<string, pair<int,FunctionPtr>> p;

    f = make_pair(2, FunctionSet::absDiff);
    p = make_pair("absDiff", f);
//    functionsNotAdded_.insert(p);
    f = make_pair(2, FunctionSet::addF);
    p = make_pair("addF", f);
    //functionsNotAdded_.insert(p);              <-----------------nie dodana
    f = make_pair(2, FunctionSet::bitwiseAnd);
    p = make_pair("bitwiseAnd", f);
    functionsNotAdded_.insert(p);
    f = make_pair(2, FunctionSet::bitwiseXor);
    p = make_pair("bitwiseXor", f);
    functionsNotAdded_.insert(p);
    f = make_pair(2, FunctionSet::bitwiseOr);
    p = make_pair("bitwiseOr", f);
    functionsNotAdded_.insert(p);
    f = make_pair(2, FunctionSet::minF);
    p = make_pair("minF", f);
    //functionsNotAdded_.insert(p);              <-----------------nie dodana
    f = make_pair(2, FunctionSet::maxF);
    p = make_pair("maxF", f);
    //functionsNotAdded_.insert(p);              <-----------------nie dodana
    f = make_pair(1, FunctionSet::bitwiseNot);
    p = make_pair("bitwiseNot", f);
    functionsNotAdded_.insert(p);
    f = make_pair(1, FunctionSet::thresHold);
    p = make_pair("threshold", f);
//    functionsNotAdded_.insert(p);               <-----------------nie dodana

    f = make_pair(1, FunctionSet::hitMiss);
    p = make_pair("hitMiss", f);
//    functionsNotAdded_.insert(p);      //        <-----------------nie dodana

    addAllFunctions();
}

int FunctionSet::absDiff(const vector<Mat>& src, Mat& dst)
{
    if (src.size() != 2)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    const Mat& src2 = src[1];
    absdiff(src1,src2,dst);
    return 2;
}

int FunctionSet::addF(const vector<Mat>& src, Mat& dst)
{
    if (src.size() != 2)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    const Mat& src2 = src[1];
    add(src1,src2,dst);
    return 2;
}

int FunctionSet::bitwiseAnd(const vector<Mat>& src, Mat& dst)
{
    if (src.size() != 2)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    const Mat& src2 = src[1];
    bitwise_and(src1,src2,dst);
    return 2;
}

int FunctionSet::bitwiseXor(const vector<Mat>& src, Mat& dst)
{
    if (src.size() != 2)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    const Mat& src2 = src[1];
    bitwise_xor(src1,src2,dst);
    return 2;
}

int FunctionSet::bitwiseOr(const vector<Mat>& src, Mat& dst)
{
    if (src.size() != 2)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    const Mat& src2 = src[1];
    bitwise_or(src1,src2,dst);
    return 2;
}

int FunctionSet::maxF(const vector<Mat>& src, Mat& dst)
{
    if (src.size() != 2)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    const Mat& src2 = src[1];
    max(src1,src2,dst);
    return 2;
}

int FunctionSet::minF(const vector<Mat>& src, Mat& dst)
{
    if (src.size() != 2)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    const Mat& src2 = src[1];
    min(src1,src2,dst);
    return 2;
}

int FunctionSet::bitwiseNot(const vector<Mat>& src, Mat& dst )
{
    if (src.size() != 1)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    bitwise_not(src1,dst);
    return 1;
}

int FunctionSet::thresHold(const vector<Mat>& src, Mat& dst)
{
    if (src.size() != 1)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];
    threshold(src1, dst, 100, 255, 0);
    return 1;
}

int FunctionSet::hitMiss(const std::vector<Mat> &src, Mat &dst)
{
    if (src.size() != 1)
    {
        string exception = "Zla liczba argumentow";
        throw exception;
    }
    const Mat& src1 = src[0];

    CV_Assert(src1.type() == CV_8U && src1.channels() == 1);

    cv::Mat k1 = (element_ == 1) / 255;
    cv::Mat k2 = (element_ == -1) / 255;

    cv::normalize(src1, src1, 0, 1, cv::NORM_MINMAX);

    cv::Mat e1, e2;
    cv::erode(src1, e1, k1, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT, cv::Scalar(0));
    cv::erode(1-src1, e2, k2, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT, cv::Scalar(0));
    if (countNonZero(k2) <= 0){
        e2 = src1;
    }
    dst = e1 & e2;

    return 1;
}



pair<FunctionId,FunctionPtr> FunctionSet::getRandomFunction() const
{
    Functions::const_iterator it = functions_.begin();
    std::advance(it, rand() % functions_.size() );

    return conversion(it);
}

pair<FunctionId,FunctionPtr> FunctionSet::getRandomFunction(int argumentsNumber) const
{
    Functions argFunctions;
    Functions::const_iterator it = functions_.begin();
        //Rewrite funciton with the same number of arguments as argumentsNumber
    for(auto it = functions_.begin(); it != functions_.end();)
    {
        if(it->second.first == argumentsNumber)
            argFunctions.insert(make_pair(it->first,it->second));
        ++it;
    }

    if (argFunctions.size() < 1)
    {
        string exception = "Nie ma zadnej funkcji o takiej liczbie argumentow";
        throw exception;
    }

    it = argFunctions.begin();
    std::advance(it, rand() % argFunctions.size() );

    return this->conversion(it);
}

pair<FunctionId,FunctionPtr> FunctionSet::getFunction(string name) const
{
    Functions::const_iterator it = functions_.find(name);

    if (it == functions_.end())
    {
        string exception = "Nie ma zadnej funkcji o takiej nazwie"
                           "lub nie jest dodana";
        throw exception;
    }

    return this->conversion(it);
}

void FunctionSet::clear()
{
    this->functions_.clear();
}

void FunctionSet::addFunction(string name)
{
    Functions::iterator it;
    it = functionsNotAdded_.find(name);
    functions_.insert(make_pair(it->first, it->second));
}

void FunctionSet::deleteFunction(string name)
{
    functions_.erase(functions_.find(name));
}

int FunctionSet::getSize() const
{
    return functions_.size();
}

std::pair<FunctionId,FunctionPtr>  FunctionSet::getFunction(int number) const
{
    if(number >= this->getSize())
    {
        throw "Argument wiekszy niz liczba funkcji";
    }

    Functions::const_iterator it = functionsNotAdded_.end();
    for(int i = 0; i <= number; i++)
    {
        it--;
    }
    return this->conversion(it);
}

void FunctionSet::addAllFunctions()
{
    this->deleteAllFunctions();
    for(const auto& it : functionsNotAdded_)
    {
        functions_.insert(make_pair(it.first, it.second));
    }
}

void FunctionSet::deleteAllFunctions()
{
    functions_.clear();
}

void FunctionSet::setStructuringElement(int size1, int size2, int type)
{
    element_ = getStructuringElement(type, Size(size1, size2));
}

pair<FunctionId,FunctionPtr> FunctionSet::conversion(Functions::const_iterator it) const
{
    string name = it->first;
    int argumentsNumber = it->second.first;
    FunctionPtr function = it->second.second;
    FunctionId id = {name, argumentsNumber};

    return make_pair(id,function);
}
