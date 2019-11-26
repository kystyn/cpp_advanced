#include <iostream>
#include <functional>

#include "command.h"

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

    Command<void, float, float> c0(doSmth);
    Command<void, int, int> c1([]( int a, int b ) { std::cout << a + b << std::endl; });
    Command<double, double, double> c2(&bar, &Foo::funct1);
    Command<double, double, double> c3([&bar]( double a, double c ) -> double { return bar.funct2(a, c); });

    std::cout << c2(1.05, 3) << std::endl;
    c0(2.0, 5.0);
    c1(2, 3);
    c1(5, 8);
    std::cout << c3(2.05, 3) << std::endl;
    std::cout << c2(2.05, 5) << std::endl;

    return 0;
}
