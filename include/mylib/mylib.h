#ifndef MYLIB_INCLUDE_MYLIB_H_
#define MYLIB_INCLUDE_MYLIB_H_

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

extern "C" {
int MYLIB_API mylib_c_func(const char* str, int repeat);
}

#endif  // MYLIB_INCLUDE_MYLIB_H_