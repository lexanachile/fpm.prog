#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "russian");
	int n;
	cout << "������� ����� �������" << endl << "p.s. ����� �� 1 �� 3 " << endl << "n := ";
	cin >> n;
	switch (n) {
	case 1: {
		//13.1.	����� �� ������� �������� A x B x C ��������� � ������� �������� X x Y x Z?
		// ��� �������� ������ ����� ������� ������ ���� ����������� �����-�� ����� �������.
		_asm {

		}
		break;
	}
	case 2: {
		//13.5.	����������, �������� �� ��� (������������� ����� �����) ����������.
		// ���������� ��������� ���, ��������� �� 4, �� ����������� ��� �����,
		// ������� ������� �� 100 � �� ������� �� 400
		// (��������, 300, 1300 � 1900 ���� �� �������� �����������, � 1200 � 2000 � ��������
		_asm {

		}
		break;
	}
	case 3: {
		int n, m, x, y, k, p, r, can;
		cout << "13.4.	����������, ������ �� ����� �� ������� x �������� �� ���� m ������, "
			<< "y ���������� �� n ������ � ����� �� k ������, ���� ���� � ������� "
			<< "p ����� �� 1000 ������ � r ����� �� 500 ������." << endl << "������� ��������: " << endl << "x = ";
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
			mov eax, p ; ����� ��������� ���������� ��������� ����� � ������� � ��� ��������(���� long long)
			mov esi, 2
			mul esi
			add eax, r
			mov esi, 500
			mul esi
			mov ebx, eax
			mov ecx, edx

			mov edx, 0 ; ������� �����
			mov eax, y
			mul n
			add eax, k

			mov esi, eax ; ����������
			mov edi, edx

			mov edx, 0 ; ����������� � ckladivaem
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
		if (can) cout << "�����" << endl;
		else cout << "������" << endl;
		break;
	}
	}
	return 0;
}