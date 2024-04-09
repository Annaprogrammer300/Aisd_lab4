#ifndef LAB1_INCLUDE_RANDOM_H
#define LAB1_INCLUDE_RANDOM_H

#include <vector>
#include "tree.h"

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

Tree generate_rand_Tree(size_t size) {
    Tree Tree;
    for (size_t i = 0; i < size; ++i) {
        Tree.insert(lcg());
    }
    return Tree;
}

std::vector<int> generate_rand_vector(size_t size) {
    std::vector<int> vec;
    for (size_t i = 0; i < size; ++i) {
        vec.push_back(lcg());
    }
    return vec;
}
#endif