#include "Enums.h"
#include "Config.h"

#include<vector>

using namespace std;

class TicTacToeBoard {

    Symbol board[Config::MAXBOARDSIZE][Config::MAXBOARDSIZE];
    int boardSize_;
    int emptyCells;

    bool checkWin(int row, int col) {
        Symbol symbol = board[row][col];
        bool win = true;

        for(int i = 0; i < boardSize_; i++) {
            if(board[i][col] != symbol) {
                win = false;
                break;
            }
        }

        if(win) {
            return win;
        }

        win = true;
        for(int i = 0; i < boardSize_; i++) {
            if(board[row][i] != symbol) {
                win = false;
                break;
            }
        }

        if(win) {
            return Gamestatus::Win;
        }

        win = true;
        for(int i = 0; i < boardSize_; i++) {
            if(board[i][i] != symbol) {
                win = false;
                break;
            }
        }

        if(win) {
            return true;
        }

        win = true;
        for(int i = 0; i < boardSize_; i++) {
            if(board[i][boardSize_ - i - 1] != symbol) {
                win = false;
                break;
            }
        }

        if(win) {
            return true;
        }
    }
public:
    TicTacToeBoard(int boardSize) : boardSize_(boardSize) {

        for(int i = 0; i < boardSize; i++) {
            for(int j = 0; j < boardSize; j++) {
                board[i][j] = Symbol::Empty;
            }
        }

        emptyCells = boardSize * boardSize;
    }

    int boardSize() {
        return boardSize_;
    }

    Symbol getSymbol(int row, int col) {
        return board[row][col];
    }

    Gamestatus insertSymbol(int row, int col, Symbol symbol) {
        board[row][col] = symbol;
        emptyCells--;
        bool isWon = checkWin(row, col);
        if(isWon) {
            return Gamestatus::Win;
        }

        if(emptyCells == 0) {
            return Gamestatus::Tie;
        }

        return Gamestatus::InProgress;
    }

    vector<pair<int, int>> getFreeCells() {
        vector<pair<int, int>> freeCells;

        for(int i = 0; i < boardSize_; i++) {
            for(int j = 0; j < boardSize_; j++) {
                if(board[i][j] == Symbol::Empty) {
                    freeCells.push_back({i, j});
                }
            }
        }

        return freeCells;
    }

};