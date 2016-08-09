#include "meptypes.h"

#include <utility>

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

void MEPId::swap(MEPId &rhs)
{
    std::swap(type, rhs.type);
    std::swap(number, rhs.number);
    std::swap(cloneNumber, rhs.cloneNumber);
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


// Format: "MEPMORPHOGENE 6516 20"
void MEPId::fromString(const string &id)
{
    size_t firstSpace = id.find_first_of(" ");
    size_t secondSpace = id.find_last_of(" ");
    string stype = id.substr(0, firstSpace);
    type = enumFromString(stype);
    string snumber = id.substr(firstSpace+1, secondSpace - firstSpace);
    number = stoi(snumber);
    string sclone = id.substr(secondSpace+1);
    cloneNumber = stoi(sclone);
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

