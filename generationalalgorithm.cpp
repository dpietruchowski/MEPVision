#include "generationalalgorithm.h"
#include <iostream>

using namespace std;

GenerationalAlgorithm::GenerationalAlgorithm()
{

}

double GenerationalAlgorithm::registerOperation(double probability,
                                                OperationType type)
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

void GenerationalAlgorithm::runAlgorithm(int i, MEPFitness *fitness,
                                    MEPGenerator &generator, Stats& stats)
{
    cout << "Iteracja nr " << i << " " << flush;
    population_.run(*fitness);

    saveImage(i);
    saveAlgorithm(i);

    MEPObjectPtr reproducedPopulation = population_.
                                            reproduce(selectionType,
                                                      generator,
                                                      operationGenerator_,
                                                      stats, fitness);

    bool save = true;
    if (save)
    {
        string name = "Population";
        name += to_string(i);
        name += ".txt";
        fstream file;
        file.open(savePath + name, fstream::out);
        file << population_.write();
        file << population_.writeTree();
        file.close();
    }

    population_.swap(dynamic_cast<MEPPopulation&>(*reproducedPopulation));

    cout << endl;
}

void GenerationalAlgorithm::setNMutatedGene(int size)
{
    operationGenerator_.setMaxNMutatedGene(size/8);
}

