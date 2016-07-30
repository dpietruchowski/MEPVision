#include "mepselection.h"

MEPSelection::MEPSelection(ScoreType* scoreType)
{
    scoreType_ = scoreType;
    worstScore_ = 0;
}

MEPSelection::~MEPSelection()
{
    delete scoreType_;
}

void MEPSelection::add(int rank, int fitness)
{
    MEPScore mepScore = scoreType_->add(rank, fitness);
    if(mepScore.value > worstScore_)
        worstScore_ = mepScore.value;

    scores_.push_back(mepScore);
}

void MEPSelection::calcScores()
{
    calcScores(scores_, worstScore_);
}

int MEPSelection::getSelectedRank() const
{
    return select(scores_);
}
