#ifndef MEPSELECTION_H
#define MEPSELECTION_H

#include "mepselectiontypes.h"

class MEPSHARED_EXPORT MEPSelection
{
public:
    MEPSelection(ScoreType*);
    virtual ~MEPSelection();

    void add(int rank, int score);
    void calcScores();
    int getSelectedRank() const;
private:
    virtual int select(const Scores&) const = 0;
    virtual void calcScores(Scores&, int worstScore) const = 0;
private:
    Scores scores_;
    ScoreType* scoreType_;
    int worstScore_;
};

#endif
