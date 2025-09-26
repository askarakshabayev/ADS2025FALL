#include <iostream>

using namespace std;

class Node {
    public:
    int data;
    Node *left;
    Node *right;
    Node *parent;
    Node(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class Tree {
    public:
    Node *root;

    Node* insert_node(Node *node, int data) {
        if (node == NULL) {
            Node *node = new Node(data);
            return node;
        }
        if (node->data < data) 
            node->right = insert_node(node->right, data);
        else
            node->left = insert_node(node->left, data);
        return node;
    }

    void insert_node2(int data) {
        if (this->root == NULL) {
            this->root = new Node(data);
            return;
        }
        Node *cur = root;
        while (cur != NULL) {
            if (data > cur->data) {
                if (cur->right == NULL) {
                    cur->right = new Node(data);
                    break;
                } else
                    cur = cur->right;
            } else {
                if (cur->left == NULL) {
                    cur->left = new Node(data);
                    break;
                } else 
                    cur = cur->left;
            }
        }
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

    Node *find_min2(Node *node) {
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    Node *delete_node(Node *node, int data) {
        if (node == NULL)
            return NULL;
        if (data < node->data)
            node->left = delete_node(node->left, data);
        else if (data > node->data)
            node->right = delete_node(node->right, data);
        else {
            if (node->right == NULL and node->left == NULL)
                node = NULL;
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
        return node;
    }
};

int main() {
    Tree *tree = new Tree();
    // tree->root = tree->insert_node(NULL, 10);
    // tree->root = tree->insert_node(tree->root, 8);
    // tree->root = tree->insert_node(tree->root, 20);
    // tree->root = tree->insert_node(tree->root, 7);
    // tree->root = tree->insert_node(tree->root, 9);
    tree->insert_node2(10);
    tree->insert_node2(8);
    tree->insert_node2(20);
    tree->insert_node2(7);
    tree->insert_node2(9);

    // cout << tree->root->left->right->data;
    // tree->in_order(tree->root);
    Node *node = tree->find_min(tree->root);
    cout << node->data;
    
    

    return 0;
}