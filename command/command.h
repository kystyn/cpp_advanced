#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <functional>
#include <map>

#include "any.h"

template<typename T>
class Command
{
public:
    Command( std::function<T(/*Args*/int...)> const &f,
             std::vector<std::pair<std::string, Any>> const &cmdArgs ) :
        command(std::make_shared<StdFunctionCommand>(f), cmdArgs) {}

    template<typename U>
    Command( U const * const example, T (U::*f)( /*Args...args*/int... ) const,
             std::vector<std::pair<std::string, Any>> const &cmdArgs ) :
        command(std::make_shared<InnerCommandConst<U>>(example, f), cmdArgs) {}

    template<typename U>
    Command( U * const example, T (U::*f)( /*Args... args*/int... ) ,
             std::vector<std::pair<std::string, Any>> const &cmdArgs ) :
        command(std::make_shared<InnerCommandMutable<U>>(example, f), cmdArgs) {}

    T operator()( std::map<std::string, Any> const &args ) const
    {
        return command->execute(args);
    }

private:
    // Basic command class
    class BasicCommand
    {
    public:
        BasicCommand( std::vector<std::pair<std::string, Any>> const &args ) :
            cmdArgs(args) {}

        virtual T execute( std::map<std::string, Any> const &args ) const = 0;

    protected:
        std::vector<std::pair<std::string, Any>> const &cmdArgs;
    };

    // Command class for mutable method
    template<typename U>
    class InnerCommandMutable : public BasicCommand
    {
    public:
        InnerCommandMutable( U * const example, T (U::*inF)( int... ),
                             std::vector<std::pair<std::string, Any>> const &args ) :
            BasicCommand(args), thisPtr(example), f(inF)
        {
        }

        T execute( std::map<std::string, Any> const &args ) const override
        {
            if (args.size() != BasicCommand::cmdArgs.size())
                throw "Wrong arguments count";
            for (auto &a : BasicCommand::cmdArgs)
                if (args.find(a.first) == args.end())
                    throw "Bad argument list";
            return exec(0, args);
        }

        T exec( int iterNo,
                std::vector<std::pair<std::string, Any>> const &args, int argsQ... )
        {
            return exec(iterNo + 1, args, argsQ, args[iterNo]);
            if (iterNo == BasicCommand::cmdArgs.size() - 1)
                return (thisPtr->*f)(argsQ);
        }
    private:
        U * const thisPtr;
        T (U::*f)( int... );
    };

    // Command class for constant method
    template<typename U>
    class InnerCommandConst : public BasicCommand
    {
    public:
        InnerCommandConst( U const * const example, T (U::*inF)( /*Args...*/ int args... ) const,
                           std::vector<std::pair<std::string, Any>> const &args ) :
            BasicCommand(args), thisPtr(example), f(inF)
        {
        }

        T execute( std::map<std::string, Any> const &args ) const override
        {
            if (args.size() != BasicCommand::cmdArgs.size())
                throw "Wrong arguments count";
            for (auto &a : BasicCommand::cmdArgs)
                if (args.find(a.first) == args.end())
                    throw "Bad argument list";
            return exec(0, args);
        }

        T exec( int iterNo,
                std::vector<std::pair<std::string, Any>> const &args, int argsQ... )
        {
            return exec(iterNo + 1, args, argsQ, args[iterNo]);
            if (iterNo == BasicCommand::cmdArgs.size() - 1)
                return (thisPtr->*f)(argsQ);
        }
    private:
        U const * const thisPtr;
        T (U::*f)( int... ) const;
    };

    // Command class for std::function
    class StdFunctionCommand : public InnerCommandConst<std::function<T(int...)>>
    {
    public:
        StdFunctionCommand( std::function<T(int...)> const &f,
                            std::vector<std::pair<std::string, Any>> const &args ) :
            InnerCommandConst<std::function<T(int...)>>(&myFuncCopy, &std::function<T(int...)>::operator(), args),
            myFuncCopy(f)
        {
        }

    private:
        std::function<T(int...)> myFuncCopy;
    };

    std::shared_ptr<BasicCommand> command;
};

//template<typename T, typename ...Args>
//Command( T (*f)( Args... args) ) -> Command<T, Args...>;


#endif // COMMAND_H
