#include <Arduino.h>
#include <stdexcept>

#include "Player.h"

Player::Player() : _moveTimer(PLAYER_DELAY) {
    _moveTimer.startTimer();
}

void Player::move(Board* board) {
    if (!_moveTimer.timeIsUp()) return;

    // Get player input
    int x = analogRead(X_PIN), y = analogRead(Y_PIN);
    Point offset{0, 0};
    if (x < 500) offset.x = 1;
    if (x > 526) offset.x = -1;
    if (y < 500) offset.y = -1;
    if (y > 526) offset.y = 1;

    if (!board->inBounds(_position + offset)) return; // save data and set current board to new board
    else if (offset.x != 0 || offset.y != 0) {
        Entity* destOccupant = board->getEntityByPosition(_position + offset);
        if (destOccupant == nullptr) _position += offset;
        else {
            Entity::MoveResult moveResult = destOccupant->receiveMove(this);
            switch(moveResult.emrCode) {
                case Entity::MoveResultCode::ITEM:
                    collectItem(moveResult.emrItem);
                    break;
                case Entity::MoveResultCode::NEEDS_KEY:
                    if (_key) {
                        _position += offset;
                        board->removeEntity(destOccupant);

                        _points += DOOR_POINTS;
                        Serial.print(F("You opened the door! Go claim your treasure! +"));
                        Serial.print(DOOR_POINTS);
                        Serial.println(F(" points"));
                    } else Serial.println(F("You need the key!"));
                    break;
                case Entity::MoveResultCode::NEEDS_PICKAXE:
                    if (_pickaxe) {
                        _position += offset;
                        board->removeEntity(destOccupant);

                        _points += BREAKABLE_WALL_POINTS;
                        Serial.print(F("You broke a wall! +"));
                        Serial.print(BREAKABLE_WALL_POINTS);
                        Serial.println(F(" points"));
                    } else Serial.println(F("You need the pickaxe!"));
                    break;
                case Entity::MoveResultCode::NEEDS_SWORD:
                    if (_sword) {
                        int points = destOccupant->getKillPoints();
                        _points += points;
                        Serial.print(F("You killed a "));
                        destOccupant->printName();
                        Serial.print(F("! +"));
                        Serial.print(points);
                        Serial.println(F(" points"));

                        _position += offset;
                        board->removeEntity(destOccupant);
                    } else Serial.println(F("You cannot attack without the sword!"));
                    break;
                default:
                    Serial.println(F("Oof!"));
            }
        }

        _moveTimer.startTimer();
    }
}

void Player::receiveAttack(int damage) {
    _health -= damage / _armor;

    if (_health <= 0) {
        if (_numHealthPotions > 0) drinkHealthPotion();
        else _alive = false;
    }
}

bool Player::isAlive() const {
    return _alive;
}

void Player::revive() {
    _alive = true;
    _health = PLAYER_INITIAL_HEALTH;
}

void Player::getPoints() const {
    return _points;
}

void Player::drinkHealthPotion() {
    if (_numHealthPotions > 0) {
        _health += HEALTH_POTION_HEALING;
        --_numHealthPotions;
    } else Serial.println(F("You do not have any health potions left."));
}

void Player::useSpeedboots() {
    if (_speedboots) {
        if (!_speedbootsOn) {
            _speedbootsOn = true;
            _moveTimer.speedUp();
            Serial.println(F("You have put on your speed boots. You are now moving twice as fast!"));
        } else Serial.println(F("You are already wearing your speed boots!"));  // shouldn't occur during normal play
    } else Serial.println(F("You do not have the speed boots."));
}

void Player::removeSpeedboots() {
    if (_speedboots) {
        if (_speedbootsOn) {
            _speedbootsOn = false;
            _moveTimer.slowDown();
            Serial.println(F("You have taken off your speed boots. You are now moving at your original speed."));
        } else Serial.println(F("You are not wearing your speed boots!"));      // shouldn't occur during normal play
    } else Serial.println(F("You do not have the speed boots."));
}

void Player::collectItem(Entity::MoveResultItem itemCode) {
    _points += ITEM_POINTS;

    switch(itemCode) {
        case Entity::MoveResultItem::ARMOR:
            ++_armor;
            Serial.print(F("You grabbed the armor! +"));
            Serial.print(ITEM_POINTS);
            break;
        case Entity::MoveResultItem::HEALTH_POTION:
            ++_numHealthPotions;
            Serial.print(F("You grabbed a health potion! +"));
            Serial.print(ITEM_POINTS);
            break;
        case Entity::MoveResultItem::KEY:
            _key = true;
            Serial.print(F("You grabbed the key! +"));
            Serial.print(ITEM_POINTS);
            break;
        case Entity::MoveResultItem::PICKAXE:
            _pickaxe = true;
            Serial.print(F("You grabbed the pickaxe! +"));
            Serial.print(ITEM_POINTS);
            break;
        case Entity::MoveResultItem::SPEEDBOOTS:
            _speedboots = true;
            _moveTimer.speedUp();
            Serial.print(F("You have picked up the speed boots! Enter U to put them on and again to take them off. +"));
            Serial.print(ITEM_POINTS);
            break;
        case Entity::MoveResultItem::SWORD:
            _sword = true;
            Serial.print(F("You grabbed the sword! +"));
            Serial.print(ITEM_POINTS);
            break;
        case Entity::MoveResultItem::TREASURE:
            _treasure = true;
            _points += TREASURE_POINTS;
            Serial.print(F("You grabbed the treasure! +"));
            Serial.print(ITEM_POINTS + TREASURE_POINTS);
            break;
        default:
            throw std::runtime_error("Invalid item type");
    }

    Serial.println(F(" points"));
}