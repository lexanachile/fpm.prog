#include <iostream>

void MinMax(int* M, int& min, int& max, int n) {
    /*min = max = M[0];
    for (int i = 1; i < n; i++) {
        if (M[i] > max) max = M[i];
        if (M[i] < min) min = M[i];
    }*/

    _asm {
        mov esi, M
        mov eax, [esi]
        mov [min], eax
        mov [max], eax
        mov ecx, n
        dec ecx

for1:   cmp 0, ecx
        jge fend1

        mov edx, [esi]
        cmp edx, [max]
        jle else1
        mov[max], edx

else1:  cmp edx, [min]
        jge else2
        mov[min], edx

else2:  add esi, 4         
        inc ebx            
        jmp for1

fend1:
    }
}


int main() {
	setlocale(LC_ALL, "russian");
	int min = 0, max = 0, n;
	std::cout << "Введите размерность массива: ";
	std::cin >> n;
	int* Mas = new int[n];
	std::cout << std::endl << "Заполните массив: " << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << "Элемент " << i + 1 << ": ";
		std::cin >> Mas[i];
		std::cout << std::endl;
	}
	MinMax(Mas, min, max, n);
	std::cout << "Min = " << min << ", Max = " << max << ".";
}
//10 4 5 6 7 8 9 10 99 28 2
