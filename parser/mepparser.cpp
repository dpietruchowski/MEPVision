#include "mepparser.h"

#include <algorithm>
#include <string>

using namespace std;

MEPObjectPtr MEPParser::getChromosome(MEPId &bestGeneId) const
{
    MEPObjectPtr cloned = chromosome_.clone();
    const MEPObject& bestGene = chromosome_.findByRank(0);
    bestGeneId = MEPId(bestGene.getId().type,
                       bestGene.getId().number,
                       bestGene.getId().cloneNumber);

    return cloned;
}

bool MEPParser::isParsed() const
{
    return parsed_;
}

/*
 * Dodac sprawdzanie czy plik jest ok
 */
void MEPParser::parse()
{
    int nLines = std::count(std::istreambuf_iterator<char>(file_),
                 std::istreambuf_iterator<char>(), '\n');
    file_.clear();
    file_.seekg(0, ios::beg);

    std::string line;
    getline(file_, line);
    lineNumber_++;

    size_t charPos = line.find_first_of("#");
    string sid = line.substr(charPos+1, line.size() - charPos);
    MEPId id;
    id.fromString(sid);
    chromosome_ = MEPChromosome(id, nLines - 1);

    for(; lineNumber_ < nLines; ++lineNumber_)
    {
        getline(file_, line);
        parseLine(line);
        ////////////// Id //////////////////
        MEPId id;
        id.fromString(sections_[0]);
        ////////////////////////////////////
        ///////// Gene Attribute ///////////
        MEPObjectPtr gene;
        switch(id.type)
        {
        case MEPTERMINALGENE:
        {
            gene = MEPObjectPtr(new TerminalGene(TerminalGene::getTerminalSet().
                                                 getRandomImage(), id));
            break;
        }
        case MEPFUNCTIONGENE:
        {
            gene = MEPObjectPtr(new FunctionGene(FunctionGene::getFunctionSet().
                                                 getFunction(sections_[2]), id));
            break;
        }
        case MEPMORPHOGENE:
        {
            size_t startPos;
            size_t endPos;
            MorphoParameters param(sections_[2]);
            startPos = 0;
            endPos = sections_[3].find_first_of(" ", startPos);
            int nRows = stoi(sections_[3].substr(startPos,
                                                 endPos - startPos));
            startPos = sections_[3].find_first_of(" ");
            endPos = sections_[3].find_first_of("[", startPos);
            int nCols = stoi(sections_[3].substr(startPos+1,
                                                 endPos - startPos - 1));

            startPos = sections_[3].find_first_of("[");
            endPos = sections_[3].find_first_of("]", startPos);
            string selement = sections_[3].substr(startPos+1,
                                                  endPos - startPos - 1);
            MorphoElement structElement(selement, nRows, nCols);

            gene = MEPObjectPtr(new MorphoGene(MorphoGene::morphologyOperation,
                                               param, structElement, id));
            break;
        }
        case MEPTHRESHGENE:
        {
            ThreshParameters param(sections_[2]);
            gene = MEPObjectPtr(new ThreshGene(ThreshGene::thresholdOperation,
                                               param, id));
            break;
        }
        default:
            throw std::string("MEPParser::parse: Wrong type");
        }

        if(line.find("$") != string::npos)
            gene->setAsFirst();

        ///////// Children Number //////////
        int size = stoi(sections_[1]);
        ////////////////////////////////////
        //////////// Children //////////////
        vector<int> args;
        for(int i = 0; i < size; i++)
        {
            MEPId id;
            id.fromString(sections_[i+4]);
            int arg = chromosome_.findNumber(id);
            args.push_back(arg);
        }
        ////////////////////////////////////
        static_cast<MEPComposite&> (chromosome_).addObject(gene, args);
    }

    file_.close();
    lineNumber_ = 0;
    parsed_ = true;
}

MEPParser::MEPParser(const std::string &path):
    chromosome_({MEPCHROMOSOME, 0, 0}, 10), lineNumber_(0)
{
    file_.open(path, ios_base::in);
    parsed_ = false;
    if(file_.is_open() == false)
        throw std::string("Nie udalo sie wczytac pliku");
}

void MEPParser::parseLine(const string &line)
{
    size_t startPos = 0;
    size_t endPos = 0;
    sections_.clear();
    for(int i = 0; i < 3; ++i)
    {
        startPos = line.find_first_of("#", endPos);
        endPos = line.find_first_of("#", startPos+1);
        string section = line.substr(startPos+1, endPos - startPos - 1);
        sections_.push_back(section);
    }

    startPos = line.find_first_of("%");
    if(startPos != string::npos)
    {
        endPos = line.find_first_of("%", startPos+1);
        string section = line.substr(startPos+1, endPos - startPos - 1);
        sections_.push_back(section);
    } else sections_.push_back("");

    int size = stoi(sections_[1]);
    for(int i = 0; i < size; ++i)
    {
        startPos = line.find_first_of("!", endPos);
        endPos = line.find_first_of("!", startPos+1);
        string section = line.substr(startPos+1, endPos - startPos - 1);
        sections_.push_back(section);
    }
}
