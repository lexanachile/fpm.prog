#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "russian");
	int n;
	cout << "Введите номер функции" << endl << "p.s. номер от 1 до 3 " << endl << "n := ";
	cin >> n;
	switch (n) {
	case 1: {
		//13.1.	Можно ли коробку размером A x B x C упаковать в посылку размером X x Y x Z?
		// При упаковке каждая грань коробки должна быть параллельна какой-то грани посылки.
		_asm {

		}
		break;
	}
	case 2: {
		//13.5.	Определить, является ли год (положительное целое число) високосным.
		// Високосным считается год, делящийся на 4, за исключением тех годов,
		// которые делятся на 100 и не делятся на 400
		// (например, 300, 1300 и 1900 годы не являются високосными, а 1200 и 2000 – являются
		_asm {

		}
		break;
	}
	case 3: {
		int n, m, x, y, k, p, r, can;
		cout << "13.4.	Определить, хватит ли денег на покупку x тетрадей по цене m рублей, "
			<< "y карандашей по n рублей и книги за k рублей, если есть в наличии "
			<< "p купюр по 1000 рублей и r купюр по 500 рублей." << endl << "Введите значения: " << endl << "x = ";
		cin >> x;
		cout << "    m = ";
		cin >> m;
		cout << endl << "y = ";
		cin >> y;
		cout << "    n = ";
		cin >> n;
		cout << endl << "k = ";
		cin >> k;
		cout << endl << "p = ";
		cin >> p;
		cout << "    r = ";
		cin >> r;
		cout << endl;
		_asm {
			mov eax, p ; Сразу посчитаем количество имеющихся денег и занесем в два регистра(типо long long)
			mov esi, 2
			mul esi
			add eax, r
			mov esi, 500
			mul esi
			mov ebx, eax
			mov ecx, edx

			mov edx, 0 ; Считаем часть
			mov eax, y
			mul n
			add eax, k

			mov esi, eax ; запоминаем
			mov edi, edx

			mov edx, 0 ; досчитываем и ckladivaem
			mov eax, x
			mul m
			add eax, esi
			add edx, edi

			cmp edx, ecx
			jg NotEqual
			cmp eax, ebx
			jle YES
			jmp NO

NotEqual:	jg NO
Yes:		mov eax, 1
			mov can, eax
			jmp endd

NO:			mov eax, 0
			mov can, eax
endd:
		}
		if (can) cout << "Можно" << endl;
		else cout << "Нельзя" << endl;
		break;
	}
	}
	return 0;
}