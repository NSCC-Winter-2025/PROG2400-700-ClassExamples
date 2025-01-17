#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& output, const std::vector<int>& v) {
    for (auto& n : v) {
        output << n << " ";
    }
    return output;
}

void operator<<(std::vector<int>& v, const std::vector<int>& in_vec) {
    for (auto& n : in_vec) {
        v.push_back(n);
    }
}

int main() {
    std::vector<int> v(5);

    for (int i = 0; i < 5; ++i) {
        v.at(i) = i + 1;
    }

    std::cout << v << std::endl;
    // shows allocated memory
    std::cout << "capacity: " << v.capacity() << std::endl;
    // shows number of elements
    std::cout << "size: " << v.size() << std::endl;

    v << std::vector({6, 7, 8, 9, 10, 11});

    std::cout << v << std::endl;
    // shows allocated memory
    std::cout << "capacity: " << v.capacity() << std::endl;
    // shows number of elements
    std::cout << "size: " << v.size() << std::endl;

    // resize the allocated memory to fit the contents
    v.shrink_to_fit();

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    v.resize(15);

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    v.reserve(25);

    std::cout << v << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    std::cout << "size: " << v.size() << std::endl;

    return 0;
}
