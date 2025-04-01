#include <iostream>
using namespace std;

void exchange(int* a, int n)
{
    _asm
    {
        mov ecx, n
        shr ecx, 1
        mov esi, a
        mov edi, a
        mov eax, n
        sub eax, 1
        imul eax, 4
        add edi, eax

for1:
        mov eax, [esi]
        mov ebx, [edi]
        mov[esi], ebx
        mov[edi], eax
        add esi, 4
        sub edi, 4
        loop for1
    }
}

int main() {
    int* M = new int[10] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; ++i) {
        cout << M[i] << " ";
    }
    cout << endl;
    exchange(M, 10);

    for (int i = 0; i < 10; ++i) {
        cout << M[i] << " ";
    }

	return 0;
}