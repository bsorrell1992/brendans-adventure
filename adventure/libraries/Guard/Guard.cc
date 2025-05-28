#include <Arduino.h>

#include "Constants.h"
#include "Guard.h"

Guard::Guard(Point& position, Point& offset) : _moveTimer(GUARD_DELAY), _position(position), _offset(offset) {
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
    return {Entity::MoveResultCode::NEEDS_SWORD, Entity::MoveResultCode::NO_ITEM};
}

int Guard::getKillPoints() const {
    return GUARD_POINTS;
}

void Guard::printName() const {
    Serial.print(F("Guard"));
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
    _offset *= -1;
}