#ifndef MEPSELECTIONTYPES_H
#define MEPSELECTIONTYPES_H

#include "../mep_global.h"
#include <vector>

enum MEPSelectionType
{
    FITNESS_ROULETTESELECTION,
    RANK_ROULETTESELECTION,
    TOURNAMENTSELECTION
};

struct MEPSHARED_EXPORT MEPScore
{
    int rank;
    int value;
    double normalized;
    MEPScore(int, int, double);
};
typedef std::vector<MEPScore> Scores;

struct MEPSHARED_EXPORT ScoreType
{
    virtual ~ScoreType() {}
    virtual MEPScore add(int rank, int fitness) const = 0;
};

struct MEPSHARED_EXPORT FitnessScore: public ScoreType
{
    MEPScore add(int rank, int fitness) const;
};

struct MEPSHARED_EXPORT RankScore: public ScoreType
{
    MEPScore add(int rank, int fitness) const;
};

#endif
