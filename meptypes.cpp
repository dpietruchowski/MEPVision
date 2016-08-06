#include "meptypes.h"

using namespace std;

MEPId::MEPId()
{
    type = MEPUNIDENTIFY;
    number = 0;
    cloneNumber = 0;
}

MEPId::MEPId(MEPType type, unsigned int number, unsigned int cloneNumber):
    type(type), number(number), cloneNumber(cloneNumber)
{
}

bool MEPId::operator ==(const MEPId& rhs) const
{
    return (type == rhs.type)
            && (number == rhs.number)
            && (cloneNumber == rhs.cloneNumber);
}

string MEPId::toString() const
{
    string id = enumToString(type);
    id += " ";
    id += to_string(number);
    id += " ";
    id += to_string(cloneNumber);

    return id;
}

//MEPScore::MEPScore()
//{
//    score = 0;
//    normalized = 0;
//    standardized = 0;
//}

//MEPScore::MEPScore(int score, double normalized, double standardized):
//    score(score), normalized(normalized), standardized(standardized)
//{
//}

//bool MEPScore::operator ==(const MEPScore& rhs) const
//{
//    return score == rhs.score;
//}

//bool MEPScore::operator ==(const int rScore) const
//{
//    return score == rScore;
//}

//string MEPScore::toString() const
//{
//    string sScore = to_string(score);
//    sScore += " ";
//    sScore += to_string_with_precision(normalized, 3);
//    sScore += " ";
//    sScore += to_string_with_precision(standardized, 3);

//    return sScore;
//}

