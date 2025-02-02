#ifndef EDGENOTFOUNDEXCEPTION_H
#define EDGENOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <sstream>

template <class T>
class EdgeNotFoundException : public std::runtime_error
{
public:
    /**
     * Exception with <i>"Can't find edge"</i> message
     */
    EdgeNotFoundException() : std::runtime_error("Can't find edge")
    {}

    /**
     * Add a costume message
     * @param msg msg to be thrown
     */
    explicit EdgeNotFoundException(const std::string& msg)
        : std::runtime_error(msg)
    {}


    /**
     * Display error with two vertices
     * @param from source vertex
     * @param to destination vertex
     */
    EdgeNotFoundException(const T& from, const T& to) :
    std::runtime_error(buildMessage(from, to)) {}


private:
    static std::string buildMessage(const T& from, const T& to)
    {
        std::ostringstream oss;
        oss << "No such edge from: " << from << " to->" << to;
        return oss.str();
    }
};


#endif //EDGENOTFOUNDEXCEPTION_H
