# Lecture 4: Binary Search Tree (BST)

## Introduction to Binary Search Tree

**A Binary Search Tree (BST)** is a type of binary tree data structure in which each node contains a unique key and satisfies a specific ordering property:

1. **All nodes in the left subtree** of a node contain values **strictly less than** the node's value
2. **All nodes in the right subtree** of a node contain values **strictly greater than** the node's value

This structure enables **efficient operations** for searching, insertion, and deletion of elements, especially when the tree remains balanced.

## BST Properties

- **In-order traversal** of a BST gives elements in **sorted order**
- **Average time complexity** for search, insert, delete: **O(log n)**
- **Worst case time complexity** (skewed tree): **O(n)**
- **Space complexity**: **O(n)** for storing n nodes

## Complete BST Implementation

```cpp
#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node *left, *right;

    Node(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class BST {
    public:
    Node *root;

    BST() {
        root = NULL;
    }

    // Insert operation - O(log n) average, O(n) worst case
    Node *insert(Node *node, int data) {
        if (node == NULL) {
            node = new Node(data);
            return node;
        }

        if (data <= node->data) 
            node->left = insert(node->left, data);
        else
            node->right = insert(node->right, data);

        return node;
    }

    // In-order traversal - gives sorted output
    void inOrder(Node *node) {
        if (node == NULL)
            return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    // Pre-order traversal
    void preOrder(Node *node) {
        if (node == NULL)
            return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    // Post-order traversal
    void postOrder(Node *node) {
        if (node == NULL)
            return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    // Find minimum element - leftmost node
    Node *findMin(Node *node) {
        if (node == NULL)
            return NULL;
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    // Find maximum element - rightmost node
    Node *findMax(Node *node) {
        if (node == NULL)
            return NULL;
        while (node->right != NULL)
            node = node->right;
        return node;
    }

    // Search for a value
    Node *search(Node *node, int data) {
        if (node == NULL || node->data == data)
            return node;
        
        if (data < node->data)
            return search(node->left, data);
        else
            return search(node->right, data);
    }

    // Delete operation - most complex
    Node *deleteNode(Node *node, int data) {
        if (node == NULL)
            return NULL;
            
        if (data < node->data)
            node->left = deleteNode(node->left, data);
        else if (data > node->data)
            node->right = deleteNode(node->right, data);
        else {
            // Node to be deleted found
            
            // Case 1: Node has no children (leaf node)
            if (node->right == NULL && node->left == NULL) {
                delete node;
                node = NULL;
            }
            // Case 2: Node has only right child
            else if (node->left == NULL) {
                Node *temp = node;
                node = node->right;
                delete temp;
            }
            // Case 3: Node has only left child
            else if (node->right == NULL) {
                Node *temp = node;
                node = node->left;
                delete temp;
            }
            // Case 4: Node has both children
            else {
                Node *tmp = findMax(node->left);  // Find inorder predecessor
                node->data = tmp->data;           // Replace data
                node->left = deleteNode(node->left, tmp->data);  // Delete predecessor
            }
        }
        return node;
    }

    // Helper function to get height of tree
    int getHeight(Node *node) {
        if (node == NULL)
            return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    // Count total nodes in tree
    int countNodes(Node *node) {
        if (node == NULL)
            return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
};

int main() {
    BST *bst = new BST();
    
    // Insert nodes
    bst->root = bst->insert(bst->root, 10);
    bst->root = bst->insert(bst->root, 15);
    bst->root = bst->insert(bst->root, 16);
    bst->root = bst->insert(bst->root, 13);
    bst->root = bst->insert(bst->root, 12);
    bst->root = bst->insert(bst->root, 14);
    bst->root = bst->insert(bst->root, 9);
    bst->root = bst->insert(bst->root, 8);
    bst->root = bst->insert(bst->root, 10);  // Duplicate - goes to left
    bst->root = bst->insert(bst->root, 10);  // Another duplicate
    bst->root = bst->insert(bst->root, 17);

    cout << "In-order traversal (sorted): ";
    bst->inOrder(bst->root);
    cout << endl;

    cout << "Pre-order traversal: ";
    bst->preOrder(bst->root);
    cout << endl;

    cout << "Post-order traversal: ";
    bst->postOrder(bst->root);
    cout << endl;

    // Find min and max
    Node *node_min = bst->findMin(bst->root);
    Node *node_max = bst->findMax(bst->root);
    cout << "Min: " << node_min->data << ", Max: " << node_max->data << endl;

    // Search for a value
    Node *found = bst->search(bst->root, 13);
    if (found)
        cout << "Found: " << found->data << endl;
    else
        cout << "Not found" << endl;

    // Tree statistics
    cout << "Tree height: " << bst->getHeight(bst->root) << endl;
    cout << "Total nodes: " << bst->countNodes(bst->root) << endl;

    // Delete a node
    cout << "Deleting node 13..." << endl;
    bst->root = bst->deleteNode(bst->root, 13);
    cout << "In-order after deletion: ";
    bst->inOrder(bst->root);
    cout << endl;

    return 0;
}
```

