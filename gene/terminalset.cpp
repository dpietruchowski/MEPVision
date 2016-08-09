#include "terminalset.h"

#include "opencv2/highgui/highgui.hpp"

MatPtr TerminalSet::inputImage_( new cv::Mat(cv::imread("auto.png", 0)) );
MatPtr TerminalSet::nullImage( new cv::Mat(cv::imread("null.png", 0)) );

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
