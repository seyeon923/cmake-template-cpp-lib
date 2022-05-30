#include "mylib.clr.h"

#include <string>

void CsStrtoCppStr(String^ cs_str, std::string& cpp_str){
    using namespace Runtime::InteropServices;
    char* c_str = static_cast<char*>
        (Marshal::StringToHGlobalAnsi(cs_str).ToPointer());
    cpp_str = c_str;
    Marshal::FreeHGlobal(IntPtr(static_cast<void*>(c_str)));
}
void CsStrToCppStr(String^ cs_str, std::u16string& cpp_str) {
    using namespace Runtime::InteropServices;
    char16_t* c_str = static_cast<char16_t*>
        (Marshal::StringToHGlobalUni(cs_str).ToPointer());
    cpp_str = c_str;
    Marshal::FreeHGlobal(IntPtr(static_cast<void*>(c_str)));
}
String^ CppStrToCsStr(const std::string& cpp_str){
    return gcnew String(cpp_str.c_str());
}

namespace mylib {
namespace CLR{
    Useless::Useless() { 
        p_useless_ = new mylib::Useless; 
        if(!p_useless_) {
            gcnew OutOfMemoryException;
        }
    }
    Useless::~Useless() {
        if(!is_disposed_) {
            this->!Useless();
        }
        is_disposed_ = true;
    }
    Useless::!Useless() { 
        if(p_useless_) {
            delete p_useless_;
        }
        p_useless_ = nullptr;
    }

    int Functions::CppFunction(String^ str, int repeat){
        std::string cpp_str;
        CsStrtoCppStr(str, cpp_str);
        return mylib::CppFunction(cpp_str, repeat);
    }
    bool Functions::IsExOptVarDefined() {
        return mylib::IsExOptVarDefined();
    }
} // namespace CLR
} // namespace mylib