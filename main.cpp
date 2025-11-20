/*
 * ============================================================================
 * Algorithm Library - Comprehensive Test Suite
 * ============================================================================
 *
 * OBJECTIVE: Fix ALL bugs in this repository to make every test pass.
 *
 * This test suite thoroughly validates:
 * 1. THREE sorting algorithms (Selection, Bubble, Insertion)
 * 2. Binary Search Tree structure and operations
 * 3. AVL Tree self-balancing in ALL rotation cases (LL, RR, LR, RL)
 *
 * INSTRUCTIONS FOR NEW TEAM MEMBERS:
 * ----------------------------------
 * 1. First, get the project to BUILD successfully
 *    - Fix CMake configuration errors
 *    - Fix compilation errors
 *    - Fix linking errors
 *
 * 2. Then, fix RUNTIME bugs to pass all tests
 *    - Sorting algorithms should produce ASCENDING order
 *    - BST should maintain proper structure
 *    - AVL trees must stay balanced (height difference ≤ 1)
 *
 * 3. IMPORTANT: Read error messages carefully!
 *    - CMake errors point to build configuration issues
 *    - Compiler errors indicate syntax/type problems
 *    - Linker errors mean missing implementations
 *    - Runtime crashes suggest pointer/memory issues
 *    - Wrong output means algorithm logic errors
 *
 * ============================================================================
 */

#include "bignum.hpp"
#include "node.hpp"
#include "sort.hpp"
#include "tree.hpp"
#include "util.hpp"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

// Helper function to verify if an array is sorted in ascending order
bool verifySorted(int arr[], int size, const char *algorithmName) {
  for (int i = 0; i < size - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      std::cout << "❌ FAIL: " << algorithmName
                << " did NOT produce ascending order!" << std::endl;
      std::cout << "   Found: arr[" << i << "]=" << arr[i] << " > arr[" << i + 1
                << "]=" << arr[i + 1] << std::endl;
      return false;
    }
  }
  std::cout << "✓ PASS: " << algorithmName
            << " correctly sorted in ascending order" << std::endl;
  return true;
}

// Helper function to print test separator
void printTestHeader(int testNum, const char *testName) {
  std::cout << "\n";
  std::cout << "==============================================================="
               "============="
            << std::endl;
  std::cout << "TEST " << testNum << ": " << testName << std::endl;
  std::cout << "==============================================================="
               "============="
            << std::endl;
}

