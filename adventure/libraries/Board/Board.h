#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>
#include "Constants.h"
#include "Entity.h"
#include "Player.h"
#include "Point.h"

struct BoardState {
    int bossCount;
    Point bossPos[MAX_NUM_BOSSES];

    int doorCount;
    Point doorPos[MAX_NUM_DOORS];

    int guardCount;
    Point guardPos[MAX_NUM_GUARDS];

    int itemCount;
    Point itemPos[MAX_NUM_ITEMS];

    int patrolCount;
    Point patrolPos[MAX_NUM_PATROLS];

    int sentryCount;
    Point sentryPos[MAX_NUM_SENTRIES];

    int wallCount;
    Point wallPos[MAX_NUM_WALLS];

    int breakableWallCount;
    Point bwallPos[MAX_NUM_BREAKABLE_WALLS];
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

    static BoardCode _currentBoard;

    BoardState* _state;
    BoardCode _left, _up, _down, _right;
    Player* _player;
};

#endif