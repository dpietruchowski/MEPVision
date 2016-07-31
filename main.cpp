#include <iostream>

#include "core/mepchromosome.h"
#include "generator/mepgenerator.h"
#include "gene/functiongene.h"
#include "gene/terminalgene.h"
#include "opencv2/highgui/highgui.hpp"
#include "fitness/hausdorff.h"

using namespace std;

int main()
{
    srand(0);
    cout << "Blabla" << endl;
    MEPId id = {MEPCHROMOSOME, 0, 0};
    int size = 5;
    MEPChromosome chromosome({MEPCHROMOSOME, 0, 0}, size);

    MEPGenerator generator;
    generator.registerGene(0.8, FunctionGene::create); // all function included
    generator.registerGene(0.2, TerminalGene::create); // terminal should be kangaroo

    Hausdorff fitness("kangur_ref.png");

    chromosome.init(generator);
    chromosome.run();
   // chromosome.assess(fitness);
    string sChromosome = chromosome.write();

    cout << sChromosome << endl;
    cv::waitKey();
    return 0;
}

