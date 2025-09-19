#include <iostream>

using namespace std;

class Node {
    public:
    int data;
    Node *next;

    Node(int data){
        this->data = data;
        next = NULL;
    }
};

int main() {
    Node *node1 = new Node(10);
    Node *node2 = new Node(20);
    Node *node3 = new Node(30);
    Node *node4 = new Node(40);
    Node *node5 = new Node(50);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    // cout << node1 << " " << node1->data << " " << node1->next << " " << node2;
    cout << node1->next->next->next->data;
    return 0;
}