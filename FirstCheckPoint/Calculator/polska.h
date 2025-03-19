#pragma once
#include <string>
#include <vector>
#include "mystack.h"
using namespace std;

struct Unknown_operation {
    string operation;
};

template <typename T>
class Calcululator {
private:
    mystack<T> numbers;
    mystack<string> operations;
    vector<pair<string, int> > vec;
    string calc_line;

public:
    ~Calcululator() {
        vec.clear();
        operations.clear();
        numbers.clear();
    }

    Calcululator() {
        calc_line = "";
        vec = {{"+", 1}, {"-", 1}};
    }

    Calcululator(const Calcululator &x) {
        calc_line = x.calc_line;
        vec = x.vec;
    }

    Calcululator(vector<pair<string, int> > &v, string str = "") {
        calc_line = str;
        vec = v;
    }

    Calcululator(string str) {
        calc_line = str;
        vec = {{"+", 1}, {"-", 1}};
    }

    void set_line(string &str) {
        calc_line = str;
    }

    T calculate(string str = "") {
        try {
            if (str != "") calc_line = str;

            string unit;
            int start = 0;
            int end = calc_line.length();
            int last_prior = 0;
            int prior = 0;
            int open = 0;
            T out = 0;
            while (start != end) {
                int num = get_unit(calc_line, unit, start, end);
                switch (num) {
                    case -1: {
                        prior = get_priority(unit);
                        if (prior > last_prior) {
                            operations.push(unit);
                            last_prior = prior;
                            break;
                        }
                        else if (prior == last_prior) {
                            T a = numbers.top();
                            numbers.pop();
                            T b = numbers.top();
                            numbers.pop();
                            numbers.push(do_op(operations.top(), a, b));
                            operations.pop();
                            operations.push(unit);
                            last_prior = prior;
                        }
                        else {
                            while (numbers.size() > 1) {
                                if (operations.top() == "(") {
                                    break;
                                }
                                T a = numbers.top();
                                numbers.pop();
                                T b = numbers.top();
                                numbers.pop();
                                numbers.push(do_op(operations.top(), a, b));
                                operations.pop();
                            }
                            operations.push(unit);
                            last_prior = prior;
                        }
                        break;
                    }
                    case  0: {
                        if (unit == "(") {
                            open++;
                            last_prior = 0;
                            operations.push(unit);
                        }
                        else {
                            open--;
                            if (open < 0) throw "Wrong input( ')' more than '(' )";
                            while (operations.top() != "(") {
                                T a = numbers.top();
                                numbers.pop();
                                T b = numbers.top();
                                numbers.pop();
                                numbers.push(do_op(operations.top(), a, b));
                                operations.pop();
                            }
                            operations.pop();
                            if (!operations.isempty()) last_prior = get_priority(operations.top());
                            else last_prior = 0;
                        }
                        break;
                    }
                    case  1: {
                        numbers.push(str_convert(unit));
                        break;
                    }
                }
            }
            while (numbers.size() > 1) {
                T a = numbers.top();
                numbers.pop();
                T b = numbers.top();
                numbers.pop();
                numbers.push(do_op(operations.top(), a, b));
                operations.pop();
            }
            out = numbers.top();
            numbers.pop();
            return out;
        } catch (Unknown_operation err) {
            string out = "Unknown operation: " + err.operation;
            throw(out);
        }
    }

    int get_priority(const string &str) {
        if (str == "(") return 0;
        for (pair<string, int> p: vec) {
            if (p.first == str) return p.second;
        }
        Unknown_operation err;
        err.operation = str;
        throw err;
    }
    T do_op(const string &op, T b, T a) {
        if (op == "+"){
            return a + b;
        }
        else if (op == "-"){
            return a - b;
        }
        if (op == "*"){
            return a * b;
        }
        if (op == "/"){
            if (b == 0) throw "Divide by zero";
            return a / b;
        }
        if (op == "^") {
            T out = 1;
            if (b == 0) return out;

            else if (b < 0) {
                out = 1;
                for (int i = b; i < 0; i++) {
                    out /= a;
                }
                return out;
            }
            for (int i = 0; i < b; i++) {
                out *= a;
            }
            return out;
        }
        else {
            Unknown_operation err;
            err.operation = op;
            throw err;
        }
    }

    int get_unit(const string &str, string &unit, int &begin, int &end) {
        unit = "";
        bool is_num = false;
        if (str[begin] == '(' || str[begin] == ')') {
            if (str[begin - 1] >= '0' && str[begin - 1] <= '9' && str[begin] == '(') operations.push("*");
            unit = str[begin];
            begin++;
            return 0;
        }

        if (str[begin - 1] == '(' && str[begin] == '-') {
            numbers.push(0);
        }

        if (str[begin] >= '0' && str[begin] <= '9') is_num = true;
        for (; begin < end; begin++) {
            if (str[begin] == '(' || str[begin] == ')') {
                if (is_num) return 1;
                else return -1;
            }
            if ((str[begin] >= '0' && str[begin] <= '9' || str[begin] == ',') == is_num) {
                unit += str[begin];
            }
            else {
                if (is_num) return 1;
                else return -1;
            }
        }
        if (is_num) return 1;
        else return -1;
    }
    T str_convert(string str) {
        return atof(str.c_str());
    }
};
