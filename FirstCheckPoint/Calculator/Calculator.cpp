#include <iostream>
#include <stack>
#include "polska.h"
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

int main(){
try{
    vector<pair<string, int>> v = {{"+", 1},{"-", 1}, {"*", 2}, {"/", 2}};
     Calcululator calc(v);
    string str;
    cin >> str;
    cout << calc.calculate(str);
}
catch(string err){
    cout << err << '\n';
}

return 0;
}