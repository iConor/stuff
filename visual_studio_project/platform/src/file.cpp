#include "file.h"


namespace platform
{
// TODO: Make an error module?
    void error(const char* function)
    {
        DWORD flags     = FORMAT_MESSAGE_ALLOCATE_BUFFER |
                          FORMAT_MESSAGE_FROM_SYSTEM |
                          FORMAT_MESSAGE_IGNORE_INSERTS;
        DWORD error     = GetLastError();
        DWORD lang      = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
        LPVOID buffer;

        DWORD length    = FormatMessage(flags, NULL, error, lang, (LPTSTR)&buffer, 0, NULL);

        // TODO: Printing this out will look more professional than reading it in the debugger.

        LocalFree(buffer);
    }


    file::file()
    {
    }


    file::~file()
    {
    }


    void file::open(const char* filename)
    {
        // use FILE_READ_ATTRIBUTES for file size to work
        m_Handle = CreateFile(filename,
                              GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL
                          );

        if(m_Handle == INVALID_HANDLE_VALUE)
        {
            error("create");
        }
    }


    void file::size()
    {
        LARGE_INTEGER size;
        BOOL size_result = GetFileSizeEx(m_Handle, &size);

        if(!size_result)
        {
            error("size");
        }

        m_Size = size.u.LowPart;
    }

    void file::read()
    {
        size();

        m_Buffer = new char[m_Size];

        DWORD bytes_read;
        BOOL read_result = ReadFile(m_Handle,
                                    m_Buffer,
                                    m_Size,
                                    &bytes_read,
                                    NULL
                                );

        if(!read_result)
        {
            error("read");
        }
    }


    void file::write(const void* data)
    {
        DWORD bytes_written;
        BOOL write_result = WriteFile(m_Handle,
                                      m_Buffer,
                                      m_Size,
                                      &bytes_written,
                                      NULL
                                  );

        if(!write_result)
        {
            error("write");
        }
    }


    void file::close()
    {
        BOOL close_result = CloseHandle(m_Handle);

        if(!close_result)
        {
            error("write");
        }
    }
}
