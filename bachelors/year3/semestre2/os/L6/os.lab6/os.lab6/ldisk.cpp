#include "ldisk.h"

char *LDisk::read_block(int id, unsigned char *dest)
{
    if (dest == nullptr || id < 0 || id >= BLOCK_CNT)
    {
        return "error";
    }
    memcpy(dest, ldisk[id], sizeof(ldisk[id]));
    return nullptr;
}

char *LDisk::write_block(int id, unsigned char *src)
{
    if (src == nullptr || id < 0 || id >= BLOCK_CNT)
    {
        return "error";
    }
    memcpy(ldisk[id], src, sizeof(ldisk[id]));
    return nullptr;
}