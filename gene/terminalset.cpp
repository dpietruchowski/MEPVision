#include "terminalset.h"

#include "opencv2/highgui/highgui.hpp"

MatPtr TerminalSet::inputImage_( new cv::Mat(cv::imread("kangur.png")) );
MatPtr TerminalSet::nullImage( new cv::Mat(cv::imread("null.png")) );

TerminalSet::TerminalSet()
{
}

MatPtr TerminalSet::getRandomImage() const
{
    if (inputImage_->empty() == true)
        throw "Nie wczytano poprawnie obazka";
    return inputImage_;
}

void TerminalSet::setInputImage(MatPtr inputImage)
{
    inputImage_ = move(inputImage);
}

void TerminalSet::setInputImage(std::string inputImage)
{

    inputImage_ = MatPtr(new cv::Mat(cv::imread(inputImage)));
    if(inputImage_->empty())
        throw "Terminal pusty";
}
