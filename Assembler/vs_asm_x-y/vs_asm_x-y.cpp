#include <iostream>
extern "C" long long _cdecl SubInt(int, int);
using namespace std;

int main() {
	int x, y;
	cout << "Input num x = ";
	cin >> x;
	cout << endl << "Input num y = ";
	cin >> y;
	cout << endl << "Resul: x - y = " << SubInt(x, y) << endl;
	return 0;
}