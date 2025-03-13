#include <iostream>
#include "mystack.h"

int main() {
    try {
        mystack<int> A;
        mystack<int> B;
        B.push(10);
        B.push(20);
        B.emplace(2, 33);
        A.swap(B);
        cout << (A == B)  << " " << (A != B)<< endl;
        cout << A.size() << endl;
        cout << A.top() << endl;
        A.pop();
        cout << A.size() << endl;
        cout << A.top() << endl;
    } catch(char const *str) {
        cout << "Throw exception: " << str << endl;
    }
    return 0;
}