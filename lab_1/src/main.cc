#include "../include/tree.h"
#include "../include/task.h"
#include "../include/random.h"
#include "../include/test_time.h"

int main() {
    Tree tree;

    tree.insert(10);
    tree.insert(8);
    tree.insert(12);
    tree.insert(3);

    std::cout << "\n tree: ";
    tree.print(); // 3 8 10 12
    std::cout << "\n tree: \n";
    tree.print_tree();

    std::cout << "\n contains 3: " << tree.contains(3) << std::endl; // Contains 3: 1

    tree.erase(8);
    std::cout << "\n tree erase: ";
    tree.print(); // 3 10 12

    tree.insert(5);
    tree.insert(13);
    tree.insert(1);
    std::cout << "\n tree: ";
    tree.print();


    std::cout << "\n Size of the tree: " << tree.size() << std::endl;


    Tree tree_1;
    Tree tree_2;

    tree_1.insert(5);
    tree_1.insert(16);
    tree_1.insert(20);
    tree_1.insert(14);
    tree_1.insert(25);
    tree_1.insert(18);
    tree_1.insert(32);
    tree_1.insert(10);

    tree_2.insert(8);
    tree_2.insert(14);
    tree_2.insert(30);
    tree_2.insert(32);

    Tree union_tree = union_Tree(tree_1, tree_2);

    Tree difference_Tree = symmetric_difference(tree_1, tree_2);

    std::cout << "\n tree_1: ";
    tree_1.print();

    std::cout << "\n tree_2: ";
    tree_2.print();

    std::cout << "\n union_tree: ";
    union_tree.print();

    std::cout << "\n union_tree: \n";
    union_tree.print_tree();

    std::cout << " \n symmetric_difference_Tree: ";
    if (difference_Tree.empty()) {
        std::cout << "Empty";
    }
    else {
        difference_Tree.print();
    }

    // Time test
    /*Tree Tree3 = generate_rand_Tree(100000);
    std::vector<int> vec = generate_rand_vector(100000);

    std::cout << "\n average_fiiling_time_Tree: " << average_filling_time(generate_rand_Tree, 100000) << std::endl;
    std::cout << "average_fiiling_time_vector: " << average_filling_time(generate_rand_vector, 100000) << std::endl;
    std::cout << "average_search_Tree: " << average_search_Tree(Tree3) << std::endl;
    std::cout << "average_search_vector: " << average_search_vector(vec) << std::endl;
    std::cout << "average_insert_Tree: " << average_insert_Tree(Tree3) << std::endl;
    std::cout << "average_insert_vector: " << average_insert_vector(vec, 8) << std::endl;
    std::cout << "average_erase_Tree: " << average_erase_Tree(Tree3) << std::endl;
    std::cout << "average_erase_vector: " << average_erase_vector(vec, 8) << std::endl;*/


    return 0;
}