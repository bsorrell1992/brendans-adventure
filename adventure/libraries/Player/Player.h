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

    int getPoints() const;

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
    bool _speedbootsOn = false;
    int _armor = 1;
    int _numHealthPotions = 0;

    Timer _moveTimer;
};