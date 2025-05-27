#include "BoardMemento.h"

BoardMemento::BoardMemento(BoardState& state) : _state(state) {}

BoardState& BoardMemento::getState() const {
    return _state;
}