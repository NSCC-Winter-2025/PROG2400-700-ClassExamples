#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include <iostream>

class BST {
    struct Node;
    using NodePtr = Node*;

    struct Node {
        int _data {-1};
        NodePtr _left {nullptr};
        NodePtr _right {nullptr};
    };

    NodePtr _root {nullptr};

public:
    void insert(int num);

    void insert(int num, NodePtr& node);

    // not a recursive function
    void remove(int num);

    void print_tree(std::ostream& output, NodePtr& node, int indent);

    void save_array(std::span<int> arr);

    void save_array(std::span<int> arr, NodePtr& node);

    friend std::ostream& operator<<(std::ostream& os, BST& tree);
};

std::ostream& operator<<(std::ostream& os, BST& tree);

#endif
