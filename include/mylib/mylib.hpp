#ifndef MYLIB_INCLUDE_MYLIB_HPP_
#define MYLIB_INCLUDE_MYLIB_HPP_

#include <string>

#include "mylib/mylib.h"

#if defined(_WIN32)
#    if defined(EXPORT_MYLIB)
#        define MYLIB_API __declspec(dllexport)
#    elif defined(IMPORT_MYLIB)
#        define MYLIB_API __declspec(dllimport)
#    else
#        define MYLIB_API
#    endif
#else  // non windows
#    define MYLIB_API
#endif

namespace mylib {
int MYLIB_API CppFunction(const std::string& str, int repeat);
bool MYLIB_API IsExOptVarDefined();
}  // namespace mylib

#endif  // MYLIB_INCLUDE_MYLIB_HPP_