Red-Black Tree Implementation (C++)
===================================

This package contains a templated C++ implementation of a Red-Black Tree,
a self-balancing binary search tree.

Files:
------
1. RBTree.h  : The header file containing the `RBTree` class and `Node` struct.
               This includes all logic for rotations, insertion fix-ups, and
               deletion fix-ups.
2. main.cpp  : A driver program that tests insertion, deletion, search, and 
               min/max operations.

Features:
---------
- Templated Class: Can store any data type (int, float, custom objects) that supports comparison operators (<, >, ==).
- Insert: Adds a node and automatically rebalances the tree.
- Delete: Removes a node and fixes double-black violations.
- Search: O(log n) lookup.
- Min/Max: Returns the smallest or largest element.

How to Compile and Run:
-----------------------
1. Ensure you have a C++ compiler installed (e.g., g++ or clang).
2. Save `RBTree.h` and `main.cpp` in the same directory.
3. Open your terminal/command prompt.
4. Run the following command to compile:

   g++ main.cpp -o rbtree_app

5. Run the executable:
   
   ./rbtree_app    (Linux/Mac)
   rbtree_app.exe  (Windows)

Understanding the Output:
-------------------------
The `main.cpp` will print the inorder traversal of the tree after various operations.
Since it is a sorted tree, the output of `inorder()` should always be a sorted list 
of numbers (e.g., 40 55 57 60 65 75). If the list is sorted, the BST property holds.
The "Fix" functions in the code ensure the Red-Black properties hold invisibly 
in the background.
