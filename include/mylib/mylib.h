#ifndef MYLIB_INCLUDE_MYLIB_MYLIB_H_
#define MYLIB_INCLUDE_MYLIB_MYLIB_H_

#include "mylib/mylib_api.h"

extern "C" {
int MYLIB_API mylib_c_func(const char* str, int repeat);
}

#endif  // MYLIB_INCLUDE_MYLIB_MYLIB_H_