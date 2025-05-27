/*
 * Abstract base class representing a non-floor element of the board
 */
#include <optional>

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
        NO_MOVE,
        ITEM,
        NEEDS_KEY,
        NEEDS_PICKAXE,
        NEEDS_SWORD
    };

    enum class MoveResultItem {
        NO_ITEM,        // only used when move code is not ITEM
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
        Entity::MoveResultItem emrItem;
    };
};