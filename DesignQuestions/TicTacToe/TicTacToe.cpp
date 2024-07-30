#include "TicTacToeBoard.h"
#include "TicTacToe.h"
#include <vector>

using namespace std;

Game::Game(int numPlayers, int boardSize, vector<string> playerNames) : numPlayers_(numPlayers) {
    if(numPlayers > Config::MAXPLAYERS) {
        throw runtime_error("Too many players");
    }

    if(boardSize > Config::MAXBOARDSIZE) {
        throw runtime_error("Board size too large");
    }

    for(int i = 0; i < numPlayers; i++) {
        Symbol symbol = Config::playerIdToSymbol.at(i);
        players.push_back(new Player(playerNames[i], symbol));
    }

    board = new TicTacToeBoard(boardSize);
    nextTurn = 0;
}

string Game::move(int playerId, int row, int col) {
    if(nextTurn != playerId) {
        throw runtime_error("Not your turn");
    }

    if(row < 0 || row >= board->boardSize() || col < 0 || col >= board->boardSize()) {
        throw runtime_error("Invalid move");
    }


    if(board->getSymbol(row, col) != Symbol::Empty) {
        return "No valid moves, please restart the game";
    }

    Gamestatus status = board->insertSymbol(row, col, Config::playerIdToSymbol.at(playerId));
    if(status == Gamestatus::Win) {
        return "Player " + players[playerId]->name() + " wins";
    }

    if(status == Gamestatus::Tie) {
        return "Game is tied";
    }
}