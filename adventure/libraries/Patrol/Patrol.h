/*
 * Wanders back and forth through corridor
 * Movement is parallel to corridor
 */
#include "Entity.h"

class Patrol : public Entity {

};

/*
    class Patrol : public MovingEntity {
        private:
        bool horizontal;
        bool vertical;
        int direction;

        public:
        Patrol(bool horizontal, bool vertical, int direction) : MovingEntity("patrol", PATROL_DELAY) {
            this->horizontal = horizontal;
            this->vertical = vertical;
            this->direction = direction;

            startMoveTimer();
            startAttackTimer();
        }

        void attack() {
            player->takeDamage(PATROL_DAMAGE);
            startAttackTimer();
            Serial.print("Patrol attacked you for ");
            Serial.print(PATROL_DAMAGE);
            Serial.print("! You have ");
            Serial.print(player->getHealth());
            Serial.println(" health left.");
        }

        void move(int x, int y) {
            int destX = x + ((horizontal) ? 1 : 0) * direction;
            int destY = y + ((vertical) ? 1 : 0) * direction;

            Entity* e = currentBoard->board[destX][destY];
            if (e == nullptr) {
            currentBoard->board[destX][destY] = this;
            currentBoard->board[x][y] = nullptr;

            if ((horizontal && (destX == 1 || destX == ARRAY_LENGTH - 2)) || (vertical && (destY == 1 || destY == ARRAY_LENGTH - 2))) direction *= -1;
            } else if (e->getType() == "player" && timeToAttack()) attack();

            startMoveTimer();
        }
    };
*/