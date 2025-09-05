#include <iostream>
#include <stack>

using namespace std;

class Node {
    public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
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
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        sz++;
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
    // stack<int> st;
    // st.push(10);
    // st.push(20);
    // st.push(30);
    // st.push(40);
    // cout << st.top() << endl;
    // st.pop();
    // cout << st.top() << endl;
    // cout << st.size() << endl;
    // cout << st.empty() << endl; 
    // Node* node1 = new Node(10);
    // Node* node2 = new Node(20);
    // Node* node3 = new Node(30);
    // node1->next = node2;
    // node2->next = node3;
    // cout << node1->data << " " << node2->data << " " << node3->data << endl;
    // cout << node1->next->next->data << endl;
    Stack *st = new Stack();
    st->push(10);
    st->push(20);   
    st->push(30);   
    st->push(40);   
    cout << st->peek() << endl;
    st->pop();
    cout << st->peek() << endl;
    cout << st->size() << endl;
    cout << st->empty() << endl;
    return 0;
}