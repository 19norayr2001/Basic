#include <cmath>

#include "priority_queue.h"

PriorityQueue::PriorityQueue()
        : m_size(0) {
    m_heap.push_back(0);
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
    return m_heap[1];
}

void PriorityQueue::insert(const int& value) {
    m_heap.push_back(value);
    m_size++;
    int id = m_size;
    while (id != 1 && m_heap[id] < m_heap[id / 2]) {
        std::swap(m_heap[id], m_heap[id / 2]);
        id /= 2;
    }
}

void PriorityQueue::pop() {
    m_size--;
    if (m_size == 0) {
        m_heap.pop_back();
    } else {
        m_heap[1] = m_heap[m_size + 1];
        m_heap.pop_back();
        int id = 1;
        while ((2 * id <= m_size && m_heap[id] > m_heap[2 * id]) ||
               (2 * id + 1 <= m_size && m_heap[id] > m_heap[2 * id + 1])) {
            int* minn = &m_heap[2 * id];
            id *= 2;
            if (id + 1 <= m_size && m_heap[id + 1] < m_heap[id]) {
                minn = &m_heap[id + 1];
                id++;
            }
            std::swap(*minn, m_heap[id / 2]);
        }
    }
}

void PriorityQueue::allocate(const PriorityQueue& object) {
    m_size = object.m_size;
    for (int i = 0; i < m_size; ++i) {
        m_heap.push_back(object.m_heap[i]);
    }
}

void PriorityQueue::deallocate() {
    m_heap.clear();
}