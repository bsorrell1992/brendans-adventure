/*
 * Moves back and forth in front of an entrance
 * Movement is perpendicular to corridor
 */
#include "Board.h"
#include "BouncingLinearMovementStrategy.h"
#include "Entity.h"
#include "Player.h"
#include "Point.h"
#include "Timer.h"

class Guard : public Entity {
public:
    friend class BouncingLinearMovementStrategy;

    Guard(Point& position, Point& offset);
    ~Guard() {};

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