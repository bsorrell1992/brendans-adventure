#include "Entity.h"

virtual Entity::MoveResult Entity::receiveMove(Entity* mover) {
    return {Entity::MoveResultCode::NO_MOVE, Entity::MoveResultItem::NO_ITEM};
}