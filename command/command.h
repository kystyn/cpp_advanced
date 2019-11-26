#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

template<typename T, typename ...Args>
class Command
{
public:
    Command( T (*f)( Args... args) ) :
        command(std::make_shared<FreeCommand>(f)) {}

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

    // Command class for global-space function
    class FreeCommand : public BasicCommand
    {
    public:
        FreeCommand( T (*f)( Args... args) ) : f(f) {}

        T execute( Args... args ) const override
        {
            return f(args...);
        }

    private:
        T (*f)( Args... args );
    };

    // Command class for mutable method
    template<typename U>
    class InnerCommandMutable : public BasicCommand
    {
    public:
        InnerCommandMutable( U * const example, T (U::*f)( Args... args) ) : thisPtr(example), f(f)
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

    // Command class for method
    template<typename U>
    class InnerCommandConst : public BasicCommand
    {
    public:
        InnerCommandConst( U const * const example, T (U::*f)( Args... args) const ) : thisPtr(example), f(f)
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

    std::shared_ptr<BasicCommand> command;
};

#endif // COMMAND_H
