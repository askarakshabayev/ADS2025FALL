#include <iostream>

using namespace std;

class Node {
    public:
    int data;
    Node *next;
    Node(int val) {
        this->data = val;
        this->next = nullptr;
    }
};

class Stack {
    public:
    Node* top;
    int sz;
    Stack() {
        top = NULL;
        sz = 0;
    }
    void push(int val) {
        Node *newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        this->sz++;
    }

    void pop() {
        if (top != NULL) {
            Node *temp = top;
            top = top->next;
            this->sz--;
            delete temp;
        }
    }

    void pop() {
        if (top == NULL) 
            return;
        Node* temp = top;
        top = top->next;
        delete temp;
        sz--;
    }
    int peek() {
        if (top == NULL) 
            return -1; // or throw an exception
        return top->data;
    }
    int size() {
        return sz;
    }
    int empty() {
        return sz == 0;
    }
};
int main() {
    Node *node1 = new Node(10);
    Node *node2 = new Node(20);
    Node *node3 = new Node(30);
    node1->next = node2;
    node2->next = node3;
    cout << node1->next->next->data;
    return 0;
}