#ifndef MEPALGORITHM_H
#define MEPALGORITHM_H

#include "core/mepcore.h"
#include "fitness/fitness.h"
#include "gene/genes.h"
#include "generator/mepgenerator.h"
#include "operation/operation.h"
#include "parser/mepparser.h"
#include "selection/selection.h"

enum GeneType { TERMINALGENE, FUNCTIONGENE, MORPHOGENE, THRESHGENE };
enum FitnessType { HAMMING, HAUSDORFF, HAUSDORFF_CANNY, HAUSDORFF_SMALL };
enum OperationType
{ RAND_ARGUMENTMUTATION, WORST_ARGUMENTMUTATION, UNIFORM_ARGUMENTMUTATION,
  RAND_ATTRIBUTEMUTATION, WORST_ATTRIBUTEMUTATION, UNIFORM_ATTRIBUTEMUTATION,
  RAND_COMBINEDMUTATION, WORST_COMBINEDMUTATION, UNIFORM_COMBINEDMUTATION,
  UNIFORM_CROSSOVER, ONEPOINT_CROSSOVER, TWOPOINT_CROSSOVER,
  BETTERGENE_CROSSOVER };
typedef MEPSelectionType SelectionType;
enum AlgorithmType { STEADY_STATE, GENERATIONAL };

class MEPAlgorithm
{
public:
    MEPAlgorithm();

public:
    double registerGene(double probability, GeneType type);
    double registerFitness(double probability, FitnessType type);
    void setInputImage(const std::string& path);
    void setReferenceImage(const std::string& path);
    void setChromosomeSize(int size);
    void setPopulationSize(int size);
    void run();

public:
    SelectionType selectionType;
    int nIterations;
    std::string savePath;

protected:
    MEPPopulation population_;
    void saveImage(int i);
    void saveAlgorithm(int i);
    void saveStats(Stats& stats);
    void swapFitnessGenerator(MEPFitnessGenerator& generator);

private:
    virtual void runAlgorithm(int i, MEPFitness *fitness,
                         MEPGenerator& generator, Stats& stats) = 0;
    virtual void setNMutatedGene(int size) = 0;

    void parseOptions(const std::string& path);
    static MEPObjectPtr createChromosome(unsigned int number);
    static MEPObjectPtr createPopulation(unsigned int number);


private:
    MEPFitnessGenerator fitnessGenerator_;
    static int ChromosomeSize;
    static int PopulationSize;
    MEPGenerator generator_;
    cv::Mat inputImage_;
    cv::Mat referenceImage_;
    int chromosomeSize_;
    int populationSize_;

    double sumProFitness_;
    double sumProGene_;

};

#endif // MEPALGORITHM_H
