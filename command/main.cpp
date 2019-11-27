#include <iostream>
#include <functional>

#include "command.h"
#include "any.h"
#include "binarytree.h"

using namespace std;

class Foo
{
public:
    Foo( int val ) : val(val) {}

    double funct1( double a, double c )
    {
        return a * c + val++;
    }

    double funct2( double a, double c ) const
    {
        return a * c + val;
    }
private:
    int val;
};

void doSmth( float x, float y )
{
    std::cout << x / y << std::endl;
}

int main()
{
    Foo bar(2);

    Command c0(doSmth);
    Command<void, int, int> c1([]( int a, int b ) { std::cout << a + b << std::endl; });
    Command c2(&bar, &Foo::funct1);
    Command<double, double, double> c3([&bar]( double a, double c ) -> double { return bar.funct2(a, c); });
    Command c4(&bar, &Foo::funct2);

    std::cout << c2(1.05, 3) << std::endl;
    c0(2.0, 5.0);
    c1(2, 3);
    c1(5, 8);
    std::cout << c3(2.05, 3) << std::endl;
    std::cout << c2(2.05, 5) << std::endl;
    std::cout << c4(10, 20) << std::endl;

    BinaryTree<std::string, Any> t;

    return 0;
}
