//
//  FixedArrayQueue.hpp
//  BirdsBirds
//
//  Created by Ansel Chang on 5/6/22.
//

#pragma once

#include <stdio.h>
#include <iostream>
#include "constants.h"

class FixedArrayQueue {
    
public:
    FixedArrayQueue(int capacity);
    ~FixedArrayQueue();
    bool isFull();
    bool isEmpty();
    bool enqueue(int r, int c);
    bool dequeue();
    bool dequeue(int* r, int* c);
    
    void print();
    
    
private:
    int start = 0;
    int end = -1;
    int size = 0;
    int N = ROWS*COLS;
    int* row;
    int* col;
};

