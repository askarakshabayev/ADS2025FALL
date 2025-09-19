#include <iostream>

using namespace std;

class Node {
    public:
    int data;
    Node *next;
    Node *prev;
    Node(int val) {
        this->data = val;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class LinkedList {
    public:
    Node *tail;
    Node *front;
    int data;

    LinkedList() {
        tail = front = NULL;
    }

    void push_front(int data) {
        Node *node = new Node(data);
        if (front == NULL) {
            front = tail = node;
        } else {
            node->next = front;
            front->prev = node;
            front = node;
        }
    }

    void push_back(int data) {
        Node *node = new Node(data);
        if (front == NULL) {
            front = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    
    void pop_back() {
        if (tail != NULL) {
            Node *temp = tail;
            tail = tail->prev;
            if (tail != NULL)
                tail->next = NULL;
            delete temp;            
        }
    }

    void del_node(Node *node) {
        if (node == tail)
            this->pop_back();
        else if (node == front) {
            // this->pop_front();
        } else {
            Node *a = node->prev;
            Node *b = node->next;
            a->next = b;
            b->prev = a;
        }
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

class Queue {
    public:
    Node *front;
    Node *end;
    Queue() {
        front = NULL;
        end = NULL;
    }
    void push(int val) {
        Node* newNode = new Node(val);
        if (end == NULL) {
            front = end = newNode;
            return;
        }
        end->next = newNode;
        end = newNode;
    }
    void pop() {
        if (front == NULL) 
            return;
        Node* temp = front;
        front = front->next;
        if (front == NULL) 
            end = NULL;
        delete temp;
    }
    int peek() {
        if (front == NULL) 
            return -1; // or throw an exception
        return front->data;
    }
    int empty() {   
        return front == NULL;
    }
    int size() {
        int count = 0;
        Node* current = front;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        return count;
    }

};

class LinkedList {
    public:
    Node* head;
    Node* tail;
    int sz;
    LinkedList() {
        head = NULL;
        tail = NULL;
        sz = 0;
    }

    void insert_at_head(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        sz++;
    }

    void insert_at_tail(int val) {
        Node* newNode = new Node(val);
        if (tail == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        sz++;
    }

    void delete_from_head() {
        if (head == NULL) 
            return;
        Node* temp = head;
        head = head->next;
        if (head == NULL) 
            tail = NULL;
        delete temp;
        sz--;
    }

    void delete_from_tail() {
        if (tail == NULL) 
            return;
        if (head == tail) {
            delete head;
            head = tail = NULL;
            sz--;
            return;
        }
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = NULL;
        sz--;
    }

    int size() {
        return sz;
    }

    bool empty() {
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