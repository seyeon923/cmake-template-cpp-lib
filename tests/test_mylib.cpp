#include <iostream>

#include "mylib.hpp"

int main() {
    std::cout << "mylib version: " << MYLIB_VERSION_MAJOR << '.'
              << MYLIB_VERSION_MINOR << '.' << MYLIB_VERSION_PATCH << std::endl;

#ifdef EX_OPT_VAR
    std::cout << "\nEX_OPT_VAR defined" << std::endl;
#else
    std::cout << "\nEX_OPT_VAR not defined" << std::endl;
#endif

    std::cout << "\nCall mylib_c_func(\"hi\", 3)" << std::endl;
    std::cout << "return: " << mylib_c_func("hi", 3) << std::endl;

    std::cout << "\nCall mylib::CppFunc(\"Hello\", 2)" << std::endl;
    std::cout << "return: " << mylib::CppFunction("Hello", 2) << std::endl;

    return 0;
}