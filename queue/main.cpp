#include <iostream>
#include <memory>

// sample object to hold data
struct Student {
    std::string _name {"uninitialized student"};
    std::string _id {"W000000"};

    ~Student() {
        std::cout << "Destroyed: " << _name << std::endl;
    }
};

std::ostream& operator<<(std::ostream& output, const Student& student) {
    output << "Name: " << student._name << ", ID: " << student._id;
    return output;
}

class Queue {
    struct Node {
        Student _data;
        std::unique_ptr<Node> _next {nullptr};
    };

    std::unique_ptr<Node> _front {nullptr};
    Node* _back {nullptr};
    size_t _size {0};

public:
    void push(const Student& student) {
        std::cout << "Pushed: " << student._name << std::endl;
        auto node = std::make_unique<Node>(student);

        // is this the first node?
        if (_front == nullptr) {
            // yes!
            _front = std::move(node);
            _back = _front.get();
        } else {
            // no, just add to end of queue
            _back->_next = std::move(node);
            _back = _back->_next.get();
        }
        _size++;
        std::cout << "Push ended: " << student._name << std::endl;
    }

    [[nodiscard]] Student front() const {
        return _front != nullptr ? _front->_data : Student();
    }

    void pop() {
        _front = std::move(_front->_next);
        _size--;
    }

    [[nodiscard]] size_t size() const { return _size; }
    [[nodiscard]] bool empty() const { return _size == 0; }

    friend std::ostream& operator<<(std::ostream& output, const Queue& queue);
};

std::ostream& operator<<(std::ostream& output, const Queue& queue) {
    auto node = queue._front.get();
    while (node != nullptr) {
        output << node->_data << std::endl;
        node = node->_next.get();
    }
    return output;
}

int main() {
    Queue queue;

    // test 1 - add students to a queue
    std::cout << "Test 1: add students to queue" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    queue.push({"John Smith", "W111111"});
    queue.push({"Jane Doe", "W222222"});
    queue.push({"Jill Hill", "W333333"});
    queue.push({"Jack Sprat", "W444444"});
    queue.push({"Bill Hill", "W555555"});

    std::cout << queue << std::endl;

    // test 2 - view data from student at the front of the queue
    std::cout << "Test 2: view data at front of the queue" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    std::cout << queue.front() << std::endl;

    // test 3 - remove student from the queue
    std::cout << "Test 3: remove student from queue" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    queue.pop();

    std::cout << queue << std::endl;

    // test 3a - add students to a queue that was recently popped
    std::cout << "Test 3a: add students to queue after pop" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    queue.push({"Terrence D'Arby", "W121212"});

    std::cout << queue << std::endl;

    // test 4 - remove all students from the queue
    std::cout << "Test 4: remove all students from queue" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    while (!queue.empty()) {
        queue.pop();
        std::cout << queue << std::endl;
    }

    // test 5 - add students to an empty queue
    std::cout << "Test 5: add students to empty queue" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    queue.push({"John Jingle-Hymer", "W888888"});
    queue.push({"Persephone Pickles", "W818181"});

    std::cout << queue << std::endl;

    return 0;
}