## Tree Traversals

### 1. In-Order Traversal (Left → Root → Right)
- **Result**: Elements in **sorted order**
- **Use case**: Getting sorted sequence from BST

### 2. Pre-Order Traversal (Root → Left → Right)  
- **Result**: Root comes first
- **Use case**: Creating a copy of the tree

### 3. Post-Order Traversal (Left → Right → Root)
- **Result**: Root comes last
- **Use case**: Deleting the tree safely

## BST Operations Analysis

| Operation | Average Case | Worst Case | Best Case |
|-----------|--------------|------------|-----------|
| **Search** | O(log n) | O(n) | O(1) |
| **Insert** | O(log n) | O(n) | O(1) |
| **Delete** | O(log n) | O(n) | O(1) |
| **Find Min** | O(log n) | O(n) | O(1) |
| **Find Max** | O(log n) | O(n) | O(1) |
| **Traversal** | O(n) | O(n) | O(n) |

## Deletion Cases in Detail

### Case 1: Deleting a Leaf Node
- Simply remove the node
- **Example**: Delete 8 from tree

### Case 2: Deleting Node with One Child
- Replace the node with its child
- **Example**: Delete 9 (has only left child 8)

### Case 3: Deleting Node with Two Children
- Find **inorder predecessor** (rightmost node in left subtree) **OR**
- Find **inorder successor** (leftmost node in right subtree)
- Replace node's data with predecessor/successor
- Delete the predecessor/successor

## BST vs Other Data Structures

| Data Structure | Search | Insert | Delete | Space |
|----------------|--------|--------|---------|-------|
| **Array (unsorted)** | O(n) | O(1) | O(n) | O(n) |
| **Array (sorted)** | O(log n) | O(n) | O(n) | O(n) |
| **Linked List** | O(n) | O(1) | O(n) | O(n) |
| **BST (balanced)** | O(log n) | O(log n) | O(log n) | O(n) |
| **Hash Table** | O(1)* | O(1)* | O(1)* | O(n) |

*Average case for hash table

## Advantages and Disadvantages

### Advantages:
- **Efficient searching**: O(log n) average case
- **In-order traversal** gives sorted sequence
- **Dynamic size**: Can grow and shrink during runtime
- **No extra space** needed for sorting

### Disadvantages:
- **Can become unbalanced** → O(n) worst case
- **No constant time operations** like hash tables
- **More complex** than arrays for simple operations

## When to Use BST

**Good for:**
- Frequent search operations
- Need to maintain sorted order
- Range queries (find all elements between x and y)
- Dynamic data with insertions and deletions

**Not ideal for:**
- Mostly sequential access
- Frequent random access by index
- When constant time operations are critical

## Key Takeaways

1. **BST maintains sorted order** through its structure property
2. **Performance depends on tree balance** - balanced tree gives O(log n), skewed tree gives O(n)
3. **In-order traversal always gives sorted output**
4. **Deletion is the most complex operation** with three different cases
5. **BST is foundation for more advanced trees** like AVL, Red-Black trees