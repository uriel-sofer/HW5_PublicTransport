#ifndef GRAPH_H
#define GRAPH_H

#include <iomanip>
#include <iostream>
#include <vector>

#include "VectorQueue.h"
#include "EdgeAlreadyExistsException.h"
#include "EdgeNotFoundException.h"
#include "VertexNotFoundException.h"

using namespace std;

/**
 * Costume pair to associate vertex with index in the weights matrix
 * @tparam VertexType The vertex type. Must support:
 * - `<<` for output.
 * - `=` for deep copying.
 */
template <typename VertexType>
struct VertexIndex
{
    VertexType vertex;
    int index;

    VertexIndex(const VertexType& v, const int i) : vertex(v), index(i)
    {}
};


/**
 * A directed graph, implemented using an adjacency matrix.
 * @tparam VertexType The vertex type. Must support:
 * - `<<` for output.
 * - `=` for deep copying.
 * @tparam Weight The weight type. Must support:
 * - A default constructor (`Weight()`) used as an "empty" indicator.
 * - `==` for comparisons
 * - `=` for copying operations.
 */
template <class VertexType, class Weight>
class Graph
{
private:
    vector<VertexIndex<VertexType>> vertices; /* Stores the list of vertices, and indexes */
    vector<vector<Weight>> matrix; /* The adjacency matrix storing edge weights. */

    /**
     * Validates whether both <i>from</i> and <i>to</i> exist in the graph.
     * @param from The source vertex.
     * @param to The destination vertex.
     * @throws VertexNotFoundException If one or both of the vertices do not exist.
     */
    void validateVertices(const VertexType& from, const VertexType& to) const;

    /**
     * Validates whether there is an edge from <i>from</i> to <i>to</i>.
     * @param from The source vertex
     * @param to The destination vertex.
     * @throws EdgeNotFoundException if no edge found
     */
    void validateEdge(VertexType from, VertexType to) const;

    /**
     * Checks if an edge exists from <i>from</i> to <i>to</i>.
     * @param from The source vertex.
     * @param to The destination vertex.
     * @return <i>true</i> if an edge exists, <i>false</i> otherwise.
     * @throws VertexNotFoundException If one or both of the vertices do not exist.
     */
    bool edgeExists(const VertexType& from, const VertexType& to) const;

    /**
     * Validates whether <i>vertex</i> is in the graph or not
     * @param vertex The vertex in question
     * @return <i>true</i> if vertex exists, <i>false</i> otherwise.
     */
    bool vertexExists(const VertexType& vertex) const;

    /**
     * Updates the indexes after insertion and removal of vertices
     */
    void updateIndexes();

    /**
     * Retrieves the index of <i>vertex</i> in <i>vertices</i>
     * @param vertex Vertex to get the index to
     * @return the index of <i>vertex</i> in <i>vertices</i>
     */
    int getIndexForVertex(const VertexType& vertex) const;

    vector<VertexType> performBFS(const VertexType& vertex) const;

    vector<VertexType> performDFS(const VertexType& vertex) const;

    void dfs_visit(const VertexType &u, vector<bool> &visited, vector<VertexType> &result) const;

public:
    Graph() = default;
    Graph(const Graph& other) = default;
    Graph(Graph&& other) noexcept = default;
    Graph& operator=(const Graph& other) = default;
    Graph& operator=(Graph&& other) noexcept = default;

    /**
     * Adds a vertex to the graph.
     * @param vertex The vertex to add.
     */
    void addVertex(const VertexType& vertex);

    /**
     * Removes a vertex and all associated edges from the graph.
     * @param vertex The vertex to remove.
     * @throws VertexNotFoundException If the vertex does not exist.
     */
    void removeVertex(VertexType vertex);

    /**
     * Adds a directed edge from <i>from</i> to <i>to</i> with a given weight.
     * @param from The source vertex.
     * @param to The destination vertex.
     * @param weight The weight of the edge.
     * @throws VertexNotFoundException If one or both of the vertices do not exist.
     * @throws EdgeAlreadyExistsException If an edge already exists.
     */
    void addEdge(VertexType from, VertexType to, Weight weight);

    /**
     * Removes a directed edge from <i>from</i> to <i>to</i>.
     * @param from The source vertex.
     * @param to The destination vertex.
     * @throws VertexNotFoundException If one or both vertices do not exist.
     * @throws EdgeNotFoundException If the edge does not exist.
     */
    void removeEdge(VertexType from, VertexType to);

