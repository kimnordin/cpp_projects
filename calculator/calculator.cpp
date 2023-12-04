#include <iostream>

using namespace std;

float add(float a, float b) {
    return a + b;
}

float subtract(float a, float b) {
    return a - b; 
}

float divide(float a, float b) {
    if (b != 0) return a / b;
    else return 0;
    return a / b;
}

float multiply(float a, float b) {
    return a * b;
}

int main() {
    float num1, num2;
    char op;
    bool running = true;

    while (running) {
        cout << "Enter operation ( + , - , * , / ) or 'q' to quit: ";
        cin >> op;

        if (op == 'q') break;

        cout << "Enter two numbers: ";
        cin >> num1 >> num2;

        switch(op) {
            case '+':
                cout << "Result: " << add(num1, num2) << endl;
                break;
            case '-':
                cout << "Result: " << subtract(num1, num2) << endl;
                break;
            case '*':
                cout << "Result: " << multiply(num1, num2) << endl;
                break;
            case '/':
                if (num2 != 0)
                    cout << "Result: " << divide(num1, num2) << endl;
                else
                    cout << "Cannot divide by zero!" << endl;
                break;
            default:
                cout << "Invalid operation!" << endl;
        }
    }

    return 0;
}
