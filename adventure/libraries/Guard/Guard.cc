#include <Arduino.h>

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
    _moveStrategy.move(board, this);
}

Entity::MoveResult Guard::receiveMove(Entity* e) override {
    return {Entity::MoveResultCode::NEEDS_SWORD, 0};
}

void Guard::attack(Player* p) {
    p->receiveAttack(GUARD_DAMAGE);

    Serial.print("Guard attacked you for ");
    Serial.print(GUARD_DAMAGE);
    Serial.print("! You have ");
    Serial.print(p->getHealth());
    Serial.println(" health left.");
}

void Guard::rebound() {
    _xOffset *= -1;
    _yOffset *= -1;
}