#include <iostream>
#include <Any.h>

using namespace std;

int main()
{
    try {
        Any v(2.0f);

        double b = v.cast<float>();
        std::cout << b << std::endl;

        Any u("abc");
        auto c = u.cast<const char *>();
        std::cout << c << std::endl;

        v = 4.0f;
        b = v.cast<float>();
        std::cout << b << std::endl;
    }
    catch (const char *msg)
    {
        std::cerr << "Error: " << msg << std::endl;
    }

    return 0;
}
