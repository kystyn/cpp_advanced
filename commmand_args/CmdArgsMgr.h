#ifndef CMDARGSMGR_H
#define CMDARGSMGR_H

#include <map>
#include <string>
#include <memory>

#include "Variable.h"

class CmdArgsMgr
{
public:
    static CmdArgsMgr & manager( void ) { return instance; }

    CmdArgsMgr & operator=( CmdArgsMgr const & ) = delete;
    CmdArgsMgr( CmdArgsMgr const & ) = delete;

    template<typename T>
    void initializeVariable( std::string const &name, T const & val )
    {
        auto it = values.find(name);
        if (it == values.end())
            values.insert({name, std::make_shared<Variable<T>>(val)});
    }

    template<typename T>
    bool getValue( std::string const &varName, T const &val )
    {
        auto it = values.find(varName);
        if (it == values.end())
            return false;

        Variable<T> *v = dynamic_cast<Variable<T>>(it->second);

        if (v == nullptr)
            return false;

        val = v->value();
        return true;
    }

private:
    CmdArgsMgr() {}

    void assignVariableFromCmd( std::string const &varName, std::string const &val )
    {
        auto it = values.find(varName);

        if (it == values.end())
            throw "This variable was not initialized";

        it->second->setValue(val);
    }

    static CmdArgsMgr instance;
    std::map<std::string, std::shared_ptr<BaseVariable>> values;
};

#endif // CMDARGSMGR_H
