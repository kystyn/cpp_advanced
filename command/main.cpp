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

int main()
{
    Foo bar(2);

    Command<void, int, int> c1([]( int a, int b ) { std::cout << a + b << std::endl; });
    Command<double, double, double> c2(&bar, &Foo::funct1);
    std::function<double(double, double)> l = [&bar]( double a, double c ) -> double { return bar.funct2(a, c); };
    Command<double, double, double> c3(&l, &std::function<double(double, double)>::operator());

    c1(2, 3);
    c1(5, 8);
    std::cout << c2(1.05, 3) << std::endl;
    std::cout << c3(2.05, 3) << std::endl;

    return 0;
}
