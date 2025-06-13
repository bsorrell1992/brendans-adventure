/*
 * Enemy which does not move
 * Deals high damage in an area around it at intervals
 */
#ifndef SENTRY_H
#define SENTRY_H

#include "Entity.h"
#include "Player.h"
#include "Point.h"
#include "Timer.h"

class Sentry : public Entity {
public:
    Sentry(Point& position, int attackAreaLength);
    ~Sentry() {};
    void move(Board* board) override;
    Entity::MoveResult receiveMove(Entity* e) override;

    int getKillPoints() const;
    void printName() const;

private:
    void attack(Entity* e) {};
    void attack(Player* p);

    Timer _attackTimer;
    int _attackAreaLength;
    Point _position;
};

#endif