#include <iostream>
#include "myqueue.h"

int main() {
        try {
                myq<int> A;
                myq<int> B;
                A.push(1);
                A.push(2);
                A.push(5);
                A.show();
                A.emplace(2, 3);
                std::cout << A.size() << std::endl;
                A.show();
                A.emplace(3, 4);
                A.show();
        }
        catch (char const *err) {
                std::cout << err << std::endl;
        }
        return 0;
}