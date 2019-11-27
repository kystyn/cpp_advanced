#ifndef ANY_H
#define ANY_H

#include <typeinfo>
#include <memory>

class Any
{
public:
    template<typename T>
    Any( T newVariable ) :
        var(std::make_unique<ConcreteHolder<T>>(ConcreteHolder<T>(newVariable)))
    {
    }

    template<typename U>
    Any & operator=( const U &newVal )
    {
        if (typeid(U).hash_code() != var->getTypeInfo())
            throw "Cannot assign variableof another type";
        static_cast<ConcreteHolder<U> *>(var.get())->setValue(newVal);
    }

    template<typename U>
    U cast( void ) const
    {
        if (typeid(U).hash_code() != var->getTypeInfo())
            throw "Bad cast";
        return static_cast<ConcreteHolder<U> *>(var.get())->getValue();
    }
private:
    class BaseHolder
    {
    public:
        size_t getTypeInfo() const
        {
            return typeInfo;
        }
    protected:
        size_t typeInfo;
    };

    template<typename T>
    class ConcreteHolder : public BaseHolder
    {
    private:
        T variable;

    public:
        ConcreteHolder( T newVar )
        {
            variable = newVar;
            typeInfo = typeid(T).hash_code();
        }

        void setValue( T newVal )
        {
            variable = newVal;
        }
        T getValue() const { return variable; }
    };

    std::unique_ptr<BaseHolder> var;
};

#endif // ANY_H
