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

class MEPAlgorithm
{
public:
    MEPAlgorithm();

public:
    double registerGene(double probability, GeneType type);
    double registerFitness(double probability, FitnessType type);
    double registerOperation(double probability, OperationType type);
    void setInputImage(const std::string& path);
    void setReferenceImage(const std::string& path);
    void setChromosomeSize(int size);
    void setPopulationSize(int size);
    void run();

public:
    SelectionType selectionType;
    int nIterations;
    std::string savePath;

    int chromosomeSize() const;

private:
    void saveImage(int i);
    void saveAlgorithm(int i);
    void parseOptions(const std::string& path);
    static MEPObjectPtr createChromosome(unsigned int number);
    static MEPObjectPtr createPopulation(unsigned int number);


private:
    static int ChromosomeSize;
    static int PopulationSize;
    MEPPopulation population_;
    MEPGenerator generator_;
    MEPFitnessGenerator fitnessGenerator_;
    MEPOperationGenerator operationGenerator_;
    cv::Mat inputImage_;
    cv::Mat referenceImage_;
    int chromosomeSize_;
    int populationSize_;

    double sumProGene_;
    double sumProFitness_;
    double sumProOperation_;

};

#endif // MEPALGORITHM_H
