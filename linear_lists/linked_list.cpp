#include <iostream>

#include "linked_list.h"

LinkedList::LinkedList()
        : _head(nullptr), _tail(nullptr) {
    _head = _tail = new Node();
    _head->next = _head;
    _head->previous = _head;
}

LinkedList::LinkedList(const LinkedList& object) {
    allocate(object);
}

LinkedList& LinkedList::operator=(const LinkedList& object) {
    if (this != &object) {
        deallocate();
        allocate(object);
    }
    return *this;
}

LinkedList::~LinkedList() {
    deallocate();
}

void LinkedList::push_back(const int& num) {
    _tail->next = new Node(num);
    _tail->next->previous = _tail;
    _tail = _tail->next;
    _tail->next = _head;
}

void LinkedList::pop_back() {
    if (_head != _tail) {
        _tail = _tail->previous;
        delete _tail->next;
        _tail->next = _head;
    }
}

void LinkedList::push_front(const int& num) {
    _head->value = num;
    _head->previous = new Node();
    _head->previous->next = _head;
    _head = _head->previous;
    _head->previous = _tail;
    _tail->next = _head;
}

void LinkedList::pop_front() {
    if (_head != _tail) {
        _head = _head->next;
        delete _head->previous;
        _head->previous = _tail;
        _tail->next = _head;
    }
}

void LinkedList::insert(const int& value, Node* prev) {
    if (prev == _tail) {
        this->push_back(value);
    } else {
        Node* temp = new Node(value);
        temp->previous = prev;
        temp->next = prev->next;
        prev->next = temp;
        temp->next->previous = temp;
    }
}

void LinkedList::erase(Node* obj) {
    if (obj == _tail) {
        this->pop_back();
    } else {
        obj->previous->next = obj->next;
        obj->next->previous = obj->previous;
        delete obj;
    }
}

std::ostream& operator<<(std::ostream& print, LinkedList& obj) {
    LinkedList::Node* ptr = obj._head->next;
    while (ptr != obj._head) {
        print << ptr->value << std::endl;
        ptr = ptr->next;
    }
    return print;
}

void LinkedList::allocate(const LinkedList& object) {
    Node* ptrobj = object._head;
    _head = new Node();
    Node* ptrthis = _head;
    while (ptrobj->next != object._head) {
        ptrthis->next = new Node();
        ptrthis->next->previous = ptrthis;
        ptrthis->next->value = ptrobj->next->value;
        ptrthis = ptrthis->next;
        ptrobj = ptrobj->next;
    }
    _tail = ptrthis;
    _tail->next = _head;
    _head->previous = _tail;
}

void LinkedList::deallocate() {
    Node* ptr = _head;
    while (ptr != _tail) {
        ptr = ptr->next;
        delete ptr->previous;
    }
    delete _tail;
}