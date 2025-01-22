#include <iostream>

class LinkedList {
    struct Node {
        int _data{-1}; // this could be any type of data
        Node* _next{nullptr};
    };

    Node* _start{nullptr};

public:
    class iterator {
        Node* _node{nullptr};

    public:
        explicit iterator(Node* node) : _node(node) {
        }

        bool operator!=(const iterator& rhs) { return _node != rhs._node; }

        iterator& operator++() {
            _node = _node->_next;
            return *this;
        }

        int operator*() const { return _node->_data; }
    };

    iterator begin() { return iterator(_start); }
    iterator end() { return iterator(nullptr); }

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

    ///
    /// @param data the data to be inserted
    /// @param before_value the value of the node to insert before
    void insert(int data, int before_value) {
        auto new_node = new Node({data});

        auto node = _start;
        auto prev = static_cast<Node*>(nullptr);

        // find the node to insert before
        while (node != nullptr) {
            // look for value to insert before
            if (node->_data == before_value) {
                break;
            }
            prev = node;
            node = node->_next;
        }

        // did we find our node?
        if (node != nullptr) {
            // are we inserting at the beginning?
            if (prev == nullptr) {
                // yes! we are at the start
                new_node->_next = _start;
                _start = new_node;
            }
            else {
                // no, just in the middle
                new_node->_next = prev->_next;
                prev->_next = new_node;
            }
        }
    }

    void remove(const int data) {
        auto prev = static_cast<Node*>(nullptr);
        auto node = _start;

        // find the node to delete
        while (node != nullptr) {
            // look for the node with a particular value
            if (node->_data == data) {
                // we found the node!
                break;
            }
            prev = node;
            node = node->_next;
        }

        // did we find the node to delete?
        if (node != nullptr) {
            // yes! we did find the node!

            // is this node the first node?
            if (prev == nullptr) {
                // yes! it is the first node!
                _start = node->_next;
            }
            else {
                // no, it isn't.
                prev->_next = node->_next;
            }

            delete node;
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

    std::cout << "Test 2: delete a node at the end" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // delete the node that contains the value 5
    list.remove(5);

    std::cout << list << std::endl;

    std::cout << "Test 3: delete a node in the middle" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    // delete the node that contains the value 3
    list.remove(3);

    std::cout << list << std::endl;

    std::cout << "Test 4: delete a node at the start" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // delete the node that contains the value 1
    list.remove(1);

    std::cout << list << std::endl;

    std::cout << "Test 5: insert a node in the middle" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    // insert the value 3 before the node that contains the value 4
    list.insert(3, 4);

    std::cout << list << std::endl;

    std::cout << "Test 6: insert a node at the start" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    // insert the value 1 before the node that contains the value 2
    list.insert(1, 2);

    std::cout << list << std::endl;

    std::cout << "Test 7: using old-style iteration" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    for (auto i = list.begin(); i != list.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    std::cout << "Test 8: using ranged for loop" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    for (auto n : list) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::cout << "Test 9: using old-style iteration" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    for (auto i = list.begin() + 2; i != list.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    return 0;
}
