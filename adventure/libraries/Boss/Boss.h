/*
 * Chases player and deals high damage
 * Position resets after screen changes
 */
#include "Board.h"
#include "Entity.h"
#include "Player.h"
#include "Point.h"
#include "Timer.h"

class Boss : public Entity {
public:
    Boss(Point& position);
    ~Boss() {}

    void move(Board* board) override;
    Entity::MoveResult receiveMove(Player* p);

private:
    void attack(Entity* e) {}
    void attack(Player* p);

    Point _position;
    Timer _moveTimer;
};