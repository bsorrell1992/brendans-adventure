#include "Board.h"
#include "Constants.h"
#include "Entity.h"
#include "Point.h"
#include "Timer.h"

class Player : public Entity {
public:
    Player();
    ~Player() {}
    void move(Board* board) override;
    void receiveAttack(int damage);

    bool isAlive() const;
    void revive();

    void drinkHealthPotion();

    void useSpeedboots();
    void removeSpeedboots();

private:
    void collectItem(Entity::MoveResultItem itemCode);

    bool _alive = true;
    int _health = PLAYER_INITIAL_HEALTH;
    int _points = 0;
    Point _position = {SPAWN_X, SPAWN_Y};
    bool _treasure = false;
    bool _key = false;
    bool _sword = false;
    bool _pickaxe = false;
    bool _speedboots = false;
    int _armor = 1;
    int _numHealthPotions = 0;

    Timer _moveTimer;
};

/*
    class Player : public MovingEntity {
    private:

    public:
        int getPoints() { return points; }
        int addPoints(int points) { this->points += points; }

        void drinkHealthPotion() {
            health += HEALTH_POTION_HEALING;
            --numHealthPotions;
        }

        void useSpeedBoots() {
            moveTimer.setDelay(PLAYER_DELAY / 2);
            Serial.println("You have put on your speed boots. You are now moving twice as fast!");
        }

        void removeSpeedBoots() {
            moveTimer.setDelay(PLAYER_DELAY);
            Serial.println("You have removed your speed boots. You are now moving at your original speed.");
        }

        void printKill(String killType) {
            Serial.print("You killed");
            Serial.print(killType);
            Serial.print(". Your total is now ");
            Serial.println(points);
        }

        void move(int dx, int dy);
    };
*/