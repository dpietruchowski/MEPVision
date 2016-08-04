#include "mepoperationtypes.h"

#include <algorithm>
#include <functional>

OperationPointsType::OperationPointsType()
{
}

const Points& OperationPointsType::getOperationPoints() const
{
    return points_;
}

void OperationPointsType::calcPoints(const MEPChromosomes& parents)
{
    points_.clear();
    calcPoints(parents, points_);
    std::sort(points_.begin(), points_.end(), std::less<int>());
}

int OperationPointsType::rand(int min, int max) const
{
    return (min + (std::rand() % (max - min)));
}

NPointsControl::NPointsControl(int nPoints):
    nPoints_(nPoints)
{
}

void NPointsControl::calcPoints(const MEPChromosomes& parents, Points& points)
{
    int maxPoint = parents[0].get().getSize();
    for(int i = 1; i < static_cast<int>(parents.size()); ++i)
    {
        if(parents[i].get().getSize() < maxPoint)
            maxPoint = parents[i].get().getSize();
    }

    if(maxPoint < 2*nPoints_)
        throw std::string("Za duzo punktow");

    Points::iterator it = points.begin();
    for(int i = 0; i < nPoints_; i++)
    {
        int calcedPoint = calcPoint(parents, maxPoint - i - 1);
        it = std::find(points.begin(), points.end(), calcedPoint);
        while(it != points.end())
        {
            calcedPoint = calcPoint(parents, maxPoint - i - 1);
            it = std::find(points.begin(), points.end(), calcedPoint);
        }
        points.push_back(calcedPoint);
    }
}

RandomPoints::RandomPoints(int nPoints): 
    NPointsControl(nPoints) 
{
}

int RandomPoints::calcPoint(const MEPChromosomes& parents, int) const
{
    int maxPoint = parents[0].get().getSize();
    for(int i = 1; i < static_cast<int>(parents.size()); ++i)
    {
        if(parents[i].get().getSize() < maxPoint)
            maxPoint = parents[i].get().getSize();
    }

    int randPoint = rand(2, maxPoint);

    return randPoint;
}

WorstPoints::WorstPoints(int nPoints): 
    NPointsControl(nPoints) 
{
}

int WorstPoints::calcPoint(const MEPChromosomes& parents, int pointNumber) const
{
    int nParents = static_cast<int>(parents.size());
    if(nParents != 1)
        throw std::string("WorstPoints::calcPoint:: too many parents");

    if(parents[0].get().getState() < MEPASSESSED)
        throw std::string("WorstPoints::calcPoint:: wrong object state");

    return parents[0].get().find(parents[0].get().find(pointNumber));
}

UniformPoints::UniformPoints() 
{
}

void UniformPoints::calcPoints(const MEPChromosomes& parents, Points& points)
{
    int nParents = static_cast<int>(parents.size());
    if(nParents != 1)
        throw std::string("UniformPoints::calcPoints: too many parents");

    int maxPoint = parents[0].get().getSize();
    int i = 0;
    points.push_back(rand(0, maxPoint/2));
    Points::reverse_iterator it = points.rbegin();
    while(*points.rbegin() < (maxPoint - 2))
    {
        points.push_back(rand(points[i] + 1, maxPoint));
        ++i;
    }
}

BetterGenePoints::BetterGenePoints() 
{
}

void BetterGenePoints::calcPoints(const MEPChromosomes& parents, Points& points)
{
    int nParents = static_cast<int>(parents.size());
    if(nParents != 2)
        throw std::string("BetterGenePoints::calcPoints: too many parents");

    std::vector<bool> comparison = parents[0].get().compare(parents[1].get(),
                                                    parents[0].get().getSize());
    bool temp = comparison[0];
    if(temp == false)
        points.push_back(0);
    int i = 0;
    for(const auto& comp: comparison)
    {
        if(comp ^ temp)
        {
            temp = comp;
            points.push_back(i);
        }
        i++;
    }
}
