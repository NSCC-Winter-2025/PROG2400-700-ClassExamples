#include <iostream>

class LinkedList {
    struct Node {
        int _data{-1}; // this could be any type of data
        Node* _next{nullptr};
    };

    Node* _start{nullptr};

public:
    void add(int data) {
        auto node = new Node({data});

        // is this the first node?
        if (_start == nullptr) {
            // yes!
            _start = node;
        }
        else {
            // no.
            auto prev = (Node*)nullptr;
            auto curr = _start;

            // loop until the end of the chain is found
            while (curr != nullptr) {
                prev = curr;
                curr = curr->_next;
            }

            // did I find the end of the chain?
            if (prev != nullptr) {
                prev->_next = node;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& output, const LinkedList& list);
};

std::ostream& operator<<(std::ostream& output, const LinkedList& list) {
    auto node = list._start;

    while (node != nullptr) {
        output << node->_data << " ";
        node = node->_next;
    }

    return output;
}

int main() {
    LinkedList list;

    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    std::cout << "Test 1: add some data" << std::endl;
    std::cout << "---------------------" << std::endl;

    std::cout << list << std::endl;

    return 0;
}
