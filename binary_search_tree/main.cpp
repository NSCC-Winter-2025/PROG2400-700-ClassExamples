#include <iomanip>
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
    void insert(int num) {
        insert(num, _root);
    }

    void insert(int num, NodePtr& node) {
        if (node == nullptr) {
            // we are the bottom of the tree
            // insert nodes here
            node = new Node({num});
        } else if (num < node->_data) {
            // we need to look to the left
            insert(num, node->_left);
        } else if (num > node->_data) {
            // we need to look to the right
            insert(num, node->_right);
        } else {
            std::cout << "Node value " << num << " already exists\n";
        }
    }

    // not a recursive function
    void remove(const int num) {
        auto node = _root;
        Node* parent = nullptr;

        // look for the node to delete
        while (node != nullptr) {
            if (num < node->_data) {
                // take the left path to find the node
                parent = node;
                node = node->_left;
            } else if (num > node->_data) {
                // take the right path to find the node
                parent = node;
                node = node->_right;
            } else {
                // found it! so stop looking.
                break;
            }
        }

        // exit if the node was not found
        if (node == nullptr) return;

        // do I have two children that would be affected?
        if (node->_left != nullptr && node->_right != nullptr) {
            // yes! so find a "successor" to replace me
            auto successor = node->_left;

            // go as far right now as possible
            parent = node;
            while (successor->_right != nullptr) {
                parent = successor;
                successor = successor->_right;
            }

            // move successor data into node
            node->_data = successor->_data;

            // the successor is now the node to delete
            node = successor;
        }

        // do I have a child that needs a new parent?

        // assume I have a left child
        auto subtree = node->_left;

        // if no left child, assume a right child
        if (subtree == nullptr) {
            subtree = node->_right;
        }

        // am I the root node?
        if (parent == nullptr) {
            // yes!
            _root = subtree;
        } else if (node == parent->_left) {
            // I'm on the left side of the parent
            // disconnect from the left side
            parent->_left = subtree;
        } else if (node == parent->_right) {
            // I'm on the right side of the parent
            // disconnect from the right side
            parent->_right = subtree;
        }

        // the node is now disconnected from the tree
        // so I can delete it now
        delete node;
    }

    void print_tree(std::ostream& output, NodePtr& node, int indent) {
        if (node != nullptr) {
            print_tree(output, node->_right, indent + 8);
            output << std::setw(indent) << node->_data << std::endl;
            print_tree(output, node->_left, indent + 8);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, BST& tree);
};

std::ostream& operator<<(std::ostream& os, BST& tree) {
    tree.print_tree(os, tree._root, 0);
    return os;
}

int main() {
    BST bst;

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    // test 1
    std::cout << "Test 1: inserting nodes into the tree" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    std::cout << bst << std::endl;

    // test 2
    std::cout << "Test 2: delete a node with no children" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    bst.remove(2);

    std::cout << bst << std::endl;

    // test 3
    std::cout << "Test 3: delete a node with one child" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    bst.remove(3);

    std::cout << bst << std::endl;

    // test 4
    std::cout << "Test 4: delete a node with two children" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    bst.remove(7);

    std::cout << bst << std::endl;

    // test 5
    std::cout << "Test 4: delete the root node" << std::endl;
    std::cout << "----------------------------" << std::endl;

    bst.remove(5);
    std::cout << bst << std::endl;

    bst.remove(4);
    std::cout << bst << std::endl;

    bst.remove(6);
    std::cout << bst << std::endl;

    bst.remove(8);
    std::cout << bst << std::endl;

    return 0;
}
