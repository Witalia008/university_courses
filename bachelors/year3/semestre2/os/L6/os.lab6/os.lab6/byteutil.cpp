#include "byteutil.h"

int get_id(int &pos)
{
    int bit_cnt = (8 * sizeof(unsigned char));
    int i = pos / bit_cnt;
    pos = (bit_cnt - pos % bit_cnt) - 1;
    return i;
}

void set_bit(int pos, unsigned char *dst)
{
    int i = get_id(pos);
    dst[i] |= 1 << pos;
}

void unset_bit(int pos, unsigned char *dst)
{
    int i = get_id(pos);
    dst[i] &= ~(1 << pos);
}

bool get_bit(int pos, unsigned char *src)
{
    int i = get_id(pos);
    return (src[i] >> pos) & 1;
}