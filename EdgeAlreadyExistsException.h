#ifndef EDGEALREADYEXISTSEXCEPTION_H
#define EDGEALREADYEXISTSEXCEPTION_H

#include <stdexcept>
#include <sstream>

template <class T>
class EdgeAlreadyExistsException : public std::runtime_error
{
public:
    explicit EdgeAlreadyExistsException(const T& from, const T& to)
        : std::runtime_error(buildMessage(from, to))
    {
    }

private:
    static std::string buildMessage(const T& from, const T& to)
    {
        std::ostringstream oss;
        oss << "Edge already exists from: " << from << " to->" << to;
        return oss.str();
    }
};
#endif //EDGEALREADYEXISTSEXCEPTION_H
