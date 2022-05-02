#ifndef MYLIB_INCLUDE_MYLIB_MYLIB_HPP_
#define MYLIB_INCLUDE_MYLIB_MYLIB_HPP_

#include <string>

#include "mylib/mylib_api.h"

namespace mylib {
MYLIB_API int CppFunction(const std::string& str, int repeat);
MYLIB_API bool IsExOptVarDefined();
MYLIB_API std::string GetBuildType();
}  // namespace mylib

#endif  // MYLIB_INCLUDE_MYLIB_MYLIB_HPP_