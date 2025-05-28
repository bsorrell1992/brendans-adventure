#include <Arduino.h>

#include "Boss.h"
#include "Constants.h"
#include "utilities.h"

Boss::Boss(Point& position) : _position(position), _moveTimer(BOSS_DELAY) {
    _moveTimer.startTimer();
}

void Boss::move(Board* board) override {
    if (!_moveTimer.timeIsUp()) return;

    Point playerPosition = board->getPlayer()->getPosition();
    Point offset{utils::sgn(playerPosition.x - _position.x), utils::sgn(playerPosition.y - _position.y)};
    if (offset.x != 0 || offset.y != y) {
        Entity* destOccupant = board->getEntityByPosition(_position + offset);
        if (destOccupant == nullptr) _position += offset;
        else attack(destOccupant);

        _moveTimer.setTimer();
    }
}

Entity::MoveResult Boss:receiveMove(Player* p) {
    return {Entity::MoveResultCode::NEEDS_SWORD, Entity::MoveResultItem::NO_ITEM};
}

int Boss::getKillPoints() const {
    return BOSS_POINTS;
}

void Boss::printName() const {
    Serial.print(F("Boss"));
}

void Boss::attack(Player* p) {
    p->receiveAttack(BOSS_DAMAGE);
}