#include <Arduino.h>

#include "Constants.h"
#include "Patrol.h"

Patrol::Patrol(Point& position, Point& offset) : _moveTimer(PATROL_DELAY), _position(position), _offset(offset) {
    _moveTimer.startTimer();
}

void Patrol::move(Board* board) override {
    _moveStrategy(board, this);
}

Entity::MoveResult Patrol::receiveMove(Entity* e) {
    return {Entity::MoveResultCode::NEEDS_SWORD, 0};
}

void Entity::attack(Player* p) {
    p->receiveAttack(PATROL_DAMAGE);

    Serial.print("Patrol attacked you for ");
    Serial.print(PATROL_DAMAGE);
    Serial.print("! You have ");
    Serial.print(player->getHealth());
    Serial.println(" health left.");
}

void Patrol::rebound() {
    _offset *= -1;
}