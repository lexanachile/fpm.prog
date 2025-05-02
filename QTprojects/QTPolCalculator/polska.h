#pragma once
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <stdexcept>
#include <cmath>
#include <functional>
#include <cctype>
#include <cstdlib>
using namespace std;
class PolCalcException : public std::runtime_error {
public:
    PolCalcException(const std::string& message) : std::runtime_error(message) {}
};

class PolCalc {
private:
    std::unordered_map<string, function<double(double, double)>> opFuncs{
        { "+", [](double a, double b) { return a + b; } },
        { "-", [](double a, double b) { return a - b; } },
        { "*", [](double a, double b) { return a * b; } },
        { "/", [](double a, double b) {
             if(b == 0) throw PolCalcException("Division by zero");
             return a / b;
         } },
        { "^", [](double a, double b) { return pow(a, b); } }
    };
    std::unordered_map<string, int> opPrecedence{
        { "+", 1 },
        { "-", 1 },
        { "*", 2 },
        { "/", 2 },
        { "^", 3 }
    };
    std::unordered_map<string, bool> rightAssociative{
        { "^", true }
    };
    bool isNumber(const std::string& token) const {
        char* endptr = nullptr;
        std::strtod(token.c_str(), &endptr);
        return endptr == token.c_str() + token.size();
    }
    bool isOperator(const std::string& token) const {
        return opPrecedence.count(token) > 0;
    }
    vector<std::string> tokenize(const std::string& expression) const {
        std::vector<std::string> tokens;
        std::string token;
        for (size_t i = 0; i < expression.size(); ) {
            if (isspace(expression[i])) {
                ++i;
                continue;
            }
            if (isdigit(expression[i]) || expression[i] == '.') {
                token.clear();
                bool dotEncountered = false;
                while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                    if (expression[i] == '.') {
                        if (dotEncountered)
                            break;
                        dotEncountered = true;
                    }
                    token.push_back(expression[i]);
                    ++i;
                }
                tokens.push_back(token);
            } else if (expression[i] == '(' || expression[i] == ')') {
                tokens.push_back(std::string(1, expression[i]));
                ++i;
            } else {
                token.clear();
                token.push_back(expression[i]);
                tokens.push_back(token);
                ++i;
            }
        }
        return tokens;
    }
    std::vector<std::string> toRPN(const std::vector<std::string>& tokens) {
        std::vector<std::string> output;
        std::stack<std::string> opStack;

        for (size_t i = 0; i < tokens.size(); ++i) {
            const std::string& token = tokens[i];

            if (isNumber(token)) {
                output.push_back(token);
            } else if (token == "(") {
                opStack.push(token);
            } else if (token == ")") {
                while (!opStack.empty() && opStack.top() != "(") {
                    output.push_back(opStack.top());
                    opStack.pop();
                }
                if (opStack.empty())
                    throw PolCalcException("Mismatched parentheses.");
                opStack.pop();
            } else if (isOperator(token)) {
                if ((token == "-" || token == "+") && (i == 0 || tokens[i - 1] == "(" || isOperator(tokens[i - 1]))) {
                    output.push_back("0");
                }
                while (!opStack.empty() && isOperator(opStack.top())) {
                    std::string topOp = opStack.top();
                    int topPrecedence = opPrecedence[topOp];
                    int currentPrecedence = opPrecedence[token];

                    if ((rightAssociative.count(token) && rightAssociative.at(token)) ?
                            (currentPrecedence < topPrecedence) :
                            (currentPrecedence <= topPrecedence)) {
                        output.push_back(topOp);
                        opStack.pop();
                    } else {
                        break;
                    }
                }
                opStack.push(token);
            } else {
                throw PolCalcException("Unknown token: " + token);
            }
        }
        while (!opStack.empty()) {
            if (opStack.top() == "(" || opStack.top() == ")")
                throw PolCalcException("Mismatched parentheses.");
            output.push_back(opStack.top());
            opStack.pop();
        }
        return output;
    }

    double evaluateRPN(const std::vector<std::string>& rpnTokens) {
        std::stack<double> numStack;
        for (const auto& token : rpnTokens) {
            if (isNumber(token)) {
                numStack.push(std::stod(token));
            } else if (isOperator(token)) {
                if (numStack.size() < 2)
                    throw PolCalcException("Invalid expression.");
                double b = numStack.top();
                numStack.pop();
                double a = numStack.top();
                numStack.pop();
                double result = opFuncs.at(token)(a, b);
                numStack.push(result);
            } else {
                throw PolCalcException("Unknown token in RPN: " + token);
            }
        }
        if (numStack.size() != 1)
            throw PolCalcException("Error during evaluation.");
        return numStack.top();
    }

public:
    PolCalc() {}
    double calculate(const std::string& expression) {
        vector<std::string> tokens = tokenize(expression);
        vector<std::string> rpn = toRPN(tokens);
        return evaluateRPN(rpn);
    }
};
