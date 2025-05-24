/*
 * Represents the entrance to the treasure room
 * Can only be opened with the key
 */
#include "Entity.h"

class Door : public Entity {
public:
    Door() {};
    ~Door() {};
    Entity::MoveResult receiveMove(Entity* e) override;
};