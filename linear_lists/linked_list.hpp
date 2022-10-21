#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

class LinkedList {
public:
    struct Node {
        int value;
        Node* next, * previous;

        Node(int v = 0)
                : value(v), next(nullptr), previous(nullptr) {}
    };

    LinkedList();

    LinkedList(const LinkedList&);

    LinkedList& operator=(const LinkedList&);

    ~LinkedList();

public:
    void push_back(const int&);

    void pop_back();

    void push_front(const int&);

    void pop_front();

    void insert(const int&, Node*);

    void erase(Node*);

    friend std::ostream& operator<<(std::ostream&, LinkedList&);

private:
    void allocate(const LinkedList&);

    void deallocate();

private:
    Node* _head;
    Node* _tail;
};

#endif