#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Cell {
public:
    int row;
    int col;
    bool operator==(const Cell& other) const {
        return row == other.row && col == other.col;
    }
};

// Define a custom hash function for Cell
struct CellHash {
    size_t operator()(const Cell& cell) const {
        // Combine row and col into a single hash value
        return hash<int>()(cell.row) ^ (hash<int>()(cell.col) << 1);
    }
};

class Piece {
    string color_;

public:
    Piece() {}
    Piece(string color) : color_(color) {}
    virtual bool isMoveValid(Cell start, Cell end, unordered_map<Cell, Piece*, CellHash> & pieces) = 0;
};

class Pawn : public Piece {
public:
    Pawn() {}
    Pawn(string color) : Piece(color) {}
    virtual bool isMoveValid(Cell start, Cell end, unordered_map<Cell, Piece*, CellHash> & pieces) override {
        // Validate based on piece type, any pieces in position?
    }
};

// To implement castling, use isMoved attribute.
class King : public Piece {
    bool isMoved;
};

class Rook : public Piece {
    bool isMoved;
};

class Player {
    int id;
    string color;
    int score;
};

enum GameStatus {
    NotStarted,
    Started,
    Ended
};

enum PieceType {
    PawnPiece,
    RookPiece,
    KnightPiece,
    BishopPiece,
    QueenPiece,
    KingPiece
};


class PieceFactory {

public:
    static Piece* createPiece(PieceType pieceType, string color) {
        if(pieceType == PieceType::PawnPiece) {
            Piece* piece = new Pawn(color);
            return piece;
        }
    }
};

class ChessGame {

    int numPlayers_;
    int boardSize_;
    int turn_;
    vector<Player> players_;
    unordered_map<Cell, Piece*, CellHash> pieces_;
    GameStatus status_;

public:
    ChessGame(int numPlayers, int boardSize) : boardSize_(boardSize), numPlayers_(numPlayers) {
        status_ = NotStarted;
        // Initialize players, pieces.
    }

    void move(int playerId, Cell start, Cell end) {
        // Validate based on player id and turn.
        // If start or end is out of bounds.
        // If start doesn't have a piece.
        Piece* piece = pieces_[start];
        if(piece->isMoveValid(start, end, pieces_)) {
            pieces_[end] = piece;
            pieces_.erase(start);
        }
    }

    // Check if Cell end has the pawn.
    // Use PieceFactory to create pieceType object.
    // Place it at end position;
    void swapPawn(Cell end, PieceType pieceType) {

    }
};