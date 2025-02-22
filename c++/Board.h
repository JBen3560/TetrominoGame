#ifndef BOARD_H
#define BOARD_H

#include "GridSquare.h"
typedef long long unsigned int vInt;

class Board{
    private:
        vector<vector<GridSquare>> board;
        int Icount = 0, Lcount = 0, Tcount = 0, Scount = 0, Ocount = 0;

    public:
        Board(int x, int y);
        void runGame();
        void print();
        bool isValidInput(const string& input, int& num1, int& num2);
        bool checkWin();
        char placeTetromino(int r, int c, vector<pair<int, int>> &visited);
};

#endif