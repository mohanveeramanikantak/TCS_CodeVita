#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

unordered_map<string, int> digit_map = {
    {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
    {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
};

// Validating if the word represents a valid digit
bool isValidDigitWord(const string &word) {
    return digit_map.find(word) != digit_map.end();
}

// Converts the string with 'c' delimiters into the actual number (e.g. "onectwocthree" => 123)
int stringToNumber(const string &s) {
    int result = 0;
    string temp;
    for (char c : s) {
        if (c == 'c') {
            if (isValidDigitWord(temp)) {
                result = result * 10 + digit_map[temp];
                temp.clear();
            } else {
                return -1; // Invalid word
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty() && isValidDigitWord(temp)) {
        result = result * 10 + digit_map[temp];
    } else if (!temp.empty()) {
        return -1; // Invalid word
    }
    return result;
}

// Apply mathematical operation on two operands based on the operator string
int applyOperation(int a, int b, const string &op) {
    if (op == "add") return a + b;
    if (op == "sub") return a - b;
    if (op == "mul") return a * b;
    if (op == "rem") return a % b;
    if (op == "pow") return (int)pow(a, b);
    return 0;
}

// Evaluates the parsed expression and returns the result
int evaluateExpression(vector<string> &tokens) {
    stack<int> operands;
    stack<string> operators;

    for (const string &token : tokens) {
        if (token == "add" || token == "sub" || token == "mul" || token == "rem" || token == "pow") {
            operators.push(token);
        } else {
            int num = stringToNumber(token);
            if (num == -1) return -1; // Invalid word
            operands.push(num);

            // Apply operations if there are at least two operands and one operator
            while (operands.size() >= 2 && !operators.empty()) {
                int b = operands.top(); operands.pop();
                int a = operands.top(); operands.pop();
                string op = operators.top(); operators.pop();
                operands.push(applyOperation(a, b, op));
            }
        }
    }

    // After processing all tokens, there should only be one operand left
    return operands.size() == 1 ? operands.top() : -2; // -2 indicates incomplete or invalid expression
}

int main() {
    string input;
    getline(cin, input);
    stringstream ss(input);
    string token;
    vector<string> tokens;

    // Tokenize the input expression
    while (ss >> token) {
        tokens.push_back(token);
    }

    // Evaluate the expression
    int result = evaluateExpression(tokens);

    // Handle different types of errors or print the result
    if (result == -1) {
        cout << "expression evaluation stopped invalid words present" << endl;
    } else if (result == -2) {
        cout << "expression is not complete or invalid" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}

