#ifndef BYTEUTIL_H
#define BYTEUTIL_H

void set_bit(int pos, unsigned char *dst);
void unset_bit(int pos, unsigned char *dst);
bool get_bit(int pos, unsigned char *src);


#endif // BYTEUTIL_H