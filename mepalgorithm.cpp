#include "mepalgorithm.h"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;

int MEPAlgorithm::ChromosomeSize;
int MEPAlgorithm::PopulationSize;

MEPAlgorithm::MEPAlgorithm():
    population_({MEPPOPULATION, 0, 0}, 100),
    sumProGene_(0), sumProFitness_(0), sumProOperation_(0)
{
    generator_.registerChromosome(MEPAlgorithm::createChromosome);
    generator_.registerPopulation(MEPAlgorithm::createPopulation);
    FunctionGene::getFunctionSet().addAllFunctions();
}

double MEPAlgorithm::registerGene(double probability, GeneType type)
{
    switch(type)
    {
    case TERMINALGENE:
        generator_.registerGene(probability, TerminalGene::create);
        break;
    case FUNCTIONGENE:
        generator_.registerGene(probability, FunctionGene::create);
        break;
    case MORPHOGENE:
        generator_.registerGene(probability, MorphoGene::create);
        break;
    case THRESHGENE:
        generator_.registerGene(probability, ThreshGene::create);
        break;
    default:
        break;
    }

    sumProGene_ += probability;
    return sumProGene_;
}

double MEPAlgorithm::registerFitness(double probability, FitnessType type)
{
    switch(type)
    {
    case HAMMING:
        fitnessGenerator_.registerObject(probability, Hamming::create);
        break;
    case HAUSDORFF:
        fitnessGenerator_.registerObject(probability, Hausdorff::create);
        break;
    case HAUSDORFF_CANNY:
        fitnessGenerator_.registerObject(probability, HausdorffCanny::create);
        break;
    case HAUSDORFF_SMALL:
        fitnessGenerator_.registerObject(probability, HausdorffSmall::create);
        break;
    default:
        break;
    }

    sumProFitness_ += probability;
    return sumProFitness_;
}

double MEPAlgorithm::registerOperation(double probability, OperationType type)
{
    switch(type)
    {
    case RAND_ARGUMENTMUTATION:
        operationGenerator_.registerObject(probability,
                                           RandArgumentMutation::create);
        break;
    case WORST_ARGUMENTMUTATION:
        operationGenerator_.registerObject(probability,
                                           WorstArgumentMutation::create);
        break;
    case UNIFORM_ARGUMENTMUTATION:
        operationGenerator_.registerObject(probability,
                                           UniformArgumentMutation::create);
        break;
    case RAND_ATTRIBUTEMUTATION:
        operationGenerator_.registerObject(probability,
                                           RandAttributeMutation::create);
        break;
    case WORST_ATTRIBUTEMUTATION:
        operationGenerator_.registerObject(probability,
                                           WorstAttributeMutation::create);
        break;
    case UNIFORM_ATTRIBUTEMUTATION:
        operationGenerator_.registerObject(probability,
                                           UniformAttributeMutation::create);
        break;
    case RAND_COMBINEDMUTATION:
        operationGenerator_.registerObject(probability,
                                           RandCombinedMutation::create);
        break;
    case WORST_COMBINEDMUTATION:
        operationGenerator_.registerObject(probability,
                                           WorstCombinedMutation::create);
        break;
    case UNIFORM_COMBINEDMUTATION:
        operationGenerator_.registerObject(probability,
                                           UniformCombinedMutation::create);
        break;
    case UNIFORM_CROSSOVER:
        operationGenerator_.registerObject(probability,
                                           UniformCrossover::create);
        break;
    case ONEPOINT_CROSSOVER:
        operationGenerator_.registerObject(probability,
                                           OnePointCrossover::create);
        break;
    case TWOPOINT_CROSSOVER:
        operationGenerator_.registerObject(probability,
                                           TwoPointCrossover::create);
        break;
    case BETTERGENE_CROSSOVER:
        operationGenerator_.registerObject(probability,
                                           BetterGeneCrossover::create);
        break;
    default:
        break;
    }

    sumProOperation_ += probability;
    return sumProOperation_;
}

void MEPAlgorithm::setInputImage(const std::string &path)
{
    inputImage_ = cv::imread(path, 0);
    TerminalGene::getTerminalSet().setInputImage(MatPtr(new cv::Mat(inputImage_)));
}

void MEPAlgorithm::setReferenceImage(const std::string &path)
{
    referenceImage_ = cv::imread(path, 0);
    fitnessGenerator_.setReferenceImage(referenceImage_);
}

void MEPAlgorithm::setChromosomeSize(int size)
{
    chromosomeSize_ = size;
    operationGenerator_.setMaxNMutatedGene(chromosomeSize_/2 - 1);
    ChromosomeSize = chromosomeSize_;
}

void MEPAlgorithm::setPopulationSize(int size)
{
    populationSize_ = size;
    PopulationSize = populationSize_;
}

void MEPAlgorithm::run()
{
    population_.init(generator_);
    for(int i = 0; i < nIterations; ++i)
    {
        cout << "Iteracja nr " << i << " " << flush;
        MEPFitness *fitness = fitnessGenerator_.createRandomPtr();
        population_.run(*fitness);

        saveImage(i);
        saveAlgorithm(i);

        MEPObjectPtr reproducedPopulation = population_.
                                                reproduce(selectionType,
                                                          generator_,
                                                          operationGenerator_);
//        MEPObjectPtr reproducedPopulation = population_.
//                                                reproduce(selectionType,
//                                                          generator_,
//                                                          0.9);
        population_.swap(dynamic_cast<MEPPopulation&>(*reproducedPopulation));

        cout << endl;
        delete fitness;
    }
}

void MEPAlgorithm::saveImage(int i)
{
    const MEPComposite& pop = dynamic_cast<MEPComposite&> (population_);
    const MEPChromosome& bestChromosome = dynamic_cast<const MEPChromosome&>
                                          (pop.findByRank(0));

    Gene& bestGene = const_cast<Gene&> (dynamic_cast<const Gene&>
                                      (bestChromosome.findByRank(0)));
    bestGene.runGeneTree();
    string name = "Best ";
    name += to_string(i);
    name += ".png";
    imwrite(savePath + name, bestGene.getResult());
    bestGene.clearResult();
}

void MEPAlgorithm::saveAlgorithm(int i)
{
    const MEPComposite& pop = dynamic_cast<MEPComposite&> (population_);
    const MEPChromosome& bestChromosome = dynamic_cast<const MEPChromosome&>
                                          (pop.findByRank(0));
    string name = "Best_";
    name += std::to_string(i);
    name += "_";
    name += std::to_string(bestChromosome.getSize());
    name += ".txt";
    fstream file;
    file.open(savePath + name, fstream::out);
    file << bestChromosome.save();
    file.close();
}

void MEPAlgorithm::parseOptions(const std::string &path)
{

}

MEPObjectPtr MEPAlgorithm::createChromosome(unsigned int number)
{
    MEPObjectPtr chromosome(new MEPChromosome({MEPCHROMOSOME, number, 0}, ChromosomeSize));
    return chromosome;
}

MEPObjectPtr MEPAlgorithm::createPopulation(unsigned int number)
{
    MEPObjectPtr population(new MEPPopulation({MEPPOPULATION, number, 0}, PopulationSize));
    return population;
}

