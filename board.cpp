//
//  board.cpp
//  BirdsBirds
//
//  Created by Ansel Chang on 5/6/22.
//

#include "board.hpp"

using namespace std;

Board::Board() {
    
    srand (time(NULL)); // randomize seed
    
    initAdjacencyList();
    resetBoard();
}

void Board::resetBoard() {
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int r = rand() % 16;
            if (r < 4) arr[i][j] = BLACK;
            else arr[i][j] = EMPTY;
        }
    }
    
    orangeRow = 4;
    orangeCol = 4;
    
    arr[0][0] = INVALID;
    arr[ROWS-1][COLS-1] = INVALID;
    
}

bool Board::isEdge(int row, int col) {
    return row == 0 || row == ROWS-1 || col == 0 || col == COLS-1;
}

bool Board::isOrangeWin() {
    return isEdge(orangeRow, orangeCol);
}

bool Board::isBlackWin() {
    int visited[ROWS][COLS];
    bfs(visited, orangeRow, orangeCol);
    
    for (int i = 0; i < COLS-1; i++) {
        if (visited[0][i+1] != -1 || visited[ROWS-1][i] != -1) return false;
    }
    for (int i = 1; i < ROWS-1; i++) {
        if (visited[i][0] != -1 || visited[i][COLS-1] != -1) return false;
    }
    
    return true; // there were no edges that were visited
    
}

void Board::moveOrangeTo(int row, int col) {
    orangeRow = row;
    orangeCol = col;
}

void Board::makeBlackMove(int row, int col) {
    arr[row][col] = BLACK;
}

// Perform BFS to see if orange can win
void Board::bfs(int visited[ROWS][COLS], int row, int col) {
    
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            visited[i][j] = -1;
    FixedArrayQueue q(ROWS*COLS);
    
    q.enqueue(row, col);
    visited[row][col] = 0;
    
    while (!q.isEmpty()) {
        
        int r, c;
        q.dequeue(&r, &c);
        if (isEdge(r,c)) continue;
        
        for (int i = 0; i < 6; i++) {
            int nr = adjacent[r][c][i][0];
            int nc = adjacent[r][c][i][1];
            
            if (visited[nr][nc] == -1 && arr[nr][nc] == EMPTY) {
                visited[nr][nc] = visited[r][c] + 1;
                q.enqueue(nr, nc);
            }
        }
    }
    visited[0][0] = -2;
    visited[ROWS-1][COLS-1] = -2;

}

void shortestUtility(int value, int *count, int *shortest) {
    if (value != -1 && value < *shortest) {
        *shortest = value;
        *count = 1;
    } else if (value == *shortest) (*count)++;
}

int Board::getShortestPath(int *count, int startRow, int startCol) {
    
    if (startRow == -1) {
        startRow = orangeRow;
        startCol = orangeCol;
    }
    
    int visited[ROWS][COLS];
    bfs(visited, startRow, startCol);
    
    int shortest = INT_MAX;
    *count = 0;
    
    for (int i = 0; i < COLS-1; i++) {
        shortestUtility(visited[0][i+1], count, &shortest);
        shortestUtility(visited[ROWS-1][i], count, &shortest);
    }
    for (int i = 1; i < ROWS-1; i++) {
        shortestUtility(visited[i][0], count, &shortest);
        shortestUtility(visited[i][COLS-1], count, &shortest);
    }
    return shortest;
}

int Board::evaluate() {
    int count;
    int distance = getShortestPath(&count);
    return distance * 100 - count;
}

void Board::makeBestOrangeMove(int depth) {
    
    int bestR, bestC;
    
    int prevOrangeRow = orangeRow;
    int prevOrangeCol = orangeCol;
    
    int value = INT_MAX;
    bool first = true;
    
    for (int i = 0; i < 6; i++) {
        int nr = adjacent[orangeRow][orangeCol][i][0];
        int nc = adjacent[orangeRow][orangeCol][i][1];
        if (arr[nr][nc] != EMPTY) continue;
        
        orangeRow = nr;
        orangeCol = nc;
        int cvalue = minimaxBlack(depth - 1, INT_MIN, INT_MAX);
        orangeRow = prevOrangeRow;
        orangeCol = prevOrangeCol;
        
        if (cvalue < value || first) {
            value = cvalue;
            bestR = nr;
            bestC = nc;
        }
        first = false;
        
    }
    
    // make best move
    orangeRow = bestR;
    orangeCol = bestC;
}