    /**
     * Updates the weight of an existing edge.
     * @param from The source vertex.
     * @param to The destination vertex.
     * @param val The new weight value.
     * @throws VertexNotFoundException If one or both vertices do not exist.
     * @throws EdgeNotFoundException If the edge does not exist.
     */
    void updateWeight(VertexType from, VertexType to, const Weight& val);

    /**
     * Retrieves the weight of an edge from <i>from</i> to <i>to</i>.
     * @param from The source vertex.
     * @param to The destination vertex.
     * @return The weight of the connection.
     * @throws EdgeNotFoundException If no such edge exists.
     */
    Weight getWeight(VertexType from, VertexType to) const;

    /**
     * Retrieves all vertices that can be reached directly from <i>vertex</i>.
     * @param vertex The vertex whose direct neighbors should be retrieved.
     * @return A vector of vertices that <i>vertex</i> has direct edges to.
     */
    vector<VertexType> getDirectNeighbors(VertexType vertex) const;

    /**
     * Retrieves all vertices that can be reached from <i>vertex</i> using any number of edges.
     * @param vertex The starting vertex for the search.
     * @param useBFS
     * @return A vector of all reachable vertices.
     */
    vector<VertexType> getConnections(VertexType vertex, bool useBFS = true) const;

    /**
     * Retrieves all vertices that have a direct edge to <i>vertex</i>.
     * @param vertex The target vertex.
     * @return A vector of vertices that directly point to <i>vertex</i>.
     */
    vector<VertexType> getDirectSources(VertexType vertex) const;

    /**
     * Prints the adjacency matrix representation of the graph.
     */
    void print(int) const;

    /**
     * Print vertex: vertex vertex
     */
    void print() const;

};


