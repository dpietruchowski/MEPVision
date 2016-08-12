#include "steadystatealgorithm.h"
#include <iostream>

using namespace std;

SteadyStateAlgorithm::SteadyStateAlgorithm():
    sumProCrossover_(0), sumProMutation_(0)
{

}

double SteadyStateAlgorithm::registerCrossover(double probability, OperationType type)
{

    switch(type)
    {
    case UNIFORM_CROSSOVER:
        crossoverGenerator_.registerObject(probability,
                                           UniformCrossover::create);
        break;
    case ONEPOINT_CROSSOVER:
        crossoverGenerator_.registerObject(probability,
                                           OnePointCrossover::create);
        break;
    case TWOPOINT_CROSSOVER:
        crossoverGenerator_.registerObject(probability,
                                           TwoPointCrossover::create);
        break;
    case BETTERGENE_CROSSOVER:
        crossoverGenerator_.registerObject(probability,
                                           BetterGeneCrossover::create);
        break;
    default:
        break;
    }

    sumProCrossover_ += probability;
    return sumProCrossover_;
}

double SteadyStateAlgorithm::registerMutation(double probability, OperationType type)
{
    switch(type)
    {
    case RAND_ARGUMENTMUTATION:
        mutationGenerator_.registerObject(probability,
                                           RandArgumentMutation::create);
        break;
    case WORST_ARGUMENTMUTATION:
        mutationGenerator_.registerObject(probability,
                                           WorstArgumentMutation::create);
        break;
    case UNIFORM_ARGUMENTMUTATION:
        mutationGenerator_.registerObject(probability,
                                           UniformArgumentMutation::create);
        break;
    case RAND_ATTRIBUTEMUTATION:
        mutationGenerator_.registerObject(probability,
                                           RandAttributeMutation::create);
        break;
    case WORST_ATTRIBUTEMUTATION:
        mutationGenerator_.registerObject(probability,
                                           WorstAttributeMutation::create);
        break;
    case UNIFORM_ATTRIBUTEMUTATION:
        mutationGenerator_.registerObject(probability,
                                           UniformAttributeMutation::create);
        break;
    case RAND_COMBINEDMUTATION:
        mutationGenerator_.registerObject(probability,
                                           RandCombinedMutation::create);
        break;
    case WORST_COMBINEDMUTATION:
        mutationGenerator_.registerObject(probability,
                                           WorstCombinedMutation::create);
        break;
    case UNIFORM_COMBINEDMUTATION:
        mutationGenerator_.registerObject(probability,
                                           UniformCombinedMutation::create);
        break;
    default:
        break;
    }

    sumProMutation_ += probability;
    return sumProMutation_;

}

void SteadyStateAlgorithm::setFitnessType(FitnessType type)
{
    MEPFitnessGenerator generator;
    swapFitnessGenerator(generator);
    registerFitness(1, type);
}

void SteadyStateAlgorithm::runAlgorithm(int i, MEPFitness *fitness,
                                        MEPGenerator &generator, Stats& stats)
{
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
    cout << "Iteracja nr " << i << " " << flush;
    saveImage(i);
    saveAlgorithm(i);
    for(int h = 0; h < population_.getSize()*4; ++h)
    {
//        cout << "//////////////////////" << endl;
//        cout << population_.write() << endl;
////        for(int l = 0; l < population_.getSize() ; ++l)
////        {
////            cout << population_.findByOrder(l).write() << endl << endl;
////            const_cast<MEPObject&>(population_.findByOrder(l)).show("window");
////        }
//        cin.ignore();
        MEPOperation *crossover = crossoverGenerator_.createRandomPtr();
        MEPOperation *mutation = mutationGenerator_.createRandomPtr();

        MEPChromosomes parents;
//        cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXD" << endl;
        for(int k = 0; k < crossover->getNParents(); ++k)
        {
            const MEPObject& selected = population_.select(selectionType);
            stats.selectionRank[selected.getRank()]++;
//            cout << selected.write() << endl << endl;
            parents.push_back(dynamic_cast<const MEPChromosome&> (selected));
        }

        MEPObjectPtr reproduced = crossover->reproduce(parents, generator);
        reproduced->run(*fitness);

//        cout << "//////////////////////" << endl;
//        cout << reproduced->write() << endl;
//        cin.ignore();

        parents.clear();
        parents.push_back(dynamic_cast<MEPChromosome&>(*reproduced));
        MEPObjectPtr mutated = mutation->reproduce(parents, generator);
        mutated->run(*fitness);



//        cout << "//////////////////////" << endl;
//        cout << reproduced->write() << endl;
//        cin.ignore();

        population_.setObject(mutated);

        delete crossover;
        delete mutation;
    }
    static_cast<MEPObject&> (population_).sort();
    double avarage = double(population_.getSumScore())/population_.getSize();
    cout << " Najlepszy wynik " << population_.getScore()
         << " Sredni wynik " << avarage << endl;


//    int r = 0;
//    for(const auto& s: stats.selectionRank)
//        cout << "Rank " << r++ << " Wybrano " << s << endl;

}

void SteadyStateAlgorithm::setNMutatedGene(int size)
{
    mutationGenerator_.setMaxNMutatedGene(size/8);
}

