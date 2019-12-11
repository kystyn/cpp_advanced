#include <iostream>
#include <functional>

#include "command.h"
#include "any.h"
#include "binarytree.h"

#include "engine.h"

using namespace std;

class Foo
{
public:
    Foo( int val ) : val(val) {}

    int funct1( int a, int c )
    {
        return a - c + val++;
    }

    int funct2( int a, int c ) const
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

    //Engine engine;
    Command
            command1(&bar, &Foo::funct1, {{"arg1", 0}, {"arg2", 0}});
            //command2(&bar, &Foo::funct2, {{"arg11", 0}, {"arg21", 0}});

    //engine.registerCommand("function1", &command1);
    //engine.registerCommand("function2", &command2);

    try {
        //std::cout << engine.execute<int, int, int>("function1", {{"arg2", 5}, {"arg1", 3}}) << "\n";
        std::cout << command1({{"arg2", 5}, {"arg1", 3}}) << "\n";
    } catch (const char *msg) {
        std::cerr << "Error: " << msg << "\n";
    }

    try {
        //std::cout << engine.execute<int, int, int>("function1", {{"arg2", 0.7f}, {"arg1", 3}}) << "\n";
        std::cout << command1({{"arg2", 0.7f}, {"arg1", 3}}) << "\n";
    } catch (const char *msg) {
        std::cerr << "Error: " << msg << "\n";
    }

    try {
        //std::cout << engine.execute<int, int, int>("function1", {{"arg2", 5}, {"arg3", 3}}) << "\n";
        std::cout << command1({{"arg2", 5}, {"arg3", 3}}) << "\n";
    } catch (const char *msg) {
        std::cerr << "Error: " << msg << "\n";
    }

    /*
    std::cout << c2(1.05, 3) << std::endl;
    c0(2.0, 5.0);
    c1(2, 3);
    c1(5, 8);
    std::cout << c3(2.05, 3) << std::endl;
    std::cout << c2(2.05, 5) << std::endl;
    std::cout << c4(10, 20) << std::endl;*/

    //BinaryTree<std::string, Any> t;

    return 0;
}
