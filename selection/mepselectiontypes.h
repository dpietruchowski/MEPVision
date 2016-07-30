#ifndef MEPSELECTIONTYPES_H
#define MEPSELECTIONTYPES_H

#include <vector>

struct MEPScore
{
    int rank;
    int value;
    double normalized;
    MEPScore(int, int, double);
};
typedef std::vector<MEPScore> Scores;

struct ScoreType
{
    virtual ~ScoreType() {}
    virtual MEPScore add(int rank, int fitness) const = 0;
};

struct FitnessScore: public ScoreType
{
    MEPScore add(int rank, int fitness) const;
};

struct RankScore: public ScoreType
{
    MEPScore add(int rank, int fitness) const;
};

#endif
