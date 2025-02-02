#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "Graph.h"

bool iequals(const string &s1, const string &s2);

using namespace std;
/**
 * Represents the arguments after parsing.
 * Has input files as a vector of filenames.
 * Holds information about output file
 */
struct ParsedArgs {
    vector<string> inputFiles;
    string outputFile;
    bool hasOutputFlag = false;
};

class Parser {
public:
    static constexpr unsigned int MAX_CITY_NAME = 16;
    Parser(int argc, char** argv);

    Graph<string, unsigned int> getGraph() const;

private:
    ParsedArgs parsedArgs;
    Graph<string, unsigned int> graph;

    /**
     * Parses a single line from an input file.
     * @param line The input line to parse.
     * @param source Output parameter for the source node.
     * @param target Output parameter for the target node.
     * @param hopTime Output parameter for the hop time.
     * @return True if parsing was successful, false otherwise.
     */
    static bool parseAndValidateLine(const string& line, string& source, string& target, unsigned int& hopTime);

    /**
     * Parses a file and adds it to <i>graph</i>
     * @param graph Graph to add parse the files into
     * @param fileName File to be parsed
     */
    static void parseSingleFile(Graph<string, unsigned int>& graph, const string &fileName);

    /**
     * Parses the input files and returns a Graph<string, unsigned int>
     * representing the network.
     * @return Graph<string, unsigned int> with the parsed data.
     */
    void parseFiles();
};

#endif //PARSER_H
