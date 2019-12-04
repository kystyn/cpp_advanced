#ifndef CMDARGSMGR_H
#define CMDARGSMGR_H

#include <map>
#include <string>
#include <memory>

#include "any.h"

class VarManager
{
public:
    VarManager() {}

    VarManager & operator=( VarManager const & ) = delete;
    VarManager( VarManager const & ) = delete;

    template<typename T>
    void initializeVariable( std::string const &name, T const & val )
    {
        auto it = values.find(name);
        if (it == values.end())
            values.insert({name, std::make_shared<Any>(val)});
    }

    template<typename T>
    void getValue( std::string const &varName, T const &val )
    {
        auto it = values.find(varName);
        if (it == values.end())
            throw (std::string("No variable with name ") + varName + " found").c_str();

        val = it->second->cast<T>(val);
    }

    void assignVariable( std::string const &varName, std::string const &val )
    {
        auto it = values.find(varName);

        if (it == values.end())
            throw "This variable was not initialized";

        *(it->second) = val;
    }

private:
    std::map<std::string, std::shared_ptr<Any>> values;
};

#endif // CMDARGSMGR_H
