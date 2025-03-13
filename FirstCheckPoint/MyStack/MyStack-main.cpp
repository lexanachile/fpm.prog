#include <iostream>
#include "mystack.h"

int main() {
    mystack<int> A;
    A.push(10);
    cout << A.top() << endl;
    cout << A.pop() << endl;
    return 0;
}