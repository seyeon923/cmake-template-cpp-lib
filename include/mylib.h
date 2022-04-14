#include "mylib_config.h"

#ifdef EXPORT_C_FUNC
extern "C" {
int mylib_c_func(const char* str, int repeat);
}
#endif