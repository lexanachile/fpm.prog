#include <iostream>
#include "polska.h"
#include <string>
#include <vector>
using namespace std;

int main(){
try{
    vector<pair<string, int>> v = {{"+", 1},{"-", 1}, {"*", 2}, {"/", 2},};
     Calcululator<double> calc(v);
    string str;
    cout << calc.calculate("2^3/2/2*(1+3(2^0))");
}
catch(string err){
    cout << err << '\n';
}

return 0;
}