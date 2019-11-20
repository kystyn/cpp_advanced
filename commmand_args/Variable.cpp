#include <cstring>
#include "Variable.h"

template<>
bool Variable<float>::setValue( std::string const &val )
{
    float valFloat;
    try {
        valFloat = std::stof(val);
    } catch (...) {
        return false;
    }
    _value = valFloat;
    return true;
}

template<>
bool Variable<int>::setValue( std::string const &val )
{
    int valFloat;
    try {
        valFloat = std::stoi(val);
    } catch (...) {
        return false;
    }
    _value = valFloat;
    return true;
}

template<>
bool Variable<double>::setValue( std::string const &val )
{
    double valFloat;
    try {
        valFloat = std::stod(val);
    } catch (...) {
        return false;
    }
    _value = valFloat;
    return true;
}

template<>
bool Variable<std::string>::setValue( std::string const &val )
{
    _value = val;
    return true;
}

template<>
bool Variable<char *>::setValue( std::string const &val )
{
    std::strcpy(_value, val.c_str());
    return true;
}
