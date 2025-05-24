#include "Item.h"

Item::Item(Entity::MoveResultItem itemCode) : _itemCode(itemCode) {}

Entity::MoveResult receiveMove(Entity* e) override {
    return {Entity::MoveResultCode::ITEM, _itemCode};
}