#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

/**
 * Represents a city with a name.
 */
struct City {
    string name;

    explicit City(string name) : name(move(name)) {}

    bool operator==(const City& other) const { return name == other.name; }
    bool operator!=(const City& other) const { return !(*this == other); }
    friend ostream& operator<<(ostream& os, const City& city) { return os << city.name; }
};

/**
 * Represents the distance of a road in kilometers.
 */
struct RoadDistance {
    double km;

    RoadDistance(double km = 0.0) : km(km) {}

    bool operator==(const RoadDistance& other) const { return km == other.km; }
    bool operator!=(const RoadDistance& other) const { return !(*this == other); }
    friend ostream& operator<<(ostream& os, const RoadDistance& rd) { return os << rd.km << " km"; }
};

int main()
{
    try
    {
        cout << "=== City Graph Testing ===" << endl << endl;

        // Create a Graph<City, RoadDistance>
        Graph<City, RoadDistance> cityGraph;

        cout << "Graph created successfully." << endl;

        // Add cities (vertices)
        City newYork("New York"), losAngeles("Los Angeles"), chicago("Chicago"), houston("Houston"), miami("Miami");

        cityGraph.addVertex(newYork);
        cityGraph.addVertex(losAngeles);
        cityGraph.addVertex(chicago);
        cityGraph.addVertex(houston);
        cityGraph.addVertex(miami);

        // Add road distances (edges)
        try
        {
            cout << "Adding road connections..." << endl;
            cityGraph.addEdge(newYork, losAngeles, RoadDistance(4500));
            cityGraph.addEdge(newYork, chicago, RoadDistance(1300));
            cityGraph.addEdge(newYork, miami, RoadDistance(3000));
            cityGraph.addEdge(losAngeles, houston, RoadDistance(2500));
            cityGraph.addEdge(chicago, houston, RoadDistance(1600));
            cityGraph.addEdge(chicago, miami, RoadDistance(1700));
            cityGraph.addEdge(houston, miami, RoadDistance(2000));
            cout << "Roads added successfully." << endl;
        }
        catch (const exception& e)
        {
            cerr << "Error adding roads: " << e.what() << endl;
        }

        // Print the adjacency matrix
        cout << endl << "Graph Representation:" << endl;
        cityGraph.print();

        // Test getWeight()
        try
        {
            cout << endl << "Testing getWeight(New York -> Los Angeles): " << cityGraph.getWeight(newYork, losAngeles) << endl;
            cout << "Testing getWeight(Chicago -> Houston): " << cityGraph.getWeight(chicago, houston) << endl;
        }
        catch (const EdgeNotFoundException<City>& e)
        {
            cerr << "Error: " << e.what() << endl;
        }

        // Test getDirectNeighbors()
        try
        {
            cout << endl << "Direct Neighbors of Chicago: ";
            for (const auto& neighbor : cityGraph.getDirectNeighbors(chicago))
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        catch (const VertexNotFoundException<City>& e)
        {
            cerr << "Error: " << e.what() << endl;
        }

        // Test getDirectSources()
        try
        {
            cout << endl << "Direct Sources of Houston: ";
            for (const auto& source : cityGraph.getDirectSources(houston))
            {
                cout << source << " ";
            }
            cout << endl;
        }
        catch (const VertexNotFoundException<City>& e)
        {
            cerr << "Error: " << e.what() << endl;
        }

        // Test removeEdge()
        try
        {
            cout << endl << "Removing road (New York -> Los Angeles)..." << endl;
            cityGraph.removeEdge(newYork, losAngeles);
            cout << "Road removed. Testing getWeight(New York -> Los Angeles)..." << endl;
            cout << cityGraph.getWeight(newYork, losAngeles) << endl; // Should throw an exception
        }
        catch (const EdgeNotFoundException<City>& e)
        {
            cerr << "Expected Error: " << e.what() << endl;
        }

        // Test removeVertex()
        try
        {
            cout << endl << "Removing city Los Angeles..." << endl;
            cityGraph.removeVertex(losAngeles);
            cout << "City Los Angeles removed." << endl;

            cout << "Testing getDirectNeighbors(Los Angeles)..." << endl;
            auto neighbors = cityGraph.getDirectNeighbors(losAngeles); // Should throw an exception
        }
        catch (const VertexNotFoundException<City>& e)
        {
            cerr << "Expected Error: " << e.what() << endl;
            cout << "Final Graph Representation:" << endl;
            cityGraph.print();
        }
    }
    catch (const exception& e)
    {
        cerr << "Unexpected error: " << e.what() << endl;
    }

    return 0;
}
