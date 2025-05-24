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

void Sentry::move(Board* board) override {
    const int offset = (_position.x - 1) / 2;
    for (int row = _position.y - offset; row <= _position.y + offset; ++row) {
        for (int col = _position.x - offset; col <= _position.x + offset; ++col) {
            Entity* curEntity = board->getEntity(row, col);
            if (curEntity != nullptr) attack(curEntity);
        }
    }
}

Entity::MoveResult Sentry::receiveMove(Entity* e) override {
    return {Entity::MoveResultCode::NEEDS_SWORD, 0};
}

void Sentry::attack(Player* player) {
    if (_attackTimer.timeIsUp()) {
        player->receiveAttack(SENTRY_DAMAGE);
        _attackTimer.startTimer();
    }
}