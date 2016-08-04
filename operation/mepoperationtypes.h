#ifndef MEPOPERATIONTYPES_H
#define MEPOPERATIONTYPES_H

#include <vector>
#include "../core/mepchromosome.h"

typedef std::vector<int> Points;
class OperationPointsType
{
public:
    OperationPointsType();
    virtual ~OperationPointsType() {}

    const Points& getOperationPoints() const;

    void calcPoints(const MEPChromosomes& parents);

protected:
    int rand(int min, int max) const;

private:
    virtual void calcPoints(const MEPChromosomes&, Points& points) = 0;

private:
    Points points_;
};

class NPointsControl: public OperationPointsType
{
public:
    NPointsControl(int nPoints);

private:
    void calcPoints(const MEPChromosomes& parents, Points& points);
    virtual int calcPoint(const MEPChromosomes& parents, int pointNumber) const = 0;

private:
    int nPoints_;
};

class RandomPoints: public NPointsControl
{
public:
    RandomPoints(int nPoints);

private:
    int calcPoint(const MEPChromosomes& parents, int pointNumber) const;
};


class WorstPoints: public NPointsControl
{
public:
    WorstPoints(int nPoints);

private:
    int calcPoint(const MEPChromosomes& parents, int pointNumber) const;
};

class UniformPoints: public OperationPointsType
{
public:
    UniformPoints();

private:
    void calcPoints(const MEPChromosomes& parents, Points& points);
};

class BetterGenePoints: public OperationPointsType
{
public:
    BetterGenePoints();

private:
    void calcPoints(const MEPChromosomes& parents, Points& points);
};


#endif
