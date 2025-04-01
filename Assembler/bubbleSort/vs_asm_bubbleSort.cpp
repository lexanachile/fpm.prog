#include <iostream>
using namespace std;

void BubSort(int* M, int n) {
    /*for (int i = 0; i < n - 1; i++) {
     for (int j = 0; j < n - i - 1; j++) {
      if (M[j] > M[j + 1]) swap(M[j], M[j + 1]);
     }
    }*/
    _asm {
        mov ecx, n
        sub ecx, 1
for1:
        mov esi, M
        push ecx
for2 :
        mov eax, [esi]
        cmp eax, [esi + 4]
        jle endif1
        mov ebx, [esi + 4]
        mov[esi], ebx
        mov[esi + 4], eax
endif1 :
        add esi, 4
        loop for2
        pop ecx
        loop for1
    }
}

int main() {
    int* M = new int[5] {1, 2, 3, 4, 5};
    BubSort(M, 5);
    return 0;
}