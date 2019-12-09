#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <functional>
#include <map>

#include "any.h"

template<typename T, typename ...Args>
class Command
{
public:
    Command( std::function<T(Args...)> const &f,
             std::vector<std::pair<std::string, Any>> const &cmdArgs ) :
        command(std::make_shared<StdFunctionCommand>(f), cmdArgs) {}

    template<typename U>
    Command( U const * const example, T (U::*f)( Args... ) const,
             std::vector<std::pair<std::string, Any>> const &cmdArgs ) :
        command(std::make_shared<InnerCommandConst<U>>(example, f), cmdArgs) {}

    template<typename U>
    Command( U * const example, T (U::*f)( Args... ) ,
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

        std::vector<std::pair<std::string, Any>> mapToVector( std::map<std::string, Any> &args ) const {
            std::vector<std::pair<std::string, Any>> v(args.size());

            size_t i = 0;
            for (auto t : cmdArgs)
                v[i++] = args.find(t.first)->second;

            return v;
        }

    protected:
        std::vector<std::pair<std::string, Any>> const &cmdArgs;
    };

    // Command class for mutable method
    template<typename U>
    class InnerCommandMutable : public BasicCommand
    {
    public:
        InnerCommandMutable( U * const example, T (U::*inF)( Args... ),
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

    private:
        T exec( int iterNo,
                std::vector<std::pair<std::string, Any>> const &args, Args... argsQ )
        {
            return exec(iterNo + 1, args, argsQ..., args[iterNo]);
            if (iterNo == BasicCommand::cmdArgs.size() - 1)
                return (thisPtr->*f)(argsQ...);
        }

        U * const thisPtr;
        T (U::*f)( Args... );
    };

    // Command class for constant method
    template<typename U>
    class InnerCommandConst : public BasicCommand
    {
    public:
        InnerCommandConst( U const * const example, T (U::*inF)( Args... ) const,
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

    private:
        T exec( int iterNo,
                std::vector<std::pair<std::string, Any>> const &args, Args ...argsQ )
        {
            return exec(iterNo + 1, args, argsQ..., args[iterNo]);
            if (iterNo == BasicCommand::cmdArgs.size() - 1)
                return (thisPtr->*f)(argsQ...);
        }

        U const * const thisPtr;
        T (U::*f)( Args... ) const;
    };

    // Command class for std::function
    class StdFunctionCommand : public InnerCommandConst<std::function<T(Args...)>>
    {
    public:
        StdFunctionCommand( std::function<T(Args...)> const &f,
                            std::vector<std::pair<std::string, Any>> const &args ) :
            InnerCommandConst<std::function<T(Args...)>>(&myFuncCopy, &std::function<T(Args...)>::operator(), args),
            myFuncCopy(f)
        {
        }

    private:
        std::function<T(Args...)> myFuncCopy;
    };

    std::shared_ptr<BasicCommand> command;
};

//template<typename T, typename ...Args>
//Command( T (*f)( Args... args) ) -> Command<T, Args...>;


#endif // COMMAND_H
