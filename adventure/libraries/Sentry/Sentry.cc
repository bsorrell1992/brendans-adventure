#include <Arduino.h>
#include <stdexception>

#include "Constants.h"
#include "Sentry.h"

Sentry::Sentry(Point& position, int attackAreaLength) : _attackTimer(SENTRY_DELAY) {
    if (attackAreaLength % 2 == 0) throw std::invalid_argument("Sentry attack area length must be an odd number");
    if (attackAreaLength < 0 || attackAreaLength > 8) throw std::invalid_argument("Sentry attack area length must be between 0 and 8");

    _attackAreaLength = attackAreaLength;
    _position = position;
    _attackTimer.startTimer();
}

/*
 * The sentry doesn't move, so its move sequence only checks for the player and attacks if able
 */
void Sentry::move(Board* board) override {
    if (!_attackTimer.timeIsUp()) return;

    const int offset = (_position.x - 1) / 2;
    for (int curX = _position.x - offset; curX <= _position.x + offset; ++curX) {
        for (int curY = _position.y - offset; curY <= _position.y + offset; ++curY) {
            Entity* curEntity = (board->inBounds(curX, curY)) ? board->getEntityByPosition(curX, curY) : nullptr;
            if (curEntity != nullptr) attack(curEntity);
        }
    }
}

Entity::MoveResult Sentry::receiveMove(Entity* e) override {
    return {Entity::MoveResultCode::NEEDS_SWORD, Entity::MoveResultItem::NO_ITEM};
}

int Sentry::getKillPoints() const {
    return SENTRY_POINTS;
}

void Sentry::printName() const {
    Serial.print(F("Sentry"));
}

void Sentry::attack(Player* player) {
    player->receiveAttack(SENTRY_DAMAGE);
    _attackTimer.startTimer();
}