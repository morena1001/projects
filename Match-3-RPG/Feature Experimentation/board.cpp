#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <time.h>
#include "boardFunctions.h" // piece.h is already include in this file

using namespace std;

int main() {
    piece board[5][7];
    generateNewPieces(board);
    matchChecking(board);
    printBoard(board);

    getMoves(board);

    return 0;
}
