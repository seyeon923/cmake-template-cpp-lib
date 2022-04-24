#ifndef MYLIB_INLCUDE_MYLIB_MYLIB_API_H_
#define MYLIB_INLCUDE_MYLIB_MYLIB_API_H_

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

#endif  // MYLIB_INLCUDE_MYLIB_MYLIB_API_H_