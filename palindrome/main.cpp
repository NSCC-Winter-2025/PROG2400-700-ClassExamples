#include <iostream>
#include <cstring>

bool is_palindrome(const char* input, const size_t length) {
    for (auto i = 0; i < length / 2; i++) {
        if (input[i] != input[length - i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_palindrome_recursive(const char* input, const size_t length) {
    if (length <= 1) return false;
    if (input[0] == input[length - 1]) {
        return is_palindrome(&input[1], length - 2);
    }
    return false;
}

bool is_palindrome2(std::string_view input) {
    while (input.size() > 1) {
        if (input[0] != input[input.length() - 1]) { return false; }
        input = std::string_view(input.data() + 1, input.length() - 2);
    }
    return true;
}

// tail recursion (recursion done last)
bool is_palindrome_recursive2(std::string_view input) {
    if (input.length() <= 1) return true;

    if (*input.begin() == *input.rbegin()) {
        return is_palindrome_recursive2({input.data() + 1, input.length() - 2});
    }
    return false;
}

// head recursion (recursion done first)
bool is_palindrome_recursive3(std::string_view input) {
    if (input.length() <= 1) return true;

    if (is_palindrome_recursive3({input.data() + 1, input.length() - 2})) {
        return *input.begin() == *input.rbegin();
    }
    return false;
}

bool is_palindrome3(std::string_view input) {
    return input == std::string(input.rbegin(), input.rend());
}

int main() {
    constexpr auto BUFFER_SIZE = 80uz;
    char buffer[BUFFER_SIZE];

    std::cout << "Enter a word: ";
    std::cin.getline(buffer, BUFFER_SIZE);

    std::cout << "c string version" << std::endl;
    if (is_palindrome(buffer, strnlen(buffer, BUFFER_SIZE))) {
        std::cout << buffer << " is a palindrome" << std::endl;
    } else {
        std::cout << buffer << " is NOT a palindrome" << std::endl;
    }

    std::cout << "c string version (recursive)" << std::endl;
    if (is_palindrome_recursive(buffer, strnlen(buffer, BUFFER_SIZE))) {
        std::cout << buffer << " is a palindrome" << std::endl;
    } else {
        std::cout << buffer << " is NOT a palindrome" << std::endl;
    }

    std::cout << "std string version" << std::endl;
    if (is_palindrome2(buffer)) {
        std::cout << buffer << " is a palindrome" << std::endl;
    } else {
        std::cout << buffer << " is NOT a palindrome" << std::endl;
    }

    std::cout << "std string version (recursive) - tail version" << std::endl;
    if (is_palindrome_recursive2(buffer)) {
        std::cout << buffer << " is a palindrome" << std::endl;
    } else {
        std::cout << buffer << " is NOT a palindrome" << std::endl;
    }

    std::cout << "std string version (recursive) - head version" << std::endl;
    if (is_palindrome_recursive3(buffer)) {
        std::cout << buffer << " is a palindrome" << std::endl;
    } else {
        std::cout << buffer << " is NOT a palindrome" << std::endl;
    }

    std::cout << "reversed string version" << std::endl;
    if (is_palindrome3(buffer)) {
        std::cout << buffer << " is a palindrome" << std::endl;
    } else {
        std::cout << buffer << " is NOT a palindrome" << std::endl;
    }

    return 0;
}
