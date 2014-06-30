#include <iostream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <string>
#include <ctime>
using namespace std;
using namespace std::chrono;

void empty_loop(uint32_t iter_cnt)
{
    int32_t a = rand(), b = rand();
    __asm {
        mov eax, a
        mov ebx, b
        mov edx, 0
        mov ecx, iter_cnt;
    loop_beg :
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

void int16_add(uint32_t iter_cnt)
{
    int16_t a = rand(), b = rand();
    __asm {
        mov ecx, iter_cnt;
        mov ax, a
        mov bx, b
    loop_beg :
        add ax, bx
        add ax, bx
        add ax, bx
        add ax, bx
        add ax, bx
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
    }
}

void int16_sub(uint32_t iter_cnt)
{
    int16_t a = rand(), b = rand();
    __asm {
        mov ecx, iter_cnt;
        mov ax, a
        mov bx, b
    loop_beg :
        sub ax, bx
        sub ax, bx
        sub ax, bx
        sub ax, bx
        sub ax, bx
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
    }
}

void int16_mul(uint32_t iter_cnt)
{
    int16_t a = rand(), b = rand();
    __asm {
        mov ecx, iter_cnt;
        mov ax, a
        mov bx, b
    loop_beg :
        mul bx
        mul bx
        mul bx
        mul bx
        mul bx
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
    }
}

void int16_div(uint32_t iter_cnt)
{
    int16_t a = rand(), b = rand();
    __asm {
        mov ecx, iter_cnt;
        mov ax, a
        mov bx, b
        mov dx, 0
    loop_beg :
        div bx
        div bx
        div bx
        div bx
        div bx
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
    }
}

void int32_add(uint32_t iter_cnt)
{
    int32_t a = rand(), b = rand();
    __asm {
        mov ecx, iter_cnt;
        mov eax, a
        mov ebx, b
    loop_beg :
        add eax, ebx
        add eax, ebx
        add eax, ebx
        add eax, ebx
        add eax, ebx
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
    }
}

void int32_sub(uint32_t iter_cnt)
{
    int32_t a = rand(), b = rand();
    __asm {
        mov ecx, iter_cnt;
        mov eax, a
        mov ebx, b
    loop_beg :
        sub eax, ebx
        sub eax, ebx
        sub eax, ebx
        sub eax, ebx
        sub eax, ebx
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
    }
}

void int32_mul(uint32_t iter_cnt)
{
    int32_t a = rand(), b = rand();
    __asm {
        mov ecx, iter_cnt;
        mov eax, a
        mov ebx, b
    loop_beg :
        mul ebx
        mul ebx
        mul ebx
        mul ebx
        mul ebx
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
    }
}

void int32_div(uint32_t iter_cnt)
{
    int32_t a = rand(), b = rand();
    __asm {
        mov ecx, iter_cnt;
        mov eax, a
        mov ebx, b
        mov edx, 0
    loop_beg :
        div ebx
        div ebx
        div ebx
        div ebx
        div ebx
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
    }
}

void float_add(uint32_t iter_cnt)
{
    float a = rand() / (rand() + 1.0), b = rand() / (rand() + 1.0);
    __asm {
        mov ecx, iter_cnt;
        fld a
        fld b
    loop_beg :
        fadd st(0), st(1)
        fadd st(0), st(1)
        fadd st(0), st(1)
        fadd st(0), st(1)
        fadd st(0), st(1)
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

void float_sub(uint32_t iter_cnt)
{
    float a = rand() / (rand() + 1.0), b = rand() / (rand() + 1.0);
    __asm {
        mov ecx, iter_cnt;
        fld a
        fld b
    loop_beg :
        fsub st(0), st(1)
        fsub st(0), st(1)
        fsub st(0), st(1)
        fsub st(0), st(1)
        fsub st(0), st(1)
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

void float_mul(uint32_t iter_cnt)
{
    float a = rand() / (rand() + 1.0), b = rand() / (rand() + 1.0);
    __asm {
        mov ecx, iter_cnt;
        fld a
        fld b
    loop_beg :
        fmul st(0), st(1)
        fmul st(0), st(1)
        fmul st(0), st(1)
        fmul st(0), st(1)
        fmul st(0), st(1)
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

void float_div(uint32_t iter_cnt)
{
    float a = rand() / (rand() + 1.0), b = rand() / (rand() + 1.0);
    __asm {
        mov ecx, iter_cnt;
        fld a
        fld b
    loop_beg :
        fdiv st(0), st(1)
        fdiv st(0), st(1)
        fdiv st(0), st(1)
        fdiv st(0), st(1)
        fdiv st(0), st(1)
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

void double_add(uint32_t iter_cnt)
{
    double a = rand() / (rand() + 1.0), b = rand() / (rand() + 1.0);
    __asm {
        mov ecx, iter_cnt;
        fld a
        fld b
    loop_beg :
        fadd st(0), st(1)
        fadd st(0), st(1)
        fadd st(0), st(1)
        fadd st(0), st(1)
        fadd st(0), st(1)
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

void double_sub(uint32_t iter_cnt)
{
    double a = rand() / (rand() + 1.0), b = rand() / (rand() + 1.0);
    __asm {
        mov ecx, iter_cnt;
        fld a
        fld b
    loop_beg :
        fsub st(0), st(1)
        fsub st(0), st(1)
        fsub st(0), st(1)
        fsub st(0), st(1)
        fsub st(0), st(1)
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

void double_mul(uint32_t iter_cnt)
{
    double a = rand() / (rand() + 1.0), b = rand() / (rand() + 1.0);
    __asm {
        mov ecx, iter_cnt;
        fld a
        fld b
    loop_beg :
        fmul st(0), st(1)
        fmul st(0), st(1)
        fmul st(0), st(1)
        fmul st(0), st(1)
        fmul st(0), st(1)
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

void double_div(uint32_t iter_cnt)
{
    double a = rand() / (rand() + 1.0), b = rand() / (rand() + 1.0);
    __asm {
        mov ecx, iter_cnt;
        fld a
        fld b
    loop_beg :
        fdiv st(0), st(1)
        fdiv st(0), st(1)
        fdiv st(0), st(1)
        fdiv st(0), st(1)
        fdiv st(0), st(1)
        dec ecx
        cmp ecx, 0
        je loop_end
        jmp loop_beg
    loop_end :
        fstp a
        fstp b
    }
}

double run_time(void (*func)(uint32_t), uint32_t iter_cnt)
{
    //steady_clock::time_point start = high_resolution_clock::now();
    clock_t start = clock();
    func(iter_cnt);
    clock_t finish = clock();
    //steady_clock::time_point finish = high_resolution_clock::now();
    return double(finish - start) / CLOCKS_PER_SEC;
}

void print(char op, string type, double op_cnt, double max_op)
{
    int bar_width = 45;
    int full_bar_width = 48;
    double p = op_cnt / max_op;
    cout << left;
    cout << setw(5) << op << setw(7) << type << setw(15) << op_cnt << setfill('#') << setw(bar_width * p) << "";
    cout << setfill(' ') << setw(full_bar_width - int(bar_width * p)) << ' ' << int(p * 100) << '%' << endl;
}

int main()
{
    int iter_cnt = 10000000;
    double loop_time = run_time(empty_loop, iter_cnt);

    double tshort_add = 5 * iter_cnt / (run_time(int16_add, iter_cnt) - loop_time);
    double tshort_sub = 5 * iter_cnt / (run_time(int16_sub, iter_cnt) - loop_time);
    double tshort_mul = 5 * iter_cnt / (run_time(int16_mul, iter_cnt) - loop_time);
    double tshort_div = 5 * iter_cnt / (run_time(int16_div, iter_cnt) - loop_time);

    double tint_add = 5 * iter_cnt / (run_time(int32_add, iter_cnt) - loop_time);
    double tint_sub = 5 * iter_cnt / (run_time(int32_sub, iter_cnt) - loop_time);
    double tint_mul = 5 * iter_cnt / (run_time(int32_mul, iter_cnt) - loop_time);
    double tint_div = 5 * iter_cnt / (run_time(int32_div, iter_cnt) - loop_time);

    double tfloat_add = 5 * iter_cnt / (run_time(float_add, iter_cnt) - loop_time);
    double tfloat_sub = 5 * iter_cnt / (run_time(float_sub, iter_cnt) - loop_time);
    double tfloat_mul = 5 * iter_cnt / (run_time(float_mul, iter_cnt) - loop_time);
    double tmp = run_time(float_div, iter_cnt);
    double tfloat_div = 5 * iter_cnt / (run_time(float_div, iter_cnt) - loop_time);

    double tdouble_add = 5 * iter_cnt / (run_time(double_add, iter_cnt) - loop_time);
    double tdouble_sub = 5 * iter_cnt / (run_time(double_sub, iter_cnt) - loop_time);
    double tdouble_mul = 5 * iter_cnt / (run_time(double_mul, iter_cnt) - loop_time);
    double tdouble_div = 5 * iter_cnt / (run_time(double_div, iter_cnt) - loop_time);

    double max_op = -1;
    max_op = max(max_op, tshort_add);
    max_op = max(max_op, tshort_sub);
    max_op = max(max_op, tshort_mul);
    max_op = max(max_op, tshort_div);

    max_op = max(max_op, tint_add);
    max_op = max(max_op, tint_sub);
    max_op = max(max_op, tint_mul);
    max_op = max(max_op, tint_div);

    max_op = max(max_op, tfloat_add);
    max_op = max(max_op, tfloat_sub);
    max_op = max(max_op, tfloat_mul);
    max_op = max(max_op, tfloat_div);

    max_op = max(max_op, tdouble_add);
    max_op = max(max_op, tdouble_sub);
    max_op = max(max_op, tdouble_mul);
    max_op = max(max_op, tdouble_div);

    print('+', "short", tshort_add, max_op);
    print('-', "short", tshort_sub, max_op);
    print('*', "short", tshort_mul, max_op);
    print('/', "short", tshort_div, max_op);

    print('+', "int", tint_add, max_op);
    print('-', "int", tint_sub, max_op);
    print('*', "int", tint_mul, max_op);
    print('/', "int", tint_div, max_op);

    print('+', "float", tfloat_add, max_op);
    print('-', "float", tfloat_sub, max_op);
    print('*', "float", tfloat_mul, max_op);
    print('/', "float", tfloat_div, max_op);

    print('+', "double", tdouble_add, max_op);
    print('-', "double", tdouble_sub, max_op);
    print('*', "double", tdouble_mul, max_op);
    print('/', "double", tdouble_div, max_op);

    cout << endl;

    cin.get();
}