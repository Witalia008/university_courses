#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <bitset>
#include <string>
#include <locale.h>
#include <windows.h>
using namespace std;

int main()
{
    const int n = 18;
    bool tmp = 0;
    setlocale(LC_ALL, "Russian");
    bitset<n> ax, R1, R2, R3, R4, R5, R6, R7, R8;
    int a = 0, b = 0, pc = 1, ps = 0, tc = 0, m = 0;
    string command;
    ifstream inp("input.txt");
    while (!inp.eof())
    {
        char buf[100];
        inp.getline(buf, 100);
        command = (string)buf;
        tc = 1;
        if (command.find("LOAD") != -1)
        {
            printf("Command = %s\n", command.c_str());
            printf("R1=");
            for (int i = 0; i < n; i++)
                printf("%d", R1[n - i - 1] == true);
            printf("  R5=");
            for (int i = 0; i < n; i++)
                printf("%d", R5[n - i - 1] == true);
            printf("\n");
            printf("R2=");
            for (int i = 0; i < n; i++)
                printf("%d", R2[n - i - 1] == true);
            printf("  R6=");
            for (int i = 0; i < n; i++)
                printf("%d", R6[n - i - 1] == true);
            printf("\n");
            printf("R3=");
            for (int i = 0; i < n; i++)
                printf("%d", R3[n - i - 1] == true);
            printf("  R7=");
            for (int i = 0; i < n; i++)
                printf("%d", R7[n - i - 1] == true);
            printf("\n");
            printf("R4=");
            for (int i = 0; i < n; i++)
                printf("%d", R4[n - i - 1] == true);
            printf("  R8=");
            for (int i = 0; i < n; i++)
                printf("%d", R8[n - i - 1] == true);
            printf("\n");
            printf(" PC = %d\n TC = %d\n PS = %d\n\n", pc, tc, ps);
            tc++;
            for (int i = 0; i < 100; i++)
            {
                buf[i] = -52;
            }
            command.copy(buf, command.length() - command.find(" R") + 3, command.find(" R") + 4);
            a = atoi(buf);
            for (int i = 0; i < 100; i++)
            {
                buf[i] = -52;
            }
            command.copy(buf, 1, command.find(" R") + 2);
            m = atoi(buf);
            ps = a < 0;
            ax = (bitset<n>)a;
            if (a < 0)
                ax.set(n - 1);
            switch (m)
            {
            case 1:
                R1 = ax;
                break;
            case 2:
                R2 = ax;
                break;
            case 3:
                R3 = ax;
                break;
            case 4:
                R4 = ax;
                break;
            case 5:
                R5 = ax;
                break;
            case 6:
                R6 = ax;
                break;
            case 7:
                R7 = ax;
                break;
            case 8:
                R8 = ax;
                break;
            };

            printf("R1=");
            for (int i = 0; i < n; i++)
                printf("%d", R1[n - i - 1] == true);
            printf("  R5=");
            for (int i = 0; i < n; i++)
                printf("%d", R5[n - i - 1] == true);
            printf("\n");
            printf("R2=");
            for (int i = 0; i < n; i++)
                printf("%d", R2[n - i - 1] == true);
            printf("  R6=");
            for (int i = 0; i < n; i++)
                printf("%d", R6[n - i - 1] == true);
            printf("\n");
            printf("R3=");
            for (int i = 0; i < n; i++)
                printf("%d", R3[n - i - 1] == true);
            printf("  R7=");
            for (int i = 0; i < n; i++)
                printf("%d", R7[n - i - 1] == true);
            printf("\n");
            printf("R4=");
            for (int i = 0; i < n; i++)
                printf("%d", R4[n - i - 1] == true);
            printf("  R8=");
            for (int i = 0; i < n; i++)
                printf("%d", R8[n - i - 1] == true);
            printf("\n");
            printf(" PC = %d\n TC = %d\n PS = %d\n\n", pc, tc, ps);
            pc++;
            tc++;
        }
        if (command.find("XOR") != -1)
        {
            printf("Command = %s\n", command.c_str());
            printf("R1=");
            for (int i = 0; i < n; i++)
                printf("%d", R1[n - i - 1] == true);
            printf("  R5=");
            for (int i = 0; i < n; i++)
                printf("%d", R5[n - i - 1] == true);
            printf("\n");
            printf("R2=");
            for (int i = 0; i < n; i++)
                printf("%d", R2[n - i - 1] == true);
            printf("  R6=");
            for (int i = 0; i < n; i++)
                printf("%d", R6[n - i - 1] == true);
            printf("\n");
            printf("R3=");
            for (int i = 0; i < n; i++)
                printf("%d", R3[n - i - 1] == true);
            printf("  R7=");
            for (int i = 0; i < n; i++)
                printf("%d", R7[n - i - 1] == true);
            printf("\n");
            printf("R4=");
            for (int i = 0; i < n; i++)
                printf("%d", R4[n - i - 1] == true);
            printf("  R8=");
            for (int i = 0; i < n; i++)
                printf("%d", R8[n - i - 1] == true);
            printf("\n");
            printf(" PC = %d\n TC = %d\n PS = %d\n\n", pc, tc, ps);
            tc++;
            for (int i = 0; i < 100; i++)
            {
                buf[i] = -52;
            }
            command.copy(buf, 1, 5);
            m = atoi(buf);
            if (command[7] == 'R')
            {
                switch (command[8])
                {
                case '1':
                    ax = R1;
                    break;
                case '2':
                    ax = R2;
                    break;
                case '3':
                    ax = R3;
                    break;
                case '4':
                    ax = R4;
                    break;
                case '5':
                    ax = R5;
                    break;
                case '6':
                    ax = R6;
                    break;
                case '7':
                    ax = R7;
                    break;
                case '8':
                    ax = R8;
                    break;
                }
            }
            else
            {
                command.copy(buf, command.length(), 7);
                a = atoi(buf);
                ax = (bitset<n>)a;
                if (a < 0)
                    ax.set(n - 1);
            };
            switch (m)
            {
            case 1:
                R1 ^= ax;
                ps = R1.test(n - 1);
                break;
            case 2:
                R2 ^= ax;
                ps = R2.test(n - 1);
                break;
            case 3:
                R3 ^= ax;
                ps = R3.test(n - 1);
                break;
            case 4:
                R4 ^= ax;
                ps = R4.test(n - 1);
                break;
            case 5:
                R5 ^= ax;
                ps = R5.test(n - 1);
                break;
            case 6:
                R6 ^= ax;
                ps = R6.test(n - 1);
                break;
            case 7:
                R7 ^= ax;
                ps = R7.test(n - 1);
                break;
            case 8:
                R8 ^= ax;
                ps = R8.test(n - 1);
                break;
            };

            printf("R1=");
            for (int i = 0; i < n; i++)
                printf("%d", R1[n - i - 1] == true);
            printf("  R5=");
            for (int i = 0; i < n; i++)
                printf("%d", R5[n - i - 1] == true);
            printf("\n");
            printf("R2=");
            for (int i = 0; i < n; i++)
                printf("%d", R2[n - i - 1] == true);
            printf("  R6=");
            for (int i = 0; i < n; i++)
                printf("%d", R6[n - i - 1] == true);
            printf("\n");
            printf("R3=");
            for (int i = 0; i < n; i++)
                printf("%d", R3[n - i - 1] == true);
            printf("  R7=");
            for (int i = 0; i < n; i++)
                printf("%d", R7[n - i - 1] == true);
            printf("\n");
            printf("R4=");
            for (int i = 0; i < n; i++)
                printf("%d", R4[n - i - 1] == true);
            printf("  R8=");
            for (int i = 0; i < n; i++)
                printf("%d", R8[n - i - 1] == true);
            printf("\n");
            printf("\n");
            printf(" PC = %d\n TC = %d\n PS = %d\n\n", pc, tc, ps);
            pc++;
            tc++;
        }
        getch();
        Sleep(200);
        getch();
    }
    getch();
    return 0;
}