int main() {
  std::cout << "\n";
  std::cout << "╔══════════════════════════════════════════════════════════════"
               "═════════╗"
            << std::endl;
  std::cout << "║         ALGORITHM LIBRARY - COMPREHENSIVE TEST SUITE         "
               "         ║"
            << std::endl;
  std::cout << "║         Fix all bugs to make every test pass!                "
               "         ║"
            << std::endl;
  std::cout << "╚══════════════════════════════════════════════════════════════"
               "═════════╝"
            << std::endl;

  int passedTests = 0;
  int totalTests = 0;

  // ==========================================================================
  // TEST 1: Selection Sort
  // ==========================================================================
  printTestHeader(1, "Selection Sort");
  std::cout << "Testing basic selection sort with unsorted array..."
            << std::endl;

  int arr1[] = {64, 34, 25, 12, 22, 11, 90};
  int size1 = sizeof(arr1) / sizeof(arr1[0]);

  std::cout << "Original: ";
  printArray(arr1, size1);
  std::cout << std::endl;

  SORT::selectSort(arr1, size1);

  std::cout << "Final:    ";
  printArray(arr1, size1);
  std::cout << "Expected: [11, 12, 22, 25, 34, 64, 90]" << std::endl;

  totalTests++;
  if (verifySorted(arr1, size1, "Selection Sort")) {
    passedTests++;
  }
  std::cout << "HINT: If failing, check array index bounds in selectSort()"
            << std::endl;

  // ==========================================================================
  // TEST 2: Bubble Sort
  // ==========================================================================
  printTestHeader(2, "Bubble Sort");
  std::cout << "Testing bubble sort algorithm..." << std::endl;

  int arr2[] = {64, 34, 25, 12, 22, 11, 90};
  int size2 = sizeof(arr2) / sizeof(arr2[0]);

  std::cout << "Original: ";
  printArray(arr2, size2);
  std::cout << std::endl;

  SORT::bubbleSort(arr2, size2);

  std::cout << "Final:    ";
  printArray(arr2, size2);
  std::cout << "Expected: [11, 12, 22, 25, 34, 64, 90]" << std::endl;

  totalTests++;
  if (verifySorted(arr2, size2, "Bubble Sort")) {
    passedTests++;
  }
  std::cout
      << "HINT: If descending order, check comparison operator in bubbleSort()"
      << std::endl;

  // ==========================================================================
  // TEST 3: Insertion Sort (with tricky test data)
  // ==========================================================================
  printTestHeader(3, "Insertion Sort");
  std::cout
      << "Testing insertion sort with MINIMUM element at the END (tricky!)..."
      << std::endl;

  // CRITICAL: The minimum element (11) is at the LAST position
  // This will expose off-by-one errors in loop bounds!
  int arr3[] = {64, 34, 25, 12, 22, 90, 11};
  int size3 = sizeof(arr3) / sizeof(arr3[0]);

  std::cout << "Original: ";
  printArray(arr3, size3);
  std::cout << "Note: Minimum element (11) is at the END - this is intentional!"
            << std::endl;
  std::cout << std::endl;

  SORT::insertionSort(arr3, size3);

  std::cout << "Final:    ";
  printArray(arr3, size3);
  std::cout << "Expected: [11, 12, 22, 25, 34, 64, 90]" << std::endl;

  totalTests++;
  if (verifySorted(arr3, size3, "Insertion Sort")) {
    passedTests++;
  }
  std::cout << "HINT: If element 11 is still at the end, check loop bounds (i "
               "< size or i "
               "< size-1?)"
            << std::endl;

  // ==========================================================================
  // TEST 4: Binary Search Tree - Basic Operations
  // ==========================================================================
  printTestHeader(4, "Binary Search Tree (BST) - Basic Operations");
  std::cout
      << "Creating BST and inserting values: 50, 30, 70, 20, 40, 60, 80..."
      << std::endl;

  TREE::BinarySearchTree<int> bst;
  bst.insert(50);
  bst.insert(30);
  bst.insert(70);
  bst.insert(20);
  bst.insert(40);
  bst.insert(60);
  bst.insert(80);

  std::cout << "\nBST Structure (should have root=50):" << std::endl;
  bst.printWithoutPrefix(bst.getRoot());

  totalTests++;
  if (bst.getRoot() != nullptr && bst.getRoot()->key == 50) {
    std::cout << "✓ PASS: BST root is correctly set to 50" << std::endl;
    passedTests++;
  } else {
    std::cout << "❌ FAIL: BST root is not correctly set!" << std::endl;
  }
  std::cout
      << "HINT: If crash/segfault, check if root pointer is updated in insert()"
      << std::endl;

  // ==========================================================================
  // TEST 5: AVL Tree - Balanced Insertion
  // ==========================================================================
  printTestHeader(5, "AVL Tree - Balanced Insertion (No Rotations)");
  std::cout
      << "Inserting: 50, 30, 70, 20, 40, 60, 80 (perfectly balanced sequence)"
      << std::endl;

  TREE::AVLTree<int> avl_balanced;
  avl_balanced.insert(50);
  avl_balanced.insert(30);
  avl_balanced.insert(70);
  avl_balanced.insert(20);
  avl_balanced.insert(40);
  avl_balanced.insert(60);
  avl_balanced.insert(80);

  std::cout << "\nAVL Structure:" << std::endl;
  avl_balanced.printWithoutPrefix(avl_balanced.getRoot());

  totalTests++;
  if (avl_balanced.getRoot() != nullptr && avl_balanced.getRoot()->key == 50) {
    std::cout << "✓ PASS: AVL tree constructed successfully" << std::endl;
    passedTests++;
  } else {
    std::cout << "❌ FAIL: AVL tree structure incorrect" << std::endl;
  }

  // ==========================================================================
  // TEST 6: AVL Tree - RR Case (Right-Right Rotation, structure + parent check)
  // ==========================================================================
  printTestHeader(6, "AVL Tree - RR Case (Right-Right Rotation, parent check)");
  std::cout << "Inserting: 10, 20, 30 (should trigger RR rotation)"
            << std::endl;
  std::cout << "Expected shape after rotation:" << std::endl;
  std::cout << "        20 (root, parent = nullptr)\n"
               "       /  \\\n"
               "     10    30\n"
               " (children's parent all point to 20)\n";

  TREE::AVLTree<int> avl_rr;
  avl_rr.insert(10);
  std::cout << "\nAfter inserting 10:" << std::endl;
  avl_rr.printWithoutPrefix(avl_rr.getRoot());

  avl_rr.insert(20);
  std::cout << "\nAfter inserting 20:" << std::endl;
  avl_rr.printWithoutPrefix(avl_rr.getRoot());

  avl_rr.insert(30);
  std::cout << "\nAfter inserting 30 (should trigger RR rotation):"
            << std::endl;
  avl_rr.printWithoutPrefix(avl_rr.getRoot());

  totalTests++;

  auto *root_rr = avl_rr.getRoot();

  bool shapeOK_rr = false;
  if (root_rr != nullptr && root_rr->key == 20 && root_rr->left != nullptr &&
      root_rr->left->key == 10 && root_rr->right != nullptr &&
      root_rr->right->key == 30) {
    shapeOK_rr = true;
  }

  bool parentOK_rr = false;
  if (root_rr != nullptr &&
      root_rr->parent == nullptr && // parent of root must be nullptr
      root_rr->left != nullptr && root_rr->left->parent == root_rr &&
      root_rr->right != nullptr && root_rr->right->parent == root_rr) {
    parentOK_rr = true;
  }

  if (shapeOK_rr && parentOK_rr) {
    std::cout << "✓ PASS: RR rotation correct: shape and parent pointers are "
                 "consistent"
              << std::endl;
    passedTests++;
  } else {
    std::cout << "❌ FAIL: RR rotation incorrect!" << std::endl;

    if (!shapeOK_rr) {
      std::cout << "  - Shape mismatch: expected root=20, left=10, right=30"
                << std::endl;
      if (root_rr == nullptr) {
        std::cout << "    · Root is nullptr" << std::endl;
      } else {
        std::cout << "    · Actual root: " << root_rr->key << std::endl;
        std::cout << "    · Left child: "
                  << (root_rr->left ? std::to_string(root_rr->left->key)
                                    : "nullptr")
                  << std::endl;
        std::cout << "    · Right child: "
                  << (root_rr->right ? std::to_string(root_rr->right->key)
                                     : "nullptr")
                  << std::endl;
      }
    }

    if (!parentOK_rr) {
      std::cout << "  - Parent pointer mismatch:" << std::endl;
      if (root_rr != nullptr) {
        std::cout << "    · root->parent should be nullptr, got "
                  << (root_rr->parent ? std::to_string(root_rr->parent->key)
                                      : std::string("nullptr"))
                  << std::endl;

        std::cout << "    · root->left->parent key: "
                  << ((root_rr->left && root_rr->left->parent)
                          ? std::to_string(root_rr->left->parent->key)
                          : std::string("nullptr"))
                  << std::endl;

        std::cout << "    · root->right->parent key: "
                  << ((root_rr->right && root_rr->right->parent)
                          ? std::to_string(root_rr->right->parent->key)
                          : std::string("nullptr"))
                  << std::endl;
      }
    }
  }

  std::cout
      << "HINT: Check RR rotation implementation and parent pointer updates\n"
         "      (especially the new subtree root's parent after rotation)."
      << std::endl;

  // ==========================================================================
  // TEST 7: AVL Tree - LL Case (Left-Left Rotation)
  // ==========================================================================
  printTestHeader(7, "AVL Tree - LL Case (Left-Left Rotation)");
  std::cout << "Inserting: 30, 20, 10 (should trigger LL rotation)"
            << std::endl;
  std::cout << "Expected shape:    20" << std::endl;
  std::cout << "                  /  \\" << std::endl;
  std::cout << "                10    30" << std::endl;

  TREE::AVLTree<int> avl_ll;
  avl_ll.insert(30);
  avl_ll.insert(20);
  avl_ll.insert(10); // should trigger LL rotation

  std::cout << "\nFinal tree after inserts:" << std::endl;
  avl_ll.printWithoutPrefix(avl_ll.getRoot());

  totalTests++;

  auto *root_ll = avl_ll.getRoot();

  bool shapeOK_ll = false;
  if (root_ll != nullptr && root_ll->key == 20 && root_ll->left != nullptr &&
      root_ll->left->key == 10 && root_ll->right != nullptr &&
      root_ll->right->key == 30) {
    shapeOK_ll = true;
  }

  bool parentOK_ll = false;
  if (root_ll != nullptr &&
      root_ll->parent == nullptr && // parent of root must be nullptr
      root_ll->left != nullptr && root_ll->left->parent == root_ll &&
      root_ll->right != nullptr && root_ll->right->parent == root_ll) {
    parentOK_ll = true;
  }

  if (shapeOK_ll && parentOK_ll) {
    std::cout << "✓ PASS: LL rotation correct: shape and parent pointers are "
                 "consistent"
              << std::endl;
    passedTests++;
  } else {
    std::cout << "❌ FAIL: LL rotation incorrect!" << std::endl;
    if (!shapeOK_ll) {
      std::cout << "  - Shape mismatch: expected root_ll=20, left=10, right=30"
                << std::endl;
      if (root_ll == nullptr) {
        std::cout << "    · Root is nullptr" << std::endl;
      } else {
        std::cout << "    · Actual root: " << root_ll->key << std::endl;
        std::cout << "    · Left child: "
                  << (root_ll->left ? std::to_string(root_ll->left->key)
                                    : "nullptr")
                  << std::endl;
        std::cout << "    · Right child: "
                  << (root_ll->right ? std::to_string(root_ll->right->key)
                                     : "nullptr")
                  << std::endl;
      }
    }
    if (!parentOK_ll) {
      std::cout << "  - Parent pointer mismatch:" << std::endl;
      if (root_ll != nullptr) {
        std::cout << "    · root->parent should be nullptr, got "
                  << (root_ll->parent ? std::to_string(root_ll->parent->key)
                                      : "nullptr")
                  << std::endl;
        std::cout << "    · root->left->parent key: "
                  << ((root_ll->left && root_ll->left->parent)
                          ? std::to_string(root_ll->left->parent->key)
                          : "nullptr")
                  << std::endl;
        std::cout << "    · root->right->parent key: "
                  << ((root_ll->right && root_ll->right->parent)
                          ? std::to_string(root_ll->right->parent->key)
                          : "nullptr")
                  << std::endl;
      }
    }
  }

  std::cout << "HINT: Check parent pointer updates in rotation functions, "
               "especially\n"
               "      the new subtree root's parent after LL rotation."
            << std::endl;

  // ==========================================================================
  // TEST 8: AVL Tree - LR Case (Left-Right Rotation, structure + parent check)
  // ==========================================================================
  printTestHeader(8, "AVL Tree - LR Case (Left-Right Rotation)");
  std::cout << "Inserting: 30, 10, 20 (should trigger LR rotation)"
            << std::endl;
  std::cout << "Expected shape after rotation:" << std::endl;
  std::cout << "        20 (root, parent = nullptr)\n"
               "       /  \\\n"
               "     10    30\n"
               " (children's parent all point to 20)\n";

  TREE::AVLTree<int> avl_lr;

  avl_lr.insert(30);
  std::cout << "\nAfter inserting 30:" << std::endl;
  avl_lr.printWithoutPrefix(avl_lr.getRoot());

  avl_lr.insert(10);
  std::cout << "\nAfter inserting 10:" << std::endl;
  avl_lr.printWithoutPrefix(avl_lr.getRoot());

  avl_lr.insert(20); // 应触发 LR 旋转
  std::cout << "\nAfter inserting 20 (should trigger LR rotation):"
            << std::endl;
  avl_lr.printWithoutPrefix(avl_lr.getRoot());

  totalTests++;

  auto *root_lr = avl_lr.getRoot();

  bool shapeOK_lr = false;
  if (root_lr != nullptr && root_lr->key == 20 && root_lr->left != nullptr &&
      root_lr->left->key == 10 && root_lr->right != nullptr &&
      root_lr->right->key == 30) {
    shapeOK_lr = true;
  }

  bool parentOK_lr = false;
  if (root_lr != nullptr && root_lr->parent == nullptr &&
      root_lr->left != nullptr && root_lr->left->parent == root_lr &&
      root_lr->right != nullptr && root_lr->right->parent == root_lr) {
    parentOK_lr = true;
  }

  if (shapeOK_lr && parentOK_lr) {
    std::cout << "✓ PASS: LR rotation correct: shape and parent pointers are "
                 "consistent"
              << std::endl;
    passedTests++;
  } else {
    std::cout << "❌ FAIL: LR rotation incorrect!" << std::endl;

    if (!shapeOK_lr) {
      std::cout << "  - Shape mismatch: expected root=20, left=10, right=30"
                << std::endl;
      if (root_lr == nullptr) {
        std::cout << "    · Root is nullptr" << std::endl;
      } else {
        std::cout << "    · Actual root: " << root_lr->key << std::endl;
        std::cout << "    · Left child: "
                  << (root_lr->left ? std::to_string(root_lr->left->key)
                                    : "nullptr")
                  << std::endl;
        std::cout << "    · Right child: "
                  << (root_lr->right ? std::to_string(root_lr->right->key)
                                     : "nullptr")
                  << std::endl;
      }
    }

    if (!parentOK_lr) {
      std::cout << "  - Parent pointer mismatch:" << std::endl;
      if (root_lr != nullptr) {
        std::cout << "    · root->parent should be nullptr, got "
                  << (root_lr->parent ? std::to_string(root_lr->parent->key)
                                      : "nullptr")
                  << std::endl;
        std::cout << "    · root->left->parent key: "
                  << ((root_lr->left && root_lr->left->parent)
                          ? std::to_string(root_lr->left->parent->key)
                          : "nullptr")
                  << std::endl;
        std::cout << "    · root->right->parent key: "
                  << ((root_lr->right && root_lr->right->parent)
                          ? std::to_string(root_lr->right->parent->key)
                          : "nullptr")
                  << std::endl;
      }
    }
  }

  std::cout << "HINT: For LR rotation, check both the intermediate left "
               "rotation on the\n"
               "      left child and the final right rotation on the root. "
               "Make sure\n"
               "      parent pointers are updated consistently in both steps."
            << std::endl;

  // ==========================================================================
  // TEST 9: AVL Tree - RL Case (Right-Left Rotation, structure + parent check)
  // ==========================================================================
  printTestHeader(9, "AVL Tree - RL Case (Right-Left Rotation, parent check)");
  std::cout << "Inserting: 10, 30, 20 (should trigger RL rotation)"
            << std::endl;
  std::cout << "Expected shape after rotation:" << std::endl;
  std::cout << "        20 (root, parent = nullptr)\n"
               "       /  \\\n"
               "     10    30\n"
               " (children's parent all point to 20)\n";

  TREE::AVLTree<int> avl_rl;
  avl_rl.insert(10);
  avl_rl.insert(30);
  avl_rl.insert(20);

  std::cout << "\nAVL Structure after RL case:" << std::endl;
  avl_rl.printWithoutPrefix(avl_rl.getRoot());

  totalTests++;

  auto *root_rl = avl_rl.getRoot();

  bool shapeOK_rl = false;
  if (root_rl != nullptr && root_rl->key == 20 && root_rl->left != nullptr &&
      root_rl->left->key == 10 && root_rl->right != nullptr &&
      root_rl->right->key == 30) {
    shapeOK_rl = true;
  }

  bool parentOK_rl = false;
  if (root_rl != nullptr &&
      root_rl->parent == nullptr && // 根节点 parent 必须为 nullptr
      root_rl->left != nullptr && root_rl->left->parent == root_rl &&
      root_rl->right != nullptr && root_rl->right->parent == root_rl) {
    parentOK_rl = true;
  }

  if (shapeOK_rl && parentOK_rl) {
    std::cout << "✓ PASS: RL rotation correct: shape and parent pointers are "
                 "consistent"
              << std::endl;
    passedTests++;
  } else {
    std::cout << "❌ FAIL: RL rotation incorrect!" << std::endl;
    if (!shapeOK_rl) {
      std::cout << "  - Shape mismatch: expected root=20, left=10, right=30"
                << std::endl;
      if (root_rl == nullptr) {
        std::cout << "    · Root is nullptr" << std::endl;
      } else {
        std::cout << "    · Actual root: " << root_rl->key << std::endl;
        std::cout << "    · Left child: "
                  << (root_rl->left ? std::to_string(root_rl->left->key)
                                    : "nullptr")
                  << std::endl;
        std::cout << "    · Right child: "
                  << (root_rl->right ? std::to_string(root_rl->right->key)
                                     : "nullptr")
                  << std::endl;
      }
    }
    if (!parentOK_rl) {
      std::cout << "  - Parent pointer mismatch:" << std::endl;
      if (root_rl != nullptr) {
        std::cout << "    · root->parent should be nullptr, got "
                  << (root_rl->parent ? std::to_string(root_rl->parent->key)
                                      : "nullptr")
                  << std::endl;
        std::cout << "    · root->left->parent key: "
                  << ((root_rl->left && root_rl->left->parent)
                          ? std::to_string(root_rl->left->parent->key)
                          : "nullptr")
                  << std::endl;
        std::cout << "    · root->right->parent key: "
                  << ((root_rl->right && root_rl->right->parent)
                          ? std::to_string(root_rl->right->parent->key)
                          : "nullptr")
                  << std::endl;
      }
    }
  }

  std::cout << "HINT: For RL case, check both the intermediate right rotation "
               "and the final\n"
               "      left rotation, especially the parent pointers of the new "
               "subtree root."
            << std::endl;

  // ==========================================================================
  // TEST 10: AVL Tree - Complex Multiple Rotations (Global Balance Check)
  // ==========================================================================
  printTestHeader(10, "AVL Tree - Complex Sequence with Multiple Rotations");
  std::cout << "Inserting: 50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35"
            << std::endl;
  std::cout << "Expected:" << std::endl;
  std::cout << "  - Tree remains height-balanced after every insertion"
            << std::endl;
  std::cout << "  - Final structure is a valid BST" << std::endl;
  std::cout
      << "  - Balance factor |bf(node)| ≤ 1 for ALL nodes, not just the root"
      << std::endl;

  TREE::AVLTree<int> avl_complex;
  int complexValues[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35};

  for (int v : complexValues) {
    std::cout << "\nInserting " << v << "..." << std::endl;
    avl_complex.insert(v);
    std::cout << "Current AVL structure:" << std::endl;
    avl_complex.printWithoutPrefix(avl_complex.getRoot());
  }

  std::cout << "\nFinal AVL Structure:" << std::endl;
  avl_complex.printWithoutPrefix(avl_complex.getRoot());

  // Global Check 1: AVL Balance Property (verify |balance factor| ≤ 1 for all
  // nodes) Global Check 2: BST Property (in-order traversal yields strictly
  // increasing sequence)

  totalTests++;

  auto *root = avl_complex.getRoot();
  bool allBalanced = true;
  bool isBST = true;

  // Recursively verify balance: invoke getBalance for each node
  auto checkBalanced = [&](auto &&self, auto *node) -> void {
    if (!node || !allBalanced)
      return;

    int bf = avl_complex.getBalance(node);
    if (bf < -1 || bf > 1) {
      allBalanced = false;
      std::cout << "  · Unbalanced node detected! key = " << node->key
                << ", balance factor = " << bf << std::endl;
    }

    self(self, node->left);
    self(self, node->right);
  };

  // Verify BST property via in-order traversal
  std::vector<int> inorder;
  auto inorderTraverse = [&](auto &&self, auto *node) -> void {
    if (!node)
      return;
    self(self, node->left);
    inorder.push_back(node->key);
    self(self, node->right);
  };

  if (root != nullptr) {
    checkBalanced(checkBalanced, root);
    inorderTraverse(inorderTraverse, root);

    for (std::size_t i = 1; i < inorder.size(); ++i) {
      if (inorder[i - 1] >= inorder[i]) {
        isBST = false;
        std::cout << "  · BST violation detected in inorder sequence at index "
                  << i - 1 << " and " << i << ": " << inorder[i - 1] << " !< "
                  << inorder[i] << std::endl;
        break;
      }
    }
  } else {
    allBalanced = false;
    isBST = false;
    std::cout << "  · Root is nullptr, tree is empty!" << std::endl;
  }

  if (allBalanced && isBST) {
    std::cout << "✓ PASS: Complex AVL tree remains globally balanced and is a "
                 "valid BST"
              << std::endl;
    passedTests++;
  } else {
    std::cout << "❌ FAIL: Complex AVL tree check failed!" << std::endl;
    if (!allBalanced) {
      std::cout << "  - Reason: Found node(s) with |balance factor| > 1"
                << std::endl;
    }
    if (!isBST) {
      std::cout << "  - Reason: Inorder traversal is not strictly increasing "
                   "(BST violated)"
                << std::endl;
    }
    std::cout
        << "HINT: Check your rotation logic (including parent/child updates),\n"
           "      and make sure height/BalanceFactor are updated correctly\n"
           "      after EACH insertion and rotation."
        << std::endl;
  }

  // ==========================================================================
  // TEST 11: AVL Tree - Deletion with Multiple Rotations
  // ==========================================================================
  printTestHeader(11, "AVL Tree - Deletion with Multiple Rotations");
  std::cout << "Inserting (build initial AVL): "
            << "50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35, 65, 85" << std::endl;
  std::cout << "Then deleting: 5, 15, 75, 50" << std::endl;
  std::cout << "Expected:" << std::endl;
  std::cout << "  - Tree remains AVL-balanced after each deletion" << std::endl;
  std::cout << "  - Deleted keys are no longer found in the tree" << std::endl;
  std::cout << "  - Remaining keys still form a valid BST" << std::endl;

  TREE::AVLTree<int> avl_delete_d;

  int insertValues_d[] = {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 35, 65, 85};
  int deleteValues_d[] = {5, 15, 75, 50};

  for (int v_d : insertValues_d) {
    std::cout << "\nInserting " << v_d << "..." << std::endl;
    avl_delete_d.insert(v_d);
    std::cout << "Current AVL structure:" << std::endl;
    avl_delete_d.printWithoutPrefix(avl_delete_d.getRoot());
  }

  for (int d_d : deleteValues_d) {
    std::cout << "\nDeleting " << d_d << "..." << std::endl;
    avl_delete_d.remove(d_d);
    std::cout << "AVL structure after deleting " << d_d << ":" << std::endl;
    avl_delete_d.printWithoutPrefix(avl_delete_d.getRoot());
  }

  std::cout << "\nFinal AVL structure after deletions:" << std::endl;
  avl_delete_d.printWithoutPrefix(avl_delete_d.getRoot());

  totalTests++;

  auto *root_d = avl_delete_d.getRoot();
  bool allBalanced_d = true;
  bool isBST_d = true;
  bool deleteOk_d = true;

  auto checkBalanced_d = [&](auto &&self_d, auto *node_d) -> void {
    if (!node_d || !allBalanced_d)
      return;

    int bf_d = avl_delete_d.getBalance(node_d);
    if (bf_d < -1 || bf_d > 1) {
      allBalanced_d = false;
      std::cout << "  · Unbalanced node detected! key = " << node_d->key
                << ", balance factor = " << bf_d << std::endl;
    }

    self_d(self_d, node_d->left);
    self_d(self_d, node_d->right);
  };

  std::vector<int> inorder_d;
  auto inorderTraverse_d = [&](auto &&self_d, auto *node_d) -> void {
    if (!node_d)
      return;
    self_d(self_d, node_d->left);
    inorder_d.push_back(node_d->key);
    self_d(self_d, node_d->right);
  };

  if (root_d != nullptr) {
    checkBalanced_d(checkBalanced_d, root_d);
    inorderTraverse_d(inorderTraverse_d, root_d);

    for (std::size_t i_d = 1; i_d < inorder_d.size(); ++i_d) {
      if (inorder_d[i_d - 1] >= inorder_d[i_d]) {
        isBST_d = false;
        std::cout << "  · BST violation in inorder sequence at index "
                  << i_d - 1 << " and " << i_d << ": " << inorder_d[i_d - 1]
                  << " !< " << inorder_d[i_d] << std::endl;
        break;
      }
    }
  } else {
    allBalanced_d = false;
    isBST_d = false;
    std::cout << "  · Root is nullptr, tree is empty after deletions!"
              << std::endl;
  }

  for (int d_d : deleteValues_d) {
    BSTNode<int> *found_d = avl_delete_d.search(d_d);
    if (found_d != nullptr) {
      deleteOk_d = false;
      std::cout << "  · Delete check FAILED: key " << d_d
                << " still found in the tree!" << std::endl;
    }
  }

  int remainCheck_d[] = {25, 30, 60, 80};
  for (int k_d : remainCheck_d) {
    BSTNode<int> *found_d = avl_delete_d.search(k_d);
    if (found_d == nullptr) {
      deleteOk_d = false;
      std::cout << "  · Existence check FAILED: key " << k_d
                << " should remain in the tree but was NOT found!" << std::endl;
    }
  }

  if (allBalanced_d && isBST_d && deleteOk_d) {
    std::cout << "✓ PASS: Deletion sequence keeps AVL balanced, BST valid, and "
                 "deleteNode works correctly"
              << std::endl;
    passedTests++;
  } else {
    std::cout << "❌ FAIL: AVL deleteNode test failed!" << std::endl;
    if (!allBalanced_d) {
      std::cout << "  - Reason: Found node(s) with |balance factor| > 1 after "
                   "deletions"
                << std::endl;
    }
    if (!isBST_d) {
      std::cout << "  - Reason: Inorder traversal is not strictly increasing "
                   "(BST violated)"
                << std::endl;
    }
    if (!deleteOk_d) {
      std::cout
          << "  - Reason: Some keys were not deleted correctly, or remaining "
             "keys disappeared unexpectedly"
          << std::endl;
    }
    std::cout << "HINT: Carefully review your deleteNode logic:" << std::endl;
    std::cout
        << "      · Successor handling when deleting a node with two children"
        << std::endl;
    std::cout << "      · transplant() correctness and parent pointer updates"
              << std::endl;
    std::cout << "      · Rebalancing loop after deletion (starting node, "
                 "height updates,"
                 " and balance calls)"
              << std::endl;
  }

  // ==========================================================================
  // TEST 12: BigInt Basic Operations
  // ==========================================================================
  printTestHeader(12, "BigInt - Basic Operations");
  std::cout << "Testing BigInt library linkage and basic operations..."
            << std::endl;

  BigInt num1(12345);
  BigInt num2(67890);

  std::cout << "num1 = ";
  num1.print();
  std::cout << "num2 = ";
  num2.print();

  totalTests++;
  std::cout << "✓ PASS: BigInt operations work (library linked successfully)"
            << std::endl;
  passedTests++;

  std::cout
      << "HINT: If linker errors about BigInt, check CMakeLists.txt sources"
      << std::endl;

  // ==========================================================================
  // FINAL RESULTS
  // ==========================================================================
  std::cout << "\n";
  std::cout << "╔══════════════════════════════════════════════════════════════"
               "═════════╗"
            << std::endl;
  std::cout << "║                        FINAL TEST RESULTS                    "
               "         ║"
            << std::endl;
  std::cout << "╚══════════════════════════════════════════════════════════════"
               "═════════╝"
            << std::endl;

  std::cout << "\nTests Passed: " << passedTests << " / " << totalTests
            << std::endl;

  if (passedTests == totalTests) {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════"
                 "═══════════╗"
              << std::endl;
    std::cout << "║                    🎉 CONGRATULATIONS! 🎉                  "
                 "           ║"
              << std::endl;
    std::cout << "║                                                            "
                 "           ║"
              << std::endl;
    std::cout << "║   You have successfully fixed ALL bugs in this repository! "
                 "           ║"
              << std::endl;
    std::cout << "║   All tests passed - excellent debugging and "
                 "problem-solving!         ║"
              << std::endl;
    std::cout << "║                                                            "
                 "           ║"
              << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════"
                 "═══════════╝"
              << std::endl;
  } else {
    int failedTests = totalTests - passedTests;
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════"
                 "═══════════╗"
              << std::endl;
    std::cout << "║                     ⚠️  TESTS FAILED  ⚠️                     "
                 "         ║"
              << std::endl;
    std::cout << "║                                                            "
                 "           ║"
              << std::endl;
    std::cout << "║   " << failedTests
              << " test(s) still failing. Keep debugging!                      "
                 "      ║"
              << std::endl;
    std::cout << "║                                                            "
                 "           ║"
              << std::endl;
    std::cout << "║   Review the HINTS above each failed test.                 "
                 "           ║"
              << std::endl;
    std::cout << "║   Read error messages carefully - they often point to the "
                 "solution!   ║"
              << std::endl;
    std::cout << "║                                                            "
                 "           ║"
              << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════"
                 "═══════════╝"
              << std::endl;
  }

  std::cout << "\n";
  return (passedTests == totalTests) ? 0 : 1;
}
