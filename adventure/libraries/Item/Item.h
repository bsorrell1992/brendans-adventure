#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity {
public:
    Item(Entity::MoveResultItem itemCode);
    ~Item() {};

    Entity::MoveResult receiveMove(Entity* e) override;

private:
    Entity::MoveResultItem _itemCode;
};

#endif