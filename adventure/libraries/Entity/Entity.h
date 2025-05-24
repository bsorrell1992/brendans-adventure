/*
 * Abstract base class representing a non-floor element of the board
 */

#include "Board.h"

class Entity {
public:
    Entity() = delete;
    virtual ~Entity() {};
    virtual void move(Board* board) {};
    virtual Entity::MoveResult receiveMove(Entity* e);

protected:
    // Enums representing result of move request
    enum class MoveResultCode {
        SUCCESS,
        NO_MOVE,
        ITEM,
        NEEDS_KEY,
        NEEDS_PICKAXE,
        NEEDS_SWORD
    };

    enum MoveResultItem {
        ARMOR,
        HEALTH_POTION,
        KEY,
        PICKAXE,
        SPEEDBOOTS,
        SWORD,
        TREASURE
    };

    typedef struct MoveResult {
        Entity::MoveResultCode emrCode;
        int data;
    };
};