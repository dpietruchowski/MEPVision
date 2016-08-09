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

using namespace std;

static void parse()
{
    MEPParser parser("Best.txt");
    parser.parse();

    MEPObjectPtr chromosome = parser.getChromosome();
    cv::Mat refImg = cv::imread("auto_ref.png", 0);
    MEPFitness *fitness = Hamming::create(refImg);

    //chromosome->run(*fitness);

    ThreshParameters param(105,0);
    ThreshGene gene(ThreshGene::thresholdOperation, param, {MEPTHRESHGENE, 0, 0});

    MEPChromosome ch({MEPCHROMOSOME, 0, 0}, 31);
    ch.clonePart(dynamic_cast<MEPComposite&>(*chromosome),0,29);
    vector<int> args;
    args.push_back(28);
    dynamic_cast<MEPComposite&>(ch).addObject(gene.clone(), args);

    Gene& bestGene = const_cast<Gene&> (dynamic_cast<const Gene&>
                                            (dynamic_cast<MEPComposite&>(
                                                 ch).findByOrder(30)));
    bestGene.runGeneTree();
    std::string name = "UDALO SIE";
    name += ".png";
    cv::imwrite(name, bestGene.getResult());

    delete fitness;
}

static void algorithm()
{
    MEPAlgorithm mep;
    mep.selectionType = RANK_ROULETTESELECTION;
    mep.setChromosomeSize(20);
    mep.setPopulationSize(100);
    mep.nIterations = 200;
////////////////////////////////////////////
    mep.setInputImage("auto2.png");
    mep.setReferenceImage("auto2_ref.png");
////////////////////////////////////////////
    mep.registerGene(0.1, TERMINALGENE);
    mep.registerGene(0.2, FUNCTIONGENE);

    double sumPro = mep.registerGene(0.5, MORPHOGENE);
    mep.registerGene(1 - sumPro, THRESHGENE);
///////////////////////////////////////////
    mep.registerFitness(0.85, HAMMING);

    sumPro = mep.registerFitness(0.1, HAUSDORFF_CANNY);
    mep.registerFitness(1 - sumPro, HAUSDORFF_SMALL);
///////////////////////////////////////////
    mep.registerOperation(0.15, UNIFORM_ARGUMENTMUTATION);
    mep.registerOperation(0.15, UNIFORM_ATTRIBUTEMUTATION);

    sumPro = mep.registerOperation(0.2, UNIFORM_COMBINEDMUTATION);
    mep.registerOperation(1 - sumPro, UNIFORM_CROSSOVER);
//////////////////////////////////////////

    mep.run();
}

int main()
{
    srand(time(NULL));
//    parse();
    algorithm();

    return 0;
}
