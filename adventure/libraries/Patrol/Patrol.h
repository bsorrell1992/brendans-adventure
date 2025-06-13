/*
 * Wanders back and forth through corridor
 * Movement is parallel to corridor
 */
#ifndef PATROL_H
#define PATROL_H

#include "Board.h"
#include "BouncingLinearMovementStrategy.h"
#include "Entity.h"
#include "Player.h"
#include "Point.h"
#include "Timer.h"

class Patrol : public Entity {
public:
    friend class BouncingLinearMovementStrategy;

    Patrol(Point& position, Point& offset);
    ~Patrol() {};

    void move(Board* board) override;
    Entity::MoveResult receiveMove(Entity* e) override;

    int getKillPoints() const;
    void printName() const;

private:
    void attack(Entity* e) {}
    void attack(Player* p);

    void rebound();

    BouncingLinearMovementStrategy _moveStrategy;
    Timer _moveTimer;

    Point _position;
    Point _offset;
};

#endif