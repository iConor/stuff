#include "file.h"

#include <windows.h>
#include <userenv.h>

#include <stdlib.h>



u32 file_read(str8 name, str8* contents)
{
    LPCSTR file_name = (char*)name.data;

    HANDLE file_handle = CreateFileA(file_name,
                                     GENERIC_READ,
                                     0,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL);

    if(file_handle == INVALID_HANDLE_VALUE)
    {

    }

    LARGE_INTEGER file_size;
    BOOL size_result = GetFileSizeEx(file_handle, &file_size);

    if(size_result == 0)
    {

    }

    LPVOID buffer = (LPVOID)malloc(file_size.LowPart);

    DWORD bytes_read;
    BOOL read_result = ReadFile(file_handle,
                                buffer,
                                file_size.LowPart,
                                &bytes_read,
                                NULL);

    if(read_result == 0)
    {

    }

    BOOL close_result = CloseHandle(file_handle);

    if(close_result == 0)
    {

    }

    contents->data = (u8*)buffer;
    contents->size = bytes_read;

    contents->data[bytes_read] = '\0';

    return 0;
}


u32 file_write(str8 name, str8 contents)
{
    LPCSTR file_name = (char*)name.data;

    HANDLE file_handle = CreateFileA(file_name,
                                     GENERIC_WRITE,
                                     0,
                                     NULL,
                                     CREATE_ALWAYS,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL);

    if(file_handle == INVALID_HANDLE_VALUE)
    {

    }

    DWORD bytes_written;
    BOOL write_result = WriteFile(file_handle,
                                  contents.data,
                                  contents.size,
                                  &bytes_written,
                                  NULL);

    if(write_result == 0)
    {

    }

    BOOL close_result = CloseHandle(file_handle);

    if(close_result == 0)
    {

    }

    return 0;
}


u32 file_move(str8 source, str8 destination)
{
    LPCSTR old_file = (char*)source.data;
    LPCSTR new_file = (char*)destination.data;

    BOOL result = MoveFileA(old_file, new_file);

    return result;
}


u32 file_copy(str8 source, str8 destination)
{
    LPCSTR old_file = (char*)source.data;
    LPCSTR new_file = (char*)destination.data;

    BOOL bFailIfExists = TRUE;

    BOOL result = CopyFileA(old_file, new_file, bFailIfExists);

    return result;
}


u32 file_remove(str8 path)
{
    LPCSTR file = (char*)path.data;

    BOOL result = DeleteFileA(file);

    return result;
}


u32 file_dir_create(str8 path)
{
    LPCSTR file = (char*)path.data;

    BOOL result = CreateDirectoryA(file, NULL);

    return result;
}


u32 file_dir_remove(str8 path)
{
    LPCSTR file = (char*)path.data;

    BOOL result = RemoveDirectoryA(file);

    return result;
}


u32 file_working_dir(str8 *path)
{
    // This one does not add the slash at the end of the path

    DWORD nBufferLength = MAX_PATH;
    LPTSTR lpBuffer = (LPTSTR)malloc(nBufferLength * sizeof(TCHAR));
    DWORD nCharsWritten = GetCurrentDirectory(nBufferLength, lpBuffer);

    path->data = (u8*)lpBuffer;

    return nCharsWritten;
}


u32 file_user_dir(str8 *path)
{
    // Requires <userenv.h> and user32.lib
    // Seems to be returning a wide string, so it's almost time for converting

    HANDLE  hToken = GetCurrentProcessToken();
    DWORD cchSize;
    BOOL size_result = GetUserProfileDirectoryA(hToken, NULL, &cchSize);

    LPSTR lpProfileDir = (LPSTR)malloc(cchSize * sizeof(TCHAR));

    BOOL char_result = GetUserProfileDirectoryA(hToken, lpProfileDir, &cchSize);

    int whatevs = IS_TEXT_UNICODE_NOT_ASCII_MASK;
    BOOL unicode = IsTextUnicode(lpProfileDir, cchSize, &whatevs);
    printf("%d\n", unicode);

    path->data = (u8*)lpProfileDir;

    return 0;
}


u32 file_temp_dir(str8 *path)
{
    // This one does add the slash at the end of the path

    DWORD nBufferLength = MAX_PATH;
    LPSTR lpBuffer = (LPSTR)malloc(nBufferLength * sizeof(CHAR));
    DWORD nCharsWritten = GetTempPathA(nBufferLength, lpBuffer);

    path->data = (u8*)lpBuffer;

    return nCharsWritten;
}
