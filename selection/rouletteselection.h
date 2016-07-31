#ifndef ROULETTESELECTION_H
#define ROULETTESELECTION_H

#include "mepselection.h"

class MEPSHARED_EXPORT RouletteSelection: public MEPSelection
{
public:
    RouletteSelection(ScoreType*);

private:
    int select(const Scores&) const;
    void calcScores(Scores&, int worstScore);
};

class MEPSHARED_EXPORT RankRouletteSelection: public RouletteSelection
{
public:
    RankRouletteSelection(): RouletteSelection(new RankScore()) {}
};

class MEPSHARED_EXPORT FitnessRouletteSelection: public RouletteSelection
{
public:
    FitnessRouletteSelection(): RouletteSelection(new FitnessScore()) {}
};

#endif
