/*
 * Represents the entrance to the treasure room
 * Can only be opened with the key
 */
#ifndef DOOR_H
#define DOOR_H

#include "Entity.h"

class Door : public Entity {
public:
    Door() {};
    ~Door() {};
    Entity::MoveResult receiveMove(Entity* e) override;
};

#endif