#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <time.h>
#include "piece.h"

using namespace std;

void generateNewPieces_e(piece board[5][7]);
// void executeMoves_e(piece board[5][7]);
void matchChecking_e(piece board[5][7]);
void pieceShuffle_e(piece board[5][7]);
void getMoves_e(piece board[5][7]);
void checkMatchAfterMove_e(piece board[5][7], int x, int y);
void removeMatched_e(piece board[5][7]);


void generateNewPieces_e(piece board[5][7]) {
    srand(time(NULL));
    // Generate a new piece for the empty tiles
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            if (board[i][j].num == 0) {
                board[i][j].num = 1 + (rand() % 5);
            }
        }
    }
}

void matchChecking_e(piece board[5][7]) {
    srand(time(NULL));

    bool leftPieces;
    bool rightPieces;
    bool topPieces;
    bool bottomPieces;
    
    // Check that the generated piece is not in a match of 3
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            leftPieces = j > 1 && board[i][j].num == board[i][j - 1].num && board[i][j - 1].num == board[i][j - 2].num;
            rightPieces = j < 5 && board[i][j].num == board[i][j + 1].num && board[i][j + 1].num == board[i][j + 2].num;
            topPieces = i > 1 && board[i][j].num == board[i - 1][j].num && board[i - 1][j].num == board[i - 2][j].num;
            bottomPieces = i < 3 && board[i][j].num == board[i + 1][j].num && board[i + 1][j].num == board[i + 2][j].num;

            // Check pieces around tile
            while (leftPieces || rightPieces || topPieces || bottomPieces) {
                board[i][j].num = 1 + (board[i][j].num % 5);

                leftPieces = j > 1 && board[i][j].num == board[i][j - 1].num && board[i][j - 1].num == board[i][j - 2].num;
                rightPieces = j < 5 && board[i][j].num == board[i][j + 1].num && board[i][j + 1].num == board[i][j + 2].num;
                topPieces = i > 1 && board[i][j].num == board[i - 1][j].num && board[i - 1][j].num == board[i - 2][j].num;
                bottomPieces = i < 3 && board[i][j].num == board[i + 1][j].num && board[i + 1][j].num == board[i + 2][j].num;
            }
        }
    }
}

void pieceShuffle_e(piece board[5][7]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i + 1][j].num == 0 && board[i][j].num != 0) {
                cout << "YES UNDERNEATH " << to_string(i + 1) << " " << to_string(j + 1) << endl;
                piece temp = board[i][j];
                board[i][j] = board[i + 1][j];
                board[i + 1][j] = temp;
            }
        }
    }

    for (int i = 2; i > -1; i--) {
        for(int j = 6; j > -1; j--) {
            if (board[i + 1][j].num == 0 && board[i][j].num != 0) {
                piece temp = board[i][j];
                board[i][j] = board[i + 1][j];
                board[i + 1][j] = temp;
            }
        }
    }

    cout << endl;
    // printBoard(board);
    cout << endl;
    generateNewPieces_e(board);
    matchChecking_e(board);
    printBoard(board);
}

