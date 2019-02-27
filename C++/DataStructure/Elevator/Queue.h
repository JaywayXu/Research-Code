#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <cassert>

#include "Passenger.h"

using namespace std;

class Queue {
public:
    Queue(int maxsize = 10);
    ~Queue();

    bool empty() const;
    bool full() const;
    int size() const;

    void push(Passenger &data);
    void pop();
    Passenger &first();
    Passenger &back();

private:
    Passenger *array;
    int front;
    int rear;
    int capacity;
};

Queue::Queue(int maxsize) :front(0), rear(0), capacity(maxsize) {
    array = new Passenger[maxsize];
    assert(array != NULL);
}

Queue::~Queue() {
    delete[] array;
}

bool Queue::empty() const {
    return front == rear;
}

bool Queue::full() const {
    return (rear + 1) % capacity == front;
}

int Queue::size() const {
    return (rear - front + capacity) % capacity;
}

void Queue::push(Passenger &data) {
    if (!full()) {
        array[rear] = data;
        rear = (rear + 1) % capacity;
    } else {
        Passenger *new_array = new Passenger[2*capacity];
        for (int i=0; i!= 2*capacity && this->empty(); i++) {
            new_array[i] = this->first();
            this->pop();
        }
        delete[] array;
        array = new_array;
        front = 0;
        array[rear] = data;
        rear = this->rear+1;
        capacity = 2 * capacity;
    }
}

void Queue::pop() {
    if (!empty()) {
        front = (front + 1) %capacity;
    } else {
        cout << "Warning: empty queue!" << endl;
    }
}

Passenger &Queue::first() {
    if (empty())
        cerr << "Error, queue is empty!";
    return array[front];
}

Passenger &Queue::back() {
    if (empty())
        cerr << "Error, queue is empty!";
    return array[rear-1];
}

#endif // QUEUE_H
