#pragma once

#include <windows.h>

namespace platform
{
    class file
    {
    public:
        file();
        ~file();

    public:
        void open(const char* filename);
        void size();
        void read();
        void write(const void* data);
        void close();

    private:
        HANDLE m_Handle;    // void*
        PVOID m_Buffer;     // void*
        DWORD m_Size;       // uint32_t
    };
}
