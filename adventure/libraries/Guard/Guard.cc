#include "Constants.h"
#include "Guard.h"

Guard::Guard(Point& position, int xOffset, int yOffset) : _attackTimer(ATTACK_DELAY), _moveTimer(GUARD_DELAY), _xOffset(xOffset), _yOffset(yOffset) {
    _position = position;

    _attackTimer.startTimer();
    _moveTimer.startTimer();
}

void Guard::move(Board* board) override {

}

Entity::MoveResult Guard::receiveMove(Entity* e) override {
    return {Entity::MoveResultCode::NEEDS_SWORD, 0};
}

void Guard::attack(Player* p) {
    if (_attackTimer.timeIsUp()) {
        p->receiveAttack(GUARD_DAMAGE);
        _attackTimer.startTimer();
    }
}