// Implementation

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::validateVertices(const VertexType& from, const VertexType& to) const
{
    if (not(vertexExists(from) and vertexExists(to)))
        throw VertexNotFoundException<VertexType>();
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::validateEdge(VertexType from, VertexType to) const
{
    validateVertices(from, to);
    if (!edgeExists(from, to))
        throw EdgeNotFoundException<VertexType>(from, to);
}


template <class VertexType, class Weight>
bool Graph<VertexType, Weight>::edgeExists(const VertexType& from, const VertexType& to) const
{
    validateVertices(from, to);
    return matrix[getIndexForVertex(from)][getIndexForVertex(to)] != Weight();
}

template <class VertexType, class Weight>
bool Graph<VertexType, Weight>::vertexExists(const VertexType& vertex) const
{
    for (auto currVertex : vertices)
    {
        if (currVertex.vertex == vertex)
            return true;
    }
    return false;
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::updateIndexes()
{
    for (int i = 0; i < vertices.size(); ++i)
        vertices[i].index = i;
}

template <class VertexType, class Weight>
int Graph<VertexType, Weight>::getIndexForVertex(const VertexType& vertex) const
{
    for (auto currVertex : vertices)
    {
        if (currVertex.vertex == vertex)
            return currVertex.index;
    }
    throw VertexNotFoundException<VertexType>(vertex);
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::addVertex(const VertexType& vertex)
{
    if (vertexExists(vertex)) return;

    vertices.emplace_back(vertex, vertices.size());
    matrix.emplace_back(vertices.size(), Weight());
    for (auto& row : matrix)
    {
        row.resize(vertices.size(), Weight());
    }
    updateIndexes();
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::removeVertex(VertexType vertex)
{
    const int index = getIndexForVertex(vertex);

    vertices.erase(vertices.begin() + index);

    matrix.erase(matrix.begin() + index);

    for (auto& row : matrix)
        row.erase(row.begin() + index);

    updateIndexes();
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::addEdge(VertexType from, VertexType to, Weight weight)
{
    validateVertices(from, to);
    if (edgeExists(from, to))
        throw EdgeAlreadyExistsException<VertexType>(from, to);

    matrix[getIndexForVertex(from)][getIndexForVertex(to)] = weight;
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::removeEdge(VertexType from, VertexType to)
{
    validateEdge(from, to);

    matrix[getIndexForVertex(from)][getIndexForVertex(to)] = Weight();
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::updateWeight(VertexType from, VertexType to, const Weight& val)
{
    validateEdge(from, to);

    matrix[getIndexForVertex(from)][getIndexForVertex(to)] = val;
}

template <class VertexType, class Weight>
Weight Graph<VertexType, Weight>::getWeight(VertexType from, VertexType to) const
{
    validateEdge(from, to);

    return matrix[getIndexForVertex(from)][getIndexForVertex(to)];
}

template <class VertexType, class Weight>
vector<VertexType> Graph<VertexType, Weight>::getDirectNeighbors(VertexType vertex) const
{
    if (not vertexExists(vertex))
        throw VertexNotFoundException<VertexType>(vertex);

    vector<VertexType> directNeighbors;
    for (auto currVertex : vertices)
        if (matrix[getIndexForVertex(vertex)][getIndexForVertex(currVertex.vertex)] != Weight())
            directNeighbors.push_back(currVertex.vertex);

    return directNeighbors;
}

template <class VertexType, class Weight>
vector<VertexType> Graph<VertexType, Weight>::getDirectSources(VertexType vertex) const
{
    if (not vertexExists(vertex))
        throw VertexNotFoundException<VertexType>(vertex);

    vector<VertexType> directSources;
    for (auto currVertex : vertices)
        if (matrix[getIndexForVertex(currVertex.vertex)][getIndexForVertex(vertex)] != Weight())
            directSources.push_back(currVertex.vertex);

    return directSources;
}

template <class VertexType, class Weight>
vector<VertexType> Graph<VertexType, Weight>::getConnections(VertexType vertex, bool useBFS) const
{
    vector<VertexType> result = useBFS ? performBFS(vertex) : performDFS(vertex);
    result.erase(result.begin());
    return result;
}

template<class VertexType, class Weight>
vector<VertexType> Graph<VertexType, Weight>::performBFS(const VertexType &vertex) const
{
    const size_t startIndex = getIndexForVertex(vertex);

    if (startIndex == static_cast<size_t>(-1))
        return {};

    vector<bool> visited(vertices.size(), false);

    vector<VertexType> result;
    VectorQueue<VertexType> queue;

    visited[startIndex] = true;
    queue.enqueue(vertex);
    result.push_back(vertex); // Include starting vertex in the result

    while (!queue.isEmpty())
    {
        VertexType currVertex = queue.dequeue();

        for (const auto& neighbor : getDirectNeighbors(currVertex))
        {
            size_t neighborIndex = getIndexForVertex(neighbor);

            if (!visited[neighborIndex])
            {
                visited[neighborIndex] = true;
                queue.enqueue(neighbor);
                result.push_back(neighbor);
            }
        }
    }

    return result;
}

template<class VertexType, class Weight>
vector<VertexType> Graph<VertexType, Weight>::performDFS(const VertexType &vertex) const
{
    const size_t startIndex = getIndexForVertex(vertex);

    if (startIndex == static_cast<size_t>(-1))
        return {};

    vector<bool> visited(vertices.size(), false);

    vector<VertexType> result;

    dfs_visit(vertex, visited, result);

    return result;
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::dfs_visit(const VertexType &u, vector<bool> &visited, vector<VertexType> &result) const
{
    const size_t index = getIndexForVertex(u);

    if (visited[index]) return;

    visited[index] = true;
    result.push_back(u);

    for (const auto& neighbor : getDirectNeighbors(u))
    {
        if (!visited[getIndexForVertex(neighbor)])
        {
            dfs_visit(neighbor, visited, result);
        }
    }
}

template <class VertexType, class Weight>
void Graph<VertexType, Weight>::print(int) const
{
    cout << "Graph Representation:" << endl;
    cout << "Adjacency Matrix:" << endl;

    size_t col_width = 10;
    for (const auto& v : vertices)
    {
        stringstream ss;
        ss << v.vertex;
        col_width = max(col_width, ss.str().length() + 2);
    }
    const int colWidthInt = static_cast<int>(col_width);

    // Print header row
    cout << setw(colWidthInt) << "";
    for (const auto& v : vertices)
        cout << setw(colWidthInt) << v.vertex;

    // Print separation row
    cout << endl << setw(colWidthInt) << "" << setfill('-') << setw(vertices.size() * col_width) << "" << setfill(' ') << endl;

    for (size_t i = 0; i < vertices.size(); ++i)
    {
        cout << setw(colWidthInt) << left << vertices[i].vertex << "|"; // Print vertex
        for (size_t j = 0; j < vertices.size(); ++j)
        {
            cout << setw(colWidthInt) << right << matrix[i][j]; // Print weights
        }
        cout << endl;
    }
}

template<class VertexType, class Weight>
void Graph<VertexType, Weight>::print() const
{
    for (int i = 0; i < vertices.size(); ++i)
    {
        vector<VertexType> neighbor = getDirectNeighbors(vertices[i].vertex);

        cout << vertices[i].vertex << ": ";

        if (neighbor.empty())
            continue;


        for (const auto& n : neighbor)
        {
            cout << n << " ";
        }

        cout << endl;
    }
}

#endif //GRAPH_H
