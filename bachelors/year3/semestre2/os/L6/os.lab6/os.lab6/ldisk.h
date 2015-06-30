#ifndef LDISK_H
#define LDISK_H

#include <memory.h>

class LDisk
{
public:
    char *read_block(int id, unsigned char *dest);
    char *write_block(int id, unsigned char *src);

    static const int BLOCK_CNT = 64;
    static const int BLOCK_SIZE = 64;

private:
    unsigned char ldisk[BLOCK_CNT][BLOCK_SIZE];
};

#endif // LDISK_H