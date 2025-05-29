#include <stdexcept>

#include "Board.h"

BoardCode Board::_currentBoard = Board::BoardCode::SPAWN_BOARD;

Board::Board(Player* player) : _player(player) {
    switch(Board::_currentBoard) {
        case Board::BoardCode::SPAWN_BOARD:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_ONE:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_TWO:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_THREE:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_FOUR:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_FIVE:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_SIX:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_SEVEN:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_EIGHT:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_NINE:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_TEN:
            static BoardState state{};
            _state = &state;
        case Board::BoardCode::BOARD_ELEVEN:
            static BoardState state{};
            _state = &state;
        default:
            throw std::logic_error("Invalid board code");
    }
}

void Board::moveEntities() {

}

Player* Board::getPlayer() {
    return _player;
}

Entity* Board::getEntityByPosition(Point& position) {

}

void Board::getPatternFromBoard(byte pattern[ARRAY_LENGTH][ARRAY_LENGTH]) const {
    for (int i = 0; i < ARRAY_LENGTH; ++i) {
        for (int j = 0; j < ARRAY_LENGTH; ++j) {
            if (board[i][j] == nullptr) pattern[i][j] = 0;
            else pattern[i][j] = 1;
        }
    }
}

void Board::setLeft() {
    Board::_currentBoard = _left;
}

void Board::setRight() {
    Board::_currentBoard = _right;
}

void Board::setUp() {
    Board::_currentBoard = _up;
}

void Board::setDown() {
    Board::_currentBoard = _down;
}

void Board::setSpawn() {
    Board::_currentBoard = BoardCode::SPAWN_BOARD;
}