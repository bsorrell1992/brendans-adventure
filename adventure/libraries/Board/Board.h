#include <Arduino.h>

#include "Entity.h"
#include "Player.h"
#include "Point.h"

struct BoardState {

};

class Board {
public:
    Board(Player* player);
    ~Board() {}

    void moveEntities();

    Player* getPlayer();
    Entity* getEntityByPosition(Point& position);
    void getPatternFromBoard(byte pattern[ARRAY_LENGTH][ARRAY_LENGTH]) const;

    void setLeft();
    void setRight();
    void setUp();
    void setDown();
    void setSpawn();

private:
    enum class BoardCode {
        NO_BOARD,
        SPAWN_BOARD,
        BOARD_ONE,
        BOARD_TWO,
        BOARD_THREE,
        BOARD_FOUR,
        BOARD_FIVE,
        BOARD_SIX,
        BOARD_SEVEN,
        BOARD_EIGHT,
        BOARD_NINE,
        BOARD_TEN,
        BOARD_ELEVEN
    };

    static BoardCode _currentBoard = Board::BoardCode::NO_BOARD;

    BoardState _state;
    BoardCode _left, _up, _down, _right;
    Player* _player;
};

/*
    class Board : public Printable {
    private:
    Board *top, *right, *down, *left;

    public:
    Entity* board[ARRAY_LENGTH][ARRAY_LENGTH];

    Board(Entity* board[ARRAY_LENGTH][ARRAY_LENGTH], Board* top, Board* right, Board* down, Board* left) {
        memcpy(this->board, board, sizeof(Entity*) * ARRAY_LENGTH * ARRAY_LENGTH);
        this->top = top;
        this->right = right;
        this->down = down;
        this->left = left;
    }

    Board(Entity* board[ARRAY_LENGTH][ARRAY_LENGTH]) : Board(board, nullptr, nullptr, nullptr, nullptr) {}

    ~Board() {
        for (int i = 0; i < ARRAY_LENGTH; ++i) {
        for (int j = 0; j < ARRAY_LENGTH; ++j)
            if (board[i][j] != nullptr) delete board[i][j];
        }
    }

    Board* getTop() { return top; }
    Board* getRight() { return right; }
    Board* getDown() { return down; }
    Board* getLeft() { return left; }
    void setTop(Board* top) { this->top = top; }
    void setRight(Board* right) { this->right = right; }
    void setDown(Board* down) { this->down = down; }
    void setLeft(Board* left) { this->left = left; }

    void getPatternFromBoard(byte pattern[ARRAY_LENGTH][ARRAY_LENGTH]) {
        for (int i = 0; i < ARRAY_LENGTH; ++i) {
        for (int j = 0; j < ARRAY_LENGTH; ++j) {
            if (board[i][j] == nullptr) pattern[i][j] = 0;
            else pattern[i][j] = 1;
        }
        }
    }

    size_t printTo(Print& p) const {
        size_t r = 0;
        for (int i = 0; i < ARRAY_LENGTH; ++i) {
        for (int j = 0; j < ARRAY_LENGTH; ++j) {
            if (board[j][i] != nullptr) {
            r += p.print(board[j][i]->getType());
            r += p.print(" ");
            } else {
            r += p.print("null ");
            }
        }
        r += p.print("\n");
        }
    }
    };
*/