void Board::makeBestBlackMove(int depth) {
    
    int bestR, bestC;
    
    int value = INT_MIN;
    bool first = true;
    
    for (int nr = 0; nr < ROWS; nr++) {
        for (int nc = 0; nc < COLS; nc++) {
            
            if (arr[nr][nc] != EMPTY) continue;
            
            arr[nr][nc] = BLACK;
            int cvalue = minimaxOrange(depth - 1, INT_MIN, INT_MAX);
            arr[nr][nc] = EMPTY;
            
            if (cvalue > value || first) {
                value = cvalue;
                bestR = nr;
                bestC = nc;
            }
            first = false;
        }
    }
    
    // make best move
    arr[bestR][bestC] = BLACK;
}


int Board::minimaxOrange(int depth, int a, int b) {
    
    if (depth == 0) return evaluate();
    else if (isOrangeWin()) return INT_MIN + (10-depth);
    
    int prevOrangeRow = orangeRow;
    int prevOrangeCol = orangeCol;
    
    int value = INT_MAX;
    for (int i = 0; i < 6; i++) {
        int nr = adjacent[orangeRow][orangeCol][i][0];
        int nc = adjacent[orangeRow][orangeCol][i][1];
        if (arr[nr][nc] != EMPTY) continue;
        
        orangeRow = nr;
        orangeCol = nc;
        value = std::min(value, minimaxBlack(depth - 1, a, b));
        orangeRow = prevOrangeRow;
        orangeCol = prevOrangeCol;
                
        if (value <= a) break; // alpha cutoff
    }
    return value;
}

int Board::minimaxBlack(int depth, int a, int b) {
    
    if (depth == 0) return evaluate();
    else if (isBlackWin()) return INT_MAX - (10-depth);
    
    int value = INT_MIN;
    for (int nr = 0; nr < ROWS; nr++) {
        for (int nc = 0; nc < COLS; nc++) {

            if (arr[nr][nc] != EMPTY) continue;
            
            arr[nr][nc] = BLACK; // place piece
            
            value = std::max(value, minimaxOrange(depth - 1, a, b));
            
            arr[nr][nc] = EMPTY; // unplace piece
                    
            if (value >= b) break; // beta cutoff
        }
    }
    return value;
}

void Board::display() {
    displayBoard(arr, REGULAR_MODE, orangeRow, orangeCol);
}

void Board::displayEdge() {
    int edges[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (arr[i][j] == INVALID) edges[i][j] = 2;
            else if (isEdge(i, j)) edges[i][j] = 1;
            else edges[i][j] = 0;
        }
    }
    displayBoard(edges);
}

void Board::initAdjacencyList() {
    for (int i = 1; i < ROWS-1; i++) {
        for (int j = 1; j < COLS-1; j++) {
            
            // handle left
            adjacent[i][j][0][0] = i;
            adjacent[i][j][0][1] = j-1;
            
            // handle right
            adjacent[i][j][1][0] = i;
            adjacent[i][j][1][1] = j+1;
            
            int j2 = j + (i % 2 == 0 ? -1 : +1);
            
            // handle up
            adjacent[i][j][2][0] = i-1;
            adjacent[i][j][2][1] = j;
            adjacent[i][j][3][0] = i-1;
            adjacent[i][j][3][1] = j2;
            
            // handle down
            adjacent[i][j][4][0] = i+1;
            adjacent[i][j][4][1] = j;
            adjacent[i][j][5][0] = i+1;
            adjacent[i][j][5][1] = j2;
        }
    }

}
