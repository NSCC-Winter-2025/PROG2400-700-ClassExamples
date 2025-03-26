#include <iomanip>
#include <iostream>
#include <chrono>
#include <random>

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

void bubble_sort(std::span<int> arr) {
    for (auto i = 0; i < arr.size() - 2; i++) {
        for (auto j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selection_sort(std::span<int> arr) {
    for (auto i = 0; i < arr.size() - 1; i++) {
        // find the smallest number
        auto lowest = i;
        for (auto j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[lowest]) {
                lowest = j;
            }
        }

        // put the lowest in the correct position
        if (arr[lowest] < arr[i]) {
            std::swap(arr[lowest], arr[i]);
        }
    }
}

void insertion_sort(std::span<int> arr) {
    for (auto i = 1; i < arr.size(); i++) {
        // pull out the card to examine
        auto temp = arr[i];

        // shuffle any elements greater than the number to the right
        // to make room for the insertion
        auto j = i;
        for (; j > 0 && temp < arr[j - 1]; j--) {
            arr[j] = arr[j - 1];
        }

        // perform the insertion
        arr[j] = temp;
    }
}

int main() {
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

        // std::cout << "After sorting" << std::endl;
        // dump_array({nums, len});
        if (check_sort({nums, len})) {
            std::cout << "SUCCESS!" << std::endl;
        } else {
            std::cout << "FAILURE!" << std::endl;
        }

        delete [] nums;
    }

    return 0;
}
