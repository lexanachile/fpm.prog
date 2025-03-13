#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int K, N;
    cin >> K >> N;
    int lena = 0, sasha = 0;

    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;

        bool div3 = (num % 3 == 0);
        bool div5 = (num % 5 == 0);

        if (div5 && !div3) {
            lena++;
        } else if (div3 && !div5) {
            sasha++;
        }

        if (lena >= K) {
            cout << "Lena" << endl;
            return 0;
        }
        if (sasha >= K) {
            cout << "Sasha" << endl;
            return 0;
        }
    }

    if (lena > sasha) {
        cout << "Lena" << endl;
    } else if (sasha > lena) {
        cout << "Sasha" << endl;
    } else {
        cout << "Draw" << endl;
    }

    return 0;
}
