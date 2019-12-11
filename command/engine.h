#ifndef ENGINE_H
#define ENGINE_H

#include "varmanager.h"
#include "command.h"

class Engine : public VarManager
{
public:
    using VarManager::VarManager;

    template<typename T, typename ...Args>
    void registerCommand( std::string const &name, Command<T, Args...> command )
    {
        VarManager::initializeVariable(name, command);
    }

    template<typename T, typename ...Args>
    int execute( std::string const &name, std::map<std::string, Any> const &args ) {
        Command<T, Args...> command;
        VarManager::getValue(name, command);
        return command(args);
    }

};

#endif // ENGINE_H
