#include <conio.h>
#include <string.h>
#include <dos.h>

int main()
{
   char ch = 0;
   int x = 0;
   int y = 0;
   char c[13] = "HELLO WORLD!";
   char value;
   unsigned int segment = 0xB800;
   unsigned int offset;
   while (ch != 13)
   {
      clrscr();
      switch (ch)
      {
      case 77:
         x = (x + 1) % 80;
         break;
      case 75:
         x = (x + 79) % 80;
         break;
      case 72:
         y = (y + 24) % 25;
         break;
      case 80:
         y = (y + 1) % 25;
         break;
      }
      for (int i = 0; i < strlen(c); i++)
      {
         offset = 160 * y + (2 * (x + i)) % 160;
         value = c[i];
         pokeb(segment, offset, value);
      }
      ch = getch();
   }
   return 0;
}