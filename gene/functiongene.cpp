#include "functiongene.h"

#include "meptypes.h"

using namespace std;

FunctionSet FunctionGene::functions_ = FunctionSet();

FunctionSet& FunctionGene::getFunctionSet()
{
    return functions_;
}

FunctionGene::FunctionGene(std::pair<FunctionId, FunctionPtr> p, MEPId id):
    Gene(id)
{
    functionId_ = p.first;
    function_ = p.second;
}

FunctionGene::FunctionGene(std::pair<FunctionId, FunctionPtr> p):
    Gene(MEPId())
{
    functionId_ = p.first;
    function_ = p.second;
}

FunctionGene::FunctionGene(const FunctionGene &functionGene):
    Gene(functionGene)
{
    functionId_ = functionGene.functionId_;
    function_ = functionGene.function_;
}

MEPObjectPtr FunctionGene::create(unsigned int geneNumber)
{
    MEPId id = {MEPGENE, geneNumber, 0};
    return MEPObjectPtr(new FunctionGene(functions_.getRandomFunction(), id));
}

MEPObjectPtr FunctionGene::create(unsigned int geneNumber, int nArguments)
{
    MEPId id = {MEPGENE, geneNumber, 0};
    return MEPObjectPtr(new FunctionGene(functions_.getRandomFunction(nArguments),
                                         id));
}

void FunctionGene::setFunction(std::pair<FunctionId, FunctionPtr> p)
{
    functionId_ = p.first;
    function_ = move(p.second);
}

MEPObjectPtr FunctionGene::cloneObject() const
{
    return MEPObjectPtr( new FunctionGene(*this) );
}

void FunctionGene::writeGene(std::string& gene) const
{
    gene += functionId_.name;
    gene += " ";
    gene += to_string(functionId_.nArguments);
}

int FunctionGene::getGeneNArguments() const
{
    return functionId_.nArguments;
}

void FunctionGene::runGene(const std::vector<cv::Mat>& src, cv::Mat& dst) const
{
    function_(src, dst);
}
