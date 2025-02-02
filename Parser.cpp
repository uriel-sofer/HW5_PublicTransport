#include "Parser.h"
#include <fstream>
#include <iostream>
#include <cctype>

bool ichar_equals(char a, char b)
{
    return tolower(static_cast<unsigned char>(a)) ==
            tolower(static_cast<unsigned char>(b));
}

bool iequals(const string &s1, const string &s2)
{
    return s1.size() == s2.size() &&  std::equal(s1.begin(), s1.end(), s2.begin(), ichar_equals);
}

Parser::Parser(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <infile1> <infile2> ... [-o] <outfile>" << endl;
        throw invalid_argument("Wrong number of input files");
    }

    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];

        if (arg == "-o" and i + 1 < argc)
        {
            parsedArgs.hasOutputFlag = true;
            parsedArgs.outputFile = argv[++i];
        }
        else if (i == argc - 1 && !parsedArgs.hasOutputFlag)
            parsedArgs.outputFile = arg;
        else
            parsedArgs.inputFiles.push_back(arg);
    }
    parseFiles();
}

Graph<string, unsigned int> Parser::getGraph() const
{
    return graph;
}

bool Parser::parseAndValidateLine(const string& line, string& source, string& target, unsigned int& hopTime)
{
    stringstream ss(line);

    if (!(getline(ss, source, '\t') && getline(ss, target, '\t') && ss >> hopTime))
        return false;

    if (source.length() > MAX_CITY_NAME)
        return false;

    if (target.length() > MAX_CITY_NAME)
        return false;

    if (iequals(source, "exit") || iequals(target, "exit"))
        return false;

    if (source.find(' ') != string::npos or target.find(' ') != string::npos)
        return false;

    return true;
}

void Parser::parseSingleFile(Graph<string, unsigned int>& graph, const string &fileName)
{
    ifstream file(fileName);
    if (!file)
        throw invalid_argument("Error: Could not open file " + fileName);

    string line;
    while (getline(file, line))
    {
        string source, target;
        unsigned int hopTime;

        if (!parseAndValidateLine(line, source, target, hopTime))
        {
            throw invalid_argument("Malformed line in file " + fileName + ": " + line);
        }

        graph.addVertex(source);
        graph.addVertex(target);

        try
        {
            graph.addEdge(source, target, hopTime);
        }
        catch (const EdgeAlreadyExistsException<string>&)
        {
            graph.updateWeight(source, target, min(hopTime, graph.getWeight(source, target)));
        }
    }

    file.close();
}

void Parser::parseFiles()
{
    Graph<string, unsigned int> result;

    for (const auto& fileName : parsedArgs.inputFiles)
    {
        try
        {
            parseSingleFile(result, fileName);
        }
        catch (const exception& e)
        {
            cerr << e.what() << endl;
            exit(EXIT_FAILURE);
        }
    }

    graph = result;
}