#include "mepalgorithm.h"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <iterator>

using namespace std;

int MEPAlgorithm::ChromosomeSize;
int MEPAlgorithm::PopulationSize;

MEPAlgorithm::MEPAlgorithm():
    population_({MEPPOPULATION, 0, 0}, 100),
    sumProGene_(0), sumProFitness_(0)
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
    setNMutatedGene(size);
    ChromosomeSize = chromosomeSize_;
}

void MEPAlgorithm::setPopulationSize(int size)
{
    populationSize_ = size;
    population_ = MEPPopulation({MEPPOPULATION, 0, 0}, size);
    PopulationSize = populationSize_;
}

void MEPAlgorithm::run()
{
    Stats stats(chromosomeSize_, populationSize_, nIterations);
    population_.init(generator_);

    MEPFitness *fitness = fitnessGenerator_.createRandomPtr();
    population_.run(*fitness);
    delete fitness;
    for(int i = 0; i < nIterations; ++i)
    {
        if(i == 150)
        {
            MEPFitnessGenerator generator;
            swapFitnessGenerator(generator);
            registerFitness(1, HAUSDORFF_CANNY);
        }
        fitness = fitnessGenerator_.createRandomPtr();
        runAlgorithm(i, fitness, generator_, stats);
        saveStats(stats);
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
    cv::Mat result = bestGene.getResult();
    cv::threshold(result,result,125,255,0);
    imwrite(savePath + name, result);
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

void MEPAlgorithm::saveStats(Stats &stats)
{
    string name = "Stats2";
    name += ".txt";
    fstream file;
    file.open(savePath + name, fstream::out);
    file << stats.toString();
    file.close();
}

void MEPAlgorithm::swapFitnessGenerator(MEPFitnessGenerator &generator)
{
    std::swap(fitnessGenerator_, generator);
    fitnessGenerator_.setReferenceImage(referenceImage_);
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

