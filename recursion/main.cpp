#include <iostream>

// factorial : 5! = 5 * 4 * 3 * 2 * 1

int factorial(int num) {
    auto answer = num;
    while (num > 1) {
        num--;
        answer *= num;
    }
    return answer;
}

int factorial_recursive(int num) {
    // end condition (1! = 1)
    if (num == 1) { return 1; }
    // determine the answer by delegating part to the next recursive call
    return num * factorial_recursive(num - 1);
}

int main() {
    std::cout << "5! = " << factorial(5) << std::endl;
    std::cout << "5! = " << factorial_recursive(5) << std::endl;

    return 0;
}
