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
    Variable( T const &val ) : theValue(val)
    {
    }

    bool setValue( T value )
    {
        theValue = value;
    }

    T value() const { return theValue; }

private:
    T theValue;
};

#endif // VARIABLE_H
