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

class Stack {
    public:
    Node *top;
    int sz;

    Stack() {
        top = NULL;
        sz = 0;
    }

    void push(int data) {
        Node *new_node = new Node(data);
        new_node->next = top;
        top = new_node;
        sz++;
    }

    void pop() {
        if (top == NULL)
            return;
        top = top->next;
        sz--;
    }

    bool empty() {
        return sz == 0;
    }

    int size() {
        return sz;
    }
};

int main() {
    Stack *st = new Stack();
    st->push(10);
    st->push(20);
    st->push(30);
    st->pop();
    cout << st->size() << " " << st->top->data;
    return 0;
}



VaynBsSmgY0TA15V