void getMoves_e(piece board[5][7]) {
    string xPosition, yPosition, direction = "";
    int xCoordinate, yCoordinate;
    int movesLeft = 3;

    do {
        cout << "What piece do want to move? { " << movesLeft << " moves left } : ";
        cin >> xPosition >> yPosition >> direction;

        if (xPosition == "skip" || yPosition == "skip" || direction == "skip") {
            movesLeft = 0;
            continue;
        }

        if(stoi(xPosition) < 1 || stoi(xPosition) > 5) {
            cout << "X coordinate is out of bounds, try another input" << endl;
        }
        
        else if(stoi(yPosition) < 1 || stoi(yPosition) > 7) {
            cout << "Y coordinate is out of bounds, try another input" << endl;
        }
        
        else if(direction != "right" && direction != "left" && direction != "up" && direction != "down" 
             && direction != "up_left" && direction != "up_right" && direction != "down_left" && direction != "down_right") {
            cout << "Incorrect direction, try another input" << endl;
        }

        else if((stoi(xPosition) == 1 && (direction == "up" || direction == "up_left" || direction == "up_right")) || 
                (stoi(xPosition) == 5 && (direction == "down" || direction == "down_left" || direction == "down_right")) ||
                (stoi(yPosition) == 1 && (direction == "left" || direction == "up_left" || direction == "down_left")) || 
                (stoi(yPosition) == 7 && (direction == "right" || direction == "up_right" || direction == "down_right"))) {
            cout << "Direction not possible, try another input" << endl;
        }

        else {
            xCoordinate = stoi(xPosition) - 1;
            yCoordinate = stoi(yPosition) - 1;
            if(board[xCoordinate][yCoordinate].matched) {
                cout << "Piece already matched, try another input" << endl;
                continue;
            }

            piece temp = board[xCoordinate][yCoordinate];
            if (direction == "up") {
                if (board[xCoordinate - 1][yCoordinate].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate] = board[xCoordinate - 1][yCoordinate];
                board[xCoordinate - 1][yCoordinate] = temp;

                checkMatchAfterMove_e(board, xCoordinate, yCoordinate);
                checkMatchAfterMove_e(board, xCoordinate - 1, yCoordinate);
            }

            else if (direction == "down") {
                if (board[xCoordinate + 1][yCoordinate].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate] = board[xCoordinate + 1][yCoordinate];
                board[xCoordinate + 1][yCoordinate] = temp;

                checkMatchAfterMove_e(board, xCoordinate, yCoordinate);
                checkMatchAfterMove_e(board, xCoordinate + 1, yCoordinate);
            }

            else if (direction == "left") {
                if (board[xCoordinate][yCoordinate - 1].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate] = board[xCoordinate][yCoordinate - 1];
                board[xCoordinate][yCoordinate - 1] = temp;

                checkMatchAfterMove_e(board, xCoordinate, yCoordinate);
                checkMatchAfterMove_e(board, xCoordinate, yCoordinate - 1);
            }

            else if (direction == "right") {
                if (board[xCoordinate][yCoordinate + 1].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }
                
                board[xCoordinate][yCoordinate] = board[xCoordinate][yCoordinate + 1];
                board[xCoordinate][yCoordinate + 1] = temp;

                checkMatchAfterMove_e(board, xCoordinate, yCoordinate);
                checkMatchAfterMove_e(board, xCoordinate, yCoordinate + 1);
            }

            else if (direction == "up_left") {
                if (board[xCoordinate - 1][yCoordinate - 1].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate] = board[xCoordinate - 1][yCoordinate - 1];
                board[xCoordinate - 1][yCoordinate - 1] = temp;

                checkMatchAfterMove_e(board, xCoordinate, yCoordinate);
                checkMatchAfterMove_e(board, xCoordinate - 1, yCoordinate - 1);
            }

            else if (direction == "up_right") {
                if (board[xCoordinate - 1][yCoordinate + 1].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate] = board[xCoordinate - 1][yCoordinate + 1];
                board[xCoordinate - 1][yCoordinate + 1] = temp;

                checkMatchAfterMove_e(board, xCoordinate, yCoordinate);
                checkMatchAfterMove_e(board, xCoordinate - 1, yCoordinate + 1);
            }

            else if (direction == "down_left") {
                if (board[xCoordinate + 1][yCoordinate - 1].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate] = board[xCoordinate + 1][yCoordinate - 1];
                board[xCoordinate + 1][yCoordinate - 1] = temp;

                checkMatchAfterMove_e(board, xCoordinate, yCoordinate);
                checkMatchAfterMove_e(board, xCoordinate + 1, yCoordinate - 1);
            }

            else if (direction == "down_right") {
                if (board[xCoordinate + 1][yCoordinate + 1].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate] = board[xCoordinate + 1][yCoordinate + 1];
                board[xCoordinate + 1][yCoordinate + 1] = temp;

                checkMatchAfterMove_e(board, xCoordinate, yCoordinate);
                checkMatchAfterMove_e(board, xCoordinate + 1, yCoordinate + 1);
            }


            movesLeft--;
        }

        // printBoard(board);
    } while (movesLeft > 0);

    removeMatched_e(board);
    pieceShuffle_e(board);
}

void checkMatchAfterMove_e(piece board[5][7], int x, int y) {
    // Check left pieces
    if (y > 1 && board[x][y].num == board[x][y - 1].num && board[x][y - 1].num == board[x][y - 2].num) {
        board[x][y].matched = board[x][y - 1].matched = board[x][y - 2].matched = true;
    }
    // Check right pieces
    if (y < 5 && board[x][y].num == board[x][y + 1].num && board[x][y + 1].num == board[x][y + 2].num) {
        board[x][y].matched = board[x][y + 1].matched = board[x][y + 2].matched = true;
    }
    // Check top pieces
    if (x > 1 && board[x][y].num == board[x - 1][y].num && board[x - 1][y].num == board[x - 2][y].num) {
        board[x][y].matched = board[x - 1][y].matched = board[x - 2][y].matched = true;
    }
    // Check bottom pieces
    if (x < 3 && board[x][y].num == board[x + 1][y].num && board[x + 1][y].num == board[x + 2][y].num) {
        board[x][y].matched = board[x + 1][y].matched = board[x + 2][y].matched = true;
    }
    // Check middle piece vertically
    if (x > 0 && x < 4 && board[x - 1][y].num == board[x][y].num && board[x][y].num == board[x + 1][y].num) {
        board[x - 1][y].matched = board[x][y].matched = board[x + 1][y].matched = true;
    }
    // Check middle piece horizontally
    if (y > 0 && y < 6 && board[x][y - 1].num == board[x][y].num && board[x][y].num == board[x][y + 1].num) {
        board[x][y - 1].matched = board[x][y].matched = board[x][y + 1].matched = true;
    }
}

void removeMatched_e(piece board[5][7]) {
    string matched = "";

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j].matched) {
                int x = i;
                int y = j;
                matched += to_string(board[i][j].num) + ":[" + to_string(x + 1) + "," + to_string(y + 1) + "]  ";
                board[i][j].num = 0;
                board[i][j].matched = false;
            }
        }
    }
    cout << endl << matched << endl;
    // printBoard_e(board);
}
