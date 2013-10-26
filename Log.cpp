#include "Log.h"

#include <stdarg.h>
#include <iostream>
#include <stdio.h>

namespace hsg {
    void Log::info(const char* fmt, ...) {
        va_list lVarArgs;
        va_start(lVarArgs, fmt);
        const size_t SIZE = 512;
        char buffer[SIZE] = { 0 };
        vsnprintf(buffer, SIZE, fmt, lVarArgs);

        std::cout<<"HSG:INFO:"<<buffer<<std::endl;
        va_end(lVarArgs);
    }

    void Log::error(const char* fmt, ...) {
        va_list lVarArgs;
        va_start(lVarArgs, fmt);
        const size_t SIZE = 512;
        char buffer[SIZE] = { 0 };
        vsnprintf(buffer, SIZE, fmt, lVarArgs);

        std::cerr<<"HSG:ERROR:"<<buffer<<std::endl;
        va_end(lVarArgs);
    }

    void Log::warn(const char* fmt, ...) {
        va_list lVarArgs;
        va_start(lVarArgs, fmt);
        const size_t SIZE = 512;
        char buffer[SIZE] = { 0 };
        vsnprintf(buffer, SIZE, fmt, lVarArgs);

        std::cout<<"HSG:WARNING:"<<buffer<<std::endl;
        va_end(lVarArgs);
    }

    void Log::debug(const char* fmt, ...) {
        va_list lVarArgs;
        va_start(lVarArgs, fmt);
        const size_t SIZE = 512;
        char buffer[SIZE] = { 0 };
        vsnprintf(buffer, SIZE, fmt, lVarArgs);

        std::cout<<"HSG:DEBUG:"<<buffer<<std::endl;
        va_end(lVarArgs);
    }
}
