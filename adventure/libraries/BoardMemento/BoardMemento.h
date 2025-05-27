/*
 * Used to store entity state between loops
 */
#include "Board.h"

class BoardMemento {
private:
    friend class Board;

    BoardMemento(BoardState* state);
    BoardState& getState() const;

    BoardState _state;
};