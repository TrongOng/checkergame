#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//global variables
char board[8][8];
char newBoard[8][8];
char blackPiece = 'b';
char redPiece = 'r';
char empty = '+';
char invalidSlot = '.';
char kingBlack = 'B'; 
char kingRed = 'R';

//initialize checkerboard
class checkerBoard {
    public:
    //init board with pieces
        void initBoard() {
            for (int y = 0; y < 3; y++) { //loop first row (y)
                for (int x = 0; x < 8; x++) { //loop first column (x)
                //pieces can only move on black sqaures
                    if (((x + y) % 2) == 0) { //odd row (white) <-note x + y (looking bottom to up)
                        board[y][x] = invalidSlot;
                    }
                    else { //even row (black) <- top to bottom
                        board[y][x] = redPiece;
                        
                    }
                }
            }
            for (int y = 3; y < 5; y++) {
                for (int x = 0; x < 8; x++) {
                    if (((x + y) % 2) == 0) {
                        board[y][x] = invalidSlot;
                    }
                    else {
                        board[y][x] = empty;
                    }
                }
            }
            for (int y = 5; y < 8; y++) {
                for (int x = 0; x < 8; x++) {
                    if (((x + y) % 2) == 0) {
                        board[y][x] = invalidSlot;
                    }
                    else {
                        board[y][x] = blackPiece;
                    }
                }
            }

        }
        //print board
        void printBoard() {
            cout << "+===============================================+\n";
            cout << "  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n";
            cout << "-----------------------------------\n";
            for (int y = 0; y < 8; y++) {
                cout << y << " | ";
                for (int x = 0; x < 8; x++) {
                    cout << board[y][x] << " | ";
                }
                cout << endl << "-----------------------------------" << endl;
            }
            cout << "+===============================================+\n";
        }
        //print new board
        void printnewBoard() {
            cout << "+===============================================+\n";
            cout << "  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n";
            cout << "-----------------------------------\n";
            for (int y = 0; y < 8; y++) {
                cout << y << " | ";
                for (int x = 0; x < 8; x++) {
                    cout << newBoard[y][x] << " | ";
                }
                cout << endl << "-----------------------------------" << endl;
            }
            cout << "+===============================================+\n";
        }
};
//bool gameOver; end game
bool gameOver(void) {
    bool winner = false;
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((newBoard[y][x] != blackPiece && newBoard[y][x] != kingBlack) || (newBoard[y][x] != redPiece && newBoard[y][x] != kingRed)) {
                return winner = true;

            }
            else {
                return winner = false;
            }
        }
    }
}
//red legal move
void redMove() {
    int pieceX; //original x cord
    int pieceY; //original y cord
    int moveX; //new x cord
    int moveY; //new y cord
    int decision;
    int playerOne; //score

    checkerBoard checkerboard;
    cout << "Player One Turn: \n"; //loop between the two (red piece first)
    cout << "Pick the piece you want to move\n";
    while (bool a = true) {
        cout << "Type Orignal X-Cord: \n";
        cin >> pieceX;
        cout << "Type Orignal Y-Cord: \n";
        cin >> pieceY;
        cout << "Type New X-Cord: \n";
        cin >> moveX;
        cout << "Type New Y-Cord: \n";
        cin >> moveY;
        if (newBoard[moveY][moveX] == empty && ((moveY == pieceY+1 && (moveX == pieceX+1 || moveX == pieceX-1)) || newBoard[pieceY][pieceX] == kingRed || (moveY == pieceY+2 && (moveX == pieceX+2 || moveX == pieceX-2)))) { //full condition
            cout << "Legal Move\n";
            if (newBoard[(pieceY + moveY)/2][(pieceX + moveX)/2] == blackPiece && (moveY == pieceY+2 && (moveX == pieceX+2 || moveY == pieceY-2))) { //capturing
                if (newBoard[pieceY][pieceX] == redPiece) { //red pawn capturing
                //if moveY = 7 and newBod is empty
                    if (newBoard[moveY][moveX] == empty && moveY == 7) { //pawn becomes king while capture
                            newBoard[(pieceY + moveY)/2][(pieceX + moveX)/2] = empty;
                            newBoard[pieceY][pieceX] = empty;
                            newBoard[moveY][moveX] = kingRed;
                            cout << "One Point For Player One\n";
                            playerOne += 1;
                            checkerboard.printnewBoard();
                            cout << "Would You Want To Jump Again [IF POSSIBLE]\n";
                            cout << "1.[Yes]\n2.[No]\n";
                            cin >> decision;
                            if (decision == 1) {
                                continue;
                            }
                            else {
                                break;
                            }
                    }
                    else { //regular capture
                        newBoard[pieceY][pieceX] = empty; //set old position to empty
                        newBoard[moveY][moveX] = redPiece; //set destination red piece 
                        newBoard[(pieceY + moveY)/2][(pieceX + moveX)/2] = empty; //set enemy empty
                        playerOne += 1; //add score
                        cout << "One Point For Player One\n";
                        checkerboard.printnewBoard();
                        cout << "Would You Want To Jump Again [IF POSSIBLE]\n";
                        cout << "1.[Yes]\n2.[No]\n";
                        cin >> decision;
                        if (decision == 1) {
                            continue;
                        }
                        else {
                            break;
                        }
                    }
                }
                else if (newBoard[pieceY][pieceX] == kingRed) { //if piece is king red
                    newBoard[pieceY][pieceX] = empty; //set old position to empty
                    newBoard[moveY][moveX] = kingRed; //set destination king red
                    newBoard[(pieceY + moveY)/2][(pieceX + moveX)/2] = empty; //set enemy empty
                    cout << "One Point For Player One\n";
                    playerOne += 1; //add score to player
                    checkerboard.printnewBoard();
                    cout << "Would You Want To Jump Again [IF POSSIBLE]\n";
                    cout << "1.[Yes]\n2.[No]\n";
                    cin >> decision;
                    if (decision == 1) {
                        continue;
                    }
                    else {
                        break;
                    }
                }
            }
            else if (((newBoard[pieceY][pieceX] == redPiece) && (moveY == pieceY+1 && (moveX == pieceX+1 || moveX ==pieceX-1))) || newBoard[pieceY][pieceX] == kingRed) { //regular moving
                //king creation
                if (newBoard[moveY][moveX] == empty && moveY == 7) { 
                        newBoard[pieceY][pieceX] = empty;
                        newBoard[moveY][moveX] = kingRed;
                        checkerboard.printnewBoard();
                        break;
                    }
                //regular move
                else if (newBoard[pieceY][pieceX] == redPiece) {
                    newBoard[pieceY][pieceX] = empty;
                    newBoard[moveY][moveX] = redPiece;
                    checkerboard.printnewBoard();
                    break;
                }
                //king move
                else if (newBoard[pieceY][pieceX] == kingRed) {  
                    newBoard[pieceY][pieceX] = empty; //set old position to empty
                    newBoard[moveY][moveX] = kingRed;
                    checkerboard.printnewBoard();
                    break;
                }
            }
        }
        else {
            cout << "Incorrect Cordination, Try Again!\n";
            checkerboard.printnewBoard();
            a = true;
        }
    }
}
void blackMove() {
    int pieceX;
    int pieceY;
    int moveX;
    int moveY;
    int decision;
    int playerTwo;
    checkerBoard checkerboard;

    cout << "Player Two Turn: \n"; 
    cout << "Pick The Piece You Wish To Move...\n";
    while (bool a = true) {
        cout << "Type Orignal X-Cord: \n";
        cin >> pieceX;
        cout << "Type Orignal Y-Cord: \n";
        cin >> pieceY;
        cout << "Type New X-Cord: \n";
        cin >> moveX;
        cout << "Type New Y-Cord: \n";
        cin >> moveY;
        if (newBoard[moveY][moveX] == empty && ((moveY == pieceY-1 && (moveX == pieceX+1 || moveX ==pieceX-1)) || newBoard[pieceY][pieceX] == kingBlack || (moveY == pieceY-2 && (moveX == pieceX+2 || moveX == pieceX-2)))) { 
            cout << "Legal Move, Continuing....\n";
            if (newBoard[(pieceY + moveY)/2][(pieceX + moveX)/2] == redPiece && (moveY == pieceY-2 && (moveX == pieceX+2 || moveY == pieceY-2))) { //capturing
                if (newBoard[pieceY][pieceX] == blackPiece) {  //when piece is blackPiece
                    if (newBoard[moveY][moveX] == empty && moveY == 0) {  //capturing and promotion
                            newBoard[(pieceY + moveY)/2][(pieceX + moveX)/2] = empty;
                            newBoard[pieceY][pieceX] = empty;
                            newBoard[moveY][moveX] = kingBlack;
                            cout << "One Point For Player Two\n";
                            playerTwo += 1;
                            checkerboard.printnewBoard();
                            cout << "Would You Want To Jump Again [IF POSSIBLE]\n";
                            cout << "1.[Yes]\n2.[No]\n";
                            cin >> decision;
                            if (decision == 1) {
                                continue;
                            }
                            else {
                                break;
                            }
                    }
                    else { //regular capture
                        newBoard[pieceY][pieceX] = empty; //set old position to empty
                        newBoard[moveY][moveX] = blackPiece;
                        newBoard[(pieceY + moveY)/2][(pieceX + moveX)/2] = empty;
                        checkerboard.printnewBoard();
                        cout << "One Point For Player Two\n";
                        playerTwo += 1;
                        cout << "Would You Want To Jump Again [IF POSSIBLE]\n";
                        cout << "1.[Yes]\n2.[No]\n";
                        cin >> decision;
                        if (decision == 1) {
                            continue;
                        }
                        else {
                            break;
                        }
                    }
                }
                else if (newBoard[pieceY][pieceX] == kingBlack) { //if piece is king black
                    newBoard[pieceY][pieceX] = empty; //set old position to empty
                    newBoard[moveY][moveX] = kingBlack;
                    newBoard[(pieceY + moveY)/2][(pieceX + moveX)/2] = empty;
                    checkerboard.printnewBoard();
                    cout << "One Point For Player Two\n";
                    playerTwo += 1;
                    cout << "Would You Want To Jump Again [IF POSSIBLE]\n";
                    cout << "1.[Yes]\n2.[No]\n";
                    cin >> decision;
                    if (decision == 1) {
                        continue;
                    }
                    else {
                        break;
                    }
                }
            }
            else if (((newBoard[pieceY][pieceX] == blackPiece) && (moveY == pieceY-1 && (moveX == pieceX+1 || moveX ==pieceX-1))) || newBoard[pieceY][pieceX] == kingBlack) { //regular move
                //king creation
                if (newBoard[moveY][moveX] == empty && moveY == 0) { 
                        newBoard[pieceY][pieceX] = empty;
                        newBoard[moveY][moveX] = kingBlack;
                        checkerboard.printnewBoard();
                        break;
                } 
                //regular move
                else if (newBoard[pieceY][pieceX] == blackPiece) {
                    newBoard[pieceY][pieceX] = empty;
                    newBoard[moveY][moveX] = blackPiece;
                    checkerboard.printnewBoard();
                    break;
                }
                //king move
                else if (newBoard[pieceY][pieceX] == kingBlack) {  
                    newBoard[pieceY][pieceX] = empty; //set old position to empty
                    newBoard[moveY][moveX] = kingBlack;
                    checkerboard.printnewBoard();
                    break;
                }
            }
        }
        else {
            cout << "Incorrect Cordination, Try Again!\n";
            checkerboard.printnewBoard();
            a = true;
        }
    }
}
int main() {
    int choice; //player team choice
    int begin; //start game
    int playerOne;
    int playerTwo;
    checkerBoard checkerboard;
    cout << "+===============================================+\n";
    cout << "Welcome To The CheckerBoard Game\n";
    cout << "[NOTE]\n";
    cout << "Red Pawn = r  Black Pawn = b\n";
    cout << "Red King = R  Black King = B\n";
    cout << "Invalid Slot = '.' Valid Slot = '*'\n";
    cout << "Would You Like To Begin?...\n1.[YES]\n2.[NO]\n";
    cout << "+===============================================+\n";
    cin >> begin;
    if (begin == 1) {
        cout << "Checker Board\n";
        checkerboard.initBoard();
        checkerboard.printBoard();
        //init new board to equal to standard board
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                newBoard[y][x] = board[y][x]; //back board
            }
        }
        //set player to piece
        cout << "Pick Which Team\n1.[Red]\n2.[Black]\n";
        cin >> choice;
        if (choice == 1) {
            cout << "Player One is Red Team\n";
            cout << "Player Two is Black Team\n";
        }
        else {
            cout << "Player One is Red Team\n";
            cout << "Player Two is Black Team\n";
        }
        do {
            int pieceX;
            int pieceY;
            int moveX;
            int moveY;
            int decision; //to jump again            
            int playerOne = 0;
            int playerTwo = 0;

            for (int i = 0; i < 25; i++) {
                redMove();
                checkerboard.printnewBoard();
                blackMove();
                checkerboard.printnewBoard();
            }
        }
        while (!gameOver());
        cout << "Score: \n" << "PlayerOne " + playerOne << endl << "PlayerTwo " + playerTwo << endl;

    }
    else {
        cout << "+===============================================+\n"; 
        cout << "[GOODBYE]\n";
        cout << "[HOPE TO SEE YOU AGAIN]\n";
        cout << "+===============================================+\n";
        return 0;
    }
}