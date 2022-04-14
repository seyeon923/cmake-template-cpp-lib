#include <iostream>

#include "mylib.hpp"

int main() {
    std::cout << "mylib version: " << MYLIB_VERSION_MAJOR << '.'
              << MYLIB_VERSION_MINOR << std::endl;

#ifdef EXPORT_C_FUNC
    std::cout << "\nCall mylib_c_func(\"hi\", 3)" << std::endl;
    std::cout << "return: " << mylib_c_func("hi", 3) << std::endl;
#else
    std::cout << "\nNo C Function" << std::endl;
#endif

    std::cout << "\nCall mylib::CppFunc(\"Hello\", 2)" << std::endl;
    std::cout << "return: " << mylib::CppFunction("Hello", 2) << std::endl;

    return 0;
}