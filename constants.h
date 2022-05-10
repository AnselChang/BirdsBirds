//
//  constants.h
//  BirdsBirds
//
//  Created by Ansel Chang on 5/6/22.
//

#pragma once
#include <functional>

using namespace std;

const int ROWS = 10;
const int COLS = 8;

const int EMPTY = 0;
const int BLACK = 1;
const int INVALID = 2;

static string REGULAR_MODE(int key) {
    switch(key) {
        case EMPTY:
            return ".";
        case BLACK:
            return "*";
        default:
            return " ";
    }
}

static string BFS_MODE(int key) {
    if (key == -2) return " ";
    else if (key == -1) return "*";
    else if (key <= 9) {
        return to_string(key);
    } else switch (key) {
                
        case 10:
            return "A";
        case 11:
            return "B";
        case 12:
            return "C";
        case 13:
            return "D";
        case 14:
            return "E";
        case 15:
            return "F";
        default:
            return "Z";
    }
}

static void displayBoard(int arr[][COLS], function<string(int)> func = nullptr, int orangeRow = -1, int orangeCol = -1) {
    
    bool shifted = false;
    for (int i = 0; i < ROWS; i++) {
        
        if (shifted) cout << " ";
        
        for (int j = 0; j < COLS; j++) {
            if (func == nullptr) cout << arr[i][j];
            else if (i == orangeRow && j == orangeCol) cout << "X";
            else cout << func(arr[i][j]);
            cout << " ";
        }
        cout << "\n";
        shifted = !shifted;
    }
    cout << endl;
    
}
