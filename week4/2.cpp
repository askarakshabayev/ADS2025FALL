#include <iostream>

using namespace std;

class Node {
    public:
    int data;
    Node *left;
    Node *right;
    // Node *parent;
    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

class Tree {
    public:
    Node *root;
    Tree() {
        this->root = NULL;
    }

    Node* insert(Node *node, int data) {
        if (node == NULL) {
            node = new Node(data);
            return node;
        }
        if (data > node->data) 
            node->right = insert(node->right, data);
        else 
            node->left = insert(node->left, data);
        return node;
    }

    void in_order(Node *node) {
        if (node == NULL)
            return;
        in_order(node->left);
        cout << node->data << " ";
        in_order(node->right);
    }

    Node* find_min(Node *node) {
        if (node->left == NULL)
            return node;            
        return find_min(node->left);
    }
    Node* find_max(Node *node) {
        if (node->right == NULL)
            return node;
        return find_max(node->right);
    }

    Node* delete_node(Node *node, int data) {
        if (node == NULL)
            return NULL;
        if (data > node->data) 
            node->right = delete_node(node->right, data);
        else if (data < node->data)
            node->left = delete_node(node->left, data);
        else {
            // node->data = data
            if (node->left == NULL && node->right == NULL)
                return NULL;
            else if (node->left == NULL)
                node = node->right;
            else if (node->right == NULL)
                node = node->left;
            else {
                Node *tmp = find_min(node->right);
                node->data = tmp->data;
                node->right = delete_node(node->right, tmp->data);
            }
        }
    }
};

int main() {
    Tree *tree = new Tree();
    tree->root = tree->insert(tree->root, 30);
    tree->root = tree->insert(tree->root, 20);
    tree->root = tree->insert(tree->root, 40);
    tree->root = tree->insert(tree->root, 10);
    tree->root = tree->insert(tree->root, 26);
    tree->root = tree->insert(tree->root, 34);
    tree->root = tree->insert(tree->root, 45);
    tree->root = tree->insert(tree->root, 9);
    tree->root = tree->insert(tree->root, 12);
    // cout << tree->root->left->right->data;
    // tree->in_order(tree->root);
    // Node *node = tree->find_min(tree->root);
    Node *node = tree->find_max(tree->root);
    cout << node->data;
    return 0;
}