#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>

#include "core/mepchromosome.h"
#include "core/meppopulation.h"
#include "generator/mepgenerator.h"
#include "gene/functiongene.h"
#include "gene/terminalgene.h"
#include "gene/morphogene.h"
#include "opencv2/highgui/highgui.hpp"
#include "fitness/hausdorff.h"
#include "fitness/hausdorffsmall.h"
#include "fitness/hausdorffcanny.h"
#include "fitness/hamming.h"
#include "fitness/mepfitnessgenerator.h"
#include "operation/mepoperationtypes.h"
#include "selection/rouletteselection.h"
#include "selection/tournamentselection.h"
#include "operation/operation.h"
#include "operation/mepoperationgenerator.h"

using namespace std;

static MEPObjectPtr createCh(unsigned int number)
{
    MEPObjectPtr chromosome(new MEPChromosome({MEPCHROMOSOME, number, 0}, 100));
    return chromosome;
}

static MEPObjectPtr createP(unsigned int number)
{
    MEPObjectPtr population(new MEPPopulation({MEPPOPULATION, number, 0}, 100));
    return population;
}

static void createGenerator(MEPGenerator& generator)
{
   generator.registerGene(0.3, FunctionGene::create);
   generator.registerGene(0.1, TerminalGene::create);
   generator.registerGene(0.6, MorphoGene::create);
   generator.registerChromosome(createCh);
   generator.registerPopulation(createP);
}

using namespace cv;

int main()
{
    srand(time(NULL));

    MEPObjectPtr population(new MEPPopulation({MEPPOPULATION, 0, 0}, 100));
    MEPObjectPtr reproducedPopulation;

    MEPGenerator generator;
    createGenerator(generator);
    MEPOperationGenerator opGenerator;
    MEPFitnessGenerator fitGenerator;

    opGenerator.registerObject(0.05, RandArgumentMutation::create);
    opGenerator.registerObject(0.05, RandAttributeMutation::create);
    opGenerator.registerObject(0.3, RandCombinedMutation::create);
    opGenerator.registerObject(0.2, UniformCrossover::create);
    opGenerator.registerObject(0.2, OnePointCrossover::create);
    opGenerator.registerObject(0.2, TwoPointCrossover::create);

    fitGenerator.registerObject(0.95, Hamming::create);
    fitGenerator.registerObject(0.02, HausdorffCanny::create);
    fitGenerator.registerObject(0.02, HausdorffSmall::create);
    fitGenerator.registerObject(0.01, Hausdorff::create);

    dynamic_cast<MEPComposite&> (*population).init(generator);
    try {
    for(int i = 0; i < 1000; i++)
    {
        MEPFitness *fitness = fitGenerator.createRandomPtr();
        MEPOperation *operation = opGenerator.createRandomPtr();

        cout << "Iteracja nr " << i << " " << flush;
        population->run(*fitness);

        const MEPComposite& pop = dynamic_cast<MEPComposite&> (*population);
        const MEPChromosome& bestChromosome = dynamic_cast<const MEPChromosome&>
                                                (pop.find(0));

        Gene& bestGene = const_cast<Gene&> (dynamic_cast<const Gene&>
                                                (bestChromosome.find(0)));
        bestGene.runGeneTree();
        std::string name = "Best ";
        name += std::to_string(i);
        name += ".png";
        cv::imwrite(name, bestGene.getResult());
        bestGene.clearResult();

        const_cast<MEPChromosome&> (bestChromosome).clearResults();

        reproducedPopulation = dynamic_cast<MEPPopulation&> (*population).
                            reproduce(RANK_ROULETTESELECTION,
                                      generator, *operation);
        population.swap(reproducedPopulation);
        cout << endl;
        delete operation;
        delete fitness;
    }
    } catch(std::string &exc)
    {
        cout << endl;
        cout << "////////////////////////////////" << endl;
        cout << exc << endl;
        cout << "////////////////////////////////" << endl;
    }

    return 0;
}

//int main()
//{
//    srand(0);
//    MEPGenerator generator;
//    createGenerator(generator);
//    MEPFitness *fitness = Hamming::create();

//    MEPObjectPtr chromosome = generator.createChromosome();

//    chromosome->init(generator);

//    cout << chromosome->write() << endl;

//    chromosome->show();

//    cout << chromosome->write() << endl;

//    return 0;
//}
