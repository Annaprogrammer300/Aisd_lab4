#include "../include/tree.h"


Tree::~Tree() {
    delete_recursive(_root);
}

Tree::Tree(const Tree& other) : _root(copy_recursive(other._root)), _size(other._size) {}

Tree& Tree::operator=(const Tree& other) {
    if (this != &other) {
        delete_recursive(_root);
        _root = copy_recursive(other._root);
        _size = other._size;
    }
    return *this;
}

size_t Tree::size() const {
    return _size;
}


void Tree::insert(int key) {
    _root = insert_recursive(_root, key);
    _size++;
}

bool Tree::contains(int key) const {
    return contains_recursive(_root, key);
}

void Tree::erase(int key) {
    _root = erase_recursive(_root, key);
    _size--;
}

bool Tree::empty() const {
    return _root == nullptr;
}


void Tree::print() const {
    return print_recursive(_root);
}

void Tree::print_tree() const {
    print_tree_recursive(_root);
}

void Tree::print_tree_recursive(Node* root, int spaces) const {
    if (!root) return;

    while (root)
    {
        print_tree_recursive(root->right, spaces + 5);

        for (int i = 1; i < spaces; ++i)
            std::cout << ' ';

        std::cout << root->key << std::endl;

        root = root->left;
        spaces += 5;
    }
}

Tree::Node* Tree::copy_recursive(Node* original_node) {
    if (!original_node)
        return nullptr;

    Node* new_node = new Node(original_node->key);
    new_node->left = copy_recursive(original_node->left);
    new_node->right = copy_recursive(original_node->right);

    return new_node;
}

void Tree::delete_recursive(Node* node) {
    if (!node)
        return;

    delete_recursive(node->left);
    delete_recursive(node->right);
    delete node;
}

void Tree::print_recursive(Node* node) const {
    if (!node)
        return;

    print_recursive(node->left);
    std::cout << node->key << " ";
    print_recursive(node->right);
}

Tree::Node* Tree::insert_recursive(Node* node, int key) {
    if (!node) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert_recursive(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert_recursive(node->right, key);
    }

    return balance(node);
    //return node;

}

bool Tree::contains_recursive(Node* node, int key) const {
    if (!node)
        return false;

    if (key == node->key)
        return true;

    if (key < node->key)
        return contains_recursive(node->left, key);

    return contains_recursive(node->right, key);
}

Tree::Node* Tree::erase_recursive(Node* node, int key) {
    if (!node)
        return nullptr;

    if (key < node->key) {
        node->left = erase_recursive(node->left, key);
    }
    else if (key > node->key) {
        node->right = erase_recursive(node->right, key);
    }
    else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }

        Node* temp = find_min(node->right);
        node->key = temp->key;
        node->right = erase_recursive(node->right, temp->key);
    }

    return balance(node);
}

Tree::Node* Tree::find_min(Node* node) {
    while (node && node->left)
        node = node->left;

    return node;
}

int Tree::height(Node* node) {
    return (node) ? node->height : 0;
}

int Tree::balance_factor(Node* node) {
    return height(node->right) - height(node->left);
}

void Tree::fix_height(Node* node) {
    int left_height = height(node->left);
    int right_height = height(node->right);

    node->height = std::max(left_height, right_height) + 1;
}

Tree::Node* Tree::rotate_right(Node* node) {
    Node* new_root = node->left;

    node->left = new_root->right;
    new_root->right = node;

    fix_height(node);
    fix_height(new_root);

    return new_root;
}

Tree::Node* Tree::rotate_left(Node* node) {
    Node* new_root = node->right;

    node->right = new_root->left;
    new_root->left = node;

    fix_height(node);
    fix_height(new_root);

    return new_root;
}

Tree::Node* Tree::balance(Node* node) {
    fix_height(node);

    if (balance_factor(node) == 2) {
        if (balance_factor(node->right) < 0)
            node->right = rotate_right(node->right);

        return rotate_left(node);
    }

    if (balance_factor(node) == -2) {
        if (balance_factor(node->left) > 0)
            node->left = rotate_left(node->left);

        return rotate_right(node);
    }
    return node;
}


int Tree::get_index(size_t index) const {
    // Проверяем, что индекс находится в допустимом диапазоне
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }

    // Реализация метода для доступа к элементу по индексу
    Node* current = _root;
    size_t current_index = 0;

    std::stack<Node*> stack;

    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->left;//Переходим к самому левому узлу, добавляя все пройденные узлы в стек stack
        }

        current = stack.top();
        stack.pop();//Извлекаем узел из вершины стека

        if (current_index == index) {
            return current->key;
        }

        current_index++;
        current = current->right;//Увеличиваем текущий индекс current_index. Переходим к правому потомку текущего узла.
    }

    throw std::out_of_range("Index out of range");
}


