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

DEFINE_ENUM(MEPType,(MEPGENE)(MEPCHROMOSOME)(MEPPOPULATION)(MEPUNIDENTIFY))

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

struct MEPSHARED_EXPORT MEPId
{
    MEPType type;
    int number;
    int cloneNumber;
    MEPId();
    MEPId(MEPType, int, int);
    bool operator ==(const MEPId&) const;
    std::string toString() const;
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

#endif // MEPTYPES_H
