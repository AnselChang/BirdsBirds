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
    
    int DEPTH = 4;
        
    Board b;
    b.display();
    
    while (true) {
        b.makeBestOrangeMove(DEPTH);
        b.display();
        if (b.isOrangeWin()) {
            cout << "Orange wins!" << endl;
            break;
        }
        
        b.makeBestBlackMove(DEPTH);
        b.display();
        if (b.isBlackWin()) {
            cout << "Black wins!" << endl;
            break;
        }
    }
    
    
    return 0;
}
