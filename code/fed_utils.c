#include <stdlib.h>
#include <stdio.h>
#include "fed_utils.h"
#include "fed_log.h"

struct t_FileDump FUtils_dumpFile(const char* file_path)
{
    char* file_content;
    FILE* file_ptr = NULL;
    long int file_size;

    file_ptr = fopen(file_path, "rb");

    if (!file_ptr) {
        FLog_errorMsg("File not found!");
        struct t_FileDump empty = {0, NULL};
        return empty;
    }

    fseek(file_ptr, 0, SEEK_END);
    file_size = ftell(file_ptr);
    rewind(file_ptr);

    file_content = malloc(file_size * (sizeof(char)));

    fread(file_content, sizeof(char), file_size, file_ptr);
    fclose(file_ptr);

    struct t_FileDump value = {file_size, file_content};
    return value;

}
