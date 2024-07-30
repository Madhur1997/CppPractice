#include<iostream>
#include<list>
#include<vector>
#include<unordered_map>
#include "TicTacToeBoard.h"
#include "Player.h"

using namespace std;

/* Design a Tic Tac Toe game:
FR:
1. 2 or more players can play the game.
2. 2 or more symbols.
*/


// Create singleton
class Game {
    TicTacToeBoard* board;
    vector<Player*> players;
    static Game* instance;
    int numPlayers_;
    int nextTurn;

    Game() = delete;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    Game(int, int, vector<string>);

public:

    static Game* getInstance(int numPlayers, int boardSize, vector<string> playerNames) {
        if(instance == nullptr) {
            instance = new Game(numPlayers, numPlayers, playerNames);
        }
        return instance;
    }

    string move(int playerId, int row, int col);
};