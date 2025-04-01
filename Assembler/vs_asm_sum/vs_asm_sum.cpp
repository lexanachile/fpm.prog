#include <iostream>
using namespace std;

int getSum(int* a, int n)
{
    int sum = 0;
    _asm{
        mov eax, 0
        mov ecx, n
        mov esi, a
for4:
        add eax, [esi]
        add esi, 4
        loop for4
        mov sum, eax
    }
    return sum;
}

int main() {
	int* M = new int[5] {1, 2, 3, 4, 5};
	int sum = getSum(M, 5);
    cout << sum << endl;

	return 0;
}