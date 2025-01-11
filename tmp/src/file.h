#ifndef FILE_H
#define FILE_H

#include "types.h"



u32 file_read(str8 name, str8* contents);
u32 file_write(str8 name, str8 contents);

u32 file_move(str8 source, str8 destination);
u32 file_copy(str8 source, str8 destination);

u32 file_remove(str8 path);

u32 file_dir_create(str8 path);
u32 file_dir_remove(str8 path);



u32 file_working_dir(str8 *path);
u32 file_user_dir(str8 *path);
u32 file_temp_dir(str8 *path);


#endif /* FILE_H */