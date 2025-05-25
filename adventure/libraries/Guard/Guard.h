/*
 * Moves back and forth in front of an entrance
 * Movement is perpendicular to corridor
 */
#include "Entity.h"
#include "Point.h"
#include "Timer.h"

class Guard : public Entity {
public:
    Guard(Point& position, int xOffset, int yOffset);
    ~Guard() {};

    void move(Board* board) override;
    Entity::MoveResult receiveMove(Entity* e) override;

private:
    void attack(Entity* e) {}
    void attack(Player* p);

    void rebound();

    Timer _moveTimer;

    Point _position;
    int _xOffset;
    int _yOffset;
};

/*
    class Guard : public MovingEntity {
    private:
    bool horizontal;
    bool vertical;
    int direction;

    public:
    Guard(bool horizontal, bool vertical, int direction) : MovingEntity("guard", GUARD_DELAY) {
        this->horizontal = horizontal;
        this->vertical = vertical;
        this->direction = direction;

        startMoveTimer();
        startAttackTimer();
    }

    void attack() {
        player->takeDamage(GUARD_DAMAGE);
        startAttackTimer();
        Serial.print("Guard attacked you for ");
        Serial.print(GUARD_DAMAGE);
        Serial.print("! You have ");
        Serial.print(player->getHealth());
        Serial.println(" health left.");
    }

    void move(int x, int y) {
        int hOffset = (horizontal) ? 1 : 0;
        int vOffset = (vertical) ? 1 : 0;
        int destX = x + hOffset * direction;
        int destY = y + vOffset * direction;

        Entity* e = currentBoard->board[destX][destY];
        if (e == nullptr) {
        currentBoard->board[destX][destY] = this;
        currentBoard->board[x][y] = nullptr;

        Entity* nextE = currentBoard->board[destX + hOffset * direction][destY + vOffset * direction];
        if (nextE != nullptr && nextE->getType() == "wall") direction *= -1;
        } else if (e->getType() == "player" && timeToAttack()) {
            if (player->hasSword()) currentBoard->board[x][y] = nullptr;
            else attack();
        }

        startMoveTimer();
    }
    };
*/