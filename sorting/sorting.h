#ifndef _SORTING_H
#define _SORTING_H

#include <span>

void bubble_sort(std::span<int> arr);

void selection_sort(std::span<int> arr);

void insertion_sort(std::span<int> arr);

void shell_sort(std::span<int> arr);

auto split(std::span<int> arr);

void quick_sort(std::span<int> arr);

void bst_sort(std::span<int> arr);

#endif