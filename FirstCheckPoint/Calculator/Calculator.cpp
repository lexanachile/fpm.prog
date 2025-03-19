#include <iostream>
#include "polska.h"
#include <string>
#include <vector>
using namespace std;

int main(){
try{
    vector<pair<string, int>> v = {{"+", 1},{"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}};
     Calcululator<double> calc(v);
    string str;
    cout << calc.calculate("(-5)^(-1)");
}
catch(string err){
    cout << err << '\n';
}

return 0;
}