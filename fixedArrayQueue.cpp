//
//  FixedArrayQueue.cpp
//  BirdsBirds
//
//  Created by Ansel Chang on 5/6/22.
//

#include "fixedArrayQueue.hpp"

using namespace std;

FixedArrayQueue::FixedArrayQueue(int capacity) {
    N = capacity;
    row = new int[N];
    col = new int[N];
}

FixedArrayQueue::~FixedArrayQueue() {
    delete [] row;
    delete [] col;
}

bool FixedArrayQueue::isFull() {
    return size == N;
}

bool FixedArrayQueue::isEmpty() {
    return size == 0;
}

// Return "last" element
bool FixedArrayQueue::enqueue(int r, int c) {
    if (isFull()) return false;
    size++;
    end = (end + 1) % N;
    row[end] = r;
    col[end] = c;
    return true;
}
bool FixedArrayQueue::dequeue() {
    
    if (isEmpty()) return false;
    
    size--;
    start = (start + 1) % N;
    return true;
}

// Return "first" element
bool FixedArrayQueue::dequeue(int* r, int* c) {
    
    
    if (isEmpty()) return false;
    
    *r = row[start];
    *c = col[start];
    
    return dequeue();
}

void FixedArrayQueue::print() {
    
    if (isEmpty()) {
        cout << "[empty]" << endl;
        return;
    }
    int curr = start;
    cout << "[";
    while (true) {
        
        cout << row[curr] << " " << col[curr];
        if (curr == end) {
            cout <<  "]" << endl;
            break;
        }  else cout << ", ";
        
        curr = (curr + 1) % N;
    }
}


