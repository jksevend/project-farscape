#pragma once

#include "../pre_compiled_header.h"

#include "binary_search_tree.h"

namespace Tobot::DataStructures::Tree {

    /// @brief AVL Tree implementation
    /// @tparam T Type of the tree values
    template <typename T>
    class AVLTree : public BinarySearchTree<T> {
        public:
            struct Node {
                    T value;
                    Node * left;
                    Node * right;
                    int height;
            };
            AVLTree();
            AVLTree(AVLTree & tree);
            ~AVLTree();
            AVLTree(std::initializer_list<T> list);

            void insert(T value);
            void remove(T value);
            bool contains(T value);
            Node * search(T value);
            void traverseInOrder(std::function<void(T)> callback);
            void traversePreOrder(std::function<void(T)> callback);
            void traversePostOrder(std::function<void(T)> callback);
            void print();
            void clear();
            std::size_t getSize();
            friend std::ostream & operator<<(std::ostream & os, AVLTree<T> const & tree) {
                TraverseInOrder([&](T value) { os << value << ", "; });
            }

        private:
            Node * root;

            Node * insert(Node * node, T value);
            Node * remove(Node * node, T value);
            Node * search(Node * node, T value);

            Node * rotateLeft(Node * node);
            Node * rotateRight(Node * node);
            Node * rotateLeftRight(Node * node);
            Node * rotateRightLeft(Node * node);
            Node * getMaximum(Node * node);
            Node * getMinimum(Node * node);

            int getHeight(Node * node);
            int getBalance(Node * node);

            Node * createNode(T value);
            void deleteNode(Node * node);
            void traverseInOrder(Node * node, std::function<void(T)> callback);
            void traversePreOrder(Node * node, std::function<void(T)> callback);
            void traversePostOrder(Node * node, std::function<void(T)> callback);
            void print(Node * node, int level);
    };

    /// @brief AVLTree constructor
    /// @tparam T The type of the value stored in the tree
    template <typename T>
    AVLTree<T>::AVLTree() {
        root = nullptr;
    }

    /// @brief AVLTree copy constructor
    /// @tparam T The type of the value stored in the tree
    /// @param tree The tree to copy
    template <typename T>
    AVLTree<T>::AVLTree(AVLTree & tree) {
        root = nullptr;
        tree.traverseInOrder([&](T value) { this->insert(value); });
    }

    /// @brief AVLTree constructor
    /// @tparam T The type of the value stored in the tree
    /// @param list The list of values to insert in the tree
    template <typename T>
    AVLTree<T>::AVLTree(std::initializer_list<T> list) {
        root = nullptr;
        for (T value : list) {
            insert(value);
        }
    }

    /// @brief AVLTree destructor
    /// @tparam T The type of the value stored in the tree
    template <typename T>
    AVLTree<T>::~AVLTree() {
    }

    /// @brief Insert a value in the tree
    /// @tparam T The type of the value stored in the tree
    /// @param value The value to insert in the tree
    template <typename T>
    void AVLTree<T>::insert(T value) {
        root = insert(root, value);
    }

    /// @brief Delete a value from the tree
    /// @tparam T The type of the value stored in the tree
    /// @param value The value to delete from the tree
    template <typename T>
    void AVLTree<T>::remove(T value) {
        root = remove(root, value);
    }

    /// @brief Check if the tree contains a value
    /// @tparam T The type of the value stored in the tree
    /// @param value The value to check if it is in the tree
    /// @return True if the tree contains the value, false otherwise
    template <typename T>
    bool AVLTree<T>::contains(T value) {
        return search(value) != nullptr;
    }

    /// @brief Search for a value in the tree
    /// @tparam T The type of the value stored in the tree
    /// @param value The value to search for in the tree
    /// @return A pointer to the node containing the value, nullptr if the value is not in the tree
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::search(T value) {
        return search(root, value);
    }

