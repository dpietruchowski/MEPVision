#include "meptypes.h"

#include <utility>
#include <iterator>

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


string Stats::toString() const
{
    stringstream sr, af, f, afb;
    copy(selectionRank.begin(), selectionRank.end(), std::ostream_iterator<int>(sr, ","));
    copy(avarageFitness.begin(), avarageFitness.end(), std::ostream_iterator<int>(af, ","));
    copy(fitness.begin(), fitness.end(), std::ostream_iterator<int>(f, ","));
    copy(avarageFitnessBest.begin(), avarageFitnessBest.end(), std::ostream_iterator<int>(afb, ","));

    string output;

    output += "selection \n" + sr.str() + "\n";
    output += "avarage fitness per gen \n" + af.str() + "\n";
    output += "best fitessn per gen \n" + f.str() + "\n";
    output += "avarage best fitness per gen \n" + afb.str() + "\n";
    output += "number of mutation " + to_string(nMutation) + "\n";
    output += "number of better offspring than partents " + to_string(nBetterAfterMutation) + "\n";
    output += "number of crossver " + to_string(nCrossover) + "\n";
    output += "number of better offspring than parents " + to_string(nBetterAfterCrossover) + "\n";

    return output;
}
