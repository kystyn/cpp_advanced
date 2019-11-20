#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class BaseVariable
{
public:
    virtual bool setValue( std::string const & ) = 0;
};

template<typename T>
class Variable : public BaseVariable
{
public:
    Variable( T const &val ) : _value(val)
    {
    }

    bool setValue( std::string const & );

    T value() const { return _value; }

private:
    T _value;
};

#endif // VARIABLE_H
