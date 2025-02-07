#include <iostream>
#include <memory>
#include <optional>

struct Data {
    int _num {0};
    float _val {0.0};
    ~Data() { std::cout << "Destroyed: " << _num << ", " << _val << std::endl; }
};

std::ostream& operator<<(std::ostream& os, const Data& data) {
    os << "num: " << data._num << ", val: " << data._val;
    return os;
}

class Stack {
    struct Node {
        Data _data;
        std::unique_ptr<Node> _next {nullptr};
    };

    std::unique_ptr<Node> _top {nullptr};

public:
    void push(const Data& data) {
        auto node = std::make_unique<Node>(data);
        node->_next = std::move(_top);
        _top = std::move(node);
    }

    std::optional<Data> top() {
        if (_top == nullptr) return std::nullopt;
        return std::make_optional(_top->_data);
    }

    void pop() {
        if (_top == nullptr) return;
        _top = std::move(_top->_next);
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& stack);
};

std::ostream& operator<<(std::ostream& os, const Stack& stack) {
    auto node = stack._top.get();
    while (node != nullptr) {
        os << node->_data << std::endl;
        node = node->_next.get();
    }
    return os;
}

int main() {
    Stack stack;

    // test 1 - add one item to the stack
    std::cout << "Test 1 - add an item to the stack" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    stack.push({1, 6.667});

    std::cout << stack << std::endl;

    // test 2 - add more items to the stack
    std::cout << "Test 2 - add more items to the stack" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    stack.push({2, 1.1});
    stack.push({3, 2.2});
    stack.push({4, 3.3});
    stack.push({5, 4.4});

    std::cout << stack << std::endl;

    std::cout << "Test 3 - get data off of the stack" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    using maybe_data = std::optional<Data>;

    auto valueless = [] {
        std::cout << "Error: ";
        return maybe_data({0, 0.0});
    };

    std::cout << stack.top().value_or(Data {-1, -1.0}) << std::endl;
    std::cout << stack.top().or_else(valueless).value() << std::endl;

    std::cout << "Test 4 - pop an item from the stack" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    stack.pop();
    std::cout << stack << std::endl;

    std::cout << "Test 5 - pop all items from the stack" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    while (stack.top() != std::nullopt) {
        stack.pop();
        std::cout << stack << std::endl;
    }

    return 0;
}
