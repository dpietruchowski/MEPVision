#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "core/mepcore.h"
#include "parser/mepparser.h"
#include "mepalgorithm.h"
#include "generationalalgorithm.h"
#include "steadystatealgorithm.h"

using namespace std;

static void parse(char *algName, char *imgName)
{
    MEPParser parser(algName);
    cv::Mat inputImg = cv::imread(imgName, 0);
    TerminalGene::getTerminalSet().setInputImage(MatPtr(new cv::Mat(inputImg)));
    parser.parse();

    MEPId bestGeneId;
    MEPObjectPtr chromosome = parser.getChromosome(bestGeneId);
    bestGeneId.cloneNumber = 1;

    MEPChromosome &ch = dynamic_cast<MEPChromosome&> (*chromosome);

    ThreshParameters param(125,0);
    ThreshGene gene(ThreshGene::thresholdOperation, param, {MEPTHRESHGENE, 0, 0});

    MEPChromosome maskChromosome({MEPCHROMOSOME, 0, 0}, ch.getSize() + 1);
    maskChromosome.clonePart(dynamic_cast<MEPComposite&>(*chromosome),0,ch.getSize() - 1);
    vector<int> args;
    args.push_back(ch.findNumber(bestGeneId));
    dynamic_cast<MEPComposite&>(maskChromosome).addObject(gene.clone(), args);

    Gene& bestGene = const_cast<Gene&> (dynamic_cast<const Gene&>
                                            (dynamic_cast<MEPComposite&>(
                                                 maskChromosome).findByOrder(maskChromosome.getSize() - 1)));
    bestGene.runGeneTree();
    cv::imwrite("output.png", bestGene.getResult());
}

static void algorithm()
{
    GenerationalAlgorithm mep;
    mep.selectionType = RANK_ROULETTESELECTION;
    mep.setChromosomeSize(100);
    mep.setPopulationSize(50);
    mep.nIterations = 200;
////////////////////////////////////////////
    mep.setInputImage("auto.png");
    mep.setReferenceImage("auto_ref.png");
////////////////////////////////////////////
    mep.registerGene(0.1, TERMINALGENE);
    mep.registerGene(0.1, FUNCTIONGENE);

    double sumPro = mep.registerGene(0.8, MORPHOGENE);
    mep.registerGene(1 - sumPro, THRESHGENE);
///////////////////////////////////////////
    mep.registerFitness(1, HAMMING);

//    sumPro = mep.registerFitness(0.05, HAUSDORFF_CANNY);
//    mep.registerFitness(1 - sumPro, HAUSDORFF_SMALL);
///////////////////////////////////////////
    mep.registerOperation(0.15, WORST_ARGUMENTMUTATION);
    mep.registerOperation(0.15, WORST_ATTRIBUTEMUTATION);
    mep.registerOperation(0.2, WORST_COMBINEDMUTATION);

    sumPro = mep.registerOperation(0.2, ONEPOINT_CROSSOVER);
    mep.registerOperation(1 - sumPro, BETTERGENE_CROSSOVER);
//////////////////////////////////////////

    mep.run();
}

void steadystate()
{

    SteadyStateAlgorithm mep;
    mep.selectionType = RANK_ROULETTESELECTION;
    mep.setChromosomeSize(20);
    mep.setPopulationSize(15);
    mep.nIterations = 200;
////////////////////////////////////////////
    mep.setInputImage("auto_bin.png");
    mep.setReferenceImage("auto_ref.png");
////////////////////////////////////////////
    mep.registerGene(0.1, TERMINALGENE);
    mep.registerGene(0.0, FUNCTIONGENE);

    double sumPro = mep.registerGene(0.9, MORPHOGENE);
    mep.registerGene(1 - sumPro, THRESHGENE);
///////////////////////////////////////////
    mep.setFitnessType(HAMMING);
///////////////////////////////////////////
    mep.registerMutation(0.15, UNIFORM_ARGUMENTMUTATION);
    sumPro = mep.registerMutation(0.15, UNIFORM_ATTRIBUTEMUTATION);
    mep.registerMutation(1 - sumPro, UNIFORM_COMBINEDMUTATION);
    mep.registerCrossover(0.5, UNIFORM_CROSSOVER);
    sumPro = mep.registerCrossover(0.3, TWOPOINT_CROSSOVER);
    mep.registerCrossover(1 - sumPro, ONEPOINT_CROSSOVER);
//////////////////////////////////////////

    mep.run();
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
//    parse(argv[1], argv[2]);
    algorithm();
//    steadystate();

    return 0;
}
