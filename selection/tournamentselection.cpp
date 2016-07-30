#include "tournamentselection.h"

#include <cstdlib>

TournamentSelection::TournamentSelection(int tournamentSize):
MEPSelection(new FitnessScore()), tournamentSize_(tournamentSize)
{
}

int TournamentSelection::select(const Scores& scores) const
{
    //extract subvector with tournament size
    int index = std::rand() % (scores.size() - tournamentSize_);
    int best = index;
    for(int i = index; i < tournamentSize_; i++)
    {
        //the better individual, the lower standardize score (score/highestScore)
        if(scores[best].normalized < scores[i].normalized)
            best = i;
    }

    return best;
}

void TournamentSelection::calcScores(Scores& scores, int worstScore)
{
    for(auto& score : scores)
    {
        score.normalized = static_cast<double>(score.value) / worstScore;
    }
}
