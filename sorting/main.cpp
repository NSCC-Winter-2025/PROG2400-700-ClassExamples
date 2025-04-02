#include <iomanip>
#include <iostream>
#include <chrono>
#include <queue>
#include <random>
#include "sorting.h"

using clk = std::chrono::high_resolution_clock;

void track_time(auto desc, void (*f)(std::span<int>), std::span<int> arr) {
    auto start = clk::now();
    f(arr);
    const std::chrono::duration<double> elapsed = clk::now() - start;
    std::cout << std::setw(15) << desc << ": ";
    std::cout << "time " << elapsed.count() << "s\n";
}

void dump_array(std::span<int> arr) {
    for (const auto num : arr) {
        std::cout << std::setw(3) << num;
    }
    std::cout << std::endl;
}

void fill_array(std::span<int> arr) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<size_t> dist(1, arr.size());
    std::generate(arr.begin(), arr.end(), [&]() {
        return dist(rng);
    });
}

bool check_sort(std::span<int> arr) {
    for (auto i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const std::span<int> arr) {
    if (arr.empty()) return os;
    auto i = 0;
    for (; i < arr.size() - 1; i++) {
        os << arr[i] << ",";
    }
    os << arr[i];
    return os;
}

std::ostream& operator<<(std::ostream& os, std::queue<int> queue) {
    if (queue.empty()) return os;
    while (queue.size() > 1) {
        auto num = queue.front();
        queue.pop();
        os << num << ",";
    }
    os << queue.front();
    return os;
}

void split(std::queue<int>& in, std::queue<int>& out1, std::queue<int>& out2) {
    auto num_subfiles = 0;

    // keep splitting while there are records to read
    auto prev = -1;
    while (!in.empty()) {
        // read a record
        auto curr = in.front();
        in.pop();

        // increase the subfile count when the next record is a decreasing value
        if (curr < prev) num_subfiles++;

        // write out subfiles in an odds/evens fashion
        if (num_subfiles % 2 == 0) {
            out1.push(curr);
        } else {
            out2.push(curr);
        }

        prev = curr;
    }
}

bool elements_in_sublist(std::queue<int> first, std::queue<int> second, int last) {
    return !first.empty() && (first.front() >= last);
}

bool elements_in_column(std::queue<int> first, std::queue<int> second, int last) {
    return !first.empty() && (first.front() >= last) &&
            (second.empty() || (second.front() < last) || (first.front() < second.front()));
}

bool elements_not_in_current_list(std::queue<int> first, std::queue<int> second, int last) {
    return first.empty() || !second.empty() &&
    ((first.front() < last) ||
        ((first.front() > last) && (second.front() < first.front())));
}

auto merge(std::queue<int>& out, std::queue<int>& in1, std::queue<int>& in2) {
    auto num_subfiles = 0;

    // who starts the process?
    auto& first = in2.empty() || (in1.front() < in2.front()) ? in1 : in2;
    auto& second = first == in1 ? in2 : in1;

    // keep merging while there are records left to read
    while (!in1.empty() || !in2.empty()) {
        auto last = -1;
        while (elements_in_sublist(first, second, last)) {
            // take records from file while they are in order
            do {
                last = first.front();
                first.pop();
                out.push(last);
            } while (elements_in_column(first, second, last));

            // done taking elements, now switch to other file
            if (elements_not_in_current_list(first, second, last)) {
                std::swap(first, second);
            }
        }

        // move to next sublist
        num_subfiles++;
    }

    return num_subfiles;
}

void merge_sort(std::span<int> arr) {
    // copy array to queue (think of a queue as a file)
    std::queue<int> merged;
    for (auto num : arr) {
        merged.push(num);
    }

    // sort done here
    std::queue<int> split1, split2;
    auto subfiles = 0;
    do {
        split(merged, split1, split2);

        std::cout << "Split" << std::endl;
        std::cout << split1 << std::endl;
        std::cout << split2 << std::endl;

        subfiles = merge(merged, split1, split2);

        std::cout << "Merge" << std::endl;
        std::cout << merged << std::endl;
    } while (subfiles != 1);

    // copy queue back to array
    auto i = 0;
    while (!merged.empty()) {
        arr[i++] = merged.front();
        merged.pop();
    }
}


int main() {
#if 0
    for (auto len = 10uz; len <= 10000uz; len *= 10uz) {
        std::cout << "len = " << len << std::endl;

        auto nums = new int[len];

        // std::cout << "Before sorting" << std::endl;
        // dump_array({nums, len});

        // bubble_sort({nums, len});
        fill_array({nums, len});
        track_time("bubble sort", bubble_sort, {nums, len});

        fill_array({nums, len});
        track_time("selection sort", selection_sort, {nums, len});

        fill_array({nums, len});
        track_time("insertion sort", insertion_sort, {nums, len});

        fill_array({nums, len});
        track_time("shell sort", shell_sort, {nums, len});

        fill_array({nums, len});
        track_time("quick sort", quick_sort, {nums, len});

        fill_array({nums, len});
        track_time("bst sort", bst_sort, {nums, len});

        // std::cout << "After sorting" << std::endl;
        // dump_array({nums, len});
        if (check_sort({nums, len})) {
            std::cout << "SUCCESS!" << std::endl;
        } else {
            std::cout << "FAILURE!" << std::endl;
        }

        delete [] nums;
    }
#endif

    auto array = std::to_array({3, 6, 8, 10, 5, 9, 4, 1, 2, 7});

    std::cout << "Unsorted Array" << std::endl;
    std::cout << array << std::endl;

    merge_sort(array);

    std::cout << "Sorted Array" << std::endl;
    std::cout << array << std::endl;

    return 0;
}
