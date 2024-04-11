#ifndef LAB1_INCLUDE_TREE_H
#define LAB1_INCLUDE_TREE_H

#include <iostream>
#include <stack>

class Tree {
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int key, Node* left = nullptr, Node* right = nullptr, int height= 1) : key(key), left(left), right(right), height(height) {}
    };

    Node* _root;
    size_t _size;

    Node* copy_recursive(Node* original_node);
    void delete_recursive(Node* node);
    void print_recursive(Node* node) const;
    Node* insert_recursive(Node* node, int key);
    bool contains_recursive(Node* node, int key) const;
    Node* erase_recursive(Node* node, int key);
    Node* find_min(Node* node);
    void print_tree_recursive(Node*, int = 0) const;

    int height(Node* node);
    int balance_factor(Node* node);
    void fix_height(Node* node);
    Node* rotate_right(Node* node);
    Node* rotate_left(Node* node);
    Node* balance(Node* node);


public:
    Tree() : _root(nullptr), _size(0) {}
    ~Tree();
    Tree(const Tree& other);
    Tree& operator=(const Tree& other);
    void insert(int key);
    bool contains(int key) const;
    void erase(int key);
    void print() const;
    size_t size() const;
    bool empty() const;
    int get_index(size_t index) const;
    void print_tree() const;

};

#endif 
