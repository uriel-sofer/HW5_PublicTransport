#include <iostream>
#include <string>
#include "Graph.h"
#include "Parser.h"

using namespace std;

void programLoop(const Graph<string, unsigned int>& graph)
{
    string input;
    do
    {
        cout << "Waiting for input..." << endl;
        cin >> input;

        if (iequals(input, "exit"))
            return;

        try
        {
            const vector<string> connections = graph.getConnections(input);
            if (connections.size() == 0)
            {
                cout << connections[0] << " : no outbound travel" << endl;
            }
            else
            {
                cout << connections[0] << '\t';
                for (auto it = connections.begin() + 1; it != connections.end(); ++it)
                {
                    cout << *it << '\t';
                }
                cout << endl;
            }
        }
        catch (const VertexNotFoundException<string>&)
        {
            cout << input << " does not exist in the current network" << endl;
            cout << "USAGE: <node> or 'exit' to terminate" << endl;
        }
    } while (true);
}


int main(int argc, char** argv)
{
    const Graph<string, unsigned int> graph = Parser(argc, argv).getGraph();
    graph.print();
    programLoop(graph);
    return 0;
}
