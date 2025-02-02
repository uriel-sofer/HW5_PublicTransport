#ifndef VERTEXNOTFOUNDEXCEPTION_H
#define VERTEXNOTFOUNDEXCEPTION_H



#include <stdexcept>
#include <sstream>

/**
 * Exception when a vertex is not found
 * @tparam T Vertex type
 */
template <class T>
class VertexNotFoundException : public std::runtime_error {
public:

    VertexNotFoundException()
        : std::runtime_error("Vertex not found") {}

    explicit VertexNotFoundException(const T& vertex)
        : std::runtime_error(buildMessage(vertex)) {}

private:
    static std::string buildMessage(const T& vertex) {
        std::ostringstream oss;
        oss << "Vertex not found: " << vertex;
        return oss.str();
    }
};



#endif //VERTEXNOTFOUNDEXCEPTION_H
