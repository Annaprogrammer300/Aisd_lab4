#ifndef LAB1_INCLUDE_TEST_H
#define LAB1_INCLUDE_TEST_H

#include <algorithm>
#include <chrono>

#include "../include/random.h"

const size_t num = 100;
const size_t num2 = 1000;

template<typename T>
double average_filling_time(T generate_func, size_t length) {
    double total_time = 0.0;

    for (int i = 0; i < num; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        generate_func(length);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        total_time += duration.count();
    }

    double average_time = total_time / num;
    return average_time;
}

double average_search_Tree(Tree& Tree) {
    double total_time = 0.0;
    for (size_t i = 0; i < num2; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        Tree.contains(lcg());
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        total_time += duration.count();
    }
    double average_time = total_time / num2;
    return average_time;
}

double average_insert_Tree(Tree& Tree) {
    double total_time = 0.0;

    for (int i = 0; i < num2; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        Tree.insert(lcg());
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        total_time += duration.count();
    }

    double average_time = total_time / num2;
    return average_time;
}

double average_erase_Tree(Tree& Tree) {
    double total_time = 0.0;

    for (int i = 0; i < num2; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        Tree.erase(lcg());
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        total_time += duration.count();
    }

    double average_time = total_time / num2;
    return average_time;
}

double average_search_vector(const std::vector<int>& vec) {
    double total_time = 0.0;
    for (size_t i = 0; i < num2; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        std::find(vec.begin(), vec.end(), lcg());
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        total_time += duration.count();
    }
    double average_time = total_time / num2;
    return average_time;
}

double average_insert_vector(std::vector<int>& vec, size_t index) {
    double total_time = 0.0;
    for (size_t i = 0; i < num2; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        vec.insert(vec.begin() + index, lcg());
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        total_time += duration.count();
    }
    double average_time = total_time / num2;
    return average_time;
}

double average_erase_vector(std::vector<int>& vec, size_t index) {
    double total_time = 0.0;
    for (size_t i = 0; i < num2; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        vec.erase(vec.begin() + index);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;
        total_time += duration.count();
    }
    double average_time = total_time / num2;
    return average_time;
}

#endif
