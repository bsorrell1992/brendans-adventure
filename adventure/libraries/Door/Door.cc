#include "Door.h"

Entity::MoveResult Door::receiveMove(Entity* e) override {
    return {Entity::MoveResultCode::NEEDS_KEY, Entity::MoveResultItem::NO_ITEM};
}