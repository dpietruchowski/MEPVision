#ifndef ROULETTESELECTION_H
#define ROULETTESELECTION_H

#include "mepselection.h"

class RouletteSelection: public MEPSelection
{
public:
    RouletteSelection(ScoreType*);

private:
    int select(const Scores&) const;
    void calcScores(Scores&, int worstScore);
};

class RankRouletteSelection: public RouletteSelection
{
public:
    RankRouletteSelection(): RouletteSelection(new RankScore()) {}
};

class FitnessRouletteSelection: public RouletteSelection
{
public:
    FitnessRouletteSelection(): RouletteSelection(new FitnessScore()) {}
};

#endif
