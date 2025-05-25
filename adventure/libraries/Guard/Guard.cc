#include "Constants.h"
#include "Guard.h"

Guard::Guard(Point& position, int xOffset, int yOffset) : _moveTimer(GUARD_DELAY), _xOffset(xOffset), _yOffset(yOffset) {
    _position = position;

    _moveTimer.startTimer();
}

/*
 * The algorithm for guard movement is as follows:
 *      - The guard first turns around if the next square is out of bounds
 *      - Then it attacks if possible and turns around again
 *      - Finally, it moves into the next square if allowed
 */
void Guard::move(Board* board) override {
    if (!_moveTimer.timeIsUp()) return;
    
    if (!board->inBounds(_position.x + _xOffset, _position.y + _yOffset)) rebound();

    int toX = _position.x + _xOffset;
    int toY = _position.y + _yOffset;
    Entity* destOccupant = board->getEntityByPosition(toX, toY);
    if (destOccupant != nullptr) {
        attack(destOccupant);
        
        rebound();
        toX = _position.x + _xOffset;
        toY = _position.y + _yOffset;
    }

    if (board->inBounds(toX, toY)) {
        _position.x = toX;
        _position.y = toY;
    }

    _moveTimer.startTimer();
}

Entity::MoveResult Guard::receiveMove(Entity* e) override {
    return {Entity::MoveResultCode::NEEDS_SWORD, 0};
}

void Guard::attack(Player* p) {
    p->receiveAttack(GUARD_DAMAGE);
    _attackTimer.startTimer();
}

void Guard::rebound() {
    _xOffset *= -1;
    _yOffset *= -1;
}