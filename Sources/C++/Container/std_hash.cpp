#include <iostream>
#include <functional>
#include <string>

int main(int argc, char *argv[])
{
    std::hash<std::string> h;
    size_t n = h("Hello world");
    std::cout << n << std::endl;

    return 0;
}
