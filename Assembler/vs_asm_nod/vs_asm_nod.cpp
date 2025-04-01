#include <iostream>

int main()
{
    int a = 2000000999, b = 3, m;
    //while (a != b)
    //{
    //    if (a >= b) a = a - b;
    //    else b = b - a;
    //}


    _asm
    {
        mov eax, a
        mov ebx, b
while1:
        cmp eax, ebx
        je endwhile1
if1:
        cmp eax, ebx
        jng else2
        sub eax, ebx
        jmp endif2
else2:
        sub ebx, eax
        jmp while1
endif2:
        jmp while1
endwhile1:
        mov m, eax


    }
    std::cout << m;
}