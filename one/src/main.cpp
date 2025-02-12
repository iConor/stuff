#include "context.h"
#include "file.h"
#include "macros.h"
#include "types.h"

#include <stdio.h>

#if OS_WINDOWS
#include "win32_file.cpp"
#endif

int main(int argc, char** argv)
{
    printf("\n");
    printf("COMPILER_MSVC\t%d\n", COMPILER_MSVC);
    printf("COMPILER_GCC\t%d\n", COMPILER_GCC);
    printf("COMPILER_CLANG\t%d\n", COMPILER_CLANG);

    printf("\n");
    printf("OS_WINDOWS\t%d\n", OS_WINDOWS);
    printf("OS_LINUX\t%d\n", OS_LINUX);
    printf("OS_MACOS\t%d\n", OS_MACOS);

    printf("\n");
    printf("ARCH_X86\t%d\n", ARCH_X86);
    printf("ARCH_X64\t%d\n", ARCH_X64);

#if OS_WINDOWS
    printf("\n");

    char* in_file  = "F:\\dev\\stuff\\one\\src\\main.cpp";
    char* out_file = "F:\\dev\\stuff\\one\\src\\insane.cpp";
    char* cop_file = "F:\\dev\\stuff\\one\\src\\membrain.cpp";
    char* mov_file = "F:\\dev\\stuff\\one\\src\\brain.cpp";
    char* dir_file = "F:\\dev\\stuff\\one\\src\\directory";

    str8 in_str;
    str8 out_str;
    str8 cop_str;
    str8 mov_str;
    str8 dir_str;
    str8 filedata;

    in_str.data = (u8*)in_file;
    in_str.size = sizeof(in_file);

    file_read(in_str, &filedata);

    // printf("%s", filedata.data);

    out_str.data = (u8*)out_file;
    out_str.size = sizeof(out_file);

    file_write(out_str, filedata);

    cop_str.data = (u8*)cop_file;
    cop_str.size = sizeof(cop_file);

    file_copy(out_str, cop_str);

    mov_str.data = (u8*)mov_file;
    mov_str.size = sizeof(mov_file);

    file_move(out_str, mov_str);

    file_remove(cop_str);
    file_remove(mov_str);

    dir_str.data = (u8*)dir_file;
    dir_str.size = sizeof(dir_file);

    file_dir_create(dir_str);
    file_dir_remove(dir_str);

    str8 working_dir;
    file_working_dir(&working_dir);
    printf("%s\n", working_dir.data);

    str8 temp_dir;
    file_temp_dir(&temp_dir);
    printf("%s\n", temp_dir.data);

    str8 user_dir;
    file_user_dir(&user_dir);
    printf("%s\n", user_dir.data);
#endif

    return 0;
}
