#ifndef MYLIB_INCLUDE_MYLIB_MYLIB_HPP_
#define MYLIB_INCLUDE_MYLIB_MYLIB_HPP_

#include <string>

#include "mylib/mylib_api.h"

namespace mylib {
int MYLIB_API CppFunction(const std::string& str, int repeat);
bool MYLIB_API IsExOptVarDefined();
std::string MYLIB_API GetBuildType();
}  // namespace mylib

#endif  // MYLIB_INCLUDE_MYLIB_MYLIB_HPP_