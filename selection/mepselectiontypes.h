#ifndef MEPSELECTIONTYPES_H
#define MEPSELECTIONTYPES_H

#include "../mep_global.h"
#include "../meptypes.h"
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
    std::string toString() const
    {
        std::string sScore = std::to_string(rank);
        sScore += " ";
        sScore += to_string_with_precision(value, 3);
        sScore += " ";
        sScore += to_string_with_precision(normalized, 3);

        return sScore;
    }
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
