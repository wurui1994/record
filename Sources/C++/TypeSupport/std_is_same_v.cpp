#include <iostream>
#include <type_traits>
#include <cstdint>

void print_separator()
{
    std::cout << "-----\n";
}

int main()
{
    // is_same [C++11] is_same_v [C++17]

    std::cout << std::boolalpha;

    std::cout << std::is_same<int, int32_t>::value << '\n';   // true
    std::cout << std::is_same<int, int64_t>::value << '\n';   // false
    std::cout << std::is_same<float, int32_t>::value << '\n'; // false

    print_separator();

    std::cout << std::is_same<int, int>::value << "\n";          // true
    std::cout << std::is_same<int, unsigned int>::value << "\n"; // false
    std::cout << std::is_same<int, signed int>::value << "\n";   // true

    print_separator();

    // unlike other types 'char' is not 'unsigned' and not 'signed'
    std::cout << std::is_same<char, char>::value << "\n";          // true
    std::cout << std::is_same<char, unsigned char>::value << "\n"; // false
    std::cout << std::is_same<char, signed char>::value << "\n";   // false

    print_separator();

    // the `const` and `*` order is matter
    std::cout << std::is_same_v<const char,char const> << std::endl; //true
    std::cout << std::is_same_v<const char*,char* const> << std::endl; // false
    std::cout << std::is_same_v<const char*,char const*> << std::endl; // true
}
