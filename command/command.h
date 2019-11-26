#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <functional>

template<typename T, typename ...Args>
class Command
{
public:
    Command( std::function<T(Args...)> const &f ) :
        command(std::make_shared<StdFunctionCommand>(f)) {}

    template<typename U>
    Command( U const * const example, T (U::*f)( Args... args) const ) :
        command(std::make_shared<InnerCommandConst<U>>(example, f)) {}

    template<typename U>
    Command( U * const example, T (U::*f)( Args... args) ) :
        command(std::make_shared<InnerCommandMutable<U>>(example, f)) {}

    T operator()( Args... args ) const
    {
        return command->execute(args...);
    }

private:
    // Basic command class
    class BasicCommand
    {
    public:
        BasicCommand( void ) {}

        virtual T execute( Args... args ) const = 0;
    };

    // Command class for mutable method
    template<typename U>
    class InnerCommandMutable : public BasicCommand
    {
    public:
        InnerCommandMutable( U * const example, T (U::*inF)( Args... args) ) : thisPtr(example), f(inF)
        {
        }

        T execute( Args... args ) const override
        {
            return (thisPtr->*f)(args...);
        }
    private:
        U * const thisPtr;
        T (U::*f)( Args... args );
    };

    // Command class for constant method
    template<typename U>
    class InnerCommandConst : public BasicCommand
    {
    public:
        InnerCommandConst( U const * const example, T (U::*inF)( Args... args) const ) : thisPtr(example), f(inF)
        {
        }

        T execute( Args... args ) const override
        {
            return (thisPtr->*f)(args...);
        }
    private:
        U const * const thisPtr;
        T (U::*f)( Args... args ) const;
    };

    // Command class for std::function
    class StdFunctionCommand : public InnerCommandConst<std::function<T(Args...)>>
    {
    public:
        StdFunctionCommand( std::function<T(Args...)> const &f ) :
            InnerCommandConst<std::function<T(Args...)>>(&myFuncCopy, &std::function<T(Args...)>::operator()),
            myFuncCopy(f)
        {
        }
    private:
        std::function<T(Args...)> myFuncCopy;
    };

    std::shared_ptr<BasicCommand> command;
};

#endif // COMMAND_H
