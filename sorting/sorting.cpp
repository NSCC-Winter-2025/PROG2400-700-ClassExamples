#include "sorting.h"
#include "binary_search_tree.h"

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

void shell_sort(std::span<int> arr) {
    // create gaps, starting with half the array size
    for (auto gap = arr.size() / 2; gap > 0; gap /= 2) {
        // select the starting element to sort with
        for (auto start = 0; start < gap; start++) {
            // apply the insertion sort on sub-array
            for (auto i = start + gap; i < arr.size(); i += gap) {
                // pull out the card to examine
                auto temp = arr[i];

                // shuffle any elements greater than the number to the right
                // to make room for the insertion
                auto j = i;
                for (; j >= gap && temp < arr[j - gap]; j -= gap) {
                    arr[j] = arr[j - gap];
                }

                // perform the insertion
                arr[j] = temp;
            }
        }
    }
}

auto split(std::span<int> arr) {
    // choose the pivot point
    auto pivot = arr[0];

    // start searching for numbers less than and greater than the pivot
    auto left = 0;
    auto right = arr.size() - 1;

    while (left < right) {
        // search for element less than the pivot
        while (right > 0 && pivot < arr[right]) right--;

        // search for element greater than the pivot
        while (left < right && pivot >= arr[left]) left++;

        // if two were found out of place, swap them
        if (left < right && arr[left] != arr[right]) {
            std::swap(arr[left], arr[right]);
        }
    }

    // now move the pivot point to its location
    arr[0] = arr[right];
    arr[right] = pivot;

    return right;
}

void quick_sort(std::span<int> arr) {
    // the array is sorted when it only has zero or one element
    if (arr.size() <= 1) return;

    // split the array into two sublists (left and right)
    auto pivot = split(arr);

    // sort the left side
    quick_sort(arr.subspan(0, pivot));

    // sort the right side
    quick_sort(arr.subspan(pivot + 1, arr.size() - pivot - 1));
}

void bst_sort(std::span<int> arr) {
    BST bst;

    for (const auto num : arr) {
        bst.insert(num);
    }

    bst.save_array(arr);
}