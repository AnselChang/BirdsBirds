//
//  main.cpp
//  BirdsBirds
//
//  Created by Ansel Chang on 5/6/22.
//

#include <iostream>
#include "board.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
        
    Board b;
    b.display();
    
    while (true) {
        
        int bestRow, bestCol;
        
        b.bestOrangeMoveStatic(&bestRow, &bestCol);
        b.moveOrangeTo(bestRow, bestCol);
        b.display();
        if (b.isOrangeWin()) {
            cout << "Orange wins!" << endl;
            break;
        }
        
        b.bestBlackMoveStatic(&bestRow, &bestCol);
        b.makeBlackMove(bestRow, bestCol);
        b.display();
        if (b.isBlackWin()) {
            cout << "Black wins!" << endl;
            break;
        }
        
    }
    
    int count;
    b.getShortestPath(&count);
    cout << "done" << endl;
    
    return 0;
}
