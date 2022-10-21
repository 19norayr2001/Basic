#include <cmath>

#include "priority_queue.hpp"

PriorityQueue::PriorityQueue()
        : _size(0) {
    _heap.push_back(0);
}

PriorityQueue::PriorityQueue(const PriorityQueue& object) {
    allocate(object);
}

PriorityQueue& PriorityQueue::operator=(const PriorityQueue& object) {
    if (this != &object) {
        deallocate();
        allocate(object);
    }
    return *this;
}

PriorityQueue::~PriorityQueue() {
    deallocate();
}


const int& PriorityQueue::top() const {
    return _heap[1];
}

void PriorityQueue::insert(const int& value) {
    _heap.push_back(value);
    _size++;
    int id = _size;
    while (id != 1 && _heap[id] < _heap[id / 2]) {
        std::swap(_heap[id], _heap[id / 2]);
        id /= 2;
    }
}

void PriorityQueue::pop() {
    _size--;
    if (_size == 0) {
        _heap.pop_back();
    } else {
        _heap[1] = _heap[_size + 1];
        _heap.pop_back();
        int id = 1;
        while ((2 * id <= _size && _heap[id] > _heap[2 * id]) ||
               (2 * id + 1 <= _size && _heap[id] > _heap[2 * id + 1])) {
            int* minn = &_heap[2 * id];
            id *= 2;
            if (id + 1 <= _size && _heap[id + 1] < _heap[id]) {
                minn = &_heap[id + 1];
                id++;
            }
            std::swap(*minn, _heap[id / 2]);
        }
    }
}

void PriorityQueue::allocate(const PriorityQueue& object) {
    _size = object._size;
    for (int i = 0; i < _size; ++i) {
        _heap.push_back(object._heap[i]);
    }
}

void PriorityQueue::deallocate() {
    _heap.clear();
}