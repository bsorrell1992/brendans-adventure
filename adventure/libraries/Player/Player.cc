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
                    } else Serial.println(F("You need the key!"));
                    break;
                case Entity::MoveResultCode::NEEDS_PICKAXE:
                    if (_pickaxe) {
                        _position += offset;
                        board->removeEntity(destOccupant);
                    } else Serial.println(F("You need the pickaxe!"));
                    break;
                case Entity::MoveResultCode::NEEDS_SWORD:
                    if (_sword) {
                        _position += offset;
                        board->removeEntity(destOccupant);
                    } else Serial.println(F("You cannot attack without the sword!"));
                    break;
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
        } else Serial.println(F("You are already wearing your speed boots!"));
    } else Serial.println(F("You do not have the speed boots."));
}

void Player::removeSpeedboots() {
    if (_speedboots) {
        if (_speedbootsOn) {
            _speedbootsOn = false;
            _moveTimer.slowDown();
            Serial.println(F("You have taken off your speed boots. You are now moving at your original speed."));
        } else Serial.println(F("You are not wearing your speed boots!"));
    } else Serial.println(F("You do not have the speed boots."));
}

void Player::collectItem(Entity::MoveResultItem itemCode) {
    switch(itemCode) {
        case Entity::MoveResultItem::ARMOR:
            ++_armor;
            break;
        case Entity::MoveResultItem::HEALTH_POTION:
            ++_numHealthPotions;
            break;
        case Entity::MoveResultItem::KEY:
            _key = true;
            break;
        case Entity::MoveResultItem::PICKAXE:
            _pickaxe = true;
            break;
        case Entity::MoveResultItem::SPEEDBOOTS:
            _speedboots = true;
            _moveTimer.speedUp();
            Serial.print(F("You have picked up the speed boots. You are now moving twice as fast!"));
            break;
        case Entity::MoveResultItem::SWORD:
            _sword = true;
            break;
        case Entity::MoveResultItem::TREASURE:
            _treasure = true;
            break;
        default:
            throw std::runtime_error("Invalid item type");
    }
}

/*
    inline void Player::move(int dx, int dy) {
        Board* destBoard = currentBoard;
        int destX = x + dx;
        int destY = y + dy;

        // Determine which board the player is moving into
        if (destX < 0) {
            destBoard = destBoard->getLeft();
            destX = ARRAY_LENGTH - 1;
        } else if (destX >= ARRAY_LENGTH) {
            destBoard = destBoard->getRight();
            destX = 0;
        }
        if (destY < 0 && destBoard != nullptr) {
            destBoard = destBoard->getDown();
            destY = 0;
        } else if (destY >= ARRAY_LENGTH && destBoard != nullptr) {
            destBoard = destBoard->getTop();
            destY = ARRAY_LENGTH - 1;
        }

        if (destBoard != nullptr) {
            Entity* e = destBoard->board[destX][destY];
            String eType = e->getType();
            if (e == nullptr) {
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            currentBoard = destBoard;
            x = destX;
            y = destY;
            } else if (eType == "guard") {
            if (!sword) {
                Guard* g = destBoard->board[destX][destY];
                if (g->timeToAttack()) g->attack();
            } else {
                addPoints(GUARD_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                printKill(eType);
            }
            } else if (eType == "patrol") {
            if (!sword) {
                Patrol* p = destBoard->board[destX][destY];
                if (p->timeToAttack()) p->attack();
            } else {
                addPoints(PATROL_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                printKill(eType);
            }
            } else if (eType == "sentry") {
            if (!sword) {
                Sentry* s = destBoard->board[destX][destY];
                if (s->timeToAttack()) s->attack();
            } else {
                addPoints(SENTRY_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                printKill(eType);
            }
            } else if (eType == "boss") {
            if (!sword) {
                Boss* b = destBoard->board[destX][destY];
                if (b->timeToAttack()) b->attack();
            } else {
                addPoints(BOSS_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                printKill(eType);
            }
            } else if (eType == "key") {
            grabKey();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Key!");
            } else if (eType == "sword") {
            grabSword();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Sword!");
            } else if (eType == "pickaxe") {
            grabPickaxe();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Pickaxe!");
            } else if (eType == "speedboots") {
            grabSpeedBoots();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Speed boots!");
            } else if (eType == "healthpotion") {
            grabHealthPotion();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("Health potion!");
            } else if (eType == "armor") {
            grabArmor();
            addPoints(ITEM_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;
            Serial.println("You grabbed the armor!");
            } else if (eType == "wall") {
            Wall* w = destBoard->board[destX][destY];
            if (w->isBreakable() && pickaxe) {
                addPoints(BREAKABLE_WALL_POINTS);
                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                Serial.print("You broke a wall!");
            } else {
                Serial.println("Oof!");
            }
            } else if (eType == "door") {
            if (key) {
                addPoints(DOOR_POINTS);

                // Remove all door objects from board
                for (int i = 0; i < ARRAY_LENGTH; ++i) {
                Entity* e = destBoard->board[i][destY];
                if (e != nullptr && e->getType() == "door") destBoard->board[i][destY] = nullptr;
                }

                destBoard->board[destX][destY] = player;
                currentBoard->board[x][y] = nullptr;
                x = destX;
                y = destY;
                Serial.print("You opened the door! Go claim your treasure!");
            } else {
                Serial.println("You need the key!");
            }
            } else if (eType == "treasure") {
            grabTreasure();
            addPoints(TREASURE_POINTS);
            destBoard->board[destX][destY] = player;
            currentBoard->board[x][y] = nullptr;
            x = destX;
            y = destY;

            // Fill edges of board with walls
            for (int i = 0; i < ARRAY_LENGTH; ++i) {
                destBoard->board[i][0] = &wall;
                destBoard->board[i][ARRAY_LENGTH - 1] = &wall;
            }
            for (int i = 1; i < ARRAY_LENGTH - 1; ++i) {
                destBoard->board[0][i] = &wall;
                destBoard->board[ARRAY_LENGTH - 1][i] = &wall;
            }

            Serial.print("Treasure! Your total is ");
            Serial.print(points);
            }
        }

        startMoveTimer();
    }
*/