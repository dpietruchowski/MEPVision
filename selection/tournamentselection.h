#ifndef TOURNAMENTSELECTION_H
#define TOURNAMENTSELECTION_H

#include "mepselection.h"

class MEPSHARED_EXPORT TournamentSelection: public MEPSelection
{
public:
    TournamentSelection(int tournamentSize);

private:
    int select(const Scores&) const;
    void calcScores(Scores&, int worstScore);
private:
    int tournamentSize_;
};

#endif
