#include "rouletteselection.h"

#include <cstdlib>

RouletteSelection::RouletteSelection(ScoreType* scoreType):
MEPSelection(scoreType)
{
}


//TODO use library to choose by probabilities
int RouletteSelection::select(const Scores& scores) const
{
    double decision = ((double) std::rand() / (RAND_MAX));
    double sum = 0;
    int i = 0;
    for(const auto& score: scores)
    {
        sum += score.normalized;
        if(decision <= sum)
            return score.rank;
        i++;
    }
    //should never get here
    return i;
}

void RouletteSelection::calcScores(Scores& scores, int worstScore)
{
    int sumOfScores = 0;
    for(auto& score : scores)
    {
        score.value = (worstScore - score.value + 1);
        sumOfScores += score.value;
    }

    for(auto& score : scores)
        score.normalized = static_cast<double>(score.value) / sumOfScores;
}
