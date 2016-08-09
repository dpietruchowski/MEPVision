#ifndef MEPPARSER_H
#define MEPPARSER_H

#include "core/mepcore.h"
#include "gene/genes.h"
#include <fstream>

class MEPParser
{
public:
    MEPObjectPtr getChromosome() const;
    bool isParsed() const;
    void parse();
public:
    MEPParser(const std::string& path);
    ~MEPParser() { file_.close(); }

private:
    const MEPGene& createGene(const std::string& gene) const;
    void createChromosome();
    void parseLine(const std::string& line);
    cv::Mat parseElement(const std::string& element) const;
private:
    std::fstream file_;
    std::vector<std::string> sections_;
    int lineNumber_;
    MEPChromosome chromosome_;
    bool parsed_;
};

#endif // MEPPARSER_H
