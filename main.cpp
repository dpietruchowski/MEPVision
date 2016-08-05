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
#include "opencv2/highgui/highgui.hpp"
#include "fitness/hausdorff.h"
#include "fitness/hamming.h"
#include "operation/mepoperationtypes.h"
#include "selection/rouletteselection.h"
#include "selection/tournamentselection.h"
#include "operation/operation.h"

using namespace std;

static MEPObjectPtr createCh(unsigned int number)
{
    MEPObjectPtr chromosome(new MEPChromosome({MEPCHROMOSOME, number, 0}, 1000));
    return chromosome;
}

static MEPObjectPtr createP(unsigned int number)
{
    MEPObjectPtr population(new MEPPopulation({MEPPOPULATION, number, 0}, 100));
    return population;
}

static void createGenerator(MEPGenerator& generator)
{
   generator.registerGene(0.8, FunctionGene::create);
   generator.registerGene(0.2, TerminalGene::create);
   generator.registerChromosome(createCh);
   generator.registerPopulation(createP);
}

int main()
{
    srand(0);

    MEPObjectPtr population(new MEPPopulation({MEPPOPULATION, 0, 0}, 100));
    MEPObjectPtr reproducedPopulation;

    MEPGenerator generator;
    createGenerator(generator);
    MEPFitness *fitness = new Hamming("kangur_ref.png");
    MEPOperation *operation = new BetterGeneCrossover();

    population->init(generator);

    for(int i = 0; i < 200; i++)
    {
        cout << "Iteracja nr " << i << " " << flush;
        population->run();
        population->assess(*fitness);

        const MEPComposite& pop = dynamic_cast<MEPComposite&> (*population);
        const MEPChromosome& bestChromosome = dynamic_cast<const MEPChromosome&>
                                                (pop.find(0));
        const Gene& bestGene = dynamic_cast<const Gene&>
                                                (bestChromosome.find(0));
        std::string name = "Best ";
        name += std::to_string(i);
        cv::imwrite(name, bestGene.getResult());

        reproducedPopulation = dynamic_cast<MEPPopulation&> (*population).
                            reproduce(RANK_ROULETTESELECTION,
                                      generator, *operation);
        population.swap(reproducedPopulation);
        cout << endl;
    }

    return 0;
}