    /// @brief Insert a value in the tree
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to insert the value in
    /// @param value The value to insert in the tree
    /// @return A pointer to the node containing the value
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::insert(Node * node, T value) {
        if (node == nullptr) {
            return createNode(value);
        }
        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        } else {
            return node;
        }
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);
        if (balance > 1 && value < node->left->value) {
            return rotateRight(node);
        }
        if (balance < -1 && value > node->right->value) {
            return rotateLeft(node);
        }
        if (balance > 1 && value > node->left->value) {
            return rotateLeftRight(node);
        }
        if (balance < -1 && value < node->right->value) {
            return rotateRightLeft(node);
        }
        return node;
    }

    /// @brief Delete a value from the tree
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to delete the value from
    /// @param value The value to delete from the tree
    /// @return A pointer to the node containing the value
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::remove(Node * node, T value) {
        if (node == nullptr) {
            return node;
        }
        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node * temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                deleteNode(temp);
            } else {
                Node * temp = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
        }
        if (node == nullptr) {
            return node;
        }
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            return rotateLeftRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            return rotateRightLeft(node);
        }
        return node;
    }

    /// @brief Search for a value in the tree
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to search the value in
    /// @param value The value to search for in the tree
    /// @return A pointer to the node containing the value, nullptr if the value is not in the tree
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::search(Node * node, T value) {
        if (node == nullptr || node->value == value) {
            return node;
        }
        if (value < node->value) {
            return search(node->left, value);
        }
        return search(node->right, value);
    }

    /// @brief Rotate the tree to the left
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to rotate the tree around
    /// @return A pointer to the new root of the tree
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::rotateLeft(Node * node) {
        Node * right = node->right;
        Node * right_left = right->left;
        right->left = node;
        node->right = right_left;
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        right->height = std::max(getHeight(right->left), getHeight(right->right)) + 1;
        return right;
    }

    /// @brief Rotate the tree to the right
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to rotate the tree around
    /// @return A pointer to the new root of the tree
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::rotateRight(Node * node) {
        Node * left = node->left;
        Node * left_right = left->right;
        left->right = node;
        node->left = left_right;
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        left->height = std::max(getHeight(left->left), getHeight(left->right)) + 1;
        return left;
    }

    /// @brief Rotate the tree to the left and then to the right
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to rotate the tree around
    /// @return A pointer to the new root of the tree
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::rotateLeftRight(Node * node) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    /// @brief Rotate the tree to the right and then to the left
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to rotate the tree around
    /// @return A pointer to the new root of the tree
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::rotateRightLeft(Node * node) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    /// @brief Gets the minimum value in the tree
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to get the minimum value from
    /// @return The minimum value in the tree
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::getMinimum(Node * node) {
        if (node->left == nullptr) {
            return node;
        }
        return getMinimum(node->left);
    }

    /// @brief Gets the maximum value in the tree
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to get the maximum value from
    /// @return The maximum value in the tree
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::getMaximum(Node * node) {
        if (node->right == nullptr) {
            return node;
        }
        return getMaximum(node->right);
    }

    /// @brief Get the height of a node
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to get the height of
    /// @return The height of the node
    template <typename T>
    int AVLTree<T>::getHeight(Node * node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    /// @brief Get the balance of a node
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to get the balance of
    /// @return The balance of the node
    template <typename T>
    int AVLTree<T>::getBalance(Node * node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    /// @brief Create a new node with the given value
    /// @tparam T The type of the value stored in the tree
    /// @param value The value to store in the node
    /// @return A pointer to the new node
    template <typename T>
    typename AVLTree<T>::Node * AVLTree<T>::createNode(T value) {
        Node * node = new Node();
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    /// @brief Delete a node from the tree
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to delete
    template <typename T>
    void AVLTree<T>::deleteNode(Node * node) {
        delete node;
    }

    /// Traverse the tree in order
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to start the traversal from
    /// @param callback The callback to call for each node
    template <typename T>
    void AVLTree<T>::traverseInOrder(Node * node, std::function<void(T)> callback) {
        if (node == nullptr) {
            return;
        }
        traverseInOrder(node->left, callback);
        callback(node->value);
        traverseInOrder(node->right, callback);
    }

    /// Traverse the tree in order
    ///  @tparam T The type of the value stored in the tree
    ///  @param callback The callback to call for each node
    template <typename T>
    void AVLTree<T>::traverseInOrder(std::function<void(T)> callback) {
        traverseInOrder(root, callback);
    }

    /// Traverse the tree in pre order
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to start the traversal from
    /// @param callback The callback to call for each node
    template <typename T>
    void AVLTree<T>::traversePreOrder(Node * node, std::function<void(T)> callback) {
        if (node == nullptr) {
            return;
        }
        callback(node->value);
        traversePreOrder(node->left, callback);
        traversePreOrder(node->right, callback);
    }

    /// Traverse the tree in pre order
    /// @tparam T The type of the value stored in the tree
    /// @param callback The callback to call for each node
    template <typename T>
    void AVLTree<T>::traversePreOrder(std::function<void(T)> callback) {
        traversePreOrder(root, callback);
    }

    /// Traverse the tree in post order
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to start the traversal from
    /// @param callback The callback to call for each node
    template <typename T>
    void AVLTree<T>::traversePostOrder(Node * node, std::function<void(T)> callback) {
        if (node == nullptr) {
            return;
        }
        traversePostOrder(node->left, callback);
        traversePostOrder(node->right, callback);
        callback(node->value);
    }

    /// Traverse the tree in post order
    /// @tparam T The type of the value stored in the tree
    /// @param callback The callback to call for each node
    template <typename T>
    void AVLTree<T>::traversePostOrder(std::function<void(T)> callback) {
        traversePostOrder(root, callback);
    }

    /// Prints the tree in a human readable format
    /// @tparam T The type of the value stored in the tree
    /// @param node The node to start the traversal from
    /// @param indent The current indentation level
    template <typename T>
    void AVLTree<T>::print(Node * node, int indent) {
        if (node == nullptr) {
            return;
        }
        print(node->right, indent + 1);
        for (int i = 0; i < indent; i++) {
            std::cout << "    ";
        }
        std::cout << node->value << std::endl;
        print(node->left, indent + 1);
    }

    /// Prints the tree in a human readable format
    /// @tparam T The type of the value stored in the tree
    template <typename T>
    void AVLTree<T>::print() {
        print(root, 0);
    }

    /// Clears the tree
    /// @tparam T The type of the value stored in the tree
    template <typename T>
    void AVLTree<T>::clear() {
        traversePostOrder([this](T value) { deleteNode(search(value)); });
        root = nullptr;
    }

    /// @brief Get the number of nodes in the tree
    /// @tparam T The type of the value stored in the tree
    /// @return The number of nodes in the tree
    template <typename T>
    std::size_t AVLTree<T>::getSize() {
        std::size_t size = 0;
        traverseInOrder([&size](T value) { size++; });
        return size;
    }

} // namespace Tobot::DataStructures::Tree