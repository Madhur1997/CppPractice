#include<unordered_map>

using namespace std;

enum GameStatus {
    NOT_STARTED,
    IN_PROGRESS,
    FINISHED
};

class Board {
    unordered_map<int, int> snakesAndLadders;
    unordered_map<int, Player*> players;

public:
    Board(vector<pair<int, int>> & snakesAndLadders, vector<Player*> & players) {
        for(auto & snakeOrLadder : snakesAndLadders) {
            this->snakesAndLadders[snakeOrLadder.first] = snakeOrLadder.second;
        }
        for(auto & player : players) {
            this->players[player->playerId] = player;
        }
    }

    int move(int playerId, int diceValue) {
        Player* player = players[playerId];
        int currPos = player->getPosition();
        int newPos = currPos + diceValue;
        if(snakesAndLadders.find(newPos) != snakesAndLadders.end()) {
            newPos = snakesAndLadders[newPos];
        }
        player->setPosition(newPos);
        return newPos;        
    }
};

class Player {
    int playerId;
    string playerName;
    string color;
    int position;

public:
    int getPosition() {
        return position;
    }

    int setPosition(int pos) {
        position = pos;
    }
};

class SnakeAndLadder {
    Board* board;
    int players;
    int playerToMove;
    enum GameStatus status;
public:
    SnakeAndLadder() {
        board = new Board(snakesAndLadders, players);
        status = GameStatus::NOT_STARTED;
    }
    int move(int playerId, int diceValue) {
        // Validations

        if(status == FINISHED) {
            // Return Error code 500, game finished.
            return -1;
        }

        if( playerId != playerToMove ) {
            // Return Error code 400, invalid user.
            return -1;
        }

        int newPos = board->move(playerId, diceValue);
        status = GameStatus::IN_PROGRESS;
        if(newPos == 100) {
            // Return 200, game finished.
            status = GameStatus::FINISHED;
            return 200;
        }

        return newPos;
    }
};

int main() {

    return 0;
}