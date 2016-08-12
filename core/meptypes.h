#ifndef MEPTYPES_H
#define MEPTYPES_H

#include "mep_global.h"

#include <boost/preprocessor.hpp>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <functional>
#include <algorithm>

#define X_DEFINE_ENUM_TOSTRING_CASE(r, data, elem)    \
case elem : return BOOST_PP_STRINGIZE(elem);

#define DEFINE_ENUM(name, enumerators)                \
enum MEPSHARED_EXPORT name {                                                               \
    BOOST_PP_SEQ_ENUM(enumerators)                                        \
};                                                                        \
                                                                          \
inline MEPSHARED_EXPORT const char* enumToString(name v)                                       \
{                                                                         \
    switch (v)                                                            \
    {                                                                     \
        BOOST_PP_SEQ_FOR_EACH(                                            \
            X_DEFINE_ENUM_TOSTRING_CASE,          \
            name,                                                         \
            enumerators                                                   \
        )                                                                 \
        default: return "[Unknown " BOOST_PP_STRINGIZE(name) "]";         \
    }                                                                     \
}

DEFINE_ENUM(MEPType,(MEPFUNCTIONGENE)(MEPTERMINALGENE)                    \
            (MEPMORPHOGENE)(MEPTHRESHGENE)                                \
            (MEPCHROMOSOME)(MEPPOPULATION)(MEPUNIDENTIFY))
DEFINE_ENUM(MEPState,(MEPCREATED)(MEPDONE)(MEPCLEARED)(MEPASSESSED)       \
            (MEPCLEAREDSORTED)(MEPCOMPLITED)(MEPUNDEFINED))

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}



inline MEPType enumFromString(const std::string& enm)
{
    if(enm == "MEPFUNCTIONGENE") return MEPFUNCTIONGENE;
    if(enm == "MEPTERMINALGENE") return MEPTERMINALGENE;                    \
    if(enm == "MEPMORPHOGENE") return MEPMORPHOGENE;
    if(enm == "MEPTHRESHGENE") return MEPTHRESHGENE;                                \
    if(enm == "MEPCHROMOSOME") return MEPCHROMOSOME;
    if(enm == "MEPPOPULATION") return MEPPOPULATION;
    if(enm == "MEPUNIDENTIFY") return MEPUNIDENTIFY;

    throw std::string("Wrong enum");
}

struct MEPSHARED_EXPORT MEPId
{
    MEPType type;
    unsigned int number;
    unsigned int cloneNumber;
    MEPId();
    MEPId(MEPType, unsigned int, unsigned int);
    void swap(MEPId& rhs);
    bool operator ==(const MEPId&) const;
    std::string toString() const;
    void fromString(const std::string&);
};

//TODO Change name of variable score.
//     Problem score_.score;
//struct MEPSHARED_EXPORT MEPScore
//{
    //int score;
    //double normalized;
    //double standardized;
    //MEPScore();
    //MEPScore(int, double, double);
    //bool operator ==(const MEPScore&) const;
    //bool operator ==(const int rScore) const;
    //std::string toString() const;
//};

struct Stats
{
    Stats(int chromosomeSize, int populationSize, int nIterations):
        selectionRank(populationSize, 0),
        avarageFitness(nIterations, 0),
        fitness(nIterations, 0),
        avarageFitnessBest(nIterations),
        nMutation(0), nBetterAfterMutation(0),
        nCrossover(0), nBetterAfterCrossover(0) {}
    std::vector<int> selectionRank;
    std::vector<double> avarageFitness;
    std::vector<int> fitness;
    std::vector<int> avarageFitnessBest;
    int nMutation;
    int nBetterAfterMutation;
    int nCrossover;
    int nBetterAfterCrossover;

    std::string toString() const;
};

#endif // MEPTYPES_H
