#include <iostream>
#include <string>

template<typename T>
void write(T value) {
    std::cout << value << std::endl;
}

template<typename T, typename... O>
void write(T arg, O... other) {
    std::cout << arg << " ";
    write(other...);
}

template <typename... t>
void debug(t... args) {
    std::cout << "DEBUG: ";
    write(args...);
}

int main() {
    int a = 12;
    double b = 234.1234;

    std::string test = "hallo";
    char d = 'a';

    debug("debug test");
    debug("number", 42);

    debug(1223, 41, 5.234);

    debug(a, b, test, d);

    return 0;
}
