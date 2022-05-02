#include "mylib/mylib.h"
#include "mylib/mylib.hpp"

#include <iostream>

#include "mylib_config.h"
#include "src/internal.h"

using namespace std;

int mylib_c_func(const char* str, int repeat) {
    for (int i = 0; i < repeat; ++i) {
        internal::MyPrint(str);
        internal::MyPrint(" ");
    }
    internal::MyPrint("\n");
    return 0;
}

int mylib::CppFunction(const string& str, int repeat) {
    return mylib_c_func(str.c_str(), repeat);
}

bool mylib::IsExOptVarDefined() {
#ifdef EX_OPT_VAR
    return true;
#else
    return false;
#endif
}