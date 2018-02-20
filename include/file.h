#ifndef __FILEH__
#define __FILEH__

/* 
 * READING AND WRITING CREEBIES DATA
 * PRETTIED FROM PSEUDO C CODE OF ASM IN CREEBIES DISASSMEBLE
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum CCreebiesFileType {
    unassign = 0,
    read = 1,
    write = 2
} CCreebiesFileType;

typedef struct CCreebiesFile {
    void *destruct_func;
    FILE *handle;
    uint32_t size;
    CCreebiesFileType type;
} CCreebiesFile;

CCreebiesFile *open_file(const char *path, CCreebiesFileType type);
int tell_file(CCreebiesFile *file);

size_t read_file(CCreebiesFile *file, void *dest, size_t esize, size_t count);
size_t write_file(CCreebiesFile *file, void *src, size_t esize, size_t count);

int seek_file(CCreebiesFile *file, int offset, int origin);

void close_file(CCreebiesFile *file);

#endif