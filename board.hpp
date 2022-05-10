//
//  board.hpp
//  BirdsBirds
//
//  Created by Ansel Chang on 5/6/22.
//
#pragma once

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include "fixedArrayQueue.hpp"

class Board {
    
public:
    Board();
    void resetBoard();
    bool isEdge(int row, int col);
    
    void moveOrangeTo(int row, int col);
    void makeBlackMove(int row, int col);
    
    bool isOrangeWin();
    bool isBlackWin();
    
    void bestOrangeMoveStatic(int *bestRow, int *bestCol);
    void bestBlackMoveStatic(int *bestRow, int *bestCol);
    int getShortestPath(int *count, int startRow = -1, int startCol = -1);
    void bfs(int visited[ROWS][COLS], int row, int col);
    
    void display();
    void displayEdge();
    
private:
    // 10 cols and 8 rows.  (0,7) and (7,0) are invalid.
    int arr[ROWS][COLS] = {};
    int adjacent[ROWS][COLS][6][2]; // at most 6 edges
    int orangeRow, orangeCol;
    
    void initAdjacencyList();
    
};

