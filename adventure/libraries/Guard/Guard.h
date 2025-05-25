/*
 * Moves back and forth in front of an entrance
 * Movement is perpendicular to corridor
 */
#include "BouncingLinearMovementStrategy.h"
#include "Entity.h"
#include "Point.h"
#include "Timer.h"

class Guard : public Entity {
public:
    friend class BouncingLinearMovementStrategy;

    Guard(Point& position, int xOffset, int yOffset);
    ~Guard() {};

    void move(Board* board) override;
    Entity::MoveResult receiveMove(Entity* e) override;

private:
    void attack(Entity* e) {}
    void attack(Player* p);

    void rebound();

    BouncingLinearMovementStrategy _moveStrategy;
    Timer _moveTimer;

    Point _position;
    int _xOffset;
    int _yOffset;
};