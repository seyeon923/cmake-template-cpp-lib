#include "mylib.hpp"

#include <iostream>

using namespace std;

int mylib_c_func(const char* str, int repeat) {
    for (int i = 0; i < repeat; ++i) {
        std::cout << str << ' ';
    }
    std::cout << endl;
    return 0;
}

int mylib::CppFunction(const string& str, int repeat) {
    return mylib_c_func(str.c_str(), repeat);
}