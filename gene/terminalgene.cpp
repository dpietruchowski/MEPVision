#include "terminalgene.h"

#include "meptypes.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <memory>

using namespace std;
using namespace cv;

TerminalSet TerminalGene::terminals_ = TerminalSet();

TerminalSet& TerminalGene::getTerminalSet()
{
    return terminals_;
}

TerminalGene::TerminalGene(MatPtr image, MEPId id):
    Gene(id, 0), terminal_(image)
{
    terminalName_ = "inputImg";
}

TerminalGene::TerminalGene(MatPtr image):
    Gene(MEPId(), 0), terminal_(image)
{
    terminalName_ = "inputImg";
}

TerminalGene::TerminalGene(const TerminalGene &terminalGene):
    Gene(terminalGene), terminal_(terminalGene.terminal_)
{
    terminalName_ = terminalGene.terminalName_;
}

MEPObjectPtr TerminalGene::create(unsigned int geneNumber)
{
    MEPId id = {MEPType::MEPGENE, geneNumber, 0};
    return MEPObjectPtr(new TerminalGene(terminals_.getRandomImage(), id));
}

void TerminalGene::setTerminal(MatPtr newTerminal)
{
    terminal_ = move(newTerminal);
}

MEPObjectPtr TerminalGene::cloneGene() const
{
    return MEPObjectPtr( new TerminalGene(*this) );
}

void TerminalGene::writeGene(std::string& gene) const
{
    gene += terminalName_;
}

int TerminalGene::getGeneNArguments() const
{
    return 0;
}

void TerminalGene::runGene(const std::vector<cv::Mat>&, cv::Mat& dst) const
{
    terminal_->copyTo(dst);
}


MEPObjectPtr TerminalGene::mutate() const
{
	MEPObjectPtr mutated = cloneGene();
    std::static_pointer_cast<TerminalGene> (mutated)->setTerminal(terminals_.getRandomImage());
	return mutated;
}
