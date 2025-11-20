# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build System

This project uses CMake with C++20 standard. The build system generates `compile_commands.json` for clangd integration.

### Building the Project

```bash
# Create build directory and configure
cmake -B build -S .

# Build the project
cmake --build build

# Run the main executable
./build/bin/main
```

The executable is output to `build/bin/main`.

### CMake Structure

- Root `CMakeLists.txt`: Defines the main project and executable
- `lib/CMakeLists.txt`: Defines the static library `algorithm_lib`
- All header files are in `lib/include/`
- Implementation files are in `lib/src/`

## Code Architecture

### Library Organization

The codebase is organized into a static library (`algorithm_lib`) that contains:

**Header-only components** (template implementations in headers):
- `tree.hpp`: Binary Search Trees (BST) and AVL Trees with full template implementations
- `node.hpp`: Node definitions for BST (`BSTNode<Key>`) and Red-Black Trees (`RBTNode`)
- `bits.hpp`: Bit manipulation utilities using C++20 concepts
- `util.hpp`: Template function `printTree()` for visualizing tree structures

**Compiled components** (declarations in headers, implementations in `.cpp`):
- `sort.hpp`/`sort.cpp`: Sorting algorithms (selection, bubble, insertion sort)
- `bignum.hpp`/`bignum.cpp`: Big integer arithmetic implementation
- `util.hpp`/`util.cpp`: Non-template utilities (swap, printArray)

### Tree Data Structures

The tree implementations use inheritance and template polymorphism:

- `BinarySearchTree<Key>` is the base class providing standard BST operations
- `AVLTree<Key>` inherits from BST and overrides insertion/deletion methods to maintain balance
- Both use the `KeyComparble` concept (requires `std::totally_ordered<Key>`)
- Node type: `BSTNode<Key>` contains key, left/right/parent pointers, and height field
- All tree implementations are **header-only** with full definitions in `tree.hpp`

Key methods in tree classes:
- Public API: `insert()`, `search()`, `remove()`, `minimum()`, `maximum()`, `successor()`
- Protected helpers: `insertNode()`, `deleteNode()`, `searchNode()`, tree rotations
- AVL-specific: `balance()` method handles LL, RR, LR, RL rotation cases

### Namespaces

- `SORT`: Sorting algorithm functions
- `TREE`: Binary tree data structures (BST, AVL)
- No namespace for global utilities and bit operations

## Code Style

The project follows these style conventions (see `.editorconfig`):

- **Indentation**: 2 spaces for C++ files
- **Line endings**: LF (Unix-style)
- **Max line length**: 80 characters
- **Encoding**: UTF-8
- **Trailing whitespace**: Trimmed
- **Final newline**: Required

### Compiler Warnings

The build is configured with strict warnings:
- `-Wall -Wextra -Wpedantic`
- `-Werror=return-type` (missing return statements are errors)

## File Header Convention

The codebase uses `.hpp` for C++ headers (not `.h`). When creating new headers, use `#pragma once` for include guards.

## Adding New Algorithms

When adding new algorithm implementations:

1. **For template-based code**: Put everything in the header file (`lib/include/`)
2. **For non-template code**:
   - Add declaration to header in `lib/include/`
   - Add implementation to `.cpp` file in `lib/src/`
   - Update `lib/CMakeLists.txt` to include the new `.cpp` file
3. Use appropriate namespace (SORT, TREE, or create new one)
4. Consider using C++20 concepts for template constraints

## Testing Approach

Currently, the project uses `main.cpp` for manual testing. The main file demonstrates:
- Creating and populating data structures
- Printing intermediate states
- Verifying algorithm correctness visually

To test new functionality, add test cases to `main.cpp` following the existing pattern.
