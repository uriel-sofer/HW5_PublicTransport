#include <iostream>
#include <string>
#include "Graph.h"
#include "VectorQueue.h"

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

    explicit RoadDistance(const double km = 0.0) : km(km) {}

    bool operator==(const RoadDistance& other) const { return km == other.km; }
    bool operator!=(const RoadDistance& other) const { return !(*this == other); }
    friend ostream& operator<<(ostream& os, const RoadDistance& rd) { return os << rd.km << " km"; }
};

void testQueue()
{
    VectorQueue<int> queue;

    std::cout << "Queue is empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;

    // Enqueue elements
    std::cout << "Enqueueing 10, 20, 30, 40..." << endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);

    // Front element
    std::cout << "Front element: " << queue.front() << endl; // Expected: 10

    // Dequeue elements
    std::cout << "Dequeue: " << queue.dequeue() << endl; // Expected: 10
    std::cout << "Dequeue: " << queue.dequeue() << endl; // Expected: 20

    // Check front again
    std::cout << "Front element: " << queue.front() << endl; // Expected: 30

    // Check size
    std::cout << "Queue size: " << queue.size() << endl; // Expected: 2

    // Enqueue more elements
    std::cout << "Enqueueing 50, 60...\n";
    queue.enqueue(50);
    queue.enqueue(60);

    // Dequeue remaining elements
    while (!queue.isEmpty()) {
        std::cout << "Dequeue: " << queue.dequeue() << endl;
    }

    // Check empty queue behavior
    std::cout << "Queue is empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;

    try {
        cout << queue.front(); // Should throw an exception
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << endl; // Expected: "VectorQueue is empty"
    }

    try {
        cout << queue.dequeue(); // Should throw an exception
    } catch (const std::out_of_range& e) {
        std::cout << "Exception caught: " << e.what() << endl; // Expected: "VectorQueue is empty"
    }
}

void test_graph()
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
        cout << "Adding road connections..." << endl;
        cityGraph.addEdge(newYork, losAngeles, RoadDistance(4500));
        cityGraph.addEdge(newYork, chicago, RoadDistance(1300));
        cityGraph.addEdge(newYork, miami, RoadDistance(3000));
        cityGraph.addEdge(losAngeles, houston, RoadDistance(2500));
        cityGraph.addEdge(chicago, houston, RoadDistance(1600));
        cityGraph.addEdge(chicago, miami, RoadDistance(1700));
        cityGraph.addEdge(houston, miami, RoadDistance(2000));
        cout << "Roads added successfully." << endl << endl;

        // Print adjacency matrix
        cout << "Graph Representation:" << endl;
        cityGraph.print(0);

        // Test getConnections (BFS & DFS)
        auto testConnections = [&](const City& city)
        {
            cout << endl << "BFS Connections from " << city << ": ";
            for (const auto& conn : cityGraph.getConnections(city, true))
                cout << conn << " ";
            cout << endl;

            cout << "DFS Connections from " << city << ": ";
            for (const auto& conn : cityGraph.getConnections(city, false))
                cout << conn << " ";
            cout << endl;
        };

        testConnections(newYork);
        testConnections(chicago);

        // Remove an edge and test again
        cout << endl << "Removing road (New York -> Los Angeles)..." << endl;
        cityGraph.removeEdge(newYork, losAngeles);

        // Test BFS and DFS again after removal
        testConnections(newYork);

        // Remove a vertex and test again
        cout << endl << "Removing city Los Angeles..." << endl;
        cityGraph.removeVertex(losAngeles);

        cout << "Final Graph Representation after removal:" << endl;
        cityGraph.print();

        // Final BFS/DFS test
        testConnections(newYork);
    }
    catch (const exception& e)
    {
        cerr << "Unexpected error: " << e.what() << endl;
    }
}
