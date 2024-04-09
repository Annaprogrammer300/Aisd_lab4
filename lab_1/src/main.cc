#include "../include/tree.h"
#include "../include/random.h"

int main() {
    Tree tree;

    tree.insert(10);
    tree.insert(8);
    tree.insert(12);
    tree.insert(3);

    std::cout << "\n tree: ";
    tree.print(); // 3 8 10 12

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

   
    return 0;
}
