#ifndef TERMINALSET_H
#define TERMINALSET_H

#include "../mep_global.h"

#include <cstdlib>
#include <memory>
#include <opencv2/core/core.hpp>

typedef std::shared_ptr<cv::Mat> MatPtr;

class MEPSHARED_EXPORT TerminalSet
{
public:
    static MatPtr nullImage;
public:
    TerminalSet();
    MatPtr getRandomImage() const;
    MatPtr getInputImage() const;
    void setInputImage(MatPtr inputImage);  
    void setInputImage(std::string inputImage);

private:
    static MatPtr inputImage_;
    static MatPtr terminal;
};

#endif // TERMINALSET_H
