#include "mepselectiontypes.h"

MEPScore::MEPScore(int rank, int value, double normalized):
rank(rank), value(value), normalized(normalized)
{
}

MEPScore FitnessScore::add(int rank, int fitness) const
{
    return MEPScore{rank, fitness, 0};
}

MEPScore RankScore::add(int rank, int) const
{
    return MEPScore{rank, rank, 0};
}
