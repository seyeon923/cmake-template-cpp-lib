#pragma once

using namespace System;

#include "mylib/mylib.hpp"

namespace mylib{
namespace CLR {
    public ref class Useless
    {
    public:
        Useless();
        ~Useless();
        !Useless();
    private:
        mylib::Useless* p_useless_ = nullptr;
        bool is_disposed_ = false;
    };

    public ref class Functions abstract sealed{
    public:
        static int CppFunction(String^ str, int repeat);
        static bool IsExOptVarDefined();
    };
} // namespace CLR
} // namespace mylib
