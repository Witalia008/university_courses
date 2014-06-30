#include <conio.h>
#include <stdio.h>
#include <bios.h>

int main()
{
    char data[512] = "";
    int M, N, K;
    printf("Input side number: ");
    scanf("%d", &K);
    printf("Input sector number: ");
    scanf("%d", &N);
    printf("Input track number: ");
    scanf("%d", &M);
    int res = biosdisk(2, 0, K, M, N, 1, data);
    if (res != 0)
    {
        printf("Error: %x\n", res);
        getch();
        return 0;
    }
    int i;
    for (i = 0; i < 512; i++)
    {
        printf("%c ", data[i]);
    }
    getch();
    return 0;
}