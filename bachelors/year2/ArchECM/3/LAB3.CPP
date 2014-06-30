#include <dos.h>
#include <stdio.h>
#include <iostream.h>

const unsigned key_queue_segm = 0x0040;
const unsigned head_off = 0x001A;
const unsigned tail_off = 0x001C;
const unsigned q_start_off = 0x001E;
const unsigned q_end_off = 0x003D;

void clear_queue()
{
    poke(key_queue_segm, head_off, q_start_off);
    poke(key_queue_segm, tail_off, q_start_off);
}

void main()
{
    puts("Dec\t Hex\t ASCII\t");
    for (int i = 0; i < 100; ++i)
    {
        delay(100);
        int head = peek(key_queue_segm, head_off);
        int tail = peek(key_queue_segm, tail_off);
        while (head != tail)
        {
            char ascii = peek(key_queue_segm, head);
            char scan = peek(key_queue_segm, ++head);
            ++head;
            int code = (ascii << 8) + scan;
            if (ascii == 0)
                printf("%u\t %x\t *\t\n", code, code);
            else
                printf("%u\t %x\t %c\t\n", code, code, ascii);
            if (head == q_end_off)
                head = q_start_off;
            clear_queue();
        }
    }
    getc(stdin);
}