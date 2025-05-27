#include "Wall.h"

Wall Wall::Wall(bool isBreakable) : _isBreakable(isBreakable) {}

Wall Wall::Wall() : Wall(false) {}

Entity::MoveResult Wall::receiveMove(Entity* e) override {
    return _isBreakable ? {Entity::MoveResultCode::NEEDS_PICKAXE, Entity::MoveResultItem::NO_ITEM} : Entity::receiveMove(e);
}