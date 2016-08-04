#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "core/mepchromosome.h"
#include "generator/mepgenerator.h"
#include "gene/functiongene.h"
#include "gene/terminalgene.h"
#include "opencv2/highgui/highgui.hpp"
#include "fitness/hausdorff.h"
#include "operation/mepoperationtypes.h"

using namespace std;

static void createGenerator(MEPGenerator& generator)
{
   generator.registerGene(0.8, FunctionGene::create);
   generator.registerGene(0.2, TerminalGene::create);
}

int main()
{
    //srand(time( NULL ));
    OperationPointsType* pointsType = new BetterGenePoints();
    MEPChromosome chromosome1({MEPCHROMOSOME, 0, 0}, 10);
    MEPChromosome chromosome2({MEPCHROMOSOME, 1, 0}, 10);
    MEPGenerator generator;
    createGenerator(generator);
    MEPFitness *fitness = new Hausdorff("kangur_ref.png");

    chromosome1.init(generator);
    chromosome1.run();
    chromosome1.assess(*fitness);
    chromosome1.find(0).show();
    chromosome2.init(generator);
    chromosome2.run();
    chromosome2.assess(*fitness);
    chromosome2.find(0).show();

    cout<<chromosome1.write()<<endl;
    cout<<chromosome2.write()<<endl;

    MEPChromosomes parents;

    parents.push_back(chromosome1);
    parents.push_back(chromosome2);

    pointsType->calcPoints(parents);
    const Points& points = pointsType->getOperationPoints();

    for(const auto& p: points)
        cout << p << " ";
    cout << endl;

    cv::waitKey(0);

    return 0;
}

