#ifndef FS_H
#define FS_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <string.h>

#include "ldisk.h"
#include "byteutil.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

class FS
{
public:
    char *create(char *file_name);
    char *destroy(char *file_name);
    int open(char *file_name);
    char *close(int oft_index);
    int read(int oft_index, unsigned char *dest, int count);
    int write(int oft_index, unsigned char *src, int count);
    char *lseek(int oft_index, int new_pos);
    char *directory();
    void init(const char *file_name);
    void save(const char *file_name);

private:
    static const int OFT_SIZE = 4;
    static const int BLOCKS_RESERVED = 6;
    static const int BLOCKS_PER_FILE = 3;
    static const int MAX_NAME_LENGTH = 4;

    struct OFTEntry
    {
        unsigned char buffer[LDisk::BLOCK_SIZE];
        unsigned int pos;
        unsigned int index;
        unsigned int length;
    };
    struct FileEntry
    {
        char name[MAX_NAME_LENGTH];
        unsigned int index;
    };
    struct Descriptor
    {
        unsigned int length;
        unsigned int disk_map[BLOCKS_PER_FILE];
    };

    LDisk disk;
    OFTEntry OFT[OFT_SIZE];

    void clear(Descriptor *fd);
    Descriptor *get_descriptor(int index, unsigned char *block);
    void write_descriptor(int index, unsigned char *block);
    char *__lseek(int oft_index, int new_pos, bool expand);
    bool __expand(int oft_index, int new_length);
};

#endif // FS_H
