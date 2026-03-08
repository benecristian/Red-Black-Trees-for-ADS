#include <iostream>
#include "RBTree.h"

int main() {
    RBTree<int> tree;

    std::cout << "--- Red-Black Tree Demo ---" << std::endl;

    // 1. Insertion
    std::cout << "Inserting: 55, 40, 65, 60, 75, 57" << std::endl;
    tree.insert(55);
    tree.insert(40);
    tree.insert(65);
    tree.insert(60);
    tree.insert(75);
    tree.insert(57);

    std::cout << "Inorder Traversal: ";
    tree.inorder();

    // 2. Min/Max
    try {
        std::cout << "Minimum: " << tree.getMinimum() << std::endl;
        std::cout << "Maximum: " << tree.getMaximum() << std::endl;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // 3. Search
    int searchKey = 60;
    std::cout << "Search for " << searchKey << ": " << (tree.search(searchKey) ? "Found" : "Not Found") << std::endl;
    searchKey = 99;
    std::cout << "Search for " << searchKey << ": " << (tree.search(searchKey) ? "Found" : "Not Found") << std::endl;

    // 4. Deletion
    std::cout << "\n--- Deleting 40 (Simple Case) ---" << std::endl;
    tree.remove(40);
    tree.inorder();

    std::cout << "--- Deleting 60 (Complex Case, triggers rotation/recolor) ---" << std::endl;
    tree.remove(60);
    tree.inorder();
    
    // 5. Deleting Root
    std::cout << "--- Deleting Root (55) ---" << std::endl;
    tree.remove(55);
    tree.inorder();
    std::cout << "New Root (implicit via traversal): " << tree.search(57) << std::endl; 

    return 0;
}
