#include "Constants.h"
#include "Entity.h"

class Player : public Entity {
public:
    void receiveAttack(int damage);

private:
    bool _alive = true;
    int _health = PLAYER_INITIAL_HEALTH;
    int _points = 0;
    int _x = SPAWN_X;
    int _y = SPAWN_Y;
    bool _treasure = false;
    bool _key = false;
    bool _sword = false;
    bool _pickaxe = false;
    bool _speedboots = false;
    int _armor = 1;
    int _numHealthPotions = 0;
};

/*
    class Player : public MovingEntity {
    private:
    bool alive = true;
    int health = PLAYER_INITIAL_HEALTH;
    int points = 0;
    int x = SPAWN_X;
    int y = SPAWN_Y;
    bool treasure = false;
    bool key = false;
    bool sword = false;
    bool pickaxe = false;
    bool speedBoots = false;
    int armor = 1;
    int numHealthPotions = 0;

    public:
    Player() : MovingEntity("player", PLAYER_DELAY) {
        startMoveTimer();
        startAttackTimer();
    }

    bool isAlive() { return alive; }
    void revive() {
        alive = true;
        health = PLAYER_INITIAL_HEALTH;
    }

    int getPoints() { return points; }
    int addPoints(int points) { this->points += points; }

    byte getX() { return x; }
    byte getY() { return y; }
    void setX(byte x) { this->x = x; }
    void setY(byte y) { this->y = y; }

    bool hasTreasure() { return treasure; }
    bool hasKey() { return key; }
    bool hasSword() { return sword; }
    bool hasPickaxe() { return pickaxe; }
    bool hasSpeedBoots() { return speedBoots; }
    bool hasHealthPotion() { return numHealthPotions > 0; }
    void grabTreasure() { treasure = true; }
    void grabKey() { key = true; }
    void grabSword() { sword = true; }
    void grabPickaxe() { pickaxe = true; }
    void grabSpeedBoots() { speedBoots = true; }
    void grabHealthPotion() { ++numHealthPotions; }
    void grabArmor() { ++armor; }

    int getHealth() { return health; }
    void takeDamage(int damage) {
        health -= damage / armor;
        if (health <= 0) {
        if (numHealthPotions > 0) {
            drinkHealthPotion();
        } else {
            alive = false;
        }
        }
    }

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