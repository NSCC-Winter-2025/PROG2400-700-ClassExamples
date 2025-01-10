#include <iostream>
#include <string_view>

using namespace std::literals;

int main() {

    constexpr auto END = "end"sv;

    std::string input;
    const auto get_input = [&]() {
        std::cout << "Enter a line of text: "sv;
        std::getline(std::cin, input);
        return std::string_view{input};
    };

    std::string user_input;
    while ((user_input = get_input()) != END) {
        std::cout << "You typed: "sv << user_input << std::endl;
    }
    return 0;
}
