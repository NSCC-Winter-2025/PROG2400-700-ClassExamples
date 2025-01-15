#include <iostream>
#include <sstream>

void cin_version() {
    std::string command;
    int start, end;

    std::cout << "Enter a command and two numbers: ";
    std::cin >> command >> start >> end;

    std::cout << "command: " << command;
    std::cout << ", start: " << start;
    std::cout << ", end: " << end << std::endl;
}

void stringstream_version() {
    std::string command;

    std::string user_input;
    std::cout << "Enter a command and two numbers: ";
    std::getline(std::cin, user_input);

    std::stringstream ss(user_input);
    ss >> command;

    if (command.length() > 1) {
        std::cout << "This is NOT a command! This just some TEXT!" << std::endl;
        std::cout << user_input << std::endl;
    }
    else {
        std::cout << "I think you are a command!" << std::endl;

        int start = -1;
        ss >> start;
        if (ss.fail()) {
            std::cout << "I REALLY think you TEXT instead!" << std::endl;
            std::cout << user_input << std::endl;
            return;
        }

        int end = -1;
        if (!ss.eof()) {
            ss >> end;
            if (ss.fail()) {
                std::cout << "I REALLY, REALLY think you TEXT instead!" << std::endl;
                std::cout << user_input << std::endl;
                return;
            }
        }

        std::cout << "command: " << command;
        std::cout << ", start: " << start;
        std::cout << ", end: " << end << std::endl;
    }
}

int main() {
    stringstream_version();

    return 0;
